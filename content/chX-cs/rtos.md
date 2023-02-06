---
title: 'X.2: Real-time Operating Systems'
pre: "<i class='fab fa-linux'></i> "
weight: 2
---

## Operating Systems
In the previous chapters, many aspects are handled that form the Operating System. The image below, linked from Wikipedia, shows the most important components in the Linux kernel.

{{% figure src="/img/Simplified_Structure_of_the_Linux_Kernel.svg.png" title="source: wikipedia.com" width="60%" %}}

The image above shows: 

* Task management
* Memory management
* the IO subsystem

<div class="multicolumn">
<div class="column">
{{% figure src="/img/chx/desired.svg" title="The desired situation." %}}
</div>
<div class="column">
{{% figure src="/img/chx/reality.svg" title="The real situation." %}}
</div>
</div>

The main goal of the OS is still the same: allow multiple programs and/or users use the same hardware. On the left-hand side of the image above a visual representation is given of what we want to experience. Everything is running truly in parallel.	We have touched on a number of reasons why reality is more like is shown on the right-hand side of the image. The OS will do its best to achieve the desired situation as good as possible. However, sometimes doing your best is **not good enough**.

Try to imagine these situations (and the possible explanations from the developers):

* A pacemaker **missed** an arrhythmia
	* *Sorry, at that moment the tiny OS was switching tasks.*
* A surveillance drone **crashed** against a construction crane
	* *Sorry, at that moment the drone should have detected the crane, the flight computer was in the middle of a TCP time-out while sending telemetry.*
* The motor of a high-end sports car **burned** out due to a faulty-timed gear shift
	* *Sorry, at the moment the timer ended, the microcontroller was handling a switch in radio stations.*

**Sometimes, doing your best is not good enough.**

## Real-time Operating Systems

While a general OS tries its best to meet all constraints, a sporadic failure is not a vital problem. If there is a dip in network handling resulting in a short lag of a youtube-clip the computer will not crash-and-burn. Operating systems like this are called **soft real-time operating systems** and examples are: Linux, Windows, iOS, ...


Like illustrated above, some situations have tasks which **have to meet their constraints**. Failing to do so results in a system failure. For these applications Real-Time Operating Systems (RTOS) can be used. These operating systems are called **hard real-time systems**. They have very specific deterministic constraints and ALL of them should be MET, at ALL TIME. Examples of RTOSes are: 

* FreeRTOS
* mbedOS
* Contiki
* Xenomai
* *(there are many more)*

For the sake of completeness it is pointed out that tweaks are available to turn the Linux kernel into a real-time kernel.

### FreeRTOS


![](/img/freertos.jpg)


[FreeRTOS](https://www.freertos.org/) is an open source real-time OS that is tailored for embedded systems. You can even run this on an Arduino.

This OS essentially consists out of merely 5 files:

* **tasks.c**: handles task management
* **queue.c**: handles queues & synchronisation 
* **list.c**: handles lists
* **port.c**: details for porting to a specific processor
* **heap_x.c**: handles the heap

FreeRTOS is a trade-off between bare-metal programming and the luxury of an OS. With everything you've seen in this course you should be able, after some studying perhaps, to understand how a **task** is described.

```C
void runClock(void* pvParameters) {
	short i, j, k, l;

	for/*ever*/(;;) {
		for(i=0;i<24;i++){
			for(j=0;j<60;j++){
				d[0]= j % 10;
				d[1]= (j-d[0]) / 10;
				d[2]= i % 10;
				d[3]= (i-d[2]) / 10;

				for(k=0;k<10;k++) {
					for(l=0;l<4;l++) {
						_delay_ms(5);
					}			 
				}
		}}
	} /* end of for/*ever*/

	// no return statement
}
```

The function above is the program/tasks that simulates time. The time is written in **shared memory** that is accessible by other programs/tasks.

The main function could like this:
```C
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
   *      6th argument: pxCreatedTask can be used to pass out a handle to the task being created. This handle can then 
   *                    be used to reference the task in API calls that, for example, change the task priority or
   *                    delete the task.
   **/
  xTaskCreate(runClock, (const portCHAR*) "runclock", 256, NULL, 3, NULL);
  xTaskCreate(showOnDisplay, (const portCHAR*) "displayer", 256, NULL, 3, NULL);
  
  /* start the scheduler */
  vTaskStartScheduler();

  /* Execution will only reach here if there was insufficient heap to start the scheduler. */
  for/*ever*/ (;;);

  return 0;
}
```

## Is a RTOS outdated?

One could state that RTOS-es are outdated. Processors and OS-es, anno 2023, are **so powerful** that no additional measures should be taken to guarantee specific constraints. While that might be true, there is also **scalability**. 

It might be feasible to write all the desired software (networking stacks, logging, sensor reading, ...) in such a way all constraints are met, **BUT** it requires a state-of-the-art system. For example: a processor with 2 GB of RAM memory and 160 GB of solid state storage. Installing this in every gearbox of a car, for example, simply is **too expensive**. If the same constraints and performance requirements can be met for a fraction of the price, industry dictates the latter option should be chosen. 

That's good news for whoever is studying this course, as skill-full programmers and engineers are a necessity to make this work!