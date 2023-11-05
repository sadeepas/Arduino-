#include <Servo.h>

class Robot {

private:
  
  int ultrasonicTriggerPin = 2;  // Ultrasonic sensor trigger pin
  int ultrasonicEchoPin = 3;     // Ultrasonic sensor echo pin
  int servoPin = 9;              // Servo motor control pin
  int leftMotor1 = 4;            // Left motor control pin 1
  int leftMotor2 = 5;            // Left motor control pin 2
  int rightMotor1 = 6;           // Right motor control pin 1
  int rightMotor2 = 7;           // Right motor control pin 2
  int leftIRPin = A0;            // Left IR sensor input pin
  int rightIRPin = A1;           // Right IR sensor input pin



// Define the motor pins
int motors[4] = {4, 5, 6, 7};

  Servo servo;
  
public:
  Robot() {
    pinMode(ultrasonicTriggerPin, OUTPUT);
    pinMode(ultrasonicEchoPin, INPUT);
    pinMode(leftMotor1, OUTPUT);
    pinMode(leftMotor2, OUTPUT);
    pinMode(rightMotor1, OUTPUT);
    pinMode(rightMotor2, OUTPUT);
    pinMode(leftIRPin, INPUT);
    pinMode(rightIRPin, INPUT);
    servo.attach(servoPin);
   
    for (int i = 0; i < 4; i++) {
      motor[i].attach(motors[i]);
      motor[i].write(150); // Set initial speed
    }
  }

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

// Create Servo objects for each motor
Servo motor[4];
Servo servoMotor;



//measure distance
  void followHand() {
    int distance = measureDistance();
    if (distance < 10) {
      stop();
      moveTowardsObject();
    } else {
      trackHand();
    }
  }

  int measureDistance() {
    // Generate a 10us pulse on the trig pin to start the measurement
    digitalWrite(ultrasonicTriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonicTriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonicTriggerPin, LOW);

    // Read the echo pin to calculate the duration of the pulse
    long duration = pulseIn(ultrasonicEchoPin, HIGH);

    // Calculate the distance in centimeters
    int distance = duration / 58;  // Speed of sound is 343 meters/second or 29 microseconds per centimeter

    return distance;
  }

  void moveTowardsObject() {
    int distance = measureDistance();

    if (distance < 10) {
      // Object is close, move forward.
      moveForward();
    } else {
      // Object is further away, stop and turn towards the object.
      stop();
      int angleToRotate = 10; // Adjust the turning angle as needed.
      if (distance > 40) {
        angleToRotate = 20; // Increase turning angle if the object is farther away.
      }
      int degreesToTurn = 90 - angleToRotate; // Calculate the degrees to turn.
      if (degreesToTurn > 0) {
        // Turn right.
        servo.write(90 + degreesToTurn);
      } else {
        // Turn left.
        servo.write(90 - abs(degreesToTurn));
      }
    }
  }

  void trackHand() {
    int leftIRValue = digitalRead(leftIRPin);
    int rightIRValue = digitalRead(rightIRPin);

    if (leftIRValue == HIGH && rightIRValue == LOW) {
     
      // Turn left
      turnLeft();
    } else if (leftIRValue == LOW && rightIRValue == HIGH) {
     
      // Turn right
      turnRight();
    } else {
      
      // Move forward
      moveForward();
    }
  }

  void rotateFace() {
    for (int i = 0; i < 90; i++) {
      servo.write(i); // Rotate the face to the left or right
      delay(15);      // Delay for smooth rotation
    }
    servo.write(90); // Return to the stop position
  }
};

Robot robot;

void setup() {
  robot = Robot(); // Initialize the robot

}



void loop() {
  robot.rotateFace(); 
  delay(1000); 

  while (true) {
    robot.followHand();
  }
}
