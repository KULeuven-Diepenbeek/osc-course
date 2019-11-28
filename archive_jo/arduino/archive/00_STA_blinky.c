
#include <avr/io.h>
#include <util/delay.h>

int main(void) {


  // init
  DDRD |= 0b00000100; 

  for/*ever*/ (;;)
  {
    // LED on
    PORTD |= 0x4;
    _delay_ms(500);

    // LED off
    PORTD &= 0xFB;
    _delay_ms(500);
  }

}
