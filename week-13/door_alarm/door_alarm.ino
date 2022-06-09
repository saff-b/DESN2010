/*  
    tilt switch alarm 
    plays the puzzle solved/secret uncovered jingle from Zelda whenever the door opens
*/
#include "pitches.h"; // from toneMelody sample code

/* PINS */
int tiltSwitch = 3;
int buzzer = 8;

  // sheet music: https://www.ninsheetmusic.org/download/pdf/1642
  int zelda_tones[] = {
    NOTE_G6, NOTE_FS6, NOTE_DS5, NOTE_A5, NOTE_GS5, NOTE_E6, NOTE_GS6, NOTE_C7
  };
  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int zelda_durations[] = {
    8, 8, 8, 8, 8, 8, 8, 8
  };

void setup() {
  // put your setup code here, to run once:
  pinMode(tiltSwitch, INPUT); //configure tilt sensor as input mode
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(tiltSwitch) == LOW) {
    play(zelda_tones, zelda_durations);
    delay (5000); // prevents it triggering multiple times in rapid succession
  }
}

// function which plays a melody of a given note declaration and note lengths
// modified from toneMelody example code
void play(int melody[], int noteDurations[]) {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }
}