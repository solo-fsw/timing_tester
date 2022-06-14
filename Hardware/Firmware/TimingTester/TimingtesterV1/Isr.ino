void EnableMarkerInt() {
  attachInterrupt(digitalPinToInterrupt(MARKER_INT), MarkerIsr, RISING);
}
void DisableMarkerInt() {
  detachInterrupt(digitalPinToInterrupt(MARKER_INT));
}

void EnableLightsensorInt(){
  EIFR |= (1 << INTF1);  //clear pending interrupts
  attachInterrupt(digitalPinToInterrupt(LIGHTSENSOR_INT), LightsensorIsr, FALLING);
}
void DisableLightsensorInt() {
  detachInterrupt(digitalPinToInterrupt(LIGHTSENSOR_INT));
}

void EnableAudioInt(){
  EIFR |= (1 << INTF3);  //clear pending interrupts
  attachInterrupt(digitalPinToInterrupt(SOUND_INT), AudioIsr, FALLING);
}
void DisableAudioInt() {
  detachInterrupt(digitalPinToInterrupt(SOUND_INT));
}

void EnableSrboxInt(){
  EIFR |= (1 << INT2);  //clear pending interrupts
  attachInterrupt(digitalPinToInterrupt(SRBOX_INT),SrboxIsr, RISING);
}
void DisableSrboxInt() {
  detachInterrupt(digitalPinToInterrupt(SRBOX_INT));
}

//Isr routines
void MarkerIsr() {
  starttime = micros();
  //Serial.print("IntM ");
  //Serial.println(starttime);
 if (TestIsRunning == SRBOXTEST){
   DataAvailable = true;
 }
}

void LightsensorIsr(){
  DisableLightsensorInt();
  stoptime =micros();
  DataAvailable = true;
 // Serial.println("IntL");
}

void AudioIsr(){
  DisableAudioInt();  //Disabele interrupt to prevent trigger on the second sinus
  stoptime =micros();
  DataAvailable = true;
  //Serial.println("IntA");
}

void SrboxIsr(){
  DisableSrboxInt();
  stoptime =micros();
  //Serial.print("IntS ");
  //Serial.println(stoptime);
  //DataAvailable = true;
}
