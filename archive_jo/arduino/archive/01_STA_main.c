#include <util/delay.h>
#include <avr/io.h>


#define HALF_SECOND 500

//                               right right  left  left  disp
//                                most              most   off
int C_DISPLAYSELECTS_PORTB[5] = {0xFD, 0xFF, 0xFF, 0xFF, 0x02};
int C_DISPLAYSELECTS_PORTD[5] = {0xFF, 0xF7, 0xDF, 0xBF, 0x68};

/*             agbf d
  PORTB |= 0b00111101; // 0x3D
  PORTD |= 0b10010000; // 0x90
             e  c
  */
int C_VALUESELECTS_PORTB[16] = {0x2D, 0x28, 0x35, 0x3C, 0x38, 0x1C, 0x1D, 0x2C, 0x3D, 0x3C, 0x3D, 0x19, 0x05, 0x39, 0x15, 0x15};
int C_VALUESELECTS_PORTD[16] = {0x90, 0x00, 0x10, 0x10, 0x80, 0x90, 0x90, 0x00, 0x90, 0x90, 0x80, 0x90, 0x90, 0x10, 0x90, 0x80};


void showOnDisplay(short display, short value) {

  // first kill the display
  PORTB = C_DISPLAYSELECTS_PORTB[4];
  PORTD = C_DISPLAYSELECTS_PORTD[4];

  // select the display
  PORTB &= C_DISPLAYSELECTS_PORTB[display];
  PORTD &= C_DISPLAYSELECTS_PORTD[display];

  // show the number
  PORTB |= C_VALUESELECTS_PORTB[value];
  PORTD |= C_VALUESELECTS_PORTD[value];
}

int main(void) {

  short i, j, k, l;
  short d[4];

  // define the outputs to be the 4 digit-selectors and the 7 segement-selectors
  DDRB |= 0b00111111; 
  DDRD |= 0b11111000; 

  for/*ever*/(;;) {
    /*for(a=0;a<4;a++) {
      for(b=0;b<16;b++) {
        showOnDisplay(a,b);
        _delay_ms(HALF_SECOND);
      }
    }*/


    for(i=0;i<24;i++){
      for(j=0;j<60;j++){
        d[0]= j % 10;
        d[1]= (j-d[0]) / 10;
        d[2]= i % 10;
        d[3]= (i-d[2]) / 10;

        for(k=0;k<100;k++) {
          for(l=0;l<4;l++) {
            showOnDisplay(l, d[l]);
            _delay_ms(1);
          }       
        }
    }}
  }
}
