int timer = 50; // timer

void setup() {
  
  // set pins 5 - 13 as output
  
  for (int thisPin = 5; thisPin < 14; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void loop() {
  // lightup LEDs from pin 5 to pin 9 and from pin 13 to pin 9
  
  for (int thisPin = 5; thisPin < 10; thisPin++) {
    digitalWrite(thisPin, HIGH);
    digitalWrite(13 - (thisPin - 5), HIGH);
    
    delay(timer); // dilay
    
    digitalWrite(thisPin, LOW);
    digitalWrite(13 - (thisPin - 5), LOW);
  }

  // light down LEDs from pin 9 to pin 5 and from pin 9 to pin 13
  
  for (int thisPin = 9; thisPin >= 5; thisPin--) {
    digitalWrite(thisPin, HIGH);
    digitalWrite(13 - (thisPin - 5), HIGH);
    
    delay(timer); // dillay
    
    digitalWrite(thisPin, LOW);
    digitalWrite(13 - (thisPin - 5), LOW);
  }


  
}
