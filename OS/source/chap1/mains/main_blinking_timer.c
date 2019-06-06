#include <avr/io.h>


int main(void) {

  unsigned char x=0, y=0;

  DDRB = (1<<5);
  /* The OC0A value will not be visible on the port pin unless the data direction for the pin is set to output. */


  TCCR1A = 0x0;
  TCCR1B = 0xD;
  
  OCR1AH = 0x3F;
  OCR1AL = 0xFF;

  /*
  16 MHz / 1024 => 15625 Hz
  15625 Hz / 256 => 61.03 Hz
  */
  while(1) {

    if(TIFR1 & 0x2) {
      x = (x+1)%2;
      PORTB &= ~(1<<5); // clear the LED
      PORTB |= (x<<5); // write the LED

      TIFR1 &= 0b11111101; // clear the flag
    }
  }
}