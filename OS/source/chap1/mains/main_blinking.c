/*#include <avr/io.h>*/

volatile unsigned int *ADDRESS_DDR_B = (volatile unsigned int*) 0x0000024;
volatile unsigned int *ADDRESS_PORT_B = (volatile unsigned int*) 0x0000025;

void setup()
{
  *ADDRESS_DDR_B |= (1 << 5);
  // or in a shorter form:  DDRD |= PORTD6;
  // or even with helper.h: bit_set(DDRD, PORTD6);
}

void loop()
{
  int i, j;

  *ADDRESS_PORT_B = *ADDRESS_PORT_B | (1 << 5);
  //PORTB = PORTB | (1 << 5);
  for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");

  *ADDRESS_PORT_B = *ADDRESS_PORT_B & ~(1 << 5);
  //PORTB = PORTB & ~(1 << 5);
  for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");
}

int main(void) {
  setup();
  while(1) {
    loop();
  }
}
