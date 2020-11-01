//Variable declarations
int potenVal = 0;
int commandNum = 6;
int keyPadCode = 999;
void setup() {
  // put your setup code here, to run once:
  //Get seed for random number generator
  Serial.begin(9600);
  randomSeed(analogRead(0));

  //Analog Input Pins
  pinMode(A0, INPUT); //Potentiometer input

}

void loop() {
  // put your main code here, to run repeatedly:  

}

//Randomly generate which command is to be completed by user
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
