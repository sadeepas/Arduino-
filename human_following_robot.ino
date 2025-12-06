#include <Servo.h>

// --- ROBOT CLASS DEFINITION ---
class Robot {

private:
  // Pin Definitions
  const int ultrasonicTriggerPin = 2;
  const int ultrasonicEchoPin = 3;
  
  // Motor Pins (L298N Driver logic)
  const int leftMotor1 = 4;
  const int leftMotor2 = 5;
  const int rightMotor1 = 6;
  const int rightMotor2 = 7;
  
  // Servo & IR Pins
  const int servoPin = 9;
  const int leftIRPin = A0;
  const int rightIRPin = A1;

  Servo headServo; // The servo for the robot's head

public:
  // Constructor
  Robot() {
    // Note: Pin configuration is best done in a begin() method or setup, 
    // but we will do it here to keep your structure.
  }

  void init() {
    // Initialize Pins
    pinMode(ultrasonicTriggerPin, OUTPUT);
    pinMode(ultrasonicEchoPin, INPUT);
    
    pinMode(leftMotor1, OUTPUT);
    pinMode(leftMotor2, OUTPUT);
    pinMode(rightMotor1, OUTPUT);
    pinMode(rightMotor2, OUTPUT);
    
    pinMode(leftIRPin, INPUT);
    pinMode(rightIRPin, INPUT);
    
    // Attach Head Servo
    headServo.attach(servoPin);
    headServo.write(90); // Look forward initially
  }

  // --- MOVEMENT FUNCTIONS ---

  void moveForward() {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }

  void moveBackward() {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
  }

  void stop() {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
  }

  void turnLeft() {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }

  void turnRight() {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
  }

  // --- SENSOR FUNCTIONS ---

  int measureDistance() {
    digitalWrite(ultrasonicTriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonicTriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonicTriggerPin, LOW);

    long duration = pulseIn(ultrasonicEchoPin, HIGH);
    
    // Calculate distance in cm
    int distance = duration / 58; 

    // Filter out 0 or huge noise readings
    if (distance == 0 || distance > 400) {
      return 400; 
    }
    return distance;
  }

  // --- LOGIC FUNCTIONS ---

  void rotateFace() {
    // Scan left
    for (int i = 90; i < 140; i++) {
      headServo.write(i);
      delay(10);
    }
    // Scan right
    for (int i = 140; i > 40; i--) {
      headServo.write(i);
      delay(10);
    }
    // Return to center
    headServo.write(90); 
    delay(200);
  }

  void trackHand() {
    int leftIRValue = digitalRead(leftIRPin);
    int rightIRValue = digitalRead(rightIRPin);
    
    // IR Sensors are usually active LOW (LOW means object detected)
    // Adjust ! (NOT) logic depending on your specific sensor model
    bool leftDetected = (leftIRValue == LOW);
    bool rightDetected = (rightIRValue == LOW);

    if (leftDetected && !rightDetected) {
      turnLeft();
      delay(100); 
      stop();
    } else if (!leftDetected && rightDetected) {
      turnRight();
      delay(100);
      stop();
    } else if (leftDetected && rightDetected) {
      moveForward();
    } else {
      stop(); // No hand detected, stay still
    }
  }

  void followHandLogic() {
    int distance = measureDistance();

    // Safety Stop / Obstacle Avoidance
    if (distance < 10 && distance > 0) {
      stop();
      delay(500);
      moveBackward(); // Too close! Back up a little
      delay(300);
      stop();
    } else if (distance < 30) {
      // If object is within range (10cm - 30cm), try to follow it
      trackHand();
    } else {
      // Object too far, just stop
      stop();
    }
  }
};

// --- GLOBAL VARIABLES ---
Robot robot;

// --- ARDUINO SETUP ---
void setup() {
  Serial.begin(9600); // For debugging
  robot.init();       // Initialize pins and servo
  
  // Optional: A startup "Wiggle" to show robot is active
  robot.rotateFace(); 
}

// --- ARDUINO LOOP ---
void loop() {
  // Continuously run the hand following logic
  robot.followHandLogic();
  
  // Small delay for stability
  delay(50);
}
