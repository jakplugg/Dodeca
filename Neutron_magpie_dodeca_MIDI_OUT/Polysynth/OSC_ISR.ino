void FASTRUN ISR_OSC(void) {
  for (int o = 0; o < 6; o++) {
    if (Oactive[o] > 0) {
      Ophase[o] = Ophase[o] + Ophase_inc[o];      
      Owave[o] = Ophase[o]>>16;
      Ooutput = Ooutput + Owave[o];
    }
  }
  analogWrite(A14, (Ooutput >> 8));
  Ooutput = 0;
  }

