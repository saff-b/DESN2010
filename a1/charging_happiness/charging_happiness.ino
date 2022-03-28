/*
  expanded from AnalogReadSerial example code
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

int xAxis = A0;
int yAxis = A1;
// int button = 5;
int buzzer = 7;

int prevxValue = -100;
int prevyValue = -100;
int happy = 1000;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  prevxValue = analogRead(xAxis);
  prevyValue = analogRead(yAxis);
  // delay before next read
  delay(1);
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

  int purrPitch;
  if (happy > 0) {
    int diff = xDiff + yDiff;
    // the more you wiggle the stick the higher the pitch goes
    purrPitch = map (diff, 0, 1000, 0, 600);
    // the happier it is the higher the pitch is also
    // limited to 100 because otherwise its too screamy
    if (happy > 10000) {
      purrPitch = purrPitch + 100;
    } else {
      purrPitch = purrPitch + (happy / 100);
    }
    happy--;
  }

  prevxValue = xValue;
  prevyValue = yValue;
  if (happy > 1) {
  // pin, pitch, duration
    Serial.println(purrPitch);
    tone(buzzer, purrPitch, 20);
    delay(20);        // delay in between reads for stability
  // make sure the tone stops before the next one
    noTone(buzzer);
  }
  delay (10);
}

int getDiff(int a,int b) {
  return abs(a - b);
}