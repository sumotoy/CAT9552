#include <Arduino.h>

#include <Wire.h>
#include "CAT9552.h"

CAT9552::CAT9552(const uint8_t address){
	_address = address;
}


void CAT9552::begin(bool avoid){
	uint8_t i;
	if (!avoid){
		Wire.begin();
#if ARDUINO >= 157
		Wire.setClock(400000UL); // Set I2C frequency to 400kHz
#else
		TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
#endif
	}
	for (i=0;i<4;i++){
		_ledState[i] = 0x55;
	}
	update();
}


void CAT9552::blinkRate(uint8_t reg,uint8_t pfreq,uint8_t pwm){
	uint8_t commandRegister;//create a temp var for command
	if (reg != 0){
		commandRegister = CAT9552_PSC1;
	} else {
		commandRegister = CAT9552_PSC0;
	}
	bitSet(commandRegister,4);//set bit4=1 to enable autoincrement
	Wire.beginTransmission(_address);
	Wire.write(commandRegister);
	Wire.write(pfreq);//PSCx Frequency Prescaler 0 = 0 ->lower is faster blink ->default was 256 = 44hz
	Wire.write(pwm);//PWMx PWM Register 0 = 128 //default - 50% duty cycle
	Wire.endTransmission();
}

void CAT9552::update(void){
	uint8_t i;
	for(i = 0; i < 4; i++){
		Wire.beginTransmission(_address);
		Wire.write((0x06 + i)); 
		Wire.write(_ledState[i]);
		Wire.endTransmission();
	}
}

void CAT9552::allLedOn(bool fupdate){
	uint8_t i;
	for (i = 0; i < 4; i++){
		_ledState[i] = 0x00;
	}
	if (fupdate) update();
}

void CAT9552::allLedOff(bool fupdate){
	uint8_t i;
	for (i = 0; i < 4; i++){
		_ledState[i] = 0x55;
	}
	if (fupdate) update();
}


void CAT9552::setLed(uint8_t led,uint8_t state){
	if (state > 3) state = 3;
	if (led > 15) led = 15;
	//unsigned int idx = 0;
	uint8_t idx = led+led;
	uint8_t udx = 0;
	if (led >= 0 && led < 4){//0...3
		//idx = led+led;
		udx = 0;
	} else if (led > 3 && led < 8){//4...7
		//idx = (led+led)-8;
		idx = idx - 8;
		udx = 1;
	} else if (led > 7 && led < 12){//8...11
		//idx = (led+led)-16;
		idx = idx - 16;
		udx = 2;
	} else if (led > 11){//12...15
		//idx = (led+led)-24;
		idx = idx - 24;
		udx = 3;
	}
	bitWrite(_ledState[udx],idx,ledCode_r[state]);
	bitWrite(_ledState[udx],idx+1,ledCode_l[state]);
}