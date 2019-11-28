//#include <Arduino_FreeRTOS.h>
#include "FreeRTOS.h"
#include <queue.h>
#include <semphr.h>

//mutex for the use of serial port 
//this is to make sure the serial ports dont get crossed -> sending data trough eachother 
  


void TaskAnalog1Read( void *pvParameters );
void TaskAnalog2Read( void *pvParameters );
void TaskAnalog3Read( void *pvParameters );
//void TaskBlink( void *pvParameters );

void TaskZendT( void *pvParameters );
void TaskZendL( void *pvParameters );
void TaskZendH( void *pvParameters );

void TaskNoodKnop( void *pvParameters );
void TaskResetKnop( void *pvParameters );

void TaskMotor( void *pvParameters );
void TaskLed( void *pvParameters ) ; 
SemaphoreHandle_t xSemaphore = NULL;



#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
  int step_number = 0;

  bool noodstop = false ;
  bool power = false ;


//QueueHandle_t    queue_1;


void setup() {

 xSemaphore = xSemaphoreCreateMutex();
  // put your setup code here, to run once:
//   xTaskCreate(
//    TaskAnalog1Read
//    ,  (const portCHAR *) "Analog1Read"
//    ,  256 // This stack size can be checked & adjusted by reading Highwater
//    ,  NULL
//    ,  0  // priority
//    ,  NULL );
xTaskCreate(
    TaskNoodKnop
    ,  (const portCHAR *)"TaskNoodKnop"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  5 // priority
    , NULL );
//      xTaskCreate(
//    TaskBlink
//    ,  (const portCHAR *)"Blink"   // A name just for humans
//    ,  128  // Stack size
//    ,  NULL
//    ,  0 // priority
//    ,  NULL );
xTaskCreate(
    TaskResetKnop
    ,  (const portCHAR *)"TaskNoodKnop"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  10 // priority
    ,  NULL );
    xTaskCreate(
    TaskMotor
    ,  (const portCHAR *)"TaskMotor"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  10 // priority
    ,  NULL );

     xTaskCreate(
    TaskAnalog1Read
    ,  (const portCHAR *) "Analog1Read"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  5  // priority
    ,  NULL );
    xTaskCreate(
      TaskAnalog2Read
      ,  (const portCHAR *) "Analog2Read"
      ,  64 // This stack size can be checked & adjusted by reading Highwater
      ,  NULL
      ,  0  // priority
      ,  NULL );
    xTaskCreate(
      TaskAnalog3Read
      ,  (const portCHAR *) "Analog3Read"
      ,  128 // This stack size can be checked & adjusted by reading Highwater
      ,  NULL
      ,  0 // priority
      ,  NULL );

}

void loop() {
  // put your main code here, to run repeatedly:

}

void TaskAnalog1Read(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
     if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
     {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A1);
    // print out the value you read:
 
     Serial.print("T");
     Serial.print(sensorValue);
    Serial.println();
                xSemaphoreGive( xSemaphore );

    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
  }

  }
}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
      Serial.begin(9600);
 Serial.println("kuh");
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 10000/portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 10000/portTICK_PERIOD_MS  ); // wait for one second
  }
}

void TaskNoodKnop(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  int buttonState = 0 ;
  int buttonPin = 5 ;
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode( buttonPin , INPUT);
  for (;;)
  {
    // read the input on analog pin 0:
    int buttonState = digitalRead(buttonPin);
    
    if( power & buttonState == 1)
    {
      noodstop = true ;
      Serial.println("noodstop");
     }
     if( !power & buttonState == 1)
     {
      Serial.println("reseten");
      noodstop = false ;
     }

        vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

//     xQueueSend(queue_1, &buttonState, 10 );

//        Serial.print("button ");
//     Serial.print(buttonState);     
//    Serial.println();

  

void TaskResetKnop(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
//  int numToDisplay = 0 ;
  int buttonPin = 7 ;
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode( buttonPin , INPUT);
  for (;;)
  {
    // read the input on analog pin 0:
    int buttonState = digitalRead(buttonPin);
    if(buttonState == 1)
    {
      //zet machine aan als power switch opstaat 
      power = true ;
    }else 
    {
      //zet machine uit als power switch afgaat
      power = false ;

    }
    //xQueueReceive(queue_1, ontvangen, 10) ;
// if (xQueueReceive(queue_1, &numToDisplay, 10) == pdPASS) {
//     
//      Serial.print("Ontvangen: ");
//      Serial.println(numToDisplay);
//    }
//xQueueReset(queue_1);
//
//        Serial.print("button2 ");
//     Serial.print(buttonState);     
//    Serial.println();
//    Serial.println(numToDisplay );
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskMotor(void *pvParameters)  // This is a task.
{
  Serial.begin(9600);
  
  (void) pvParameters;
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  for (;;)
  {
if(power)
{
  if(!noodstop)
  {
      OneStep(false);
  }
 
}
      vTaskDelay(5);

       
//    }
//    }
 
   
  }

  
}

//void TaskAnalog1Read(void *pvParameters)  // This is a task.
//{
//  (void) pvParameters;
//
//  // initialize serial communication at 9600 bits per second:
//  Serial.begin(9600);
//
//  for (;;)
//  {
//    // read the input on analog pin 0:
//    int sensorValue = analogRead(A0);
//    // print out the value you read:
//     String StrUno = "L";
//     String StrDos = StrUno + sensorValue ;
//     Serial.print("L");
//     Serial.print(sensorValue);     
//    Serial.println();
//    vTaskDelay(500);  // one tick delay (15ms) in between reads for stability
//  }
//}

void TaskAnalog2Read(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
     if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
     {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A1);
    // print out the value you read:
   
     Serial.print("L");
     Serial.print(sensorValue);
    Serial.println();
                xSemaphoreGive( xSemaphore );

    vTaskDelay(200);  // one tick delay (15ms) in between reads for stability
  }

  }
}

void TaskAnalog3Read(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
     if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
     {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A2);
    // print out the value you read:
    
     Serial.print("H");
     Serial.print(sensorValue);
    Serial.println();
                    xSemaphoreGive( xSemaphore );

    vTaskDelay(200);  // one tick delay (15ms) in between reads for stability
     }
  }
}



void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
