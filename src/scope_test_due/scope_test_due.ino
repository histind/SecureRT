#define NOP __asm__ __volatile__ ("nop\n\t")
//g_APinDescription[4].pPort -> PIO_SODR = g_APinDescription[4].ulPin;
//g_APinDescription[4].pPort -> PIO_CODR = g_APinDescription[4].ulPin;
#define DEBUG_MODE 1
#define TEST_MODE 2
int restart, data;
char result[30];
char CMD;

void setup() {
  // runs once
  // flag to restart main menu
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  restart = 1;
  data = 0;
}

void debug_mode(){
  // run repeatedly:
  Serial.println("debug mode activated");
  while(1){
    digitalWrite(4, HIGH);
    digitalWrite(4, LOW);
    delay(20);
    digitalWrite(3, HIGH);
    digitalWrite(3, LOW);
    delay(20);
    if(Serial.available() > 0){ 
        Serial.println("returning to menu...");
        restart = 1;
        return;
      }
    } 
  }

void test_mode(){
   while(1){
     digitalWrite(3, HIGH);
     digitalWrite(3, LOW);
     while(digitalRead(4) != HIGH){
       Serial.println("waiting for response on pin 4...");
       if(Serial.available() > 0){
         restart = 1;
         return;
       }
     }
     // digitalRead is HIGH
     data++;
     print_result();
     // time to see result
     delay(500); 
   }
}

void help(){
  Serial.println("press 'd' for debug mode");
  Serial.println("      't' for test mode");
  Serial.println("      'r' for results");
  while(1){
     if(Serial.available() > 0){
        restart = 0;
        return;
     } 
  }
  
}

void print_result(){
   sprintf (result, "number of samples is %d", data);
   Serial.println(result);
   restart = 0;
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
      case 'r':
        print_result();
        break;
      default:
        break;
    }
  }
}
