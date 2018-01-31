// ---------------------------------------------------------------------------
// Musafir Motor LOW Level Control Library - v1 - 29/01/2018
//
// AUTHOR/LICENSE:
// Created by Maaz Mobin
// BASE CODE COPIED FROM NEWPING LIBRARY: https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
// Copyright 2015 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
//
// LINKS:
// Project home: TODO
// Blog: TODO
//
// DISCLAIMER:
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
//
// BACKGROUND:
// TODO
//
// FEATURES:
// * TODO
//
// CONSTRUCTOR:
//   MusafirBTS7960 motor(enable_1_pin, enable_2_pin, pwm1_pin, pwm2_pin)
//
// SYNTAX:
//   motor.forwardPWM(uint8_t pwm)
//	 motor.backwardPWM(uint8_t pwm)
//   motor.disable()
//	 motor.brakePWM(uint8_t pwm)
//
// 29/01/2018 v1.0 - Initial release.
// ---------------------------------------------------------------------------

#ifndef MusafirBTS7960_h
#define MusafirBTS7960_h

#if defined (ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#if defined (__AVR__)
	#include <avr/io.h>
#endif


class MusafirBTS7960 {
	public:
		MusafirBTS7960(uint8_t en1_pin, uint8_t en2_pin, uint8_t pwm1_pin, uint8_t pwm2_pin);
		void forwardPWM(uint8_t pwm);
		void backwardPWM(uint8_t pwm);
		void disable();
		void brakePWM(uint8_t pwm);
	private:
		uint8_t _en1_pin;
		uint8_t _en2_pin;
		uint8_t _pwm1_pin;
		uint8_t _pwm2_pin;
		uint8_t _pwm;
};

#endif