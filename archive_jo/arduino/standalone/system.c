#include "system.h"

void SystemUSART_Init( void ) {
  /* Set baud rate */
  UBRR0H = (unsigned char)(MYUBRR>>8);
  UBRR0L = (unsigned char)MYUBRR;

  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void SystemUSART_Transmit( unsigned char data ) {
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) ) ;

  /* Put data into buffer, sends the data */
  UDR0 = data;
}

//void vPrintString( const char *pcString )
void SystemPrintString( const char *pcString ) {
  short a;
 /* Write the string to stdout, using a critical section as a crude method of
 mutual exclusion. */
 /*taskENTER_CRITICAL();
 {
 printf( "%s", pcString );
 //fflush( stdout );
 }
 taskEXIT_CRITICAL();
*/

  //for(a=0;a<4;a++)
  a=1;
  //SystemUSART_Transmit((unsigned char)pcString[a]);
  SystemUSART_Transmit('W');

}
