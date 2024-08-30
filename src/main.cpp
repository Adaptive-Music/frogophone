#include <Arduino.h>
#include <MIDI.h>

// Button locations

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

// Define LED pins 
const int ledPinY = 8;    // 
const int ledPinP = 9;    // Purple Triangle
const int ledPinR = 10;    // Red Heart
const int ledPinO = 11;    // Orange Prism
const int ledPinB = 13;   // Blue Square
const int ledPinG = 12;   // Green Circle

// Variables for reading the pushbutton status
int buttonStateY = 0;
int buttonStateP = 0;
int buttonStateR = 0;
int buttonStateO = 0;
int buttonStateB = 0;
int buttonStateG = 0;
int handRVal = 0;
int handLVal = 0;

void setup() {
  Serial.begin(19200);
  // Initialize the LED pins as output
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinP, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinO, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);

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
  // buttonStateY = digitalRead(buttonPinY);
  // buttonStateP = digitalRead(buttonPinP);
  // buttonStateR = digitalRead(buttonPinR);
  // buttonStateO = digitalRead(buttonPinO);
  // buttonStateB = digitalRead(buttonPinB);
  // buttonStateG = digitalRead(buttonPinG);
  // 
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


//   // Check if the pushbutton is pressed. If it is, the buttonState is LOW:
//   // Yellow Button
//   if (buttonStateY == LOW) {
//     MIDI.sendNoteOn(60, 127, 1);  // Send MIDI Note On for C4
//     while (buttonStateY == LOW) {
//       digitalWrite(ledPinY, LOW);
//       buttonStateY = digitalRead(buttonPinY);
//   }
//   } else {
//     digitalWrite(ledPinY, HIGH);   // LED off
//     MIDI.sendNoteOff(60, 0, 1);   // Send MIDI Note Off for C4
//   }
// //Purple Button
//   if (buttonStateP == LOW) {
//     MIDI.sendNoteOn(62, 127, 1);  // D4
//     while (buttonStateP == LOW) {
//       digitalWrite(ledPinP, LOW);
//       buttonStateP = digitalRead(buttonPinP);
//     }
//   }
//   else {
//     digitalWrite(ledPinP, HIGH);
//     MIDI.sendNoteOff(62, 0, 1);
//   }
// //Red Button
//   if (buttonStateR == LOW) {
//     MIDI.sendNoteOn(64, 127, 1);  // E4
//     while (buttonStateR == LOW) {
//       digitalWrite(ledPinR, LOW);
//       buttonStateR = digitalRead(buttonPinR);
//     }
//   } 
//   else {
//     digitalWrite(ledPinR, HIGH);
//     MIDI.sendNoteOff(64, 0, 1);
//   }
// // Orange Button
//   if (buttonStateO == LOW) {
//     MIDI.sendNoteOn(65, 127, 1);  // F4
//     while (buttonStateO == LOW) {
//       digitalWrite(ledPinO, HIGH);
//       buttonStateO = digitalRead(buttonPinO);
//     }
//   } 
//   else {
//     digitalWrite(ledPinO, LOW);
//     MIDI.sendNoteOff(65, 0, 1);
//   }
// //Blue Button
//   if (buttonStateB == LOW) {
//     MIDI.sendNoteOn(67, 127, 1);  // G4
//     while (buttonStateB == LOW) {
//       digitalWrite(ledPinB, LOW);
//       buttonStateB = digitalRead(buttonPinB);
//     }
//   } 
//   else {
//     digitalWrite(ledPinB, HIGH);
//     MIDI.sendNoteOff(67, 0, 1);
//   }
  
// //Green Button
//   if (buttonStateG == LOW) {
//     MIDI.sendNoteOn(69, 127, 1);  // A4
//     while (buttonStateG == LOW) {
//       digitalWrite(ledPinG, LOW);
//       buttonStateG = digitalRead(buttonPinG);
//     }
//   } 
//   else {
//     digitalWrite(ledPinG, HIGH);
//     MIDI.sendNoteOff(69, 0, 1);
//   }


// //HAND RIGHT 
// handRVal = analogRead(handR);
//  if (handRVal<900)
//  {
//    MIDI.sendNoteOn(71, 127, 1);  // B4
//   while (handRVal<900) {
//     handRVal = analogRead(handR);
//     }
//  }
//   else {
//     MIDI.sendNoteOff(71, 127, 1); 
//   }

// //HAND LEFT
// handLVal= analogRead(handL);
//  if (handLVal<900)
//  {
//    MIDI.sendNoteOn(72, 127, 1);  // C5
//     while (handLVal<900) {
//       handLVal= analogRead(handL);
//     }
//  }
//    else {
//     MIDI.sendNoteOff(72, 127, 1); 
//   }



}
