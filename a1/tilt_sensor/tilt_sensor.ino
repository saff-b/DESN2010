// tilt sensor: digital input, when the circuit is wiggled around the plate disconnects
// note: requires a 240 resistor between the sensor and ground

int tiltSwitch = 9;
int buzzer = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tiltSwitch, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int switchResult = digitalRead(tiltSwitch);
  Serial.println(switchResult);
  if (switchResult = LOW) {
    bwooop();
  }
}

// make a 'bwooop' sound out of the buzzer
void bwooop() {
  for (int i = 200; i < 400; i++) {
    tone(buzzer, i, 5);
    delay(5);
  }
    noTone(buzzer);
}