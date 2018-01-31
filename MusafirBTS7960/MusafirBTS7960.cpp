// ---------------------------------------------------------------------------
// Created by Maaz Mobin
// Copyright 2015 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
//
// See "MusafirBTS7960.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------

#include "MusafirBTS7960.h"
	

// ---------------------------------------------------------------------------
// MusafirBTS7960 constructor
// ---------------------------------------------------------------------------

MusafirBTS7960::MusafirBTS7960(uint8_t en1_pin, uint8_t en2_pin, uint8_t pwm1_pin, uint8_t pwm2_pin) {
	_en1_pin = en1_pin;
	_en2_pin = en2_pin;
	_pwm1_pin = pwm1_pin;
	_pwm2_pin = pwm2_pin;
	pinMode(en1_pin, OUTPUT);
	pinMode(en2_pin, OUTPUT);
	pinMode(pwm1_pin, OUTPUT);
	pinMode(pwm2_pin, OUTPUT);
	digitalWrite(en1_pin, HIGH);
	digitalWrite(en2_pin, HIGH);
}


// ---------------------------------------------------------------------------
// Standard  methods
// ---------------------------------------------------------------------------

void MusafirBTS7960::forwardPWM(uint8_t pwm) {
	_pwm = pwm;
	analogWrite(_pwm1_pin,_pwm);
	digitalWrite(_pwm2_pin , LOW);
}
void MusafirBTS7960::backwardPWM(uint8_t pwm) {
	_pwm = pwm;
	analogWrite(_pwm2_pin , _pwm);
	digitalWrite(_pwm1_pin , LOW);
}
void MusafirBTS7960::disable() {

	digitalWrite(_pwm2_pin , LOW);
	digitalWrite(_pwm1_pin , LOW);
}
void MusafirBTS7960::brakePWM(uint8_t pwm) {
	_pwm = pwm;
	analogWrite( _pwm2_pin , _pwm);
	analogWrite( _pwm1_pin , _pwm);
}