/*
 * FastPins.h
 * Author: Thomas Müller
 * Copyright 2013 Thomas Müller <tmuel1123 at gmail.com>
 * 
 * Some macro definitions for faster pin access of the Arduino
 * 
 */


/******************************************************************************
***   Include                                                               ***
******************************************************************************/

#include <avr/io.h>

#if(ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

/******************************************************************************
***   Define                                                                ***
******************************************************************************/

#define PA PORTA
#define PB PORTB
#define PC PORTC
#define PD PORTD
#define PE PORTE
#define PF PORTF
#define PG PORTG
#define PH PORTH
#define PI PORTI
#define PJ PORTJ
#define PK PORTK
#define PL PORTL

#define TRUE  1
#define FALSE 0

/******************************************************************************
***   Macro                                                                 ***
******************************************************************************/

/*
 * DigitalFastWrite
 * 
 * This macro provdies a much faster acces to the arduino output pins.
 * 
 * The price for the faster pin access are the following drawbacks:
 *  * The easy pin assignment fron the arduino is not possible. Now PORT and PIN must be known
 *  * Different Arduinos (UNO, MEGA, LEONARDO...) have different pin assignments: PIN13 (LED) is PORTB Pin5 on the UNO, PORTB Pin7 on the MEGA and PORTC Pin7 on the Leonardo
 *  * Usage makes the Arduino sketch fixed to one board due to different pin assignment
 *  * If a pin is configured as input the internal pullup resitor will be activated
 * 
 * Usage:
 * digitalFastWrite(Port,Pin number, Output H/L);
 * digitalFastWrite(PC, 150);  // Sets the complete PORTC to 214 which is 0b10010110
 * digitalFastWrite(PB, 5, 1); // Sets the pin number 5 of PORTB true which is PIN13 (LED) on an Arduino UNO
 * digitalFastWrite(PB, 5, 3, 1); // Sets the PIN13 (LED) and PIN11 to a high level
 */

#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME
#define digitalFastWrite(...) GET_MACRO(__VA_ARGS__, digitalFastWrite8, digitalFastWrite7, digitalFastWrite6, digitalFastWrite5, digitalFastWrite4, digitalFastWrite3, digitalFastWrite2, digitalFastWrite1, digitalFastWritePort)(__VA_ARGS__)
#define digitalFastWritePort(_port, _value)  (_port = _value)
#define digitalFastWrite1(_port, _pin1, _level)  (_level ? (_port |= (1<<_pin1)) : (_port &= ~(1<<_pin1)))
#define digitalFastWrite2(_port, _pin1, _pin2, _level)  (_level ? (_port |= ((1<<_pin1)|(1<<_pin2))) : (_port &= ~((1<<_pin1)|(1<<_pin2))))
#define digitalFastWrite3(_port, _pin1, _pin2, _pin3, _level)  (_level ? (_port |= ((1<<_pin1)|(1<<_pin2)|(1<<_pin3))) : (_port &= ~((1<<_pin1)|(1<<_pin2)|(1<<_pin3))))
#define digitalFastWrite4(_port, _pin1, _pin2, _pin3, _pin4, _level)  (_level ? (_port |= ((1<<_pin1)|(1<<_pin2)|(1<<_pin3)|(1<<_pin4))) : (_port &= ~((1<<_pin1)|(1<<_pin2)|(1<<_pin3)|(1<<_pin4))))
#define digitalFastWrite5(_port, _pin1, _pin2, _pin3, _pin4, _pin5, _level)  (_level ? (_port |= ((1<<_pin1)|(1<<_pin2)|(1<<_pin3)|(1<<_pin4)|(1<<_pin5))) : (_port &= ~((1<<_pin1)|(1<<_pin2)|(1<<_pin3)|(1<<_pin4)|(1<<_pin5))))
#define digitalFastWrite6(_port, _pin1, _pin2, _pin3, _pin4, _pin5, _pin6, _level)  (_level ? (_port |= ((1<<_pin1)|(1<<_pin2)|(1<<_pin3)|(1<<_pin4)|(1<<_pin5)|(1<<_pin6))) : (_port &= ~((1<<_pin1)|(1<<_pin2)|(1<<_pin3)|(1<<_pin4)|(1<<_pin5)|(1<<_pin6))))
#define digitalFastWrite7(_port, _pin1, _pin2, _pin3, _pin4, _pin5, _pin6, _pin7, _level)  (_level ? (_port |= ((1<<_pin1)|(1<<_pin2)|(1<<_pin3)|(1<<_pin4)|(1<<_pin5)|(1<<_pin6)|(1<<_pin7))) : (_port &= ~((1<<_pin1)|(1<<_pin2)|(1<<_pin3)|(1<<_pin4)|(1<<_pin5)|(1<<_pin6)|(1<<_pin7))))
#define digitalFastWrite8(_port, _pin1, _pin2, _pin3, _pin4, _pin5, _pin6, _pin7, _pin8, _level)  (_level ? (_port = 0xFF) : (_port = 0x00))

/*
 * DigitalFastRead
 */

#define digitalFastRead(_port, _pin) ((_port) & (1<<_pin) ? (1) : (0))
