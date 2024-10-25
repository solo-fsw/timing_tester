# Timing Tester

**Protocol commands**
| Event | Command (decimal)	| Note |
| ------------- | ------------- | ------------- | 
| MYINFO |	80	|  |
| PING	| 81	|  |
| RESETTESTER	| 90	|  |
| TESTINGFINISHED	| 91	|  |
| DISPLAYTESTSETUP| 100	|  |
| AUDIOTESTSETUP	| 101 |  |
| SRBOXTESTSETUP	| 102	|  |
| MARKER|109	|  |
| STARTDISPLAYTEST	|110	|  |
| STARTAUDIOTEST	| 111	|  |
| STARTSRBOXTEST | 112	|  |
| STOPTESTER	| 115	|  |
| DUMPDISPLAYDATA	| 48	|  |
| DUMPAUDIODATA	| 151	|  |
| DUMPSRBOXDATA	| 152	|  |



# Timing Tester standalone 
<br/>

**Description**<br/>
The timingtester standalone is a easy to use tool for validating the monitor timing of your stimulus.
It's a drop in replacement for the [Usbparmarker](https://researchwiki.solo.universiteitleiden.nl/xwiki/wiki/researchwiki.solo.universiteitleiden.nl/view/Hardware/Markers%20and%20Events/UsbParMarker/) so no need to change your experiment. Future release it will also be possible to dropin replace the Eva.


**How to use**<br/>
If you have used the [Eprime](https://github.com/solo-fsw/eprime_package_markers), [OpenSesame](https://github.com/solo-fsw/opensesame_plugin_markers) or [Python](https://github.com/solo-fsw/python-markers) package for the Usbparmaker it's as simple to unplug the Usbparmarker and plugin the timingtester.
Hold the tester in the middle of the screen and start your script. On the display of the timingtester the test result will be displayed.
On the display you will see at the left upper corner the last measurement. V is for video, A for audio but this is not implement yet.
In the upper right corner is the last marker value is shown.

For correct timing is important that you change your slide from dark to light to activate the lightsensor. After timing testing you can always set the screen color back to the desired color.

If you are not using one of our packages for the Usbparmarker you have to look up yourself the comport in the windows devicemanager and change this in your script.

**What is a correct response time**<br/>
That's hard to say and depends on the stimules software used , hardware and your script.
Minimum response time is depending on you refresh rate. For example a 60Hz monitor has a frame duratione of 1 sec / 60Hz = 16ms. Measuring half way the screen wil give an ideal reponse of 8ms.
As seen in the example below the rest of the system eats up 3ms and the total response time wil be 11ms.
This test is done in E-prime setting the marker in the onset.
If you are in doubt, please contact labsupport the help you testing or give you advise to get the timing better.


**Advanced use**<br/>
The timingtester standalone can be placed in command mode by (re)opening the com port at 2400Baud.
The following commands are supported.
| Event | Command | Note |
| ------------- | ------------- | ------------- | 
| MYINFO |	V	|  |
| PING	| P	|  |
| RESETTESTER	| R	|  |

![Timingtester](https://github.com/user-attachments/assets/6ec28160-2cc4-406b-bf0b-176640540af7)



