void DumpDisplayData() {
  lcd.clear();
  lcd.print("Dumping display data");
  for (int lus = 1; lus <= Counter; lus++) {
    Serial.print("D;");
    Serial.print(lus);
    Serial.print(";");
    Serial.println(Data[lus]);
  }
  Dumpstat();
  Serial.write(ETX);
}


void DumpAudioData() {
  lcd.clear();
  lcd.print("Dumping audio data");
  for (int lus = 1; lus <= Counter; lus++) {
    Serial.print("A;");
    Serial.print(lus);
    Serial.print(";");
    Serial.println(Data[lus]);
  }
  Dumpstat();
  Serial.write(ETX);
}

void DumpSrboxData() {
  lcd.clear();
  lcd.print("Dumping SrBox data");
  for (int lus = 1; lus <= Counter; lus++) {
    Serial.print("S;");
    Serial.print(lus);
    Serial.print(";");
    Serial.println(Data[lus]);
  }
  Dumpstat();
  Serial.write(ETX);
}
void Dumpstat() {
  Serial.print("Max:");
  Serial.print(maxim);
  Serial.print(" Min:");
  Serial.print(minum);
  Serial.print(" Avg:");
  Serial.print(AverageTotaal / Counter);
}

void DumpMyInfo() {
  Serial.print("Version:");
  Serial.print(Version);
  Serial.print(" ");
  Serial.print("Serialno:");
  Serial.println(Serialno);
  Serial.write(ETX);
}

void  Ping() {
  lcd.clear();
  lcd.print("Ping received");
  Serial.print("pong");
}
