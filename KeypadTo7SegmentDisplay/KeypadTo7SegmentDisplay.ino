#include <Keypad.h>

// define the symbols on the buttons of the keypad
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[4] = {14, 27, 26, 25}; // connect to the row pinouts of the keypad
byte colPins[4] = {13, 21, 22, 23};   // connect to the column pinouts of the keypad

// initialize an instance of class NewKeypad
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

int dataPin = 15;          // Pin connected to DS of 74HC595（Pin14）
int latchPin = 2;          // Pin connected to ST_CP of 74HC595（Pin12）
int clockPin = 4;          // Pin connected to SH_CP of 74HC595（Pin11）

// Define the encoding of characters 0-F for the common-anode 7-Segment Display
byte num[] = {
  0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
  0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};

void setup() {
  Serial.begin(115200); // Initialize the serial port and set the baud rate to 115200
  Serial.println("ESP32 is ready!");  // Print the string "UNO is ready!"

  // set pins to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // Get the character input
  char keyPressed = myKeypad.getKey();
  // If there is a character input, sent it to the serial port
  if (keyPressed) {
    Serial.println(keyPressed);

    // Use Hashtable for cleaner code (keyPressed is the key)
    if (keyPressed == '0') {
      writeData(num[0]);
    } else if (keyPressed == '1') {
      writeData(num[1]);
    } else if (keyPressed == '2') {
      writeData(num[2]);
    } else if (keyPressed == '3') {
      writeData(num[3]);
    } else if (keyPressed == '4') {
      writeData(num[4]);
    } else if (keyPressed == '5') {
      writeData(num[5]);
    } else if (keyPressed == '6') {
      writeData(num[6]);
    } else if (keyPressed == '7') {
      writeData(num[7]);
    } else if (keyPressed == '8') {
      writeData(num[8]);
    } else if (keyPressed == '9') {
      writeData(num[9]);
    } else if (keyPressed == 'A') {
      writeData(num[10]);
    } else if (keyPressed == 'B') {
      writeData(num[11]);
    } else if (keyPressed == 'C') {
      writeData(num[12]);
    } else if (keyPressed == 'D') {
      writeData(num[13]);
    } else {
      writeData(0xff);
    }
  }
}

void writeData(int value) {
  // Make latchPin output low level
  digitalWrite(latchPin, LOW);
  // Send serial data to 74HC595
  shiftOut(dataPin, clockPin, LSBFIRST, value);
  // Make latchPin output high level, then 74HC595 will update the data to parallel output
  digitalWrite(latchPin, HIGH);
}
