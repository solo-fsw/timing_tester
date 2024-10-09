

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

void SendMarker() {                        //Needed to create HW interrupt
  digitalWrite(MARKEROUT, HIGH);
  delay(1);
  digitalWrite(MARKEROUT, LOW);
}


void DumpMyInfo() {
  Serial.print("{\"Version\":\"");
  Serial.print(Version);
  Serial.print("\",");
  Serial.print("\"Serialno\":\"");
  Serial.print(Serialno);
  Serial.print("\",");
  Serial.println("\"Device\":\"UsbParMarker\"}");  
 // Serial.println("\"Device\":\"TimingTesterSA\"}");
  //Serial.write(ETX);
}

void handlecommands() {
  switch (Serial.read()) {
    case 'V':
      DumpMyInfo();
      break;
    case 'P':
      //Serial.println("Pong,TimingTesterSA");
      Serial.println("Pong,UsbParMarker");
      break;
   case 'R':
      SrboxIsr();
      break;   
    default:
      Serial.println("Unknown command");
      break;
  }
}

