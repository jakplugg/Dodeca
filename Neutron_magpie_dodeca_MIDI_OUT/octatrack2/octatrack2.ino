/*
   Neutron magpie dodeca:
   Octatrack2 may be slaved to octatrack1 or used seperately
   pitch out on out 2
   gate on out 1
   velocity on out 3
   9 CC output respond to CC 1,2,3,4,5,6,7,8,9 (out 4-12)
 * */

#include <MIDI.h>
#include "notelist.h"

const uint8_t CHAN = 2;//set the MIDI channel here!
uint8_t GateOut = 0; //gate is on first output.
uint8_t VelOut = 2;
int numNotes = 0;
uint8_t out2pin[] = {23, 0, 22, 25, 20, 6, 21, 5, 9, 4, 10, 3}; //actual pin mapping for teensy, dont change unless you redesign the board
uint8_t cc2out[] = {40, 41, 42, 1, 2, 3, 4, 5, 6, 7, 8, 9}; //MIDI CCs that be detected. (first 3 not used in theis sketch)
static const unsigned sMaxNumNotes = 16;
MidiNoteList<sMaxNumNotes> midiNotes;
void setup() {
  for (int i = 0; i < 12; i ++) {//set all the required pins to output and adjust PWM speed.
    if (out2pin[i]) {
      pinMode(out2pin[i], OUTPUT);
      analogWriteFrequency(out2pin[i], 375000);
    }
    else analogWriteFrequency(A14,40000);
  }

  analogWriteResolution(12);//for the DAC channel 2. because of high PWM frequency, PWM resolution is reduced to 7 bits used by MIDI

  for (int i = 0; i < 13; i ++) {//startup animation
    for (int j = 0; j < 128; j ++) {
      if (out2pin[i] == 0) analogWrite(A14, (j << 5));
      else analogWrite(out2pin[i], j << 5);
      delay(1);
    }
    if (out2pin[i] == 0) analogWrite(A14, 0);
    analogWrite(out2pin[i], 0);
  }//end animation

  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Connect the functions to the library, so it is called upon reception.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandleNoteOff(HandleNoteOff);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("dodeca");  
}

void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();
  // There is no need to check if there are messages incoming if they are bound to a Callback function.
}
