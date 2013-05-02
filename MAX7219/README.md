MAX7219 / MAX7221
================
This is an easy sketch to get the MAX7219 / MAX7221 up and running


The MAX7219 was the first device which i ever have connected to a microcontroller.
It was the end of 2006 and i have started to experiment with a PIC16F84.
Due to the lag of a SPI interface in the PIC16F84 I implemented the interface by bit banging.

The MAX7219 / MAX7221 is a good start for playing with a bit banging / SPI interface because it has a verry well written datasheet and the only thing someone could stuble is that the MAX7219 / MAX7221 automatically goes into shut down mode after initial power up (See "Initial Power-Up" chapter on page 7 in the datasheet).
