void DisplayTestSetup() {
  DisableMarkerInt();
  DisableLightsensorInt();
  lcd.clear();
  lcd.print("Display Test");
  lcd.setCursor(0, 1);
  lcd.print("Waiting for trigger");
  Counter = 0;
  AverageTotaal = 0;
  maxim = 0;
  minum = -1;
  TestIsRunning = DISPLAYTEST;
  EnableMarkerInt();
  EnableLightsensorInt();
}

void AudioTestSetup() {
  DisableMarkerInt();
  DisableAudioInt();
  lcd.clear();
  lcd.print("Audio Test");
  lcd.setCursor(0, 1);
  lcd.print("Waiting for trigger");
  Counter = 0;
  AverageTotaal = 0;
  maxim = 0;
  minum = -1;
  TestIsRunning = AUDIOTEST;
  EnableMarkerInt();
  EnableAudioInt();
}

void SrboxTestSetup() {
  DisableMarkerInt();
  DisableSrboxInt();
  lcd.clear();
  lcd.print("Srbox Test");
  lcd.setCursor(0, 1);
  lcd.print("Waiting for trigger");
  Counter = 0;
  AverageTotaal = 0;
  maxim = 0;
  minum = -1;
  TestIsRunning = SRBOXTEST;
  EnableMarkerInt();
  EnableSrboxInt();
}

//void SsartAudioTest() {
//  lcd.clear();
//  lcd.print("Audio Test");
//  lcd.setCursor(0, 1);
//  lcd.print("Waiting for trigger");
//  Counter = 0;
//  AverageTotaal = 0;
//  TestIsRunning = AUDIOTEST;
//  EnableMarkerInt();
//  EnableAudioInt();
//}


void ResetTimingTester() {
  Serialno = 100 + EEPROM.read(20);
  lcd.clear();
  lcd.print(" * TIMING TESTER *");
  lcd.setCursor(0, 1);
  lcd.print(" STANDALONE VERSION ");
  lcd.setCursor(0, 2);
  lcd.print("Version: ");
  lcd.print(Version);
  lcd.setCursor(0, 3);
  lcd.print("Serial#: ");
  lcd.print(Serialno);
  DisableMarkerInt();
  DisableLightsensorInt();
  DisableAudioInt();
  DisableSrboxInt();
}

void SendMarker() {
  digitalWrite(MARKEROUT, HIGH);
  delay(1);
  digitalWrite(MARKEROUT, LOW);
}

void InvalidCommand() {
  lcd.clear();
  lcd.print("Invalid command");
  lcd.setCursor(0, 1);
  lcd.print("received!");
}

void TestingFinished() {
  DisableMarkerInt();
  DisableLightsensorInt();
  DisableAudioInt();
  DisableSrboxInt();
  lcd.clear();
  lcd.print("Testing Finished");
  lcd.setCursor(0, 2);
  lcd.print("Have a nice day");
}
