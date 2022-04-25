/*
  Saf Bannister 2022
  Get height of person passing under 210cm doorway (doorway height can be configured)
  Distance calucation based on: https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
*/

int trigPin = 9;
int echoPin = 8;
// DISTANCES ARE IN CM.
int doorHeight = 210;
long duration;
int height;

void setup() {
  // put your setup code here, to run once:
  /* ULTRASONIC SET UP */
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  /* SERIAL */
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  /* get the height of the person under the doorframe */
  int distance;
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
  int tempHeight = doorHeight - distance;
  if (tempHeight > 0 && abs(tempHeight - height) > 20) {
    height = tempHeight;
    /* print that height to serial */
    Serial.println(height);
  }
}
