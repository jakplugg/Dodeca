void FASTRUN ISR_OSC(void) {

  Ophase2[0] = Ophase2[0] + (33554432 << Ooctave[0]);
  Owave2[0] = waveLink[Ophase2[0]>> 23];
  Ophase[0] = Ophase2[0] +  (((int32_t(Owave2[0]*FMindex)))) ;
  Owave[0] = waveLink[Ophase[0]>> 23];



  if (Oactive[0]) {
    Ooutput = (Owave[0] >> 8) + (Owave[1] >> 8) + (Owave[2] >> 8);
    analogWrite(A14, (Ooutput) + 511);
  }
}

void FASTRUN ISR_OSC1(void) {

  
   Ophase2[1] = Ophase2[1] + (33554432 << Ooctave[1]);
  Owave2[1] = waveLink[Ophase2[1]>> 23];
  Ophase[1] = Ophase2[1] +  (((int32_t(Owave2[1]*FMindex)))) ;
  Owave[1] = waveLink[Ophase[1]>> 23];

  if (!Oactive[0] && Oactive[1]) {
    Ooutput = (Owave[0] >> 8) + (Owave[1] >> 8) + (Owave[2] >> 8);
    analogWrite(A14, (Ooutput) + 511);
  }
}

void FASTRUN ISR_OSC2(void) {


  Ophase2[2] = Ophase2[2] + (33554432 << Ooctave[2]);
  Owave2[2] = waveLink[Ophase2[2]>> 23];
  Ophase[2] = Ophase2[2] +  (((int32_t(Owave2[2]*FMindex)))) ;
  Owave[2] = waveLink[Ophase[2]>> 23];

  if (!Oactive[0] && !Oactive[1]) {
    Ooutput = (Owave[0] >> 8) + (Owave[1] >> 8) + (Owave[2] >> 8);
    analogWrite(A14, (Ooutput) + 511);
  }
}

