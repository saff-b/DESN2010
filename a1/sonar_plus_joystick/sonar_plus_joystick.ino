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
int button = 3;

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
int charge = 0; // initial happiness val
int streak = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  /* SONAR SET UP */
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  /* JOYSTICK SET UP */
  prevxValue = analogRead(xAxis);
  prevyValue = analogRead(yAxis);
  /* JOYSTICK BUTTON INTERRUPT : currently disabled because the interrupt triggers randomly :( */
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), decharge, RISING);
}

void loop() {
  /* STEP 1: get distance from sensor! */
  // reset distance
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
    distance = distance + duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  }
  distance = distance / smoothingFactor;

  /* STEP 2: Convert the distance to the length of the tone that is to be played */
  int toneLength; // delcare local variable for how long the tone sounds for
  if (distance > 30 || distance < 0) {
    toneLength = 10; // default chirp delay
  }
  else {
    toneLength = map (distance, 0, 30, 300, 10); // otherwise map the distance value to the delay
  }

  /* STEP 3: get how much the joystick has moved since the last read */
  // read the values on the joystick
  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);
  
  //get the difference between this read and the previous read
  int xDiff = getDiff(xValue, prevxValue);
  int yDiff = getDiff(yValue, prevyValue);

  // add to the charge if the joystick has moved
  if (charge < 1000 && (xDiff > 3 || yDiff > 3)) {
    // the increase is exponential
    charge = (charge + 10) + streak * 2;
    streak++;
  } else {
    streak = 0;
  }

  // calculate the pitch based on both the charge and how much the joystick moved
  int pitch;
  if (charge > 0) {
    int diff;
    if (xDiff > 3 && yDiff > 3) {
      diff = (xDiff + yDiff) / 2;
    } else {
      diff = max (xDiff, yDiff);
    }
    // the more you wiggle the stick the higher the pitch goes,
    // and the longer that the joystick has been rubbed for then it is the higher the pitch
    pitch = map (diff, 0, 512, charge, charge + 500);
    // decrease happiness value slightly less than it was increased
    charge-=5;
  }

  /* STEP 4: Play the tone using the parameters! */
  if (charge > 1) {
  // tone: pin, pitch, duration
    tone(buzzer, pitch, toneLength);
  }

  // save the x and y values for comparison next loop
  prevxValue = xValue;
  prevyValue = yValue;

  // ensure charge is within bounds
  if (charge < 0) {
    charge = 0;
  }
}

int getDiff(int a,int b) {
  return abs(a - b);
}

void decharge() {
  charge = -100;
} 