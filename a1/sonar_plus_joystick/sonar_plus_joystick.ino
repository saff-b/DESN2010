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
  /* SONAR SET UP */
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  /* JOYSTICK SET UP */
  prevxValue = analogRead(xAxis);
  prevyValue = analogRead(yAxis);
  /* JOYSTICK BUTTON INTERRUPT */
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
    toneLength = map (distance, 0, 30, 50, 10); // otherwise map the distance value to the delay
  }

  /* STEP 3: get how much the joystick has moved since the last read */
  // read the values on the joystick
  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);
  
  //get the distance between this read and the previous read
  // jsdist = joystick distance
  float jsdist = getDist(xValue, yValue, prevxValue, prevyValue);

  // add to the charge if the joystick has moved
  if (charge < 1000 && jsdist > 5) {
    // the increase depends on the distance in the previous iteration
    charge += streak;
    streak += jsdist/100;
  } else {
    streak = 0;
  }

  // calculate the pitch based on both the charge and how much the joystick moved
  int pitch;
  if (charge > 0) {
    // the more you wiggle the stick the higher the pitch goes,
    // and the longer that the joystick has been rubbed for then it is the higher the pitch
    pitch = map (jsdist, 0, 1024, charge, charge + 700);
    // decrease happiness value
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

// return distance between two points, based on pythag theorem
float getDist(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x2 - x1, 2) +
              pow(y2 - y1, 2));
}

// interrupt function to decharge the charge completely
void decharge() {
  charge = -100;
}