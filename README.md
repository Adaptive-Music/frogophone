# Frogophone

Frogophone is a MIDI instrument made from a [LeapFrog Baby Tad](https://leapfrog.fandom.com/wiki/Baby_Tad) soft toy, created by [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS) at their two-day [2024 Hackathon](https://www.instagram.com/p/C-mOJVxqIss/) for one of the students of Melbourne Youth Orchestras and the University of Melbourne's [Adaptive Music Bridging Program](https://myo.org.au/programs/ensemble-program/adaptive-music-bridging-program/).

Using an Arduino Uno with a MIDI shield, it outputs MIDI signals when triggered by the eight buttons on the toy's hands and belly.

## Features

### MIDI Output
* Each of the eight buttons corresponds to a note in the selected scale, initially set to C major (C4 - C5).
* Pressing down on a button sends a **NOTE ON** MIDI message, with a velocity of 127, on channel 1.
* Releasing the button sends a corresponding **NOTE OFF** with velocity 0.
* Allows for harmonic output with multiple simultaneous button presses.

### Key and Scale Selection
* The key can be raised or lowered, either by semitone or by octave, using special 3-button combinations as outlined below.
* The scale can be cycled through major, minor and pentatonic modes, using the 4-button combination below.
* This restrict's the instrument's output to valid notes in the selected key/scale.
* No requirement for user to possess musical theory knowledge to know which buttons to press to avoid dissonant sounds - there are no incorrect notes.
* Promotes inclusion when used in ensembles as it can be set to play in tune with any song.

### Chord Mode Selection
* The instrument can be cycled between single note, triad chord, and power chord mode with the 4-button combination below.
* Allows for a wide range of harmonious, suitable
// TODO FINISH THIS!!

## Instructions

### Buttons
On startup, Frogophone is set to play the C Major scale, from C4 to C5. Refer to image below for button order.

![Button order](https://github.com/user-attachments/assets/b0775f6c-9156-48a7-ad7b-15e903892f39)  
*Button order. Image source: https://leapfrog.fandom.com/wiki/Baby_Tad?file=0C0F59E0-7E8D-4824-ADF4-F2616A6DF0B5.jpeg*

To play the C Major scale ascending, press the buttons in order from 1 to 8.

---
![Frogophone controls](https://github.com/user-attachments/assets/3d467442-fafe-4c6f-8fd6-7beb1f82d520)  
*Key, scale and chord mode controlled with simultaneous button press combinations*

## Changing key and scale

Key and scale can be changed as follows. Each successful change is signalled with an arpeggiated chord in the new key, played for one second.

To raise the key by one semitone, press the three upper buttons 1, 2 and 3 simultaneously. To lower it by one semitone, press the lower buttons 4, 5 and 6 simultaneously. Keep buttons held down for multiple steps.

To raise the key by one octave, press buttons 2, 4 and 6 simultaneously. To lower it by one octave, press the buttons 1, 3 and 5 simultaneously.

The scale can be cycled between major, minor, and blues scales by pressing buttons the four buttons 1, 3, 4 and 6 at once.

The mode can be cycled between single note, power chord, and triad chord mode by pressing any other four button combination at the same time. Each mode change is accompanied by the base note/chord being played for one second. Note: Triad chord mode does not work when blues scale is selected, and outputs single notes instead.


# Contributors

#### [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS)
Physical build, initial Arduino code.

#### [Vincent Ekpanyaskun](https://github.com/vekp),
Multiple input detection, key change, scale change, power chord mode.

####  [Warren Kuah](https://github.com/W-Kuah)
Triad chord mode.
