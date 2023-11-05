// ultrasonic censor pins
int trigpin = 3;
int echopin = 2;

//start LED pin
const int ledstartpin = 8;
const int ledendpin = 13;

//distance
int distance;


void setup() {
  
//initialize serial communocation
Serial.begin(9600);

pinMode (echopin, INPUT);  // Input
pinMode (trigpin, OUTPUT); // Output

// Set LED pins as output
for (int i = 0; i < 6; i++) {
    pinMode(ledstartpin + i, OUTPUT);
    }

// Max and min distances
  const int maxDistance = 60; // cm
  const int minDistance = 10; // cm


}

void loop() {
  
// Store the duration and distance
  long duration;

 // Send a pulse to the ultrasonic sensor
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

// Measure the duration of the pulse
 duration = pulseIn(echopin, HIGH);

 // Calculate distance in centimeters (cm)
  float speed = 0.0343; 
  float distance = (speed * duration) / 2;

// Turn on/off LEDs based on distance
  if (distance <= 10) {
    
// If the distance is less than or equal to 10cm, turn off all LEDs
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledstartpin + i, LOW);
    }

    
  } else if (distance >= 60) {
  // If the distance is more than or equal to 60cm, turn on all LEDs
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledstartpin + i, HIGH);
    }
    
  
      } else {
    // If the distance is between 10cm and 60cm, light up LEDs gradually from left to right
    int numLEDsToLightUp = map(distance, 10, 60, 1, 6);
    
    for (int i = ledstartpin; i < ledstartpin + numLEDsToLightUp; i++) {
      digitalWrite(i, HIGH);
    }
    
    for (int i = ledstartpin + numLEDsToLightUp; i < ledstartpin + 6; i++) {
      digitalWrite(i, LOW);
    }
    
    delay(100);   // Delay for smooth transition of LEDs
  }

}
