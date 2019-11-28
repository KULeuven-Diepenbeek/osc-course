#include <avr/io.h>

//#define FOSC 1843200 // Clock Speed
#define FOSC 16777216 // Clock Speed - 16 MHz
//#define BAUD 9600
#define BAUD 115200
#define MYUBRR (FOSC/16/BAUD-1)

void SystemUSART_Init( void );
void SystemUSART_Transmit( unsigned char data );
void SystemPrintString( const char *pcString );