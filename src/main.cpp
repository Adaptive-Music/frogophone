#include <Arduino.h>
#include <vector>
#include <MIDI.h>

/*
  Frogophone
*/


/*

  Button locations

  6. LeftHand                        7. RightHand
       0. Yellow    1. Purple   2. Red
       3. Orange    4. Blue     5. Green

*/


// Create a MIDI object
MIDI_CREATE_DEFAULT_INSTANCE();

// Define button pins 
const int buttonPinY = 2;  // Yellow Star
const int buttonPinP = 3;  // Purple Triangle
const int buttonPinR = 4;  // Red Heart
const int buttonPinO = 5;  // Orange Prism
const int buttonPinB = 6;  // Blue Square
const int buttonPinG = 7;  // Green Circle
const int handL = A4;      // Night time
const int handR = A5;      // Daytime

// Array to store button pins, in ascending tone order
int pins[] = {buttonPinY, buttonPinP, buttonPinR, buttonPinO, buttonPinB, buttonPinG, handL, handR};

// Arrays to store button states
bool oldState[] = {false, false, false, false, false, false, false, false};
bool newState[] = {false, false, false, false, false, false, false, false};

// Define key - initially set to C4 (Middle C)
int key = 60;

// Define notes to be played by each button - numbers represent how many semitones above tonic.
int scales[][8] = {
  {0, 2, 4, 5, 7, 9, 11, 12},   // Major
  {0, 2, 3, 5, 7, 8, 10, 12},   // Minor
  {0, 3, 5, 7, 10, 12, 15, 17},  // Pentatonic
};

// Currently selected scale - 0: Major, 1: Minor, 2: Pentatonic
int currentScale = 0;

// Constants to define scales
const int MAJOR = 0;
const int MINOR = 1;
const int PENTATONIC = 2;

// Define current mode - 0: Single note, 1: Power chord, 2: Triad chord
int currentMode = 0;

// Number of available modes
int numModes = 3;

// Constants to define chord modes
const int SINGLE_NOTE = 0;
const int TRIAD_CHORD = 1;
const int POWER_CHORD = 2;

// Define arpeggio notes for each scale
int arpeggioNotes[][6] = {
  {-12, 0, 4, 7, 12, 16},     // Major
  {-12, 0, 3, 7, 12, 15},     // Minor
  {-12, 0, 3, 7, 10, 15},     // Pentatonic - Minor 7th
};

// Vector to store chord's notes for playing/ending
std::vector<int> notes;

void silence() {
  // Stop all currently playing notes
  // TODO: Find more efficient way to do this.
  for (int i = 0; i < 128; i++) MIDI.sendNoteOff(i, 0, 1);
}


void playArpeggio() {
  // Play arpeggiated chord to indicate change of key or scale

  int totalDuration = 1000;
  int noteDuration = 70;
  int timeElapsed = 0;

  silence();

  // Play notes of the chord, with short pause between each
  for (int i : arpeggioNotes[currentScale]) {
    int note = key + i;
    MIDI.sendNoteOn(note, 127, 1);
    delay(noteDuration);
    timeElapsed += noteDuration;
  }

  // Pause until total duration elapsed
  delay(totalDuration - timeElapsed);

  // End all chord notes
  for (int i : arpeggioNotes[currentScale]) {
    int note = key + i;
    MIDI.sendNoteOff(note, 0, 1);
  }
}


void changeKey(int newKey) {
  // Check if key within valid range
  if (newKey < 12 || newKey > 111) return;
  // Store the new key
  key = newKey;
  // Play arpeggio to indicate success
  playArpeggio();
}


void changeScale() {
  // Cycle through scale options
  currentScale = (currentScale + 1) % (sizeof(scales) / sizeof(scales[0]));
  if (currentScale == PENTATONIC && currentMode==TRIAD_CHORD) {
    currentMode = SINGLE_NOTE;
  }
  playArpeggio();  
}


void playOrEndNotes(int i, bool noteOn) {
  notes.clear();
  int rootNote = key + scales[currentScale][i];
  // Power chord: I, V, VIII (0-7-12)
  if (currentMode == POWER_CHORD) {
    notes = {rootNote - 12, rootNote - 5, rootNote};
  } 

  // Triad chords: Major (0-4-7), Minor (0-3-7), and Diminished (0-3-6)
  else if (currentMode == TRIAD_CHORD && currentScale != PENTATONIC) {
    int thirdPos = (i + 2) % 7;
    int fifthPos = (i + 4) % 7;

    int thirdNote = i > thirdPos ? key + scales[currentScale][thirdPos] + 12 : key + scales[currentScale][thirdPos];
    int fifthNote = i > fifthPos ? key + scales[currentScale][fifthPos] + 12 : key + scales[currentScale][fifthPos];
    
    notes = {rootNote - 12, thirdNote - 12, fifthNote - 12, rootNote};
  }

  // Default to single note
  else {
    notes = {rootNote};
  }
  // Play or end each note
  for (int note : notes) {
    if (noteOn) MIDI.sendNoteOn(note, 127, 1);
    else MIDI.sendNoteOff(note, 0, 1);
  } 
}


void changeMode() {
  // Cycle through chord modes. 
  // If the current scale is Pentatonic AND the current mode is single note, skip to the power chord .
  currentMode = (currentScale == PENTATONIC) && (currentMode == SINGLE_NOTE) ? POWER_CHORD : (currentMode + 1) % numModes;

  // Play a note in the new mode for one second
  silence();
  playOrEndNotes(0, true);
  delay(1000);
  playOrEndNotes(0, false);
}


void setup() {
  Serial.begin(19200);

  // Initialize the pushbutton pins as input
  for (int pin : pins) pinMode(pin, INPUT_PULLUP);

  // Start MIDI communication
  MIDI.begin(MIDI_CHANNEL_OMNI);
}


void loop() {
  int buttonCount = 0;
  // Read the state of the pushbutton values
  for (int i = 0; i < 8; i++) {
    newState[i] = digitalRead(pins[i]) == LOW;
    if (newState[i]) buttonCount++;
    }

  // Check for key/scale/mode change combo button presses
  // Four buttons - toggle between major/minor scales
  if (newState[0] && newState[2] && newState[3] && newState[5]) changeScale();
  // Other four button combo - cycle through modes
  else if (buttonCount > 3) changeMode();
  // Top three buttons - raise key by semitone
  else if (newState[0] && newState[1] && newState[2]) changeKey(key + 1);
  // Raise key by octave
  else if (newState[1] && newState[3] && newState[5]) changeKey(key + 12);
  // Bottom three buttons - lower key by semitone
  else if (newState[3] && newState[4] && newState[5]) changeKey(key - 1);
  // Lower key by octave
  else if (newState[0] && newState[2] && newState[4]) changeKey(key - 12);

  // Action button press/release if change detected
  else {
    for (int i = 0; i < 8; i++) {
    // No action required if button state unchanged
    if (oldState[i] == newState[i]) continue;
    // Update oldState with changed value
    oldState[i] = newState[i];
    // Play/end note if pressed/released
    playOrEndNotes(i, newState[i]);
    }
  }
  // Delay for debouncing
  delay(10);
}
