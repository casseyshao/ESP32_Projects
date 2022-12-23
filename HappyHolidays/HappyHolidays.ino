int latchPin = 2;          // Pin connected to ST_CP of 74HC595（Pin12）
int clockPin = 4;          // Pin connected to SH_CP of 74HC595（Pin11）
int dataPin = 15;          // Pin connected to DS of 74HC595（Pin14）
int comPin[] = {25,26,27,14};// Common pin (anode) of 4 digit 7-segment display
int cnt = 0; // Iterate through num[]

// Define the encoding of characters 0-F of the common-anode 7-Segment Display
// Define the encoding of characters for Happy Holidays (HAPPY HOLIdAYS)
byte num[] = {0x89, 0x88, 0x8c, 0x8c, 0x91, 0xff,
              0x89, 0xc0, 0xc7, 0xf9, 0xa1, 0x88, 0x91, 0x92, 0xff};
              
void setup() {
  // set pins to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(comPin[i], OUTPUT);
  }
}

void loop() {
  int timer_cnt = 0;
  while (timer_cnt < 60) {
    for (int i = 0; i < 4; i++) {
      // Select a single 7-segment display
      electDigitalDisplay (i);
      // Send data to 74HC595
      writeData(num[(cnt+i)%15]);
      delay(5);
      // Clear the display content
      writeData(0xff);
    }
    timer_cnt++;
  }
  timer_cnt = 0;
  cnt = cnt+1;
}

void electDigitalDisplay(byte com) {
  // Close all single 7-segment display
  for (int i = 0; i < 4; i++) {
    digitalWrite(comPin[i], LOW);
  }
  // Open the selected single 7-segment display
  digitalWrite(comPin[com], HIGH);
}

void writeData(int value) {
  // Make latchPin output low level
  digitalWrite(latchPin, LOW);
  // Send serial data to 74HC595
  shiftOut(dataPin, clockPin, LSBFIRST, value);  // Make latchPin output high level
// Make latchPin output high level, then 74HC595 will update data to parallel output
  digitalWrite(latchPin, HIGH);
}
