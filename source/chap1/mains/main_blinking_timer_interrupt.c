#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {

  cli();                            // disable all interrupts

  DDRB = (1<<5);                    // set bit as output
  TCCR1A = 0x0;                     // set part of "mode of operation"
  TCCR1B = 0x4;                     // set part of "mode of operation" & clock prescaler

  TIMSK1 = 0x1;

  sei();                            // enable all interrupts

  while(1) {
  }
}

ISR(TIMER1_OVF_vect) {
  PORTB ^= (1<<5);
}