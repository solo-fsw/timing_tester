/*
  HardwareTimingTester V1 Build 1 28-5-2019
  Copyright Leiden University - SOLO
  1.0 20241007  Port to standalone version, standalone version works by itself for display timing test only.
  1.1 20251215  Enabled device name TimingTesterSA
*/

/* IMPORTANT NOTE
  TXLED must be disabled to prevent Interference with PORTD, done with #UNDEF
*/
#undef TX_RX_LED_INIT  //DDRD |= (1<<5), DDRB |= (1<<0)
#undef TXLED0    //  PORTD |= (1<<5)
#undef TXLED1    //  PORTD &= ~(1<<5)
#undef RXLED0    //  PORTB |= (1<<0)
#undef RXLED1    //  PORTB &= ~(1<<0)

//include the library code:
#include "timingtester.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>

//Defines
#define NONE 0
#define VIDEO 1
#define AUDIO 2

//Version
#define Version "1.1"

//Instance
LiquidCrystal lcd(6, 12, A0, A1, A2, A3);

//Globals
byte incomingByte = 0;   // for incoming serial data
unsigned long starttime;
unsigned long stoptime;
byte TestIsRunning = NOTEST;
byte DataAvailable = 0;
unsigned int Counter = 0 ;
unsigned long AverageTotaal = 0;
unsigned long Data[50];
unsigned long maxim = 0;
unsigned long minum = -1;
String Serialno;

void setup() {
  //writeStringToEEPROM(10, "S01626");    //Use ones to program te serial number in the eeprom of the device
  Serialno = readStringFromEEPROM(10);
  lcd.begin(20, 4);
  pinMode(MARKEROUT, OUTPUT);
  pinMode(MARKER_INT, INPUT_PULLUP);
  pinMode(SRBOX_INT, INPUT_PULLUP);  //SrBox = now the reset button
  pinMode(LIGHTSENSOR_INT, INPUT_PULLUP);
  Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps
  ResetTimingTester();
  EnableMarkerInt();
  lcd.createChar(0, MicroSign); //adds µ to display character set
  delay (1000);
  EnableMarkerInt();
  //EnableAudioInt();
  EnableSrboxInt(); // Alleen nog nodig voor reset
  DisableLightsensorInt();
}


void loop() {
  if (Serial.baud() == 115200 || Serial.baud() == 9600 ) {    //data mode
    if (Serial.available() > 0) {
      SendMarker();
      incomingByte = Serial.read(); // read the incoming byte:
    }
  }
  else if (Serial.baud() == 4800) { //command mode
    if (Serial.available() > 0) {
      handlecommands();
    }
  }


  if (DataAvailable > NONE) {
    unsigned long diff;
    diff = stoptime - starttime;
    lcd.clear();
    if (DataAvailable == VIDEO) {
      lcd.print("V:");
    }
    else if  (DataAvailable == AUDIO) {
      lcd.print("A:");
    }

    lcd.print(diff / 1000);
    lcd.print(" ");
    lcd.print("ms");
    lcd.setCursor(17, 0);
    lcd.print(incomingByte);


    AverageTotaal = AverageTotaal + (diff);
    maxim = max( diff , maxim);
    minum = min( diff , minum);
    ++Counter;
    lcd.setCursor(0, 2);

    lcd.print("Max:");
    lcd.print(maxim / 1000);
    lcd.print(" Min:");
    lcd.print(minum / 1000);
    lcd.setCursor(0, 3);
    lcd.print("Avg:");
    lcd.print((AverageTotaal / Counter) / 1000);
    lcd.print(" Count:");
    lcd.print(Counter);
    //Data[Counter] = diff;  //nog naar een apparte array en kopieren na een STOP
    DataAvailable = NONE;

  }
}
