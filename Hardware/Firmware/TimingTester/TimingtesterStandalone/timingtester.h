
//Hw
#define MARKEROUT 4
#define MARKER_INT 3  //Int0
#define LIGHTSENSOR_INT 2  //Int1
#define SOUND_INT 1  //Int3
#define SRBOX_INT 0  //Int2
#define NOTEST 0
#define DISPLAYTEST 1
#define AUDIOTEST 2
#define SRBOXTEST 3



//Constante
#define MYINFO 80
#define PING 81
#define RESETTESTER 90
#define TESTINGFINISHED 91
#define DISPLAYTESTSETUP 100
#define AUDIOTESTSETUP 101
#define SRBOXTESTSETUP 102
#define MARKER 109
#define STARTDISPLAYTEST 110
#define STARTAUDIOTEST 111
#define STARTSRBOXTEST 112
#define STOPTESTER 115
#define DUMPDISPLAYDATA 48
#define DUMPAUDIODATA 151
#define DUMPSRBOXDATA 152
#define STX 0x02 //start of text
#define ETX 0x03 //end of text

byte MicroSign[] = { //µ
  B00000,
  B00000,
  B00000,
  B10010,
  B10010,
  B10010,
  B11100,
  B10000

};
