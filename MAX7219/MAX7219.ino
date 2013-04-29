/*

MAX7219

The datasheet for the MAX7219 can be found here:
http://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf

Arduino - MAX7219

5V      - Pin 19
GND     - Pin 4 + Pin 9

Pin 10  - Pin 12 (LOAD /CS)
Pin 11  - Pin  1 (DIN)
Pin 13  - Pin 13 (CLK)


*/
#include <SPI.h>

const int CS_pin = 10; // Pin for chip select

//MAX7219/MAX7221's memory register addresses:
// See Table 2 on page 7 in the Datasheet

const byte NoOp        = 0x00;
const byte Digit0      = 0x01;
const byte Digit1      = 0x02;
const byte Digit2      = 0x03;
const byte Digit3      = 0x04;
const byte Digit4      = 0x05;
const byte Digit5      = 0x06;
const byte Digit6      = 0x07;
const byte Digit7      = 0x08;
const byte DecodeMode  = 0x09;
const byte Intensity   = 0x0A;
const byte ScanLimit   = 0x0B;
const byte ShutDown    = 0x0C;
const byte DisplayTest = 0x0F;


void setup()
{
  // The MAX7219 has officially no SPI / Microwire support like the MAX7221 but the
  // serial interface is more or less the same like a SPI connection
  SPI.begin();

  // initalize chip select pins:
  pinMode(CS_pin, OUTPUT);
  
  SetDecodeMode(0);
  SetScanLimit(7);
  SetIntensity(0x05);
  SetShutDown(false);
}

void SetShutDown(byte Mode) { SetData(ShutDown, !Mode); }
void SetScanLimit(byte Digits) { SetData(ScanLimit, Digits); }
void SetIntensity(byte intense) { SetData(Intensity, intense); }
void SetDecodeMode(byte Mode) { SetData(DecodeMode, Mode); }

void SetData(byte adr, byte data)
{
  digitalWrite(CS_pin, LOW);
  SPI.transfer(adr);
  SPI.transfer(data);
  digitalWrite(CS_pin, HIGH);
  delay(1);
}

void loop()
{

  unsigned int rowBuffer[]=
  {
    0b0010000010000000,
    0b0001000100000000,
    0b0011111110000000,
    0b0110111011000000,
    0b1111111111100000,
    0b1011111110100000,
    0b1010000010100000,
    0b0001101100000000
  };

  while(1)
  {
    for (int shiftCounter = 0; 15 >= shiftCounter; shiftCounter++)
    {
      for (byte rowCounter = 0; 7 >= rowCounter; rowCounter++)
      {
        rowBuffer[rowCounter] = ((rowBuffer[rowCounter] & 0x8000)?0x01:0x00) | (rowBuffer[rowCounter] << 1);
        SetData(rowCounter+1, byte(rowBuffer[rowCounter]));
      }    
      delay(180);
    }
  }
}
