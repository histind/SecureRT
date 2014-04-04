#define DEBUG_MODE 1
#define TEST_MODE 2
void setup() {
  // runs once
  char CMD;
  // flag to restart main menu
  int restart ;
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  restart = 0;
}

void debug_mode(){
  // run repeatedly:
  Serial.println("debug mode activated");
  while(1){
    digitalWrite(3, HIGH);
    delay(250);
    digitalWrite(3, LOW);
    delay(125);
    if((Serial.available() > 0){ 
      CMD = Serial.read();
      if (CMD == 't')){
        Serial.println("trigger");
        digitalWrite(4, HIGH);
        //delay(5);
        digitalWrite(4, LOW);
      }
      else {
        Serial.println("invalid command, returning to menu");
        restart = 1;
        return;
      }
    } 
    delay(125);
  }
}

void test_mode(){
   while(1){
     digitalWrite(3, HIGH);
     delay(100);
     digitalWrite(3, LOW); 
     if(Serial.available() > 0){
       restart = 1;
       return;
     }
   }
}

void help(){
  Serial.println("press 'd' for debug mode");
  Serial.println("press 't' for test mode");
  while(1){
     if(Serial.available() > 0){
        restart = 1;
        return;
     } 
  }
  
}
void loop() {
  // put your main code here, to run repeatedly
  if(restart == 1){
    Serial.println("Main menu: enter 'h' for help...");
    restart = 0;
  }
  if((Serial.available() > 0)){
    CMD = Serial.read();
    switch(CMD){
      case 'd': 
        debug_mode();
        break;
      case 't':
        test_mode();
        break;
      case 'h':
        help();
        break;
      default:
    }
  }
}
