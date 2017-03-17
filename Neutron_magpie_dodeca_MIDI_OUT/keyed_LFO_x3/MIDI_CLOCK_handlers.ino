void HandleClock(void) {
  if (playing) {
    pulses ++;
    per16th ++;
    if (per16th > 5)
    { 
      per16th = 0;
      sixteenths ++;
      analogWrite(out2pin[6],0);
    } 
    if (per16th <= 3) {
      analogWrite(out2pin[5], 4095);
    }
    else {
      analogWrite(out2pin[5], 0);
    }   
    
    if (pulses > 23) {
      quarters ++;
      MIDIclockRate = MIDIclockRateIn;
      //      BPM = float(60000.0/MIDIclockRate);
      intBPM = (((4294967295 / MIDIclockRate) >> 10) * rateScaler) >> 10;

      //      Serial.print(MIDIclockRate);
      //      Serial.print("    ");
      //      Serial.print(intBPM);
      //      Serial.print("    ");
      //     Serial.println(per16th);
      pulses = MIDIclockRateIn = 0;
      if (quarters >= 4) {
        sixteenths = quarters = 0;
        analogWrite(out2pin[6],512);//outputting low voltage pulse at the srart of measure for scope.
        //        lfo1.phase = 0; //temp for testing reset on bar end
      }
    }
  }
}

void HandleStart() {
  pulses = 0;
  //sixteenthnotes = 0;
  playing = 1;
}

void HandleStop() {
  playing = 0; //remove this to have continuous clock pulses on dodeca after sequencer is stopped
  //digitalWriteFast(out2pin[11],LOW);  //turn pulse off when stopped even if it is in the middle of "on" cycle
}


void HandleContinue() {
  //maybe only needed for song position pointer
}

