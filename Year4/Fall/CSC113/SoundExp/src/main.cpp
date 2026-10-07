/*

  Melody

  Plays a melody

  circuit:

  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010

  modified 30 Aug 2011

  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/Tone

*/

#include <Arduino.h>
#include "notes.h"

// Upper melody from Reze, measures 1-14.
// Row 1: measures 1-8. Row 2: measures 9-14.
int melody[] = {
  NOTE_B4, NOTE_A4, // measure 1
  NOTE_FS4, // measure 2
  NOTE_B4, NOTE_CS5, // measure 3
  NOTE_FS4, NOTE_A4, // measure 4
  NOTE_B4, NOTE_A4, // measure 5
  NOTE_FS4, // measure 6
  NOTE_B4, // measure 7
  NOTE_CS5, // measure 8
  NOTE_B4, NOTE_E4, NOTE_CS5, NOTE_B4, // measure 9
  NOTE_CS5, NOTE_FS4, NOTE_D5, NOTE_CS5, // measure 10
  NOTE_D5, NOTE_A4, NOTE_E5, NOTE_D5, // measure 11
  NOTE_FS5, NOTE_E5, NOTE_B4, // measure 12
  NOTE_B4, NOTE_A4, NOTE_E4, NOTE_D4, NOTE_CS5, NOTE_B4, // measure 13
  NOTE_CS5, NOTE_B4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_CS5 // measure 14
};

// Durations in sixteenth notes: 1 = sixteenth, 2 = eighth,
// 3 = dotted eighth, 4 = quarter, 8 = half, 12 = dotted half.
int noteDurations[] = {
  8, 4, // measure 1
  12, // measure 2
  8, 4, // measure 3
  4, 8, // measure 4
  8, 4, // measure 5
  12, // measure 6
  12, // measure 7
  12, // measure 8
  4, 4, 3, 1, // measure 9
  4, 4, 3, 1, // measure 10
  4, 4, 3, 1, // measure 11
  4, 4, 4, // measure 12
  2, 2, 2, 2, 3, 1, // measure 13
  2, 2, 2, 2, 3, 1 // measure 14
};

const int tempoBPM = 60;
const int beatDuration = 60000 / tempoBPM;
const int noteCount = sizeof(melody) / sizeof(melody[0]);

void setup() {

  // iterate over the notes of the melody:

  for (int thisNote = 0; thisNote < noteCount; thisNote++) {

    // Four sixteenth notes make one beat.
    int noteDuration = beatDuration * noteDurations[thisNote] / 4;

    tone(8, melody[thisNote], noteDuration * 9 / 10);

    // Leave a short gap within each note to keep the tempo at 60 BPM.
    delay(noteDuration);

    // stop the tone playing:

    noTone(8);

  }
}

void loop() {

}