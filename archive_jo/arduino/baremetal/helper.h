#include <avr/io.h>
#include <util/delay.h>

/* UART settings: Asynchronous Normal Mode */
#define FOSC 16777216 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x) (0x01 << (x))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))

void USART_Init();
void USART_Transmit( unsigned char data );
