/*
  HardwareTimingTester V1 Build 1 28-5-2019
  Copyright Leiden University - SOLO
  1.0 Initial release
  1.1 20190709  Added Pull-up for LIGHTSENSOR_INT, in prototype this was a fixed resistor
  1.2 20220607  lcd.clear in the STARTxxxTEST cases causes extra delay of 2.3ms, moved this to the xxxTESTSETUP
  5.0 20241007  Port to standalone version, standalone version works by itself for display timing test only.
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

//Version
#define Version "5.0"

//Instance
LiquidCrystal lcd(6, 12, A0, A1, A2, A3);

//Globals
byte incomingByte = 0;   // for incoming serial data
unsigned long starttime;
unsigned long stoptime;
byte TestIsRunning = NOTEST;
boolean DataAvailable = false;
unsigned int Counter = 0 ;
unsigned long AverageTotaal = 0;
unsigned long Data[50];
unsigned long maxim = 0;
unsigned long minum = -1;
unsigned int Serialno = 100;

void setup() {
  lcd.begin(20, 4);
  pinMode(MARKEROUT, OUTPUT);
  pinMode(MARKER_INT, INPUT_PULLUP);
  pinMode(SRBOX_INT, INPUT_PULLUP);
  pinMode(LIGHTSENSOR_INT, INPUT_PULLUP);
  Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps
  ResetTimingTester();
  EnableMarkerInt();
  lcd.createChar(0, MicroSign);
  //EEPROM.write(20, 1); //Only need to be enable when flashing for the first time to wite serial# to eeprom
  delay (1000);
  EnableMarkerInt();
  DisableLightsensorInt();
}


void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    SendMarker();
  }

  if (DataAvailable == true) {
    unsigned long diff;

    diff = stoptime - starttime;


    lcd.clear();
    lcd.print(diff/1000);
    lcd.print(" ");
    //lcd.write(byte(0));
    lcd.print("ms");

    AverageTotaal = AverageTotaal + (diff);
    maxim = max( diff , maxim);
    minum = min( diff , minum);
    ++Counter;
    lcd.setCursor(0, 2);

    lcd.print("Max:");
    lcd.print(maxim/1000);
    lcd.print(" Min:");
    lcd.print(minum/1000);
    lcd.setCursor(0, 3);
    lcd.print("Avg:");
    lcd.print((AverageTotaal / Counter)/1000);
    lcd.print(" Count:");
    lcd.print(Counter);
    Data[Counter] = diff;  //nog naar een apparte array en kopieren na een STOP

    DataAvailable = false;
  }
}