/*
                               _                
 ___  _   _  _ __ ___    ___  | |_  ___   _   _ 
/ __|| | | || '_ ` _ \  / _ \ | __|/ _ \ | | | |
\__ \| |_| || | | | | || (_) || |_| (_) || |_| |
|___/ \__,_||_| |_| |_| \___/  \__|\___/  \__, |
                                          |___/ 
CAT9552 Library
----------------------------------------
A fast C library for CAT9552 chip drived with I2C
version 2.0
coded by Max MC Costa
--------------------------------------------------------
Library works with most arduino compatible processors and teensy3
BUGLIST

*/
#include <Arduino.h>

#include <Wire.h>
#include "CAT9552.h"

CAT9552::CAT9552(const byte address)
{
	_address = address;
}


void CAT9552::begin(void)
{
	for (byte i=0;i<4;i++){
		CAT9552_LEDSTATE[i] = 0x55;
	}
}


void CAT9552::blinkRate(uint8_t reg,uint8_t pfreq,uint8_t pwm){
  uint8_t commandRegister;//create a temp var for command
  if (reg == 0){
    commandRegister = CAT9552_PSC0;
  } 
  else {
    commandRegister = CAT9552_PSC1;
  }
  bitSet(commandRegister,4);//set bit4=1 to enable autoincrement
  Wire.beginTransmission(_address);
#if ARDUINO < 100
  Wire.send(commandRegister);
  Wire.send(pfreq);//PSCx Frequency Prescaler 0 = 0 ->lower is faster blink ->default was 256 = 44hz
  Wire.send(pwm);//PWMx PWM Register 0 = 128 //default - 50% duty cycle
#else
  Wire.write(commandRegister);
  Wire.write(pfreq);//PSCx Frequency Prescaler 0 = 0 ->lower is faster blink ->default was 256 = 44hz
  Wire.write(pwm);//PWMx PWM Register 0 = 128 //default - 50% duty cycle
#endif
  Wire.endTransmission();
}

void CAT9552::update(void){
  for(byte i = 0; i < 4; i++){
    Wire.beginTransmission(_address);
#if ARDUINO < 100
    Wire.send((0x06 + i)); 
    Wire.send(CAT9552_LEDSTATE[i]);
#else
    Wire.write((0x06 + i)); 
    Wire.write(CAT9552_LEDSTATE[i]);
#endif
    Wire.endTransmission();
  }
}

void CAT9552::allLedOn(bool fupdate){
  for(byte i = 0; i < 4; i++){
    CAT9552_LEDSTATE[i] = 0x00;
  }
  if (fupdate) update();
}

void CAT9552::allLedOff(bool fupdate){
  for(byte i = 0; i < 4; i++){
    CAT9552_LEDSTATE[i] = 0x55;
  }
  if (fupdate) update();
}


void CAT9552::setLed(uint8_t led,byte state){
  unsigned int idx = 0;
  byte udx = 0;
  byte go = false;
  if (led < 16 && state < 4){
    if (led >= 0 && led < 4){//0,1,2,3
      idx = led+led;
      udx = 0;
      go = true;
    } 
    else if (led > 3 && led < 8){//4,5,6,7
      idx = (led+led)-8;
      udx = 1;
      go = true;
    } 
    else if (led > 7 && led < 12){//8,9,10,11
      idx = (led+led)-16;
      udx = 2;
      go = true;
    } 
    else if (led > 11 && led < 16){//12,13,14,15
      idx = (led+led)-24;
      udx = 3;
      go = true;
    }
    if (go){
      bitWrite(CAT9552_LEDSTATE[udx],idx,ledCode_r[state]);
      bitWrite(CAT9552_LEDSTATE[udx],idx+1,ledCode_l[state]);
    }
  }
}