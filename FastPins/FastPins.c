/*
 * Filename.c
 * Author: Thomas Müller
 * Copyright 2013 Thomas Müller <tmuel1123 at gmail.com>
 */


/******************************************************************************
***   Include                                                               ***
******************************************************************************/

#include <FastPins.h>

/*#if(ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif*/


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
 
void shiftFastOut(volatile uint8_t *port, uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
  uint8_t compareBit = bitOrder == MSBFIRST ? 0b10000000 : 0b00000001;
  
  // for (uint8_t i = 0; i < 8; i++) 
  // Replaced the "for" loop with a "while" condition
  // because compareBit will be valid for exactly 8 times
  // until the 1 is shifted out of the byte.
  while(compareBit)
  {
    // Set DATA pin
    if (value & compareBit)
      digitalFastWrite(*port,dataPin,1);
    else
      digitalFastWrite(*port,dataPin,0);

    // Shift compareBit depending on MSB or LSB first      
    compareBit = bitOrder == MSBFIRST ? compareBit >> 1 : compareBit << 1;

    // CLOCK pulse
    digitalFastWrite(*port,clockPin,1);
    digitalFastWrite(*port,clockPin,0);
  }
}
