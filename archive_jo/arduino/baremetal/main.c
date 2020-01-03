#include "helper.h"

#define HEARTBEAT_LED_DIR DDRD      // '1' is output
#define HEARTBEAT_LED_PORT PORTD
#define HEARTBEAT_LED_BIT PORTD7


/* PORT B7: OCR0A
 * PORT D0: OCR0B */

int main(void) {
  short a;
  const char * message = "helloworld\r\n";
  int SWprescaler = 0;

  /*
   * initialisation()
   */

  a = 0;

  // set data directions
  bit_set(HEARTBEAT_LED_DIR, BIT(HEARTBEAT_LED_BIT));
  bit_set(PORTB, BIT(PORTB7));
  bit_set(PORTD, BIT(PORTD0));

  /**
   * initialise the timer
   *   First we set the Waveform Generation Mode: WGM02 WGM01 WGM00
   *     000 => NORMAL
   *   Compare Output Mode: 
   *     COM0A1: 0
   *     COM0A0: 1  set compare output mode to toogle OC0A
   *     COM0B1: 0
   *     COM0B0: 0  set compare output mode to toogle OC0A
   *   Force Output compare
   *     FOC0A: 0
   *     FOC0B: 0
   *   ClockSelectBit:
   *     101= CLK_{IO}/1024: from prescaler
   *   
   *   TCCR0A: COM0A1 COM0A0 COM0B1 COM0B0 –      –   WGM01 WGM00
   *   TCCR0B: FOC0A  FOC0B    –      –    WGM02 CS02  CS01  CS00
   *   
   *   TCCR0A = 0100 0000 = 0x40
   *   TCCR0B = 0000 0101 = 0x05
   */
  TCCR0A =  0x40;
  TCCR0B |= 0x05;

  /**
   * TODO: readback of CLKPR first
   */

  //CKSEL ....111.
  //             1
  //SUT   ......11             
  CLKPR = 0x80; // disable prescaler
  CLKPR = 0x00;


  OCR0A = 0x10;
  OCR0B = 0xC0;
  TIMSK0 = 0x00; // no interrupt enables 



  /* USART INIT */
  USART_Init();


  /*
   * loop()
   */
  for/*ever*/ (;;)
  {
    // LED on
    bit_set(HEARTBEAT_LED_PORT, BIT(HEARTBEAT_LED_BIT));
    _delay_ms(500);

    // LED off
    bit_clear(HEARTBEAT_LED_PORT, BIT(HEARTBEAT_LED_BIT));
    _delay_ms(500);
   


    // 
    // a = (a+1)%4;
    // _delay_ms(500);*/
    // if (TCNT0 & 0x80) {
    //   bit_set(HEARTBEAT_LED_PORT, BIT(HEARTBEAT_LED_BIT));
    //   SWprescaler = (SWprescaler + 1)%4096;
    // } else  {
    //   bit_clear(HEARTBEAT_LED_PORT, BIT(HEARTBEAT_LED_BIT));
    // }

    // if( SWprescaler == 4096-1 ) {
    //   USART_Transmit('x');
    //   USART_Transmit(CLKPR);
    //   USART_Transmit(' ');
    // }

  }
}
