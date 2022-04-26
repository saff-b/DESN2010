/* motion sensor */

int sensorPin = 3;
int ledPin = 13;

int motion = HIGH; // low = no motion ; high = motion

void setup() {
  // put your setup code here, to run once:
  /* Pin setup */
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /* Take a read from the sensor */
  int sensorData = digitalRead(sensorPin);
  if (sensorData = HIGH) {
    if (motion = LOW) {
      motion = HIGH;
      digitalWrite(ledPin, HIGH);
    }
  } else {
    if (motion = HIGH) {
      motion = LOW;
      digitalWrite(ledPin, LOW);
    }
  }
  Serial.println(sensorData);
}
