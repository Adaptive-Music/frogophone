# Frogophone

Frogophone is a MIDI instrument made from a [LeapFrog Baby Tad](https://leapfrog.fandom.com/wiki/Baby_Tad) soft toy, created by [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS) at their [2024 Hackathon](https://www.instagram.com/p/C-mOJVxqIss/) for one of the students of Melbourne Youth Orchestras and the University of Melbourne's [Adaptive Music Bridging Program](https://myo.org.au/programs/ensemble-program/adaptive-music-bridging-program/).

Using an Arduino Uno with a MIDI shield, it outputs MIDI signals when triggered by the eight buttons on the toy's hands and chest.


## Instructions

### Buttons
On startup, Frogophone is set to play the C Major scale, from C4 to C5. Refer to image below for button order.

![Button order](https://github.com/user-attachments/assets/b0775f6c-9156-48a7-ad7b-15e903892f39)  
*Button order. Image source: https://leapfrog.fandom.com/wiki/Baby_Tad?file=0C0F59E0-7E8D-4824-ADF4-F2616A6DF0B5.jpeg*

To play the C Major scale ascending, press the buttons in order from 1 to 8.

---

![Controls](https://github.com/user-attachments/assets/42cf0422-3059-4f2b-85b6-b1032552f4bf)  
*Mode, key and scale controlled with simultaneous button presses*

## Changing key and scale

Key and scale can be changed as follows. With each successful change, a chord in the new key is played for one second.

To raise the key by one semitone, press the three upper buttons 1, 2 and 3 simultaneously. To lower it by one semitone, press the lower buttons 4, 5 and 6 simultaneously. Keep buttons held down for multiple steps.

The scale can be toggled between major and minor by pressing buttons 1, 3, 4 and 6 at once.


# Contributors

#### [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS)
Physical build and initial Arduino code.

#### [Vincent Ekpanyaskun](https://github.com/vekp)
