/*
   Neutron magpie dodeca:
   12 drum trigs variable by velocity.
   12 notes (anywhere on keyboard) C=1 C#=2 etc
 * */

#include <MIDI.h>


// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation ere:
// http://arduinomidilib.sourceforge.net/class_m_i_d_i___class.html


uint8_t out2pin[] = {23, 0, 22, 25, 20, 6, 21, 5, 9, 4, 10, 3};
uint8_t triggerTimer[12];
uint8_t trigLength = 20; //this is how long the drum triggers are

uint8_t bottomNote = 12; //the bottom MIDI note, the module puts out 8 octaves.
uint8_t topNote = bottomNote + 95;
uint16_t pitchOut;

//uint8_t cc2out[] = {40, 41, 42, 1, 44, 45, 46, 47, 48, 49, 50, 51};

void HandleControlChange (byte channel, byte number, byte value) {
  //maybe use a CC to change drum trigger length
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  int modNote = pitch % 12;
  if (velocity != 0) {
    if (out2pin[modNote]) {
      analogWrite(out2pin[modNote], velocity);
    }
    else analogWrite(A14, velocity);
    triggerTimer[modNote] = 0;
  }

  else digitalWriteFast(out2pin[0], 0);

  // Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
  // and have a bad impact on real-time performance.
}
void ISR_TRIGEND(void);

IntervalTimer countdownTimer;

void setup() {
  // Initiate MIDI communications, listen to all channels

  for (int i = 0; i < 12; i ++) {
    if (out2pin[i]) {
      pinMode(out2pin[i], OUTPUT);
      analogWriteFrequency(out2pin[i], 375000);
    }
  }


  analogWriteResolution(7);
  //digitalWriteFast(4, HIGH);

  for (int i = 0; i < 12; i ++) {
    for (int j = 0; j < 128; j ++) {
      if (out2pin[i] == 0) analogWrite(A14, (j ));
      else analogWrite(out2pin[i], j );
      delay(2);
    }
    if (out2pin[i] == 0) analogWrite(A14, 0);
    analogWrite(out2pin[i], 0);
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Connect the HandleNoteOn function to the library, so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleControlChange(HandleControlChange);

  countdownTimer.begin(ISR_TRIGEND, 1000);

  Serial.begin(9600);
}


void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();

  // There is no need to check if there are messages incoming if they are bound to a Callback function.
}
