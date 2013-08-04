#include <Wire.h>
#include <CAT9552.h>

#define CAT9552__ADDR0 0x60

CAT9552 leds = CAT9552(CAT9552__ADDR0);

void setup(void) {
  Wire.begin();
  TWBR = ((F_CPU / 400000L) - 16) / 2;//I2C a 400Khz
  leds.begin();
  leds.blinkRate(0,40,128);
  leds.blinkRate(1,20,128);
  delay(200);
  leds.allLedOff();
  leds.allLedOn();
  delay(1000);
  leds.allLedOff();
}


void loop(void) {
  for (byte i=0;i<16;i++){
    leds.setLed(i,1);
    leds.update();
    delay(200);
  }
  delay(1000);
  for (byte i=0;i<16;i++){
    leds.setLed(i,0);
    leds.update();
    delay(200);
  }
  delay(1000);
  for (byte i=0;i<16;i++){
    leds.setLed(i,2);
    leds.update();
    delay(200);
  }
  delay(1000);
  for (byte i=0;i<16;i++){
    leds.setLed(i,0);
    leds.update();
    delay(200);
  }
  delay(1000);
  for (byte i=0;i<16;i++){
    leds.setLed(i,3);
    leds.update();
    delay(200);
  }
  delay(1000);
  for (byte i=0;i<16;i++){
    leds.setLed(i,0);
    leds.update();
    delay(200);
  }
}
