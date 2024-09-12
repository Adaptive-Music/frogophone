# Frogophone

*The world's most accessible, inclusive, and versatile MIDI amphibian*

Frogophone is a bespoke MIDI instrument made from a [LeapFrog Baby Tad](https://leapfrog.fandom.com/wiki/Baby_Tad) soft toy, created by [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS) at their two-day [2024 Hackathon](https://www.instagram.com/p/C-mOJVxqIss/) for one of the students of Melbourne Youth Orchestras and the University of Melbourne's [Adaptive Music Bridging Program (AMBP)](https://myo.org.au/programs/ensemble-program/adaptive-music-bridging-program/).

The student has a special connection with this toy, helping her to overcome her disability when using it. Taking advantage of this connection, AMBP converted it to a MIDI controller to enable her to express her creativity through it. We have built on the features of the Arduino code, in the hope that it will serve in helping her to be included in ensemble settings by making it easy for her to play in tune to any song, and that the variety of possible sounds it can produce will allow how to play any genre of her choosing. 

Using an Arduino Uno with a MIDI shield, Frogophone outputs MIDI signals when triggered by the eight buttons on the toy's hands and belly.

## Features

### MIDI Output
* Each of the eight buttons corresponds to a note in the selected scale, initially set to C major (C4 - C5).
* Pressing down on a button sends a **NOTE ON** MIDI message, with a velocity of 64, on channel 1.
* Releasing the button sends a corresponding **NOTE OFF** with velocity 0.
* Allows for polyphonic output in response to multiple simultaneous button presses.

### Key and Scale Selection
* The key can be raised or lowered, either by semitone or by octave, using special 3-button combinations as outlined below.
* The scale can be cycled through major, minor and pentatonic modes, using the 4-button combination below.
* This restrict's the instrument's output to valid notes in the selected key/scale.
* No requirement for user to possess musical theory knowledge to know which buttons to press to avoid dissonant sounds - there are no incorrect notes.
* Promotes inclusion when used in ensembles as it can be set to play in tune with any song.

### Chord Mode Selection
* The instrument can be cycled between different chord modes with the 4-button combination below, giving the instrument greater versatility.
    * **Single note mode:** Standard mode, with each button playing one note.
    * **Triad chord mode:** Plays a triad chord with each button press, creating a full, rich harmony easily.
    * **Power chord mode:** Power chords, when used with a suggested rock guitar setting on the synthesiser, can be used to produce powerful riffs.
* Constructing chords typically requires solid music theory experience to determine the correct notes that belong together. Performing a chord would also normally require a high degree of dexterity to hit multiple buttons correctly at once.
* Frogophone's chord mode makes playing chords more accessible for people with disabilities who may struggle with applying both the theoretical knowledge and physical coordination required to perform a chord, as the software works out the correct notes and plays them all at once, with just a single button press.

## Instructions

### Buttons
On startup, Frogophone is set to play the C Major scale, from C4 to C5. Refer to image below for button order.

![Diagram showing ordering of buttons on Frogophone](https://github.com/user-attachments/assets/b0775f6c-9156-48a7-ad7b-15e903892f39)  
*Button order. Image source: https://leapfrog.fandom.com/wiki/Baby_Tad?file=0C0F59E0-7E8D-4824-ADF4-F2616A6DF0B5.jpeg*

To play the C Major scale ascending, press the buttons in order from 1 to 8.

---
![Diagram showing button combinations for Frogophone controls](https://github.com/user-attachments/assets/654a3244-39cc-4430-bbb9-9041560e4e89)  
*Key, scale and chord mode controlled with simultaneous button press combinations*

## Changing key, scale and mode

Key, scale and mode can be changed as follows. For successful key and scale changes, this is signalled with an arpeggiated chord in the new key, played for one second, while chord mode changes are signalled by the base note/chord being played for one second.

The special three/four button combinations are intentionally difficult to press, and intended to be used by the user's carer. This is to minimise the chance of the user accidentally triggering an unintended key/scale/mode change.

### Key

To raise the key by one semitone, press the three upper buttons 1, 2 and 3 simultaneously. To lower it by one semitone, press the lower buttons 4, 5 and 6 simultaneously. Keep buttons held down for multiple steps.

To raise the key by one octave, press buttons 2, 4 and 6 simultaneously. To lower it by one octave, press the buttons 1, 3 and 5 simultaneously.

### Scale

The scale can be cycled between major, minor, and pentatonic scales by pressing buttons the four buttons 1, 3, 4 and 6 at once.

### Mode

The mode can be cycled between single note, triad chord, and power chord mode by pressing any other four button combination at the same time. Each mode change is accompanied by the base note/chord being played for one second. Note: Triad chord mode is not valid when pentatonic scale is selected, so it is skipped.

## How to build Frogophone

### Hardware

TODO: BERSS to write this?

### Software

Frogophone's software is built using Visual Studio Code's [PlatformIO IDE extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).

## Contributors

#### [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS)
Physical build, initial Arduino code.

#### [Vincent Ekpanyaskun](https://github.com/vekp)
Multiple input detection, polyphonic output, key change, scale change, power chord mode.

####  [Warren Kuah](https://github.com/W-Kuah)
Triad chord generator algorithm, pentatonic scale, code optimisation.
