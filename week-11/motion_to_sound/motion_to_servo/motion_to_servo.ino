/*
  motion sensor -> mp3 sound
  uses code from examples for :
  DFPlayer - A Mini MP3 Player For Arduino
    <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

  combined with my motion to servo code  
*/

// include the Servo library
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

/* PINS */
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX -- used by mp3 player
int motionSensor = 2; // the pin for the motion sensor

/* CONFIG VARIABLES : change these to change things about the program */
int sensitivity = 1000; // the max value for how high the detection buffer value can go. 
// note: the lower it is, the more sensitive the system is to movement
int minVolume = 10; // the minimum volume
int maxVolume = 30; // the maximum volume

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
  
  /* set up mp3 player */

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(0);  //Set volume value. From 0 to 30
  myDFPlayer.play(2);  //play the laughter track
}

void loop() {
  /* take reading from movement sensor */
  int move = digitalRead(motionSensor); 

  if (move == HIGH) {
    // do movement thing
    if (detection < sensitivity) {
      detection = detection + 25;
    }
  } else {
    // do no movement thing
    if (detection > 0) {
      detection = detection - 1;
    }
  }

  if (detection > 0) {
    volume = map (detection, 0, sensitivity, minVolume, maxVolume);
    // if the sound is not currently playing, start it
  } else {
    // if no movement is detected, set volume to 0
    // keeping the track playing means that the start point is more dynamic
    volume = 0;
  }
  
  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
  Serial.println(detection);
}


// error messages
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