#define NOP __asm__ __volatile__ ("nop\n\t")
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  //DDRD = B00011000;
}
void loop() {
  if((Serial.available() > 0) && (Serial.read() == 't')){
  Serial.println("trigger");
  while(!Serial.available() > 0){
    // 20 uS to toggle pins
    digitalWrite(4, HIGH);
    digitalWrite(4, LOW);
    // due pin on/off:
    //g_APinDescription[4].pPort -> PIO_SODR = g_APinDescription[4].ulPin;
    //g_APinDescription[4].pPort -> PIO_CODR = g_APinDescription[4].ulPin;    // similate rpi delay
    // digitalRead(3);
    // resolution of 4 uS
    delay(20);
    
    digitalWrite(3, HIGH);
    digitalWrite(3, LOW);
    delay(20);
    // due pin on/off:
    //g_APinDescription[3].pPort -> PIO_SODR = g_APinDescription[3].ulPin;
    //g_APinDescription[3].pPort -> PIO_CODR = g_APinDescription[3].ulPin;
    }
  }
  //delay(125);
}
