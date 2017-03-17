void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  //  if (channel == CHANA) {
  //    int modNote = (whitekeys[pitch % 12] - 1)*2;
  //    if (velocity != 0) {
  //      if (out2pin[modNote]) {
  //        analogWrite(out2pin[modNote], velocity);
  //      }
  //      else analogWrite(A14, velocity);
  //    }
  //    else bothNoteOff(channel, pitch, velocity);
  //  }
  //  if (channel == CHANB) {
  //    int modNote = ((whitekeys[pitch % 12] - 1)*2)+1;
  //    if (velocity != 0) {
  //      if (out2pin[modNote]) {
  //        analogWrite(out2pin[modNote], velocity);
  //      }
  //      else analogWrite(A14, velocity);
  //    }
  //    else bothNoteOff(channel, pitch, velocity);
  //  }
}

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  //  bothNoteOff(channel, pitch, velocity);
}

void bothNoteOff(byte channel, byte pitch, byte velocity) { //this is called by handle noteoff and note on when velocity = 0
  //  if (channel == CHANA) {
  //    int modNote = (whitekeys[pitch % 12] - 1)*2;
  //    if (out2pin[modNote]) {
  //      analogWrite(out2pin[modNote], 0);
  //    }
  //    else analogWrite(A14, 0);
  //  }
  //  if (channel == CHANB) {
  //    int modNote = ((whitekeys[pitch % 12] - 1)*2)+1;
  //    if (out2pin[modNote]) {
  //      analogWrite(out2pin[modNote], 0);
  //    }
  //    else analogWrite(A14, 0);
  //  }
}

void HandleControlChange (byte channel, byte number, byte value) {
  if (channel == CHANA) {
    for (int n = 0; n < 6; n ++) {
      if ( number == cc2out[n]) { //ignore wrong channel or CC numbers
        analogWrite(out2pin[n * 2], value); //output on ,1,3,5 etc
      }
    }
  }
  if (channel == CHANB) {
    for (int n = 0; n < 6; n ++) {
      if ( number == cc2out[n]) { //ignore wrong channel or CC numbers
        if (n == 0) {
          analogWrite(A14, value);
        }
        else analogWrite(out2pin[(n * 2) + 1], value); //output on ,2,4,6 etc
      }
    }
  }
}



