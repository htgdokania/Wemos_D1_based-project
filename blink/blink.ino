void setup() {
  // put your setup code here, to run once:
pinMode(D13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(D13,1);
delay(1000);
digitalWrite(D13,0);
delay(1000);

}
