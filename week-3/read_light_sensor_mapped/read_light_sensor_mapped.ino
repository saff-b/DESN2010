/*
  based on AnalogReadSerial example sketch
  calibration taken from calibration example
  smoothing from https://www.youtube.com/watch?v=_yB-DDOFrhI

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/
const int sensorPin = A0;
const int noisePin = 7;

int sensorValue = 0;
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

// how scared is he?
int fear = 0;
bool screaming = false;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  pinMode(noisePin, OUTPUT);

  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue = analogRead(sensorPin);
  delay(1);        // delay in between reads for stability

  int numReads = 30;
  int senseSum = 0;

  for (int i = 0; i < numReads; i++) {
    senseSum += analogRead(sensorPin);
    delay(1);
  }
  
  int senseAve = senseSum / numReads;
  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(senseAve, sensorMin, sensorMax);

  // apply the calibration to the sensor reading
  int mappedValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  int screamIntensity = map(sensorValue, 950,1023,400,1600);
  // print out the value you read:
  Serial.print(screamIntensity);
  Serial.print(" ; ");
  Serial.println(mappedValue);

 if (mappedValue >= 170) {
    if (fear < 20) {
      fear ++;
    }
  } else {
    if (fear > 0) {
      fear --;
    }
  }

    screaming = (fear > 0);
    
     Serial.println(fear);
  if (screaming) {
    Serial.println("AAAAAA");
    
     tone(noisePin, screamIntensity, 10);
  }
  delay(1);
  
}
