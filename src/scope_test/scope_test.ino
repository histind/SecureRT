void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  //DDRD = B00011000;
}
void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(3, HIGH);
  //delay(250);
  //digitalWrite(3, LOW);
  //delay(125);
  if((Serial.available() > 0) && (Serial.read() == 't')){
  Serial.println("trigger");
  while(!Serial.available() > 0){
    // 20 uS to toggle pins
    digitalWrite(4, HIGH);
    digitalWrite(4, LOW);
    //PORTD = B00010000;
    //PORTD = B00000000;
    // similate rpi delay
    // digitalRead(3);
    // resolution of 4 uS
    delay(20);
    digitalWrite(3, HIGH);
    digitalWrite(3, LOW);
    //PORTD = B00001000;
    //PORTD = B00000000;
    }
  }
  //delay(125);
}
