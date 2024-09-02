#include <Arduino.h>
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

// Store major/minor status
bool major = true;

// Define notes to be played by each button - numbers represent how many semitones above tonic.
int notes[][8] = {
  {0, 2, 4, 5, 7, 9, 11, 12},   // Major
  {0, 2, 3, 5, 7, 8, 10, 12},   // Minor
  {0, 3, 5, 6, 7, 10, 12, 15},  // Blues
};

int currentScale = 0;


void silence() {
  // Stop all currently playing notes
  // TODO: Find more efficient way to do this.
  for (int i = 0; i < 128; i++) MIDI.sendNoteOff(i, 0, 1);
}


void playArpeggio() {
  // Play arpeggiated chord for to indicate change of key or scale
  // TODO: update to handle blues

  int totalDuration = 1000;
  int noteDuration = 70;

  int timeElapsed = 0;
  int chord[] = {-12, 0, major ? 4 : 3, 7, 12, major ? 16 : 15};

  silence();

  // Play notes of the chord, with short pause between each
  for (int i : chord) {
    int note = key + i;
    MIDI.sendNoteOn(note, 127, 1);
    delay(noteDuration);
    timeElapsed += noteDuration;
  }

  // Pause until total duration elapsed
  delay(totalDuration - timeElapsed);

  // End all chord notes
  for (int i : chord) {
    int note = key + i;
    MIDI.sendNoteOff(note, 0, 1);
  }
}


void keyChange(int newKey) {
  // Check if key within valid range
  if (newKey < 12 || newKey > 115) return;
  // Store the new key
  key = newKey;
  // Play arpeggio to indicate success
  playArpeggio();
}


void scaleChange() {
  // Cycle through scale options
  currentScale = (currentScale + 1) % sizeof(notes);
  major = currentScale == 0; //TODO: Remove after updating arpeggio
  playArpeggio();  
}


void setup() {
  Serial.begin(19200);

  // Initialize the pushbutton pins as input
  for (int pin : pins) pinMode(pin, INPUT_PULLUP);

  // Start MIDI communication
  MIDI.begin(MIDI_CHANNEL_OMNI);
}


void loop() {
  // Read the state of the pushbutton values
  for (int i = 0; i < 8; i++) newState[i] = digitalRead(pins[i]) == LOW;

  // Check for key/mode change button presses
  // Top three buttons - raise key by semitone
  if (newState[0] && newState[1] && newState[2]) keyChange(key + 1);
  // Raise key by octave
  else if (newState[1] && newState[3] && newState[5]) keyChange(key + 12);
  // Bottom three buttons - lower key by semitone
  else if (newState[3] && newState[4] && newState[5]) keyChange(key - 1);
  // Lower key by octave
  else if (newState[0] && newState[2] && newState[4]) keyChange(key - 12);
  // Four buttons - toggle between major/minor scales
  else if (newState[0] && newState[2] && newState[3] && newState[5]) scaleChange();
  // TODO: Both hand buttons - cycle through modes

  // Action button presses
  else {
    for (int i = 0; i < 8; i++) {
    // No action required if button state unchanged
    if (oldState[i] == newState[i]) continue;
    // Update oldState with changed value
    oldState[i] = newState[i];
    int note = key + notes[currentScale][i];
    // Play note if pressed
    if (newState[i]) MIDI.sendNoteOn(note, 127, 1);
    // End note on release
    else MIDI.sendNoteOff(note, 0, 1); 
    }
  }
  // Give board a rest - is this needed?
  delay(20);
}
