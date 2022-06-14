/*
  HardwareTimingTester V1 Build 1 28-5-2019
  Copyright Leiden University - SOLO
1.0 Initial release
1.1 20190709  Added Pull-up for LIGHTSENSOR_INT, in prototype this was a fixed resistor
1.2 20220607  lcd.clear in the STARTxxxTEST cases causes extra delay of 2.3ms, moved this to the xxxTESTSETUP 
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
#define Version "1.2"

//Instance
LiquidCrystal lcd(6, 12, A0, A1, A2, A3);

//Globals
byte incomingByte = 0;   // for incoming serial data
unsigned long starttime;
unsigned long stoptime;
byte TestIsRunning = NOTEST;
boolean DataAvailable = false;
unsigned int Counter =0 ;
unsigned long AverageTotaal = 0;
unsigned long Data[50];
unsigned long maxim = 0;
unsigned long minum = -1;
unsigned int Serialno=100;

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
  
}

void loop() {
   if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    switch (incomingByte) {
      case 10: //Linefeed, ignore
        break;
      case 13: //Carriage return, ignore
        break;
      case 0xA0: //Ping start for SrBox search, ignore
        break;
      case 0x20: //Ping stop for SrBox search, ignore
        break;
      case MYINFO:
        DumpMyInfo();
        break;
      case PING:
        Ping();
        break;
      case RESETTESTER:
        ResetTimingTester();
        break;
      case DISPLAYTESTSETUP:
        DisplayTestSetup();
        lcd.clear();
        break;
      case AUDIOTESTSETUP:
        AudioTestSetup();
        lcd.clear();
        break;
      case SRBOXTESTSETUP:
        SrboxTestSetup();
        lcd.clear();
        break;
      case MARKER: //m marker
        SendMarker();
        break;
      case STARTDISPLAYTEST:
        EnableLightsensorInt();
        //lcd.clear();
        SendMarker();
        break;
      case STARTAUDIOTEST:
        EnableAudioInt();
        //lcd.clear();
        SendMarker();
        break;
      case STARTSRBOXTEST:
        EnableSrboxInt();
        //lcd.clear();
        //SendMarker();
        break;
      case STOPTESTER: //s stop
        DisableMarkerInt(); //moet de rest nog bij
        DisableLightsensorInt();
        break;
      case DUMPDISPLAYDATA:
        DumpDisplayData();
        break;
      case DUMPAUDIODATA:
        DumpAudioData();
        break;
      case DUMPSRBOXDATA:
        DumpSrboxData();
        break;
      case TESTINGFINISHED:
        TestingFinished();
        break;
      default:
        InvalidCommand();
        break;
    }

  }

  if (DataAvailable == true) {
    unsigned long diff;
    if (TestIsRunning == SRBOXTEST) {
      diff = starttime - stoptime;
    }
    else {
      diff = stoptime - starttime;
    }

    lcd.clear();
    lcd.print(diff);
    lcd.print(" ");
    lcd.write(byte(0));
    lcd.print("s");

    AverageTotaal = AverageTotaal + (diff);
    maxim = max( diff , maxim);
    minum = min( diff , minum);
    ++Counter;
    lcd.setCursor(0, 2);

    lcd.print("Max:");
    lcd.print(maxim);
    lcd.print(" Min:");
    lcd.print(minum);
    lcd.setCursor(0, 3);
    lcd.print("Avg:");
    lcd.print(AverageTotaal / Counter);
    lcd.print(" Count:");
    lcd.print(Counter);
    Data[Counter] = diff;  //nog naar een apparte array en kopieren na een STOP

    DataAvailable = false;
  }
}
