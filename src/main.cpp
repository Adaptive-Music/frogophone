#include <Arduino.h>
#include <MIDI.h>

// Button locations
// ----------------------
// Yellow  Purple  Red
// Orange  Blue    Green


// Create a MIDI object
MIDI_CREATE_DEFAULT_INSTANCE();

// Define button pins 
const int buttonPinY = 2;  // red/green wire
const int buttonPinP = 3;  // Purple Triangle
const int buttonPinR = 4;  // Red Heart
const int buttonPinO = 5;  // Orange Prism
const int buttonPinB = 7;  // Blue Square
const int buttonPinG = 6;  // Green Circle
const int handR = A5;
const int handL = A4;

// Array to store button pins, in ascending tone order
int pins[] = {buttonPinY, buttonPinP, buttonPinR, buttonPinO, buttonPinB, buttonPinG, handR, handL};

// Array to store button states
bool oldState[] = {false, false, false, false, false, false, false, false};
bool newState[] = {false, false, false, false, false, false, false, false};

// Set initial key to C4 
int key = 60;

// Define notes to be played by each button with numbers representing how many semitones above tonic.
int notes[] = {0, 2, 4, 5, 7, 9, 11, 12};

void setup() {
  Serial.begin(19200);

  // Initialize the pushbutton pins as input
  pinMode(buttonPinY, INPUT_PULLUP);
  pinMode(buttonPinP, INPUT_PULLUP);
  pinMode(buttonPinR, INPUT_PULLUP);
  pinMode(buttonPinO, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  pinMode(buttonPinG, INPUT_PULLUP);
  pinMode(handR, INPUT_PULLUP);
  pinMode(handL, INPUT_PULLUP);

  // Start MIDI communication
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  // Read the state of the pushbutton values
  for (int i = 0; i < 8; i++) {
    if (i < 6) {
      newState[i] = digitalRead(pins[i]) == LOW;
    } else {
      newState[i] = analogRead(pins[i]) < 900;
    }
  }

  // TODO: Check for key change button presses here.


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

}
