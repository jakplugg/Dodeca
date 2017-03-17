void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (velocity > 0) {
    switch (channel) {

      case CHAN:
        LFO_rate_mult[0] = keyDivs[pitch % 12];
        vel[0] = velocity;
        ENVactive[0] = 1;
        s1 = LFOselLen[LFO_wavenum1];
        LFOsel1 = LFOpool[LFO_wavenum1];
        lfo1.phase = 0;
        break;

      case (CHAN+1):
        LFO_rate_mult[1] = keyDivs[pitch % 12];
        vel[1] = velocity;
        ENVactive[1] = 1;
        s2 = LFOselLen[LFO_wavenum2];
        LFOsel2 = LFOpool[LFO_wavenum2];
        lfo2.phase = 0;
        break;

      case (CHAN + 2):
        LFO_rate_mult[2] = keyDivs[pitch % 12];
        vel[2] = velocity;
        ENVactive[2] = 1;
        s3 = LFOselLen[LFO_wavenum3];
        LFOsel3 = LFOpool[LFO_wavenum3];
        lfo3.phase = 0;
        break;
    }
  }
  else bothNoteOff(channel, pitch, velocity);
}

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  bothNoteOff(channel, pitch, velocity);
}

void bothNoteOff(byte channel, byte pitch, byte velocity) { //this is called by handle noteoff and note on when velocity = 0
  switch (channel) {
    case CHAN:
      ENVactive[0] = 0;
      break;
    case CHAN+1:
      ENVactive[1] = 0;
      break;
    case CHAN+2:
      ENVactive[2] = 0;
      break;
  }
}

void HandleControlChange (byte channel, byte number, byte value) {
  INvert = 127 - value;
  switch (channel) {
    case CHAN:
      if (number == CC_A) lfo1.phaseOffset = value << 25;
      if (number == CC_B) LFO_wavenum1 = value >> 5;
      if (number == CC_C) ENVattack[0] =  (INvert * INvert * INvert)>>2;
      if (number == CC_D) ENVdecay[0] =  (INvert * INvert * INvert)>>2;
      break;
    case (CHAN+1):
      if (number == CC_A) lfo2.phaseOffset = value << 25;
      if (number == CC_B) LFO_wavenum2 = value >> 5;
      if (number == CC_C) ENVattack[1] = 2097152 - (value * value * value); //2097152
      if (number == CC_D) ENVdecay[1] = 2097152 - (value * value * value);
      break;
    case (CHAN+2):
      if (number == CC_A) lfo3.phaseOffset = value << 25;
      if (number == CC_B) LFO_wavenum3 = value >> 5;
      if (number == CC_C) ENVattack[2] = 2097152 - (value * value * value);
      if (number == CC_D) ENVdecay[2] = 2097152 - (value * value * value);
      break;
  }
}



