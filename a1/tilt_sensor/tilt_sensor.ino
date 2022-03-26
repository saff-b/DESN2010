// tilt sensor: digital input, when the circuit is wiggled around the plate disconnects
// note: requires a 240 resistor between the sensor and ground

int tiltSwitch = 3;
int buzzer = 7;

bool bwoop = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tiltSwitch, INPUT);
  pinMode(buzzer, OUTPUT);
  // interrupts https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  attachInterrupt(digitalPinToInterrupt(tiltSwitch), makeBwoop, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  //if (bwoop) {

  noInterrupts();
    //Serial.print("bwooptime!");
    for (int i = 440; i < 600; i++) {
      tone(buzzer, i, 50);
      delay(5);
    }
    noTone(buzzer);    
    //bwoop = false;
  interrupts();
  //};
}

void makeBwoop() {
  bwoop = true;
  Serial.println("bwoop");
}