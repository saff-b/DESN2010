/*
  motion sensor -> mp3 sound
  uses code from examples for :
  DFPlayer - A Mini MP3 Player For Arduino
    <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

  combined with my motion to servo code (https://github.com/saff-b/DESN2010/blob/main/week-9/motion_to_servo/motion_to_servo.ino)
*/

// include the necessary libraries
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

/* PINS */
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX -- used by mp3 player
int motionSensor = 2; // the pin for the motion sensor

/* CONFIG VARIABLES : change these to change things about the program */
int sensitivity = 1000; // the max value for how high the detection buffer value can go. 
// note: the lower it is, the more sensitive the system is to movement
int increaseRate = 4; // the rate which the sensitivity buffer will increase. Higher = faster increase in volume
int degredationRate = 2; // the rate which the sensitivity buffer will degrade. Higher = faster decrease in volume
int minVolume = 5; // the minimum volume
int maxVolume = 30; // the maximum volume
int delayRate = 50; // Delay between reads in miliseconds. (set to 0 if the sensor has hardware delay controls)

/* STATIC VARIABLES */ 
int volume = minVolume; // default volume. Speed will be mapped to this.
int detection; // a value from 0 to sensitivity denoting how fast the servo should be moving (closer to max -> faster)
bool playing = false; // simple check if currently playing an mp3

/* SETUP FOR MP3 PLAYER */
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup() {
  // put your setup code here, to run once:
  /* set up motion sensor */
   pinMode(motionSensor, INPUT);
  
  /* set up mp3 player - from sample code https://www.dfrobot.com/index.php?route=product/product&product_id=1121 */

  mySoftwareSerial.begin(9600); // Use softwareSerial to communicate with mp3 player module.
  Serial.begin(115200); // information about the MP3 player function will be printed on this line
  
  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)")); // user information
  
  if (!myDFPlayer.begin(mySoftwareSerial)) { // if the mp3 player doesn't start, print this  
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(0);  // Set volume value. From 0 to 30
  myDFPlayer.loop(2);  // play the laughter track on loop
}

void loop() {
  /* take reading from movement sensor */
  int move = digitalRead(motionSensor); 

  if (move == HIGH) {
    // if there is movement, then increase the detection meter
    if (detection < sensitivity) {
      detection = detection + increaseRate;
    }
  } else {
    // when there is no movement, the detection meter degrades
    if (detection > 0) {
      detection = detection - degredationRate;
    }
  }

  if (detection > 0) {
    // if the detection meter is currently above 0 then map the volume to match with that
    volume = map (detection, 0, sensitivity, minVolume, maxVolume);
  } else {
    // if the detection meter is depleted, set volume to 0
    volume = 0;
  }
  
  myDFPlayer.volume(volume);  // Set volume value
  delay(delayRate); // this delays readings. 
  // Some PIR motion detectors have a physical dial for this but mine broke so I added it on the code side.
}


// Error messages for the MP3 player. Used for debugging issues. 
// Source: https://www.dfrobot.com/index.php?route=product/product&product_id=1121
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}