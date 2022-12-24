#include <UltrasonicSensor.h>

UltrasonicSensor ultrasonic(13, 14);
#define PIN_BUZZER 12

void setup() {
  Serial.begin(115200);
  
  int temperature = 22;
  ultrasonic.setTemperature(temperature);

  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  int distance = ultrasonic.distanceInCentimeters();
  Serial.printf("Distance: %dcm\n",distance);
  delay(300);

  if (distance < 5) {
    digitalWrite(PIN_BUZZER,HIGH);
  }else{
    digitalWrite(PIN_BUZZER,LOW);
  }
}
