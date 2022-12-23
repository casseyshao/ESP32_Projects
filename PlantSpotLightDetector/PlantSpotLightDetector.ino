#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SDA 13                    //Define SDA pins
#define SCL 14                    //Define SCL pins
#define PIN_ANALOG_IN   4
#define PIN_LED         12
#define CHAN            0
#define LIGHT_MIN       372
#define LIGHT_MAX       2048

/*
 * note:If lcd1602 uses PCF8574T, IIC's address is 0x27,
 *      or lcd1602 uses PCF8574AT, IIC's address is 0x3F.
*/
LiquidCrystal_I2C lcd(0x27,16,2); 
void setup() {
  Wire.begin(SDA, SCL);           // attach the IIC pin
  lcd.init();                     // LCD driver initialization
  lcd.backlight();                // Open the backlight
  lcd.setCursor(0,0);             // Move the cursor to row 0, column 0
  lcd.print("Good plant spot?");     // The print content is displayed on the LCD
  ledcSetup(CHAN, 1000, 12);
  ledcAttachPin(PIN_LED, CHAN);
}

void loop() {
  lcd.setCursor(0,1);             // Move the cursor to row 1, column 0
  int adcVal = analogRead(PIN_ANALOG_IN); //read adc
  int pwmVal = map(constrain(adcVal, LIGHT_MIN, LIGHT_MAX), LIGHT_MIN, LIGHT_MAX, 0, 4095);  // adcVal re-map to pwmVal
  ledcWrite(CHAN, pwmVal);    // set the pulse width.
  if (pwmVal == 4095) {
    lcd.print("No, need light");
  } else {
    lcd.print("Yes           ");
  }
//  lcd.print("Counter:");          // The count is displayed every second
//  lcd.print(millis() / 1000);
//  delay(1000);
}
