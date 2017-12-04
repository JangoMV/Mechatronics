const int pingPin = 7;
boolean temp_bool = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, inches;
  pinMode(pingPin,OUTPUT);
  digitalWrite(pingPin,LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,High);
  delayMicroseconds(5);
  digitalWrite(pingPin,LOW);

  pinMode(pingPin,INPUT);
  duration = pulseIn(pingPin,HIGH);

  inches = duration / 74 / 2;

  if (inches > 5)
  {
    temp_bool = 0;
    Serial.println("No Obstructions Detected");
  }
  else
  {
    temp_bool = 1;
    Serial.println("Obstruction Detected");
  }
}
