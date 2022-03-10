/*
  from in-class slides + analogue input example sketch
*/

int sensorPin = A0;    // select the input pin for the potentiometer
int ledR = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int outputValue = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  outputValue = map(sensorValue, 0, 1023, 0, 255);

  //print value to serial
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t outputs = ");
  Serial.println(outputValue);

  // turn the ledPin on
  analogWrite(ledPin, outputValue);
}
