// getting a reading from the ambient light sensor
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorReading = analogRead(A0);
  Serial.println(sensorReading);
}
