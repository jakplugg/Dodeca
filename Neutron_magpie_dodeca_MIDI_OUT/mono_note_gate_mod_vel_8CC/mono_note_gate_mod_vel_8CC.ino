//Neutron QnD MIDI out 12 mono voice + 8x CC/CVs

#include <MIDI.h>


// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation ere: 
// http://arduinomidilib.sourceforge.net/class_m_i_d_i___class.html


uint8_t out2pin[] = {23,0,22,25,20,6,21,5,9,4,10,3};

uint8_t bottomNote = 12; //the bottom MIDI note, the module puts out 8 octaves.  
uint8_t topNote = bottomNote + 95;
uint16_t pitchOut;

uint8_t cc2out[] = {40,41,42,1,2,3,4,5,6,7,8,9}; //ignore first 3 these are the MIDI CCs that will be output.

void HandlePitchBend (byte channel, int bend){
  Serial.println(bend);
}

void HandleControlChange (byte channel, byte number, byte value){
  for (int i = 3;i < 13;i ++){
    if (number == cc2out[i]){
    { 
      if (out2pin[i] == 0) analogWrite(A14,(value<<5));
      else analogWrite(out2pin[i],value<<5);    
      }
    }
  } 
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) { 
  
  if (velocity != 0) {
 
    digitalWriteFast(out2pin[0],1);
    analogWrite(out2pin[2],velocity<<5);    
    constrain (pitch,bottomNote,topNote);
    pitch = (pitch ) - bottomNote;
    pitchOut = pitch*36;
    analogWrite(A14,pitchOut);
  }

  else digitalWriteFast(out2pin[0],0);

  // Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
  // and have a bad impact on real-time performance.
}


void setup() {
  // Initiate MIDI communications, listen to all channels
     
  
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(20,OUTPUT);
  pinMode(21,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(25,OUTPUT);
analogWriteFrequency(3,40000);
analogWriteFrequency(4,40000);
analogWriteFrequency(5,40000);
analogWriteFrequency(6,40000);
analogWriteFrequency(9,40000);
analogWriteFrequency(10,40000);
analogWriteFrequency(20,40000);
analogWriteFrequency(21,40000);
analogWriteFrequency(22,40000);
analogWriteFrequency(23,40000);
analogWriteFrequency(25,40000);

analogWriteResolution(12);
  digitalWriteFast(4,HIGH);

  for (int i = 0;i < 13;i ++){
    for (int j = 0;j < 128; j ++){
      if (out2pin[i] == 0) analogWrite(A14,(j<<5)); 
      else analogWrite(out2pin[i],j<<5);
      delay(1);
    }
     if (out2pin[i] == 0) analogWrite(A14,0); 
    analogWrite(out2pin[i],0);
  }

  MIDI.begin(MIDI_CHANNEL_OMNI); 
  // Connect the HandleNoteOn function to the library, so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleControlChange(HandleControlChange); 
  Serial.begin(9600);
}


void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();
  
  // There is no need to check if there are messages incoming if they are bound to a Callback function.
}
