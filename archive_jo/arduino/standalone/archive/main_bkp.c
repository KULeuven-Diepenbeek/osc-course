#include "FreeRTOS.h"
#include "task.h"
//#include "queue.h"
#include "semphr.h"

#include <util/delay.h>
#include <avr/io.h>

#include "system.h"


void vHeartBeat( void *pvParameters );
void vTask1( void *pvParameters );

int main(void) {

  /* initialisation */
  DDRD |= 0x04;       // heartbeat is output
  SystemUSART_Init(); // uart
  SystemUSART_Transmit('@');
  SystemUSART_Transmit('!');

  xTaskCreate( vHeartBeat, "Heartbt", 1000, NULL, 1, NULL);

  /* Create one of the two tasks. Note that a real application should check
      the return value of the xTaskCreate() call to ensure the task was created
      successfully. */
  xTaskCreate( vTask1, /* Pointer to the function that implements the task. */
    "Task 1",/* Text name for the task. This is to facilitate
    debugging only. */
    1000, /* Stack depth - small microcontrollers will use much
    less stack than this. */
    NULL, /* This example does not use the task parameter. */
    1, /* This task will run at priority 1. */
    NULL ); /* This example does not use the task handle. */



  /* Start the scheduler so the tasks start executing. */
  vTaskStartScheduler();

  /* If all is well then main() will never reach here as the scheduler will
  now be running the tasks. If main() does reach here then it is likely that
  there was insufficient heap memory available for the idle task to be created.
  Chapter 2 provides more information on heap memory management. */
  for( ;; );
}

void vTask1( void *pvParameters ) {
  //const char *pcTaskName = "T1 is running!\r\n";
  const char *pcTaskName = "T1\r\n";
  //volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */

  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; ) {
    /* Print out the name of this task. */
    SystemUSART_Transmit('!');
    //_delay_ms(500);
    //while ( !( UCSR0A & (1<<UDRE0)) ) ;
    /* Put data into buffer, sends the data */
    //UDR0 = 0x77;

    vTaskDelay( pdMS_TO_TICKS(500) );
    //_delay_ms(500);
    //for( ul = 0; ul < 0XFFFF; ul++ );

  }
}

void vHeartBeat( void *pvParameters ) {
  for/*ever*/ (;;) {
    PORTD |= 0x4;       // LED on
    vTaskDelay( pdMS_TO_TICKS(500) );
    //_delay_ms(500);

    PORTD &= 0xFB;      // LED off
    vTaskDelay( pdMS_TO_TICKS(500) );
    //_delay_ms(500);
    //vTaskDelay( pdMS_TO_TICKS(500) );
  }
}