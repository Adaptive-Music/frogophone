# Frogophone

Frogophone is a MIDI instrument made from a [LeapFrog Baby Tad](https://leapfrog.fandom.com/wiki/Baby_Tad) soft toy, created by [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS) at their [2024 Hackathon](https://www.instagram.com/p/C-mOJVxqIss/) for one of the students of Melbourne Youth Orchestras and the University of Melbourne's [Adaptive Music Bridging Program](https://myo.org.au/programs/ensemble-program/adaptive-music-bridging-program/).

Using an Arduino Uno with a MIDI shield, it outputs MIDI signals when triggered by the eight buttons on the toy's hands and belly.


## Instructions

### Buttons
On startup, Frogophone is set to play the C Major scale, from C4 to C5. Refer to image below for button order.

![Button order](https://github.com/user-attachments/assets/b0775f6c-9156-48a7-ad7b-15e903892f39)  
*Button order. Image source: https://leapfrog.fandom.com/wiki/Baby_Tad?file=0C0F59E0-7E8D-4824-ADF4-F2616A6DF0B5.jpeg*

To play the C Major scale ascending, press the buttons in order from 1 to 8.

---
![Frogophone controls](https://github.com/user-attachments/assets/26b78b6e-a3fa-4598-8008-aa21ee4aed6e)  
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