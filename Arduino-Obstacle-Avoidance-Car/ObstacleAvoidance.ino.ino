#include <Servo.h>

// Ultrasonic Sensor Pins
#define TRIG_PIN 9
#define ECHO_PIN 10

// Motor Driver Pins (L298N)
#define ENA 5   // Right motor enable (PWM)
#define ENB 3   // Left motor enable (PWM)
#define IN1 7   // Right motor input 1
#define IN2 6   // Right motor input 2
#define IN3 4   // Left motor input 3
#define IN4 2   // Left motor input 4

// Servo Pin
#define SERVO_PIN 11

Servo myServo;

// Variables
long duration;
int distance;

void setup() {
  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Servo setup
  myServo.attach(SERVO_PIN);
  myServo.write(90); // Center position

  Serial.begin(9600);
  stopMotors();
}

void loop() {
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 10 || distance == 0) {
    forward(); // Safe → move forward
  } else {
    // 🚨 Obstacle detected → stop immediately
    stopMotors();
    delay(500);

    // 🧠 Scan surroundings
    myServo.write(30);  // Look right
    delay(500);
    int distRight = getDistance();
    delay(200);

    myServo.write(150); // Look left
    delay(500);
    int distLeft = getDistance();
    delay(200);

    myServo.write(90);  // Back to center
    delay(300);

    Serial.print("Right distance: ");
    Serial.println(distRight);
    Serial.print("Left distance: ");
    Serial.println(distLeft);

    // 🔀 Decide turn direction
    if (distLeft > distRight) {
      Serial.println("Turning LEFT");
      leftTurn();
    } else {
      Serial.println("Turning RIGHT");
      rightTurn();
    }

    stopMotors();
    delay(300);
  }
}

// ---------- Motor Functions ----------

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 140); // Reduced forward speed for safe braking
  analogWrite(ENB, 140);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void rightTurn() {
  stopMotors();
  delay(200);

  // Spin turn
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  // Right motor backward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);   // Left motor forward

  analogWrite(ENA, 200);    // High speed for spin turn
  analogWrite(ENB, 200);

  delay(700);               // Adjust duration for sharpness
  stopMotors();
  delay(200);
}

void leftTurn() {
  stopMotors();
  delay(200);

  // Spin turn
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);   // Right motor forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  // Left motor backward

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  delay(700);
  stopMotors();
  delay(200);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// ---------- Ultrasonic Function ----------

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 20000); // timeout 20ms
  int dist = duration * 0.034 / 2;

  if (dist == 0) return 0; // fail-safe
  return dist;
}
