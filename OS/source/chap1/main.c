#include <avr/io.h>

void setup()
{
  /* Arduino style:  
  pinMode(13, OUTPUT); 
  */

//  DDRD = DDRD | PORTD6; // 1: output
  DDRB |= (1 << 5);
  // or in a shorter form:  DDRD |= PORTD6;
  // or even with helper.h: bit_set(DDRD, PORTD6);

}

void loop()
{
  int i, j, k;
  /* Arduino style: 
  digitalWrite(13, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  */

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
