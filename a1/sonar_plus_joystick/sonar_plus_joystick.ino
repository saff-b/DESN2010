/*
  Adding sonar to the joystick
  distance calculation modified from:
  https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
  smoothing:
  https://www.youtube.com/watch?v=_yB-DDOFrhI
*/

// joystick axes
int xAxis = A0;
int yAxis = A1;
// int button = 5;

// buzzer: used for sound
int buzzer = 7;

// sonar
int trigPin = 8;
int echoPin = 9;

// global variables
long duration; // for sonar
int distance; // for sonar
int prevxValue; // for joystick
int prevyValue; // for joystick
int smoothingFactor = 30; // for sonar reads
int happy = 10000; // initial happiness val
int chirpDelay = 20; // default chirp delay

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  /* SONAR SET UP */
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  /* JOYSTICK SET UP */
  prevxValue = analogRead(xAxis);
  prevyValue = analogRead(yAxis);
}

void loop() {
  /* STEP 1: get distance from sensor! */
  // handle dropout and outlier data with this
  int tempSmoothingFactor = smoothingFactor;
  // reset distance, save previous value in case of major loss
  int tempDistance = distance;
  distance = 0;
  for (int i = 0; i < smoothingFactor; i++) {
    int tempDistance;
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    tempDistance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    if (tempDistance < 1000) {
      distance = distance + tempDistance;
    }
    else {
      tempSmoothingFactor--;
    }
  }
  distance = distance / tempSmoothingFactor;
  // a 0 value is invalid so we reset to the prior known value
  if (distance = 0) {
    distance = tempDistance;
  }

  if (distance > 30) {
    chirpDelay = 15;
  }
  else {
    chirpDelay = map (distance, 0, 30, 5, 15);
  }

  // read the values on the joystick
  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);
  
  //get the difference between this read and the previous read
  int xDiff = getDiff(xValue, prevxValue);
  int yDiff = getDiff(yValue, prevyValue);

  if (happy < 10000 && (xDiff > 3 || yDiff > 3)) {
    happy+=10;
  }

  int purrPitch;
  if (happy > 0) {
    int diff;
    if (xDiff > 3 && yDiff > 3) {
      diff = (xDiff + yDiff);
    } else {
      diff = max (xDiff, yDiff);
    }
    // the more you wiggle the stick the higher the pitch goes
    purrPitch = map (diff, 0, 1024, 0, 600);
    // the longer that the joystick has been rubbed for then it is the higher the pitch
    purrPitch = purrPitch + (happy / 100);
    // decrease happiness value slightly less than it was increased
    happy-=5;
  }

  prevxValue = xValue;
  prevyValue = yValue;
  if (happy > 1) {
  // pin, pitch, duration
    Serial.println(purrPitch);
    tone(buzzer, purrPitch, chirpDelay);
    delay(chirpDelay);        // delay in between reads for stability
  // make sure the tone stops before the next one
    noTone(buzzer);
  }
}

int getDiff(int a,int b) {
  return abs(a - b);
}