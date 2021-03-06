/*
 * FastPins.h
 * Author: Thomas Müller
 * Copyright 2013 Thomas Müller <tmuel1123 at gmail.com>
 * 
 * Some macro definitions and functions for faster pin access of the Arduino
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

// Ports
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

// Pins

#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6
#define PC7 7

#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#define PE0 0
#define PE1 1
#define PE2 2
#define PE3 3
#define PE4 4
#define PE5 5
#define PE6 6
#define PE7 7

#define PF0 0
#define PF1 1
#define PF2 2
#define PF3 3
#define PF4 4
#define PF5 5
#define PF6 6
#define PF7 7

#define PG0 0
#define PG1 1
#define PG2 2
#define PG3 3
#define PG4 4
#define PG5 5
#define PG6 6
#define PG7 7

#define PH0 0
#define PH1 1
#define PH2 2
#define PH3 3
#define PH4 4
#define PH5 5
#define PH6 6
#define PH7 7

#define PI0 0
#define PI1 1
#define PI2 2
#define PI3 3
#define PI4 4
#define PI5 5
#define PI6 6
#define PI7 7

#define PJ0 0
#define PJ1 1
#define PJ2 2
#define PJ3 3
#define PJ4 4
#define PJ5 5
#define PJ6 6
#define PJ7 7

#define PK0 0
#define PK1 1
#define PK2 2
#define PK3 3
#define PK4 4
#define PK5 5
#define PK6 6
#define PK7 7

#define PL0 0
#define PL1 1
#define PL2 2
#define PL3 3
#define PL4 4
#define PL5 5
#define PL6 6
#define PL7 7


// Constants
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
 *  * The easy pin assignment from the Arduino is not possible. Now PORT and PIN must be known
 *  * Different Arduinos (UNO, MEGA, LEONARDO...) have different pin assignments: PIN13 (LED) is PORTB Pin5 on the UNO, PORTB Pin7 on the MEGA and PORTC Pin7 on the Leonardo
 *  * Usage makes the Arduino sketch fixed to one board due to different pin assignment
 *  * If a pin is configured as input the internal pullup resitor will be activated
 * 
 * Usage:
 * digitalFastWrite(Port,Pin number, Output H/L);
 * digitalFastWrite(PC, 150);  // Sets the complete PORTC to 150 which is 0b10010110
 * digitalFastWrite(PB, 5, 1); // Sets the pin number 5 of PORTB true which is PIN13 (LED) on an Arduino UNO
 * digitalFastWrite(PB, 5, 3, 1); // Sets the PIN13 (LED) and PIN11 to a high level
 * 
 * To set an pin as an output the corrosponding bit in the DDRx (Data Direction Register) must be set to 1.
 * The initial state after power on is that all pins are configured as inputs
 * 
 * Example:
 * digitalFastWrite(DDRC, 0,1,2, OUTPUT); // sets pins 0,1 and 2 as outputs
 * digitalFastWrite(DDRC, 0,1,2, INPUT);  // sets pins 0,1 and 2 as inputs
 * 
 * The constant INPUT_PULLUP does not work with this macros!
 * 
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
 * 
 * The input and output registers are at different addresses. For this reason use PINx instead of PORTx or Px.
 * If readed from the address of PORTx the status of the internal pullup resistors is read which could be different form the real input state
 * 
 * Usage:
 * byte myVariable = digitalFastRead(PINC, 2); // Reads Pin 2 from PORTC and writes the result into the variable myVariable
 */

#define digitalFastRead(_port, _pin) ((_port) & (1<<_pin) ? (1) : (0))

/******************************************************************************
***   Functions                                                             ***
******************************************************************************/

/*
 * shiftFastOut
 * 
 * This function replaces the original shiftOut function from Arduino it is aproximately 6 times faster than the original.
 * Execution time shiftOut      126uS
 * Execution time shiftFastOut   20uS
 *
 * The price for the faster function are the following drawbacks:
 *  * The easy pin assignment from the Arduino is not possible. Now PORT and PIN must be known
 *  * Different Arduinos (UNO, MEGA, LEONARDO...) have different pin assignments: PIN13 (LED) is PORTB Pin5 on the UNO, PORTB Pin7 on the MEGA and PORTC Pin7 on the Leonardo
 *  * Usage makes the Arduino sketch fixed to one board due to different pin assignment
 *  * The port must be given as a pointer to the function
 *  * The data and the clock pin must be on the same port
 * 
 * Usage:
 * void shiftFastOut(pointerToPort, dataPin, clockPin, MSBFIRST, value) // 
 *
 * Example:
 * shiftFastOut(&PORTB, 3, 5, MSBFIRST, 'A'); // Shifts out the value of 'A' (0x41) on PORTB with pin 3 for data and pin 5 for clock. The MSB is sent first.
 */
#ifdef __cplusplus
extern "C" {
#endif

void shiftFastOut(volatile uint8_t *port, uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);

#ifdef __cplusplus
}
#endif
