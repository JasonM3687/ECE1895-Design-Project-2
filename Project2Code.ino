//Arduino Implementation of Bop It
//Zach Kubitz, Jason Matuszak, Joe Tonecha

//----------------------SETUP-------------------------//
#include <LiquidCrystal.h>
//Variable declarations
LiquidCrystal lcd(1, 3, 5, 6, 7, 8); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)
int potenVal = 0; 
int commandNum = 6;
int keyPadCode = 999;
int buttonVal = 0;
bool correctInput = true;
int inputCount = 0;
int score = 0;
int roundTime = 6000;
void setup() {
  // put your setup code here, to run once:
  //Get seed for random number generator
  randomSeed(analogRead(5));
  lcd.begin(16,2);

  //--------Pin Setup--------------------------------//
  pinMode(A0, INPUT); //Twist input
  pinMode(2, INPUT_PULLUP); //Start Game Button
  pinMode(13, INPUT_PULLUP); //Push It Button
  pinMode(12, INPUT_PULLUP); //Push Button 1
  pinMode(11, INPUT_PULLUP); //Push Button 2
  pinMode(10, INPUT_PULLUP); //Push Button 3
  pinMode(9, INPUT_PULLUP);  //Push Button 4
  //------------------------------------------------//

}
//----------------END SETUP-------------------------//


//-----------------------MAIN CODE-------------------//
void loop() {
  // put your main code here, to run repeatedly:
  
  //Check if new game button is pressed
  bool gameState = false;
  int startButton = digitalRead(2);
  int comNum = 9;
  //Button pressed if LOW
  if (startButton == LOW){
    //Swap game state if user presses new game button
    gameState = !gameState;
  }
  //Run while gameState is true
  while(gameState){
    //Play intro tone and display initial values
    playIntro();
    score = 0;
    keyPadCode = 999;
    lcdDisplay(score, keyPadCode);
    delay(2000);
    //DO main game logic WHILE user keeps inputing correct responses 
    do {
      comNum = commandGenerate();
      //Check keypad
      if(comNum == 0){
        correctInput = keyPadCheck();
      }
      //Check twist
      if (comNum == 1){
        delay(2500);
        correctInput = twistCheck(potenVal);
      }
      //Check Button
      if (comNum == 2){
        correctInput = buttonCheck();
      }

      //If user answers correctly, update score and display
      if(correctInput == true){
        score++;
        lcdDisplay(score, keyPadCode);
        delay(500);
      }
      //If user answers incorrectly, end game and display final score 
      if(correctInput == false){
        lcd.clear();
        lcd.print("Final score = ");
        lcd.print(score);
        playTone(5);
        delay(500);
      }
      //Win game at 100 points
      if(score == 100){
        lcd.clear();
        lcd.print("WINNER!");
        playTone(1);
        correctInput = false;
      }
      //Decrase time each round by 50 ms
      if(score % 1 == 0){
        roundTime -= 50;
      }
      
    }while(correctInput);
    gameState = 0;
  }
}
//--------------END MAIN---------------------------//


//--------------FUNCTIONS--------------------------//
//Generate initial game audio 
void playIntro(){
  //Play New Game Sound Through Speaker
  playTone(1);
}
//Randomly generate which command is to be completed by user
int commandGenerate(){
  commandNum = random(3);
  
  //Call correct start function based on random number
  if(commandNum == 0){
    keyPadStart();
    return commandNum;
  }
  if(commandNum == 1){
    twistStart();
    return commandNum;
  }
  if(commandNum == 2){
    bopStart();
    return commandNum;
  }
}
//Initialize the keypad and code
int keyPadStart(){
  //Get random value for keypad code 
  int kCode[3];
  for(int i = 0; i < 3; i++){
    kCode[i] = random(1, 5);
  }
  keyPadCode = kCode[0];
  for(int i = 1; i < 3; i++){
    keyPadCode = keyPadCode * 10 + kCode[i]; 
  }

  //Play type it audio through speaker
  playTone(4);

  //Display to led
  lcdDisplay(score, keyPadCode);
  
}
//Get initial value of potentiometer and play audio
void twistStart(){
  //Read value of potentiometer
  potenVal = analogRead(A0);

  //Play twist audio through speaker
  playTone(2);
  
}
void bopStart(){
  //Play bop it audio through speaker
  playTone(3);
  
}
//Check for user input
bool buttonCheck(){
  unsigned long int start = 0, next = 0, elapsed = 0;
  start = millis();
  while(elapsed < roundTime){
     next = millis();
     elapsed = next - start;
     int buttonState = digitalRead(13);
     if(!buttonState){
      return true;
    }
    else{
      if(elapsed >= roundTime - 2){
        return false;
     }
    }
   }
}
bool twistCheck(int val){
  int newPot = analogRead(A0);
  if(newPot != potenVal){
    potenVal = analogRead(A0);
    return true;
  }
  else{
    return false;
  }
}
bool keyPadCheck(){
   int code2 = keyPadRead();
   lcd.clear();
   lcd.print(code2);
   delay(1000);
   if(code2 == keyPadCode){
    return true;
   }
   else{
    return false;
   }
}
//Keypad read 
int keyPadRead(){
  unsigned long int start = 0, next = 0, elapsed = 0;
  start = millis();
  int inputs = 0;
  int code[3];
  while(inputs < 4 && elapsed < roundTime){
    next = millis();
    elapsed = next - start;
    int key1 = digitalRead(11);
    int key2 = digitalRead(12);
    int key3 = digitalRead(9);
    int key4 = digitalRead(10);

    //Check when released
    if(!key1){
      delay(300);
      code[inputs] = 1;
      inputs++;
       
    }
    if(!key2){
      delay(300);
      code[inputs] = 2;
      inputs++;
    }
    if(!key3){
      delay(300);
      code[inputs] = 3;
      inputs++;
    }
    if(!key4){
      delay(300);
      code[inputs] = 4;
      inputs++;
    }
  }
  if(inputs == 0){
    return 0;
  }
  //Convert array into integer
  int code2 = code[0];
  lcd.clear();
   for(int i = 1; i < 3; i++){
     code2 = code2 * 10 + code[i]; 
   }
  
  return code2;
}
void playTone(int i){
  //Tone one (Start Game Tone)
  if(i == 1){
    for(int k = 0; k < 5; k++){
      tone(4, k*3 + 300, k*3 + 200);
      delay(400);
    }
    noTone(4);
  }
  //Tone 2 (Twist-it tone)
  if(i == 2){
    tone(4, 400, 2500);
    delay(1000);
    noTone(4);
  }
  //Tone 3 (Push-it tone)
  if(i == 3){
    tone(4, 500, 1000);
    delay(1500);
    tone(4, 500, 1000);
    delay(1000);
    noTone(4);
  }
  //Tone 4 (Type-it tone)
  if(i == 4){
    tone(4, 600, 750);
    delay(1000);
    tone(4, 600, 750);
    delay(1000);
    tone(4, 600, 750);
    delay(1000);
    noTone(4);
  }
  //Tone 5 (Game Over Tone)
  if(i == 5){
    tone(4, 500, 1000);
    delay(350);
    tone(4, 400, 1000);
    delay(350);
    tone(4, 300, 1000);
    delay(350);
    noTone(4);
  }
}
//Display score and code to LCD
void lcdDisplay(int s, int c){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Score: ");
  lcd.print(s);
  lcd.setCursor(0,1);
  lcd.print("Code: ");
  lcd.print(c);
}
