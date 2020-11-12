#include <LiquidCrystal.h> // includes the LiquidCrystal Library
LiquidCrystal lcd(1, 3, 5, 6, 7, 8); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)
void setup() {
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display }
 lcd.print("Score: 69"); // Prints "Hello World" on the LCD
 lcd.setCursor(0,1);    //New Line
 lcd.print("Type: 312"); // Prints "Hello World" on the LCD

 pinMode(2, INPUT_PULLUP); //Start Game Button
 pinMode(13, INPUT_PULLUP); //Push It Button
 pinMode(12, INPUT_PULLUP); //Push Button 1
 pinMode(11, INPUT_PULLUP); //Push Button 2
 pinMode(10, INPUT_PULLUP); //Push Button 3
 pinMode(9, INPUT_PULLUP);  //Push Button 4
}
void loop() {
  //Play a note on pin 8 for 500 ms
  int startBut = digitalRead(2);
  int pushIt = digitalRead(13);
  int but1 = digitalRead(12);
  int but2 = digitalRead(11);
  int but3 = digitalRead(10);
  int but4 = digitalRead(9);
  int pot = analogRead(A0);
  
  if(!startBut){
  tone(4, 440, 1000);
  noTone(4);
  }
  if(!pushIt){
  tone(4, 500, 2000);
  noTone(4);
  }
  if(!but1){
  tone(4, 440, 3000);
  noTone(4);
  }
  if(!but2){
  tone(4, 440, 4000);
  noTone(4);
  }
  if(!but3){
  tone(4, 440, 5000);
  noTone(4);
  }
  if(!but4){
  tone(4, 440, 6000);
  noTone(4);
  }
  if(pot > 900){
    tone(4, 500, 7000);
    noTone(4);
  }


  
}
