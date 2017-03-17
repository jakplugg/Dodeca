/*
   Neutron magpie dodeca sketch:
   Poly synth 1 osc output (out 2)
   1,3,5,7,9,11, gates for each voice (not much use, just show voices active)

   Paraphonic outputs   
   6 velocity (last),stays on
   4 gate for all envelops,

 * */

#include <MIDI.h>

uint8_t out2pin[] = {23, 0, 22, 25, 20, 6, 21, 5, 9, 4, 10, 3};
uint8_t maxPower = 0;
uint8_t lastPower = 0;
int notes = 0;

//oscillators
uint32_t Ophase_inc[6];
uint32_t Ophase[6];
uint8_t Opower[6];
uint8_t Oactive[6];
uint16_t Owave[6];
uint32_t note2inc[128];
uint32_t Ooutput;

//uint8_t cc2out[] = {40, 41, 42, 1, 44, 45, 46, 47, 48, 49, 50, 51};

void ISR_OSC(void);

IntervalTimer OSC;

void setup() {
  // Initiate MIDI communications, listen to all channels

  for (int i = 0; i < 12; i ++) {
    if (out2pin[i]) {
      pinMode(out2pin[i], OUTPUT);
      analogWriteFrequency(out2pin[i], 46875);
    }
  }

  analogWriteResolution(10);

  //populate the phase increment
  for (int i; i < 128; i++) {
    note2inc[i] = uint32_t(890000.0 * pow(2.0, i / 12.0)); //not exact 440 tuning for now
  }

  OSC.begin(ISR_OSC, 25);


  //digitalWriteFast(4, HIGH);
  //----------------------light animation--------------------
  for (int i = 0; i < 12; i ++) {
    for (int j = 0; j < 128; j ++) {
      if (out2pin[i] == 0) analogWrite(A14, j << 3);
      else analogWrite(out2pin[i], j << 3 );
      delay(1);
    }
    if (out2pin[i] == 0) analogWrite(A14, 0);
    analogWrite(out2pin[i], 0);
    //------------------end light animation---------------------
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Connect the function to the library, so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandlePitchBend (HandlePitchBend);

  Serial.begin(9600);
}

void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();
  // There is no need to check if there are messages incoming if they are bound to a Callback function.
}
