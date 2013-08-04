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

#ifndef CAT9552_H
#define CAT9552_H

#include "Arduino.h"

/* CAT9552 ----------------------------------*/
//Command Registers
#define CAT9552_INREG0  B00000000 //[R]    Input Register 0
#define CAT9552_INREG1  B00000001 //[R]    Input Register 1
#define CAT9552_PSC0    B00000010 //[R/W]  Freq Prescaler 0
#define CAT9552_PWM0    B00000011 //[R/W]  PWM Reg 0
#define CAT9552_PSC1    B00000100 //[R/W]  Freq Prescaler 1
#define CAT9552_PWM1    B00000101 //[R/W]  PWM Reg 1

#define CAT9552_LS0     B00000110 //[R/W]  LED 0-3
#define CAT9552_LS1     B00000111 //[R/W]  LED 4-7
#define CAT9552_LS2     B00001000 //[R/W]  LED 8-11
#define CAT9552_LS3     B00001001 //[R/W]  LED 12-15
const byte ledCode_l[4] = {0,0,1,1};//left
const byte ledCode_r[4] = {1,0,0,1};//right

class CAT9552
{
private:
	byte _address;
	byte CAT9552_LEDSTATE[4];
public:
	CAT9552(const byte address);
	void begin(void);
	void blinkRate(uint8_t reg,uint8_t pfreq,uint8_t pwm);
	void update(void);
	void allLedOn(bool fupdate=1);
	void allLedOff(bool fupdate=1);
	void setLed(uint8_t led,byte state);



};

#endif	// sumoDots.h

