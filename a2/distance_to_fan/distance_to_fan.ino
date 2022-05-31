/* 
  blow clothes using the fan when a person is picked in a certain distance up using the ultrasonic sensor (uss)
  ultrasonic distance calculation modified from:
  https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
  smoothing:
  https://www.youtube.com/watch?v=_yB-DDOFrhI
*/

/* PIN SET UP */
int fanPin = 3; // fan
int echoPin = 9; // ultrasonic echo
int trigPin = 10; // ultrasonic trigger

/* CONFIG VARIABLES */
int smoothing = 30; // for ultrasonic reads
int detectionRange = 100; // distance in CM
int fanTime = 20000; // how long the fan stays on once it has been triggered.

/* GLOBAL VARIABLES */
int distance; // for ultrasonic
int ultrasonicReadSpacing = 1; // how often to take reads from the distance sensor. 1000 = 1 second

void setup() {
  // put your setup code here, to run once:
  /* PIN SET UP */
  pinMode(fanPin, OUTPUT); // Sets fan pin as an OUTPUT
  digitalWrite(fanPin, HIGH); // turn fan off to start
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  distance = getDist(smoothing);
  Serial.begin(9600);
}

void loop() {
   // we only get the distance once per ultrasonicRadSpacing. 
  // this allows for the fan to run smoothly without being interrupted by the distance sensor going off
  static unsigned long timer = millis();
  if (millis() - timer > ultrasonicReadSpacing) {
    timer = millis();
    distance = getDist(smoothing); // use the getDist function to get the distance
    Serial.println(distance);
    // if there is a person (or object) within range of the sensor, set the fan to be on
    // if the distance is less than 0 that indicates an out of range error
    if (distance > detectionRange || distance < 0) {
      digitalWrite(fanPin, HIGH); // this turns the fan off
      ultrasonicReadSpacing = 30; // continuously check distance so that the fan is responsive
    } else {
      digitalWrite(fanPin, LOW); // this turns the fan on
      ultrasonicReadSpacing = fanTime;  // keep the fan on for 20 seconds
    }
  }
}

// Function that takes a reading from the ultrasonic sensor
int getDist(int smoothingFactor) {
  Serial.println("getting distance!");
  int d = 0;
  long duration; // for ultrasonic
  for (int i = 0; i < smoothingFactor; i++) {
    int tempD;
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
    tempD = duration * 0.034 / 2;
    d = d + tempD; // Speed of sound wave divided by 2 (go and back)
  }
  return d / smoothingFactor;
}