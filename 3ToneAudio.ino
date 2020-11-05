//Author: Jason Matuszak
//Arduino uno with atmega328p microcontroller
void setup() {
 //Not used
}

void loop() {
  //Play a note on pin 6 for 500 ms
  tone(6, 440, 500);
  //Delay 3 seconds
  delay(3000);

  //Play a note on digital pin 6 for 500 ms
  tone(6, 494, 500);
  //Wait 3 seconds
  delay(3000);
  
  //Play a note on digital pin 6 for 500 ms
  tone(6, 523, 500);
  //Wait 3 seconds
  delay(3000);
  
  //Turn off tone function for digital pin 6
  noTone(6);
}
