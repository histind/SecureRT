#define NOP __asm__ __volatile__ ("nop\n\t")
#define INPUT_PIN 3
#define OUTPUT_PIN 4
// due equivalent port manipulation
//g_APinDescription[4].pPort -> PIO_SODR = g_APinDescription[4].ulPin;
//g_APinDescription[4].pPort -> PIO_CODR = g_APinDescription[4].ulPin;
// flag for restart and number of collected samples
int restart, data;
// results string
char result[30];
// user input
char CMD;

void setup() {
  // runs once
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
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
    //digitalWrite(3, HIGH);
    //digitalWrite(3, LOW);
    //delay(20);
    if(Serial.available() > 0){ 
        Serial.println("returning to menu...");
        restart = 1;
        return;
      }
    } 
  }

// todo: add parameterized version?
void test_mode(){
   while(1){
     digitalWrite(4, HIGH);
     //digitalWrite(4, LOW);
     while(digitalRead(3) != HIGH){
       Serial.println("waiting for response on pin 3...");
       if(Serial.available() > 0){
         digitalWrite(4, LOW);
         restart = 1;
         return;
       }
     }
     // digitalRead is HIGH
     digitalWrite(4, LOW);
     data++;
     print_result();
     // wait for pin 3 to release signal
     while(digitalRead(3) != LOW){
       //wait
     }
   }
}

void help(){
  Serial.println("press 'd' for debug mode");
  Serial.println("      't' for test mode");
  Serial.println("      'r' for results");
  restart = 0;
  return;
  
}

void print_result(){
   sprintf (result, "number of samples is %d", data);
   Serial.println(result);
   restart = 0;
   return;
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

