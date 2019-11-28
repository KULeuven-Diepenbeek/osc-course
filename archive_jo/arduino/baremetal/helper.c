#include "helper.h"

void USART_Init() {
  
  /* Set baud rate */
  UBRR0H = (unsigned char)(MYUBRR>>8);
  UBRR0L = (unsigned char)MYUBRR;

  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);

  /** 
   * Set USART frame format: 8data, 2stop bit 
   *   7 UMSELn1 : USART Mode Select 1
   *   6 UMSELn0: USART Mode Select 0   => Asynchronous USART
   *   5 UPMn1:  USART Parity Mode 1
   *   4 UPMn0:  USART Parity Mode 0    => Parity Disabled
   *   3 USBSn:  USART Mode Select 0    => 2 stop bit
   *   2 UCSZn1: USART Mode Select 2
   *   1 UCSZn0: USART Mode Select 1
   *   0 UCPOLn: USART Mode Select 0    => Character size
   */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00); // Async | no parity | 2 stopbit | 8 bit
}

void USART_Transmit( unsigned char data ) {
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) ) ;

  /* Put data into buffer, sends the data */
  UDR0 = data;
}