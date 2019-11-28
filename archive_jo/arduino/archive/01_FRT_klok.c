#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

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

/* global variables */
short d[4];

/* prototypes */
void runClock(void* pvParameters);
void showOnDisplay(void* pvParameters);

int main(void) {

  /* Perform any hardware setup necessary. */

  // define the outputs to be the 4 digit-selectors and the 7 segement-selectors
  DDRB |= 0b00111111; 
  DDRD |= 0b11111000; 



  /* APPLICATION TASKS CAN BE CREATED HERE 
   * eg. xTaskCreate(TaskBlinkGreenLED, (const portCHAR*) "GreenLED", 256, NULL, 3, NULL);
   * with 1st argument: name of the function
   *      2nd argument: human readable name (only for debugging purposes)
   *      3rd argument: stacksize (in "words" (words*stackwidth = memory))
   *      4th argument: function parameters
   *      5th argument: priority (0 ... (configMAX_PRIORITIES – 1))
   *      6th argument: pxCreatedTask can be used to pass out a handle to the task being created. This handle can then be used to reference the task in API calls that, for example, change the task priority or delete the task.
   **/
  xTaskCreate(runClock, (const portCHAR*) "runclock", 256, NULL, 3, NULL);
  xTaskCreate(showOnDisplay, (const portCHAR*) "displayer", 256, NULL, 3, NULL);
  
  /* start the scheduler */
  vTaskStartScheduler();

  /* Execution will only reach here if there was insufficient heap to
     start the scheduler. */
  for/*ever*/ (;;);

  return 0;
  
}


void runClock(void* pvParameters) {
  short i, j, k, l;
  //short d[4];

  for/*ever*/(;;) {
    for(i=0;i<24;i++){
      for(j=0;j<60;j++){
        d[0]= j % 10;
        d[1]= (j-d[0]) / 10;
        d[2]= i % 10;
        d[3]= (i-d[2]) / 10;

        for(k=0;k<10;k++) {
          for(l=0;l<4;l++) {
            //showOnDisplay(l, d[l]);
            _delay_ms(5);
          }       
        }
    }}
  } /* end of for/*ever*/

  // no return statement
}


//void showOnDisplay(short display, short value) {
void showOnDisplay(void* pvParameters) {
  int l;

  for/*ever*/(;;) {
    for(l=0;l<4;l++) {
      // first kill the display
      PORTB = C_DISPLAYSELECTS_PORTB[4];
      PORTD = C_DISPLAYSELECTS_PORTD[4];

      // select the display
      PORTB &= C_DISPLAYSELECTS_PORTB[l];
      PORTD &= C_DISPLAYSELECTS_PORTD[l];

      // show the number
      PORTB |= C_VALUESELECTS_PORTB[d[l]];
      PORTD |= C_VALUESELECTS_PORTD[d[l]];
    }
  } /* end of for/*ever*/

  // no return statement
  // vTaskDelete( NULL );
}