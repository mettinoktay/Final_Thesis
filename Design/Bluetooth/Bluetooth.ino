int value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    value = Serial.read();
    Serial.write("PITOT: RECEIVED\n");
    Serial.write("SPEED: RECEIVED\n");
    Serial.write("DIRECTION: RECEIVED\n");
    Serial.flush();
  }
}
