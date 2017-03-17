
// -----------------------------------------------------------------------------

inline void handleGateChanged(bool inGateActive)
{
    analogWrite(out2pin[GateOut], inGateActive ? (127<<5) : 0);
}

inline void pulseGate()
{
    handleGateChanged(false);
    delay(1);
    handleGateChanged(true);
}

// -----------------------------------------------------------------------------

void handleNotesChanged(bool isFirstNote = false)
{
    if (midiNotes.empty())
    {
        handleGateChanged(false);
        analogWrite(out2pin[GateOut], 0);
    }
    else
    {
        // Possible playing modes:
        // Mono Low:  use midiNotes.getLow
        // Mono High: use midiNotes.getHigh
        // Mono Last: use midiNotes.getLast

        byte currentNote = 0;
        if (midiNotes.getLast(currentNote))
        {
            analogWrite(A14, currentNote<<5);

            if (isFirstNote)
            {
                handleGateChanged(true);
            }
            else
            {
                pulseGate(); // Retrigger envelopes. Remove for legato effect.
            }
        }
    }
}

// -----------------------------------------------------------------------------

void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (channel == CHAN) {    
    if (velocity != 0) {
        const bool firstNote = midiNotes.empty();
        midiNotes.add(MidiNote(pitch, velocity));
        handleNotesChanged(firstNote);
        analogWrite(out2pin[VelOut],velocity<<5);
      }
      else bothNoteOff(channel,pitch,velocity);   
    }    
  }

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  bothNoteOff(channel,pitch,velocity);
}  

//this is called by handle noteoff and note on when velocity = 0 not part of MIDI lib.
void bothNoteOff(byte channel, byte pitch, byte velocity) { 
  if (channel == CHAN) {    
     midiNotes.remove(pitch);
     handleNotesChanged();
    }    
  }


  
void HandlePitchBend (byte channel, int bend){
  if (channel == CHAN){
  Serial.println(bend);//to be fixed add pb to note value
  }
}

void HandleControlChange (byte channel, byte number, byte value){
  if (channel == CHAN){
  for (int i = 3;i < 13;i ++){
    if (number == cc2out[i]){           
    analogWrite(out2pin[i],value<<5);    
      }
    }
  } 
}




