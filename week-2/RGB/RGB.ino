/*
  from in-class slides + analogue input example sketch
  uses dfrobot circuit layout from project 12
*/

int sensorPinR = A0;    // select the input pin for the potentiometer
int ledR = 10;      // select the pin for the LED
int sR = 0;  // variable to store the value coming from the sensor
int oR = 0;

int sensorPinG = A1;    // select the input pin for the potentiometer
int ledG = 9;      // select the pin for the LED
int sG = 0;  // variable to store the value coming from the sensor
int oG = 0;

int sensorPinB = A2;    // select the input pin for the potentiometer
int ledB = 8;      // select the pin for the LED
int sB = 0;  // variable to store the value coming from the sensor
int oB = 0;
void setup() {
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sR = analogRead(sensorPinR);
  oR = map(sR, 0, 1023, 0, 255);
  sG = analogRead(sensorPinG);
  oG = map(sG, 0, 1023, 0, 255);
  sB = analogRead(sensorPinB);
  oB = map(sB, 0, 1023, 0, 255);
  Serial.print("red : ");
  Serial.print(sR);
  Serial.print(" green: ");
  Serial.print(sG);
  Serial.print(" blue: ");
  Serial.println(sB);
  // turn the ledPin on
  analogWrite(ledR, oR);
  analogWrite(ledG, oG);
  analogWrite(ledB, oB);
}
