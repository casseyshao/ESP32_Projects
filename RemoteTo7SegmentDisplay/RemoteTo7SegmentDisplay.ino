#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t recvPin = 15; // Infrared receiving pin
IRrecv irrecv(recvPin);      // Create a class object used to receive class
decode_results results;       // Create a decoding results class object

int dataPin = 18;          // Pin connected to DS of 74HC595（Pin14）
int latchPin = 2;          // Pin connected to ST_CP of 74HC595（Pin12）
int clockPin = 4;          // Pin connected to SH_CP of 74HC595（Pin11）

// Define the encoding of characters 0-F for the common-anode 7-Segment Display
byte num[] = {
  0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
  0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};

void setup()
{
  irrecv.enableIRIn();                  // Start the receiver

  // set pins to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {        // Waiting for decoding
    handleControl(results.value);       // Handle the commands from remote control
    irrecv.resume();                    // Receive the next value
  }
}

void handleControl(unsigned long value) {
  // Handle the commands
  switch (value) {
    case 0xFF6897:              // Receive the number '0'
      writeData(num[0]);        // Send data to 74HC595
      break;
    case 0xFF30CF:              // Receive the number '1'
      writeData(num[1]);        // Send data to 74HC595
      break;
    case 0xFF18E7:              // Receive the number '2'
      writeData(num[2]);        // Send data to 74HC595
      break;
    case 0xFF7A85:              // Receive the number '3'
      writeData(num[3]);        // Send data to 74HC595
      break;
    case 0xFF10EF:              // Receive the number '4'
      writeData(num[4]);        // Send data to 74HC595
      break;
    case 0xFF38C7:              // Receive the number '5'
      writeData(num[5]);        // Send data to 74HC595
      break;
    case 0xFF5AA5:              // Receive the number '6'
      writeData(num[6]);        // Send data to 74HC595
      break;
    case 0xFF42BD:              // Receive the number '7'
      writeData(num[7]);        // Send data to 74HC595
      break;
    case 0xFF4AB5:              // Receive the number '8'
      writeData(num[8]);        // Send data to 74HC595
      break;
    case 0xFF52AD:              // Receive the number '9'
      writeData(num[9]);        // Send data to 74HC595
      break;
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
