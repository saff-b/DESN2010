/* 
  get a reading from dual ultrasonic sensor module and write to serial
  How it works!
  there are two pins: trig and echo
  trig is 
  Modified from this:
  https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
*/

int trigPin = 8;
int echoPin = 9;
long duration;
int distance;
int smoothingFactor = 30;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("sensor test");
}

void loop() {
  // handle dropout and outlier data with this
  int tempSmoothingFactor = smoothingFactor;
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
    tempDistance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    if (tempDistance < 1000) {
      distance = distance + tempDistance;
    }
    else {
      tempSmoothingFactor--;
    }
  }
  distance = distance / tempSmoothingFactor;
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
