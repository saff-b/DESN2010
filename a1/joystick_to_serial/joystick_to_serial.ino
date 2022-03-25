/*
  expanded from AnalogReadSerial example code
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

int xAxis = A0;
int yAxis = A1;
int button = 3;

int prevxValue = -100;
int prevyValue = -100;
int happy = 500;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  prevxValue = analogRead(xAxis);
  prevyValue = analogRead(yAxis);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the values on the joystick
  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);
  
  int xDiff = getDiff(xValue, prevxValue);
  int yDiff = getDiff(yValue, prevyValue);

  if (happy < 20000 && (xDiff > 3 || yDiff > 3)) {
    happy+=10;
  }

  if (happy > -1000) {
    Serial.print(happy);
    Serial.println("% happy!");
    happy--;
  }

  prevxValue = xValue;
  prevyValue = yValue;

  delay(1);        // delay in between reads for stability
}

int getDiff(int a,int b) {
  return abs(a - b);
}