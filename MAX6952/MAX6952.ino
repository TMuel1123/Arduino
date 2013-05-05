/*

MAX6952

Arduino - MAX6952

5V      - 35, 36, 37
GND     - 4, 5, 6, 18

Pin 10  - 23
Pin 11  - 20
Pin 13  - 21

I've chosen 68k for Rset and 33pF for Cset which works fine so far

*/
#include <SPI.h>

#define ActiveMode            0b00000001 // not shutdown mode
#define FastBlinkRate         0b00000100
#define GlobalBlinkEnable     0b00001000
#define GlobalBlinkTimingSync 0b00010000
#define GlobalClearDigitData  0b00100000
#define BlinkPhaseReadback    0b10000000


const int  CS_pin = 10;      // Pin for chip select

const byte NoOp              = 0x00;
const byte Intensity10       = 0x01; // see datasheet page 14 (Insesity Registers) & 17 (Table 21, 22)
const byte Intensity32       = 0x02; // see datasheet page 14 (Insesity Registers) & 17 (Table 21, 22)
const byte ScanLimit         = 0x03; // false = 2 digits; true = 4 digits
const byte Configuration     = 0x04;
const byte UserDefinedFonts  = 0x05;
//Factory reserved. Do not write to this.= 0x06;
const byte DisplayTest       = 0x07; // False = normal operation; True = test (all LED on)
const byte Digit0P0          = 0x20;
const byte Digit1P0          = 0x21;
const byte Digit2P0          = 0x22;
const byte Digit3P0          = 0x23;
const byte Digit0P1          = 0x40;
const byte Digit1P1          = 0x41;
const byte Digit2P1          = 0x42;
const byte Digit3P1          = 0x43;


void SetData(byte adr, byte data)
{
  digitalWrite(CS_pin, LOW);
  SPI.transfer(adr);
  SPI.transfer(data);
  digitalWrite(CS_pin, HIGH);
  delay(1);
}

void SetIntesity(byte Intensity) // intense can be a value between 0 and 15 (4bit)
{
 /*
 This function sets the same intensity to all digits
 The intensity is set in the both registers Intensity10 and Intensity32
 
 The lower  4 bit of Intensity10 are the intesity for Digit0
 The higher 4 bit of Intensity10 are the intesity for Digit1
 The lower  4 bit of Intensity32 are the intesity for Digit2
 The higher 4 bit of Intensity32 are the intesity for Digit3
 */
  
  Intensity = (Intensity & 0x0f) + ((Intensity & 0x0f)<<4);
  
  SetData(Intensity10, Intensity);
  SetData(Intensity32, Intensity);
}


void setup()
{
  SPI.begin();

  // Initalize chip select pins:
  pinMode(CS_pin, OUTPUT);
  pinMode(A0, OUTPUT);

  SetData(ScanLimit, true); // false = 2 digits; true = 4 digits
  SetData(Configuration, ActiveMode + GlobalBlinkEnable);
  SetIntesity(15);
  
}

void loop()
{
  SetData(DisplayTest, true);
  delay(1000);
  SetData(DisplayTest, false);
  
  
  
  SetData(Digit0P0, 'A');
  SetData(Digit1P0, 'B');
  SetData(Digit2P0, 'C');
  SetData(Digit3P0, 'D');

  SetData(Digit0P1, '1');
  SetData(Digit1P1, '2');
  SetData(Digit2P1, '3');
  SetData(Digit3P1, '4');
  
  digitalWrite(A0, true);
  while(1);
}
