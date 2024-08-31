# Frogophone

Frogophone is a MIDI instrument made from a LeapFrog Baby Tad soft toy, created by [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS) at their [2024 Hackathon](https://www.instagram.com/p/C-mOJVxqIss/) for the [Adaptive Music Bridging Program](https://myo.org.au/programs/ensemble-program/adaptive-music-bridging-program/). It uses an Arduino Uno with a MIDI shield.


# Instructions

## Buttons
On startup, Frogophone is set to play the C Major scale, from C4 to C5. Refer to image below for button order.

![1 (1)](https://github.com/user-attachments/assets/b0775f6c-9156-48a7-ad7b-15e903892f39)  
*Button order on toy. Image source: https://leapfrog.fandom.com/wiki/Baby_Tad?file=0C0F59E0-7E8D-4824-ADF4-F2616A6DF0B5.jpeg*

To play the C Major scale ascending, press the buttons in order from 0 to 7.

## Changing key
The key can be raised or lowered by one semitone at a time. To raise the key, press the three upper buttons 1, 2 and 3 simultaneously. To lower, press the lower buttons 4, 5 and 6 simultaneously. On key change, Frogophone will output a major chord in the new key for one second to indicate a successful key change. 


# Contributors

#### [The Biomedical Engineering RMIT Student Society (BERSS)](https://rusu.rmit.edu.au/Clubs/BERSS)
Physical build and initial Arduino code.

#### [Vincent Ekpanyaskun](https://github.com/vekp)
