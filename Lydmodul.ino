#include <MIDI.h>  //MIDI I/Os for Arduino https://github.com/FortySevenEffects/arduino_midi_library
#include <Tone.h>  //Bhagman Tone Library https://github.com/bhagman/Tone

byte i = 0, j = 1, k = 1;

static const uint16_t note[89] = {   //MIDI NOTES TO FREQUENCY ARRAY
  NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1,
  NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1, NOTE_C2, NOTE_CS2, NOTE_D2,
  NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2,
  NOTE_B2, NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3,
  NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4,
  NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4,
  NOTE_B4, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5,
  NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, NOTE_C6, NOTE_CS6, NOTE_D6,
  NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6,
  NOTE_B6, NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7,
  NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7, NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8,
};

MIDI_CREATE_DEFAULT_INSTANCE();

Tone notePlayer[3];   //[3] = 3 OSC (MAX)

const int synthIn = 7;

void setup(void) {

  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  notePlayer[0].begin(3);    //OSC 1 - OSC 1 OUTPUT PIN 3
  notePlayer[1].begin(5);    //OSC 2 - OSC 2 OUTPUT PIN 5
  notePlayer[2].begin(11);   //OSC 3 - OSC 3 OUTPUT PIN 11

  MIDI.setHandleNoteOn(MyHandleNoteOn);
  MIDI.setHandleNoteOff(MyHandleNoteOff);
  pinMode(synthIn,INPUT_PULLUP);
}

void loop(void) {
  if (digitalRead(synthIn)==HIGH);
   MIDI.read();
}

void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  i = pitch - 23;

  j = j + 1;
  if (j > 3) j = 1;

  switch (j) {
    case 1:
      notePlayer[0].play(note[i]);
      break;
    case 2:
      notePlayer[1].play(note[i]);
      break;
    case 3:
      notePlayer[2].play(note[i]);
      break;
  }
}

void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {

  k = k + 1;
  if (k > 3) k = 1;

  switch (k) {
    case 1:
      notePlayer[0].stop();
      break;
    case 2:
      notePlayer[1].stop();
      break;
    case 3:
      notePlayer[2].stop();
      break;
  }
}
