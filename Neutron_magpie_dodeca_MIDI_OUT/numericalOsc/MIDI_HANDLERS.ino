void HandleControlChange (byte channel, byte number, byte value) {
  switch (number) {
    case 10: waveLink = wavePointer[value >> 5]; break;
    case 11: FMindex = int32_t(value<<9); break;

  }
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) {

  if (velocity == 0) {//some controllers send note on with 0 velocity, copy note off code here
    NoteOffBoth(channel, pitch, velocity);
  }



  else {
      
    for (int k = 0; k < 3; k++) {
      if (Oactive[k] == 0) {
        
        Oactive[k] = pitch;
        if (pitch > 47)Ooctave[k] = int((pitch - 48) / 12);
        //bottom 4 octaves are 512 steps then divided by 2 as octaves increase
        //to keep the sample rate from getting too high
        else Ooctave[k] = 0;
        Opower[k] = velocity;
        //Ophase[k] = 0;//if you want the osc to reset. on the Dodeca, it will still click because the DAC output is not offset.
            Ophase_inc[k] = note2inc[pitch] >> Ooctave[k];
        analogWriteFrequency(timerPin[k], Ophase_inc[k]);
        switch (k) {
          case 0:
            attachInterrupt(timerPin[0], ISR_OSC, RISING); break;
          case 1:
            attachInterrupt(timerPin[1], ISR_OSC1, RISING); break;
          case 2:
            attachInterrupt(timerPin[2], ISR_OSC2, RISING); break;
        }
         if (notes < 1){
      analogWrite(out2pin[5],512);
      notes ++;
    }
        break;
      }
    }
  }
}

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  NoteOffBoth(channel, pitch, velocity);
}

void HandlePitchBend (byte channel, int bend) {
  //pitch bend will mult/divide Phase increments that were calculated in note handler 
}

void NoteOffBoth(byte chan, byte pitc, byte velo) {
  for (int buh = 0; buh < 3; buh ++) {
    if (pitc == Oactive[buh]) {
      notes --;
      //detachInterrupt(timerPin[buh]);
      Oactive[buh] = 0;
      if (notes < 1)analogWrite(out2pin[5],0);
    }
  }
}

