#include <Arduino.h>
#include <MIDI.h>

/*
  Button locations
  7. LeftHand            8. RightHand
  1. Yellow    2. Purple   3. Red
  4. Orange    5. Blue     6. Green
*/


// Create a MIDI object
MIDI_CREATE_DEFAULT_INSTANCE();

// Define button pins 
const int buttonPinY = 2;  // red/green wire
const int buttonPinP = 3;  // Purple Triangle
const int buttonPinR = 4;  // Red Heart
const int buttonPinO = 5;  // Orange Prism
const int buttonPinB = 6;  // Blue Square
const int buttonPinG = 7;  // Green Circle
const int handL = A4;
const int handR = A5;

// Array to store button pins, in ascending tone order
int pins[] = {buttonPinY, buttonPinP, buttonPinR, buttonPinO, buttonPinB, buttonPinG, handL, handR};

// Arrays to store button states
bool oldState[] = {false, false, false, false, false, false, false, false};
bool newState[] = {false, false, false, false, false, false, false, false};

// Set initial key to C4 (Middle C)
int key = 60;

// Store major/minor status
bool major = true;

// Define notes to be played by each button - numbers represent how many semitones above tonic.
int notes[] = {0, 2, 4, 5, 7, 9, 11, 12};


void playChord(int tonic, bool isMajor) {
  // Plays a chord for 1 second to indicate change of key or major/minor switch
  // Stop all notes
  // TODO: Find more efficient way to do this.
  for (int i = 0; i < 128; i++) MIDI.sendNoteOff(i, 0, 1);

  int chord[] = {-12, 0, isMajor ? 4 : 3, 7, 12, isMajor ? 16 : 15};
  for (int i : chord) {
    int note = key + i;
    MIDI.sendNoteOn(note, 127, 1);
  }
  delay(1000);
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
  // Play major chord for 1 second to indicate success
  playChord(key, major);
}

void scaleChange() {
  // Toggle between major and minor scales
  major = !major;
  if (major) {
    notes[2] = 4;
    notes[5] = 9;
    notes[6] = 11;
  } else {
    notes[2] = 3;
    notes[5] = 8;
    notes[6] = 10;
  }
  playChord(key, major);  
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
  // Top three buttons - raise key
  if (newState[0] && newState[1] && newState[2]) keyChange(key + 1);
  // Bottom three buttons - lower key
  else if (newState[3] && newState[4] && newState[5]) keyChange(key - 1);
  // Four buttons - toggle between major/minor
  else if (newState[0] && newState[2] && newState[3] && newState[5]) scaleChange();

  // Action button presses
  for (int i = 0; i < 8; i++) {
    // No action required if button state unchanged
    if (oldState[i] == newState[i]) continue;
    // Update oldState with changed value
    oldState[i] = newState[i];
    int note = key + notes[i];
    // Play note if pressed
    if (newState[i]) MIDI.sendNoteOn(note, 127, 1);
    // End note on release
    else MIDI.sendNoteOff(note, 0, 1); 
  }
  // Give board a rest - is this needed?
  delay(20);
}
