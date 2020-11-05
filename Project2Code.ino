//Variable declarations
int potenVal = 0;
int commandNum = 6;
int keyPadCode = 999;
int buttonVal = 0;
bool correctInput = true;
int inputCount = 0;
void setup() {
  // put your setup code here, to run once:
  //Get seed for random number generator
  Serial.begin(9600);
  randomSeed(analogRead(0));

  //Analog Input Pins
  pinMode(A0, INPUT); //Potentiometer input
  //Digital Input Pins
  pinMode(1, INPUT_PULLUP); //Push It Input
  pinMode(11, INPUT_PULLUP); //Keypad 1
  pinMode(6, INPUT_PULLUP); //Keypad 2
  pinMode(5, INPUT_PULLUP); //Keypad 3
  pinMode(4, INPUT_PULLUP); //Keypad 4

}

void loop() {
  // put your main code here, to run repeatedly:  

}
//Generate initial game audio 
void playIntro(){
  //Play New Game Sound Through Speaker
    //TO DO
}
//Randomly generate which command is to be completed by user
//Needs Tested
void commandGenerate(){
  commandNum = random(3);
  
  //Call correct start function based on random number
  if(commandNum == 0){
    keyPadStart();
  }
  if(commandNum == 1){
    twistStart();
  }
  if(commandNum == 2){
    bopStart();
  }
}
//Initialize the keypad and code
void keyPadStart(){
  //Get random value for keypad code 
  keyPadCode = random(100, 999);

  //Play type it audio through speaker
    //TO DO

  //Diplay code on LCD screen
    //TO DO
}
//Get initial value of potentiometer and play audio
void twistStart(){
  //Read value of potentiometer
  potenVal = analogRead(A0);

  //Play twist audio through speaker
    //TO DO
  
}
void bopStart(){
  //Play bop it audio through speaker
    //TO DO
  
}
//Check for user input
bool checkInput(int command){
  //Keypad check
  if(command == 1){
    int userCode = keyPadRead();
    if(userCode == keyPadCode){
       return true;
    }
    else{
      return false;
    }
  }
  //Twist check
  if(command == 2) {
    //Get current value from potentiometer
    int userPot = analogRead(A0);
    if(userPot != potenVal){
      return true;
    }
    else{
      return false;
    }
  }
  //Pushbutton check
  if(command == 3){
    //Read pushbutton state
    int buttonState = digitalRead(1);
    if(!buttonState){
      return true;
    }
    else{
      return false;
    }
  }
}
//Keypad read 
int keyPadRead(){
  int inputs = 0;
  int code[3];
  while(inputs < 4){
    int key1 = digitalRead(11);
    int key2 = digitalRead(6);
    int key3 = digitalRead(5);
    int key4 = digitalRead(4);

    //Check when released 
    if(!key1){
      code[inputs] = 1;
      inputs++; 
    }
    if(!key2){
      code[inputs] = 2;
      inputs++;
    }
    if(!key3){
      code[inputs] = 3;
      inputs++;
    }
    if(!key4){
      code[inputs] = 4;
      inputs++;
    }
  }
  //Convert array into integer
  int codeInt = code[0];
  for(int i = 1; i < 4; i++){
    codeInt = codeInt * 10 + code[i]; 
  }
  return codeInt;
}
