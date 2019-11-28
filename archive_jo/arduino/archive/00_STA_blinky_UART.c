
#include <avr/io.h>
#include <util/delay.h>

//#define FOSC 1843200 // Clock Speed16777216
#define FOSC 16777216 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init_bis( unsigned int ubrr );
void USART_Transmit( unsigned char data );

int main(void) {
  short a;
  const char * message = "helloworld\r\n";

  // init
  DDRD |= 0x04; 
  USART_Init_bis(MYUBRR);

  for/*ever*/ (;;)
  {
    // LED on
    PORTD |= 0x4;
    _delay_ms(500);

    // LED off
    PORTD &= 0xFB;
    _delay_ms(500);

    for(a=0;a<12;a++)
      USART_Transmit(message[a]);
  }
}

void USART_Init_bis( unsigned int ubrr ) {
  
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data ) {
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) ) ;

  /* Put data into buffer, sends the data */
  UDR0 = data;
}
