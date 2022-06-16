# **Software: OpenSesame**
This folder contains the description of the Open Sesame timing testing task. The tests are run for a blank screen, for a picture stimulus, as well as for audio stimuli. The OpenSesame experiment can be found in the software folder: Software\OpenSesame

## **Introduction**
This document lays out how the OpenSesame can be tested in regards to timing, and what degree of accuracy can be assumed when running time critical experiments that conbtain different kinds of stimuli. The timing-testing task was built following the scheme which was used to test the timing accuracy in E-Prime 2 and E-Prime 3. 

## **Tests**
### *Slide Onset Timing Accuracy*

The timing accuracy of the onset of the slide was tested by comparing the marker sent by OpenSesame and the slide onset detected using the phototransistor of the Spider (see Hardware). White background target slides were programmed to appear after black background slides, and send a ‘writeport on onset’ signal via the printer port. The test was run with three types of slides: 

1) A black slide object with a white rectangle in the middle of the slide. 

2) A slide object with a 1600*1200 5.49 MB bitmap image. 

3) A slide object with a 600ms long wave sound file (sampling rate: 44.1 kHz, file size: 104 KB). 

The abovementioned slides were shown with durations of 1000 milliseconds. All conditions were repeated 5 times. 

## **Set up**
A phototransistor that is bilt in into the "Spider"-device recorded and saved the signals mentioned above. The light-intensity of the monitor was measured using the phototransistor, the audio signals were measured using the PC's sound output.

The timing accuracy was gauged by comparing the directly measured values, mentioned above, and the values reported  by OpenSesame, through the serial markers.

### OpenSesame Task 
The test is called *Timing_Tester_simplified.osexp* and can be found in the software/OpenSesame folder. It starts with an init python script which imports the neccesary libraries (timing_tester_lib) from a python file and defines the experiment path as a variable. Moreover, it defines the serial object and initialises the "Spider""-device. A table is created where the later obtained output can be stored. 
After the init script, the experiment contains a loop object that describes each part of the experiment with the neccessary set-up options for each test (i.e. the label, the code for dumping the data, the code for the setup which is linekd to the Spider divice and a variable whether the current test should be performed or not). From this table, the structure of the whole timing test can be controlled.
Within the loop, there is a sewuence defined which describes the trial structure for each test. It starts with a prepare screen, goes into teh test loop where an according stimulus is being selected and ends with a init script for dumping the obtained data. 
The experiment sequence itself ends with a separate init script for displaying and saving the results. First, a canvas is drawn and a keyboard is defined in oder to get an answer from the tester (to close the experiement). Thereafter, the table which was defined int eh first init script at the start is filled with the saved values and finally displayed on the previouslz created canvas. 
As the last step, the tablek is saved as a .tsv file in the same where the OpenSesame test is saved to and named *timingresults_{var.subject_nr}*.

![timingtester_sceleton](https://user-images.githubusercontent.com/99676357/174033929-3e1df8fc-d6d0-47d0-bf7f-5840dd3d156c.PNG)

### *Blank screen* 
The blank screen is a white rectangkle in the middle of the screen, drawn on a canvas and displyed for 1000 ms. 

### *Picture* 
The picture is a large image file named Hello.bpm, also displayed for 1000 ms. 

### *Audio*
The audio data is taken from the file called TestSound.wav and plays the audio once (however, the trial is repeated five times and the averge delay from these five trials is computed afterwards).

### *Video*
The video data is taken from the file called Moef.wav and plays the video once (however, the trial is repeated five times and the averge delay from these five trials is computed afterwards).The video is being de-selecterd currently (which can be done in the first loop calle dthe experiment_loop_with_all_trials) because it needs a different back-end to be played. We use the psycho backend, however, it is not compartible with the video file. The video file works only if "legacy" is the selected back-end. 

## **Results**

### *Onset Timing (Photo Transistor vs. Serial Marker)*
The Onset DIFF value is defined as: 

(Slide onset-time as measured by the transistor) – (Slide onset-time as measured via the serial port) 

The statistics are given in milliseconds. 

<<<<<<< HEAD
| Iteration     | Delay         | Label    |
| ------------- | ------------- | -------- |
| 1.0           | 17020.0       | blank    |
| 2.0           | 30308.0       | blank    | 
| 3.0           | 21548.0       | blank    |
| 4.0           | 17360.0       | blank    |
| 5.0           | 19748.        | blank    |
| 1.0           | 24110         | picture  |
| 2.0           | 256.0         | picture  |
| 3.0           | 504.0         | picture  |
| 4.0           | 37612.0       | picture  |
| 5.0           | 28620.0       | picture  |
| 1.0           | 128748.0      | audio    |
| 2.0           | 136444.0      | audio    |
| 3.0           | 137808.0      | audio    |
| 4.0           | 132512.0      | audio    |
| 5.0           | 140188.0      | audio    |



=======
>>>>>>> c751ef4aa7cc0b182d0e3f24ac129695b6117ded

