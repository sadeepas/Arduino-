# 🤖 Arduino Smart Hand-Following Robot

A C++ based Arduino project for an autonomous robot that follows a user's hand using IR sensors and maintains a safe distance using an Ultrasonic sensor. The robot features a servo-controlled "head" and intelligent motor control.

## 📋 Project Description

This robot is designed to interact with humans. It waits for an object (like a hand) to come within range.
1.  **Detection:** Using two IR sensors (Left & Right), it detects which direction the hand is moving.
2.  **Tracking:** It turns the motors to face the hand.
3.  **Distance Control:** Using an HC-SR04 Ultrasonic sensor, it moves forward to follow the hand but stops and reverses if the hand gets too close (< 10cm) to prevent collisions.

## 🚀 Features

*   **Hand Tracking:** Automatically steers Left or Right based on IR sensor input.
*   **Distance Keeping:** Maintains a specific distance from the hand (10cm - 30cm).
*   **Obstacle Safety:** Auto-stop and reverse functionality if an object is too close.
*   **Startup Scan:** Servo "Head" looks left and right upon initialization.
*   **Modular Code:** Written using C++ Object Oriented Programming (Class `Robot`) for cleaner logic.

## 🛠️ Hardware Requirements

*   **Microcontroller:** Arduino Uno / Nano.
*   **Motor Driver:** L298N H-Bridge Module.
*   **Motors:** 2x DC Gear Motors (plus wheels and chassis).
*   **Sensors:**
    *   1x HC-SR04 Ultrasonic Sensor.
    *   2x IR Proximity Sensors (Adjustable).
*   **Servo:** 1x SG90 Micro Servo (for the Ultrasonic sensor).
*   **Power:** 2x 18650 Li-ion batteries (7.4V) or 9V battery case.

## 🔌 Circuit Pinout

Connect your components to the Arduino as follows:

| Component | Pin Name | Arduino Pin |
| :--- | :--- | :--- |
| **Ultrasonic Sensor** | Trig | D2 |
| **Ultrasonic Sensor** | Echo | D3 |
| **Left Motor** | Input 1 / Input 2 | D4 / D5 |
| **Right Motor** | Input 3 / Input 4 | D6 / D7 |
| **Servo Motor** | Signal (Orange/Yellow) | D9 |
| **Left IR Sensor** | Out | A0 |
| **Right IR Sensor** | Out | A1 |

*> **Note:** Pins D5 and D6 must be PWM enabled pins if you plan to control speed in the future, though this code uses simple digital High/Low.*

## ⚙️ Installation & Setup

1.  **Assembly:** Mount the motors and L298N driver to your chassis. Mount the Servo at the front and attach the Ultrasonic sensor to the servo horn (so it looks like a face). Mount the IR sensors on the left and right front bumper.
2.  **Wiring:** Follow the pinout table above.
3.  **Code Upload:**
    *   Open `robot.ino` in the Arduino IDE.
    *   Install the `Servo` library if not installed (Sketch -> Include Library -> Servo).
    *   Select your Board and Port, then click **Upload**.
4.  **Calibration:**
    *   Power on the robot.
    *   Use a screwdriver to adjust the potentiometer on the back of the **IR Sensors**.
    *   Adjust until the light on the IR sensor turns ON only when your hand is about 10-15cm away.

## 🐛 Troubleshooting

*   **Robot spins in circles:** Swap the wires on *one* of the motors (e.g., swap the wires connected to Output A on the L298N).
*   **Robot goes backward instead of forward:** Swap the wires on *both* motors.
*   **Robot doesn't move:** Check your battery voltage. The L298N driver drops about 2V; a weak battery won't drive the motors.
*   **IR Sensor Logic:** The code assumes your IR sensors send a `LOW` signal when an object is detected. If your robot acts inverted, look for this line in the code: `bool leftDetected = (leftIRValue == LOW);` and change `LOW` to `HIGH`.

## 📄 License

This project is open-source. Feel free to modify and use it for educational purposes.
