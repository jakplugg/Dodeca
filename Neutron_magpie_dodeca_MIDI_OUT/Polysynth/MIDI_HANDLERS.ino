void HandleControlChange (byte channel, byte number, byte value) {
  //maybe use a CC to change drum trigger length
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) {

  if (velocity == 0) {//some controllers send note on with 0 velocity, copy note off code here
    for (int buh = 0; buh < 6; buh ++) {
      if (pitch == Oactive[buh]) {
        Oactive[buh] = 0;
        analogWrite(out2pin[((buh<<1))],0);
        notes --;
        if (notes < 1) analogWrite(out2pin[3],0);
        break;
      }
    }

  }
  else
    for (int buh = 0; buh < 6; buh ++) {
      if (Oactive[buh] == 0) {
        Oactive[buh] = pitch;
        Opower[buh] = velocity;
        Ophase_inc[buh] = note2inc[pitch];
        analogWrite(out2pin[((buh<<1))],Opower[buh]<<3);
        notes ++;
        analogWrite(out2pin[3],1023);
        analogWrite(out2pin[5],velocity<<3);
        break;
      }

    }
}

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  for (int buh = 0; buh < 6; buh ++) {
    if (Oactive[buh] == pitch) {
      Oactive[buh] = 0;
      Opower[buh] = 0;
      analogWrite(out2pin[((buh<<1))],0);
      notes--;
      if (notes < 1) analogWrite(out2pin[3],0);
      break;
    }
  }
}

void HandlePitchBend (byte channel, int bend) {
//pitch bend will mult/divide Phase increments as they are calculated in note handler.
}

