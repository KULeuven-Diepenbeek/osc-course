#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "exercise_01.h"

/* prototypes */
static void TaskBlinkGreenLED(void* pvParameters);




int main() {

  /* Perform any hardware setup necessary. */


  /* APPLICATION TASKS CAN BE CREATED HERE 
   * eg. xTaskCreate(TaskBlinkGreenLED, (const portCHAR*) "GreenLED", 256, NULL, 3, NULL);
   * with 1st argument: name of the function
   *      2nd argument: human readable name (only for debugging purposes)
   *      3rd argument: stacksize (in "words" (words*stackwidth = memory))
   *      4th argument: function parameters
   *      5th argument: priority (0 ... (configMAX_PRIORITIES – 1))
   *      6th argument: pxCreatedTask can be used to pass out auptime handle to the task being created. This handle can then be used to reference the task in API calls that, for example, change the task priority or delete the task.
   **/
  xTaskCreate(TaskBlinkGreenLED, (const portCHAR*) "GreenLED", 256, NULL, 3, NULL);
  //xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, NULL );
  
  /* start the scheduler */
  vTaskStartScheduler();

  /* Execution will only reach here if there was insufficient heap to
     start the scheduler. */
  for/*ever*/ (;;);

  return 0;
}

//-----------------------------------------------------------

// Main Green LED Flash
static void TaskBlinkGreenLED(void* pvParameters)
{
  // set pin 5 of PORTB for output
  DDRB |= _BV(DDB5);

  TickType_t xLastWakeTime = xTaskGetTickCount();
  for/*ever*/ (;;)
  {
    // LED on
    PORTB |= _BV(PORTB0);
    vTaskDelayUntil(&xLastWakeTime, (500 / portTICK_PERIOD_MS));

    // LED off
    PORTB &= ~_BV(PORTB0);
    vTaskDelayUntil(&xLastWakeTime, (500 / portTICK_PERIOD_MS));
  }

  vTaskDelete(NULL);
}

//-----------------------------------------------------------

void vApplicationStackOverflowHook(TaskHandle_t xTask, portCHAR* pcTaskName)
{
  // main LED on
  DDRB |= _BV(DDB5);
  PORTB |= _BV(PORTB0);

  // die
  for/*ever*/ (;;)
  {
    PORTB |= _BV(PORTB0);
    _delay_ms(5000);
    PORTB &= ~_BV(PORTB0);
    _delay_ms(5000);
  }
}
