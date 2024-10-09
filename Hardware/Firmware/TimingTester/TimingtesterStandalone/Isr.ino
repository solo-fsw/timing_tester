void EnableMarkerInt() {
  attachInterrupt(digitalPinToInterrupt(MARKER_INT), MarkerIsr, RISING);
}
void DisableMarkerInt() {
  detachInterrupt(digitalPinToInterrupt(MARKER_INT));
}

void EnableLightsensorInt() {
  EIFR |= (1 << INTF1);  //clear pending interrupts
  attachInterrupt(digitalPinToInterrupt(LIGHTSENSOR_INT), LightsensorIsr, FALLING);
}
void DisableLightsensorInt() {
  detachInterrupt(digitalPinToInterrupt(LIGHTSENSOR_INT));
}

void EnableAudioInt() {
  EIFR |= (1 << INTF3);  //clear pending interrupts
  attachInterrupt(digitalPinToInterrupt(SOUND_INT), AudioIsr, FALLING);
}
void DisableAudioInt() {
  detachInterrupt(digitalPinToInterrupt(SOUND_INT));
}

void EnableSrboxInt() {
  EIFR |= (1 << INT2);  //clear pending interrupts
  attachInterrupt(digitalPinToInterrupt(SRBOX_INT), SrboxIsr, RISING);
}
void DisableSrboxInt() {
  detachInterrupt(digitalPinToInterrupt(SRBOX_INT));
}

//Isr routines
void MarkerIsr() {
  EnableLightsensorInt();
  starttime = micros();
  //Serial.print("IntM ");
  //Serial.println(starttime);

}

void LightsensorIsr() {
  DisableLightsensorInt();
  stoptime = micros();
  DataAvailable = true;
  //Serial.println("IntL");
}

void AudioIsr() {
  DisableAudioInt();  //Disabele interrupt to prevent trigger on the second sinus
  stoptime = micros();
  DataAvailable = true;
  //Serial.println("IntA");
}

void SrboxIsr() { //Srbox ISR is now used for reset button
  DisableSrboxInt();
  lcd.clear();
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("Data cleared");
  lcd.setCursor(0, 2);
  lcd.print("Waiting for trigger");
  Counter = 0;
  AverageTotaal = 0;
  maxim = 0;
  minum = -1;
  delay(200);
  EnableSrboxInt();
}
