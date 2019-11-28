# FreeRTOS


## variables

Variables are prefixed with their type: 
‘c’ for char 
‘s’ for int16_t (short)
‘l’ int32_t (long)
‘x’ for BaseType_t and any other non-standard types (structures, task handles, queue handles, etc.).

If a variable is unsigned, it is also prefixed with a ‘u’. 
If a variable is a pointer, it is also prefixed with a ‘p’. 
For example: a variable of type uint8_t will be prefixed with ‘uc’, 
             a variable of type pointer to char will be prefixed with ‘pc’. 

## functions

Functions are prefixed with both the type they return, and the file they are defined within. For
example:
 vTaskPrioritySet() returns a void and is defined within task.c.
 xQueueReceive() returns a variable of type BaseType_t and is defined within queue.c.
 pvTimerGetTimerID() returns a pointer to void and is defined within timers.c


Tasks are simply C functions that never exit and, as such, are normally
implemented as an infinite loop

## Timing
include projdefs.h in freertos/include/FreeRTOS.h
in projedefs.h: 
  #ifndef pdMS_TO_TICKS
    #define pdMS_TO_TICKS( xTimeInMs ) ( ( TickType_t ) ( ( ( TickType_t ) (   xTimeInMs ) * ( TickType_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000 ) )
  #endif
could be overwritten in FreeRTOSConfig.h

so pdMS_TO_TICKS(x) = x * configTICK_RATE_HZ / 1000

configTICK_RATE_HZ is defined in FreeRTOSConfig.h 
  #define configTICK_RATE_HZ      ( ( TickType_t ) 1000 )
