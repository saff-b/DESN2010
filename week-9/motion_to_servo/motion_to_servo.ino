/*
  motion sensor -> servo
  The servo interacts with a line which clothing is strung on, in order to move clothing
  when motion is sensed, the servo goes, when there is no motion, the servo remains still 

  includes code from "Arduino Starter Kit example Project 5 - Servo Mood Indicator" in the arduino IDE
*/

// include the Servo library
#include <Servo.h>

Servo myServo;  // create a servo object
int motionSensor = 2; // the pin for the motion sensor


/* CONFIG VARIABLES : change these to change things about the program */
int sensitivity = 1000; // the max value for how high the detection buffer value can go. 
// note: the lower it is, the more sensitive the system is to movement
int servoMinSpeed = 3; // the fastest speed the servo can go
int servoMaxSpeed = 30; // the slowest speed the servo can go
int minAngle = 0; // 0 degrees (don't set this lower than 0)
int maxAngle  = 90; // 90 degrees (don't set this higher than 180)

/* STATIC VARIABLES */ 
int servoSpeed = servoMaxSpeed; // default servospeed. Speed will be mapped to this in reverse.
int detection; // a value from 0 to sensitivity denoting how fast the servo should be moving (closer to max -> faster)
int angle; // the servo angle, ranges from minAngle <-> maxAngle
bool rising = true; // indicates whether the servo is currently moving towards maxAngle or minAngle

void setup() {
  // put your setup code here, to run once:
  /* set up motion sensor */
   pinMode(motionSensor, INPUT);

  /* set up servo */
  myServo.attach(9); // attaches the servo on pin 9 to the servo object

  /* FOR TESTING: set up serial */
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /* take reading from movement sensor */
  int move = digitalRead(motionSensor); 

  if (move == HIGH) {
    // do movement thing
    if (detection < sensitivity) {
      detection = detection + 1;
    }
  }
  else {
    // do no movement thing
    if (detection > 0) {
      detection = detection - 1;
    }
  }

  //Serial.println(speed);
  if (detection > 0) {
    servoSpeed = map (detection, 0, sensitivity, servoMaxSpeed, servoMinSpeed);
    // check if the angle is currently risng or falling
    switch (rising) {
      // if it's rising, increase the angle by one
      case true:
        if (angle < maxAngle) {
          angle = angle + 1;
        } else {
          // if we have reached the maximum angle, we are no longer rising and are now falling.
          rising = false;
        }
      break;
      // otherwise, decrease the angle by one
      default:
        if (angle > minAngle) {
          angle = angle - 1;
        } else {
          // if we have reached the maximum angle, we are no longer rising and are now falling.
          rising = true;
        }
    }
    
    myServo.write(angle);
    delay(servoSpeed);
  }
  Serial.println(servoSpeed);

  // Serial.println(angle);

}