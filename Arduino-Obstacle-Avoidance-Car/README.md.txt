# Arduino Obstacle Avoidance Car

## Overview
This is an **Arduino-based obstacle avoidance car** that navigates autonomously using an **ultrasonic sensor**, **servo motor**, and **L298N motor driver**. The car moves forward, stops when an obstacle is detected within 10 cm, scans its surroundings, and turns toward the direction with more free space.

Perfect for **beginners** learning about sensors, motors, and robotics.

---

## Features
- Forward movement at safe speed for precise braking  
- Stops immediately when obstacles are detected ≤10 cm  
- Servo scans **left and right** for free space measurement  
- Spin-turns toward the side with more free space  
- Fully autonomous navigation in indoor environments  

---

## Components
- Arduino Uno (or compatible board)  
- HC-SR04 Ultrasonic Sensor  
- L298N Motor Driver Module  
- Servo Motor (for scanning)  
- DC Motors with wheels  
- Battery pack (5V–12V depending on motors)  
- Jumper wires and chassis  

---

## Wiring / Connections

| Component | Pin |
|-----------|-----|
| HC-SR04 TRIG | 9 |
| HC-SR04 ECHO | 10 |
| L298N ENA (Right Motor PWM) | 5 |
| L298N ENB (Left Motor PWM) | 3 |
| L298N IN1 (Right Motor) | 7 |
| L298N IN2 (Right Motor) | 6 |
| L298N IN3 (Left Motor) | 4 |
| L298N IN4 (Left Motor) | 2 |
| Servo Motor | 11 |

---

## How It Works
1. The car moves forward at a safe speed.  
2. Ultrasonic sensor continuously measures distance to obstacles.  
3. If an obstacle is detected ≤10 cm:  
   - The car stops immediately  
   - Servo rotates to scan **right and left**  
   - Car spins toward the side with more space  
4. The cycle repeats, allowing fully autonomous navigation.  

---

## Installation
1. Open the Arduino IDE.  
2. Copy the contents of `ObstacleAvoidance.ino` into a new sketch.  
3. Connect the Arduino to your PC and select the correct board and port.  
4. Upload the sketch.  

---

## Optional Improvements
- Reverse slightly before turning for tight spaces  
- Add Bluetooth for manual override  
- LED indicators for turn direction  
- Integrate IR sensors for better obstacle detection  

---

## License
This project is open-source under the **MIT License**.  

---

## Author
LKSHAY TYAGI – https://github.com/lkshaytyagi192
