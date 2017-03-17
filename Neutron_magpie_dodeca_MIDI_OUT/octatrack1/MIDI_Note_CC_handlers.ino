void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (channel == CHAN) {
    int modNote = whitekeys[pitch % 12] - 1;
    if (velocity != 0) {
      if (out2pin[modNote]) {
        analogWrite(out2pin[modNote], velocity);
      }
      else analogWrite(A14, velocity);
    }
    else bothNoteOff(channel, pitch, velocity);
  }
}

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  bothNoteOff(channel, pitch, velocity);
}

void bothNoteOff(byte channel, byte pitch, byte velocity) { //this is called by handle noteoff and note on when velocity = 0
  if (channel == CHAN) {
    int modNote = whitekeys[pitch % 12] - 1;
    if (out2pin[modNote]) {
      analogWrite(out2pin[modNote], 0);
    }
    else analogWrite(A14, 0);
  }
}

void HandleControlChange (byte channel, byte number, byte value) {
  if (channel == CHAN && number < 4) { //ignore wrong channel or CC numbers
    analogWrite(out2pin[number + 7], value); //output on ,9,10,11
  }
}



