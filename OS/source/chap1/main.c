#include <avr/io.h>

void setup()
{
  DDRB |= (1 << 5);
  // or in a shorter form:  DDRD |= PORTD6;
  // or even with helper.h: bit_set(DDRD, PORTD6);
}

void loop()
{
  int i, j;

  PORTB = PORTB | (1 << 5);
  for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");

  PORTB = PORTB & ~(1 << 5);
  for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");
}

int main(void) {
  setup();
  while(1) {
    loop();
  }
}
