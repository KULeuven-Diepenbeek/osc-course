#include "stdio.h"

/*AnalogOut my_output(PA_4);
DigitalIn mypin(USER_BUTTON);*/

#define PI        (3.141592653589793238462)
#define AMPLITUDE (1.0)    // x * 3.3V
#define PHASE     (PI * 1) // 2*pi is one period
#define RANGE     (0x7FFF)
#define OFFSET      (0x7FFF)
#define BUFFER_SIZE (360)

uint16_t buffer[BUFFER_SIZE];

void calculate_sinewave(void){
  int i;
  double rads;
  for (i = 0; i < BUFFER_SIZE; i++) {
    rads = (PI * i)/180.0; // Convert degree in radian
    buffer[i] = (uint16_t)(AMPLITUDE * (RANGE * (cos(rads + PHASE))) + OFFSET);
  }
}

int main() {
  int i;
  unsigned int timer=-1;
/*  int count=1, interval=1, a=0, b=0;

  if(mypin.is_connected()) {
    printf("mypin is connected and initialized \r\n");
  }

  printf("Sinewave example\n");
*/s
  calculate_sinewave();

  while(1) {      
    /*b = a;
    a = 1-mypin.read();
    if (a==1 && b==0) {
      count++;
      if(count == 8) {
        count = 1;
      }
      printf("I'm going to increase the count variable to %d\r\n", count);
      interval = 16*count;
    } */
    for (i = 0; i < BUFFER_SIZE; i++) {
      my_output.write_u16(buffer[i]);
      for(timer=-1;timer>0;timer--);
    }  
  }
}


