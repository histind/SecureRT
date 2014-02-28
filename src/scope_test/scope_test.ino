void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(3, HIGH);
  delay(250);
  digitalWrite(3, LOW);
  delay(125);
  if((Serial.available() > 0) && (Serial.read() == 's')){
  Serial.println("trigger");
  digitalWrite(4, HIGH);
  //delay(5);
  digitalWrite(4, LOW);
  }
  delay(125);
}
