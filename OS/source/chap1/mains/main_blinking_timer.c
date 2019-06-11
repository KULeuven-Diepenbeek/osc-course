#include <avr/io.h>

int main(void) {

  unsigned char y=0, x=0;

  DDRB = (1<<5);                    // set bit as output
  TCCR1A = 0x0;                     // set part of "mode of operation"
  TCCR1B = 0x4;                     // set part of "mode of operation" & clock prescaler

  while(1) {
                                    // read and shift MSB of 16-bit wide counter
    x = (unsigned char)((TCNT1 & 0x8000)>>15);
                                    // shift and write the LED
    PORTB = (PORTB & 0b11011111) | (x<<5);
  }
}