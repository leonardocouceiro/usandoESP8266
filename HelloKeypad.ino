/* @file HelloKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates the simplest use of the matrix Keypad library.
  || #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {2, 0, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 14}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);

  pinMode(16, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
  }
  switch (key) {
    case '9':
      digitalWrite(16, HIGH);
      break;
    case '8':
      digitalWrite(16, LOW);
      break;
  }
}

