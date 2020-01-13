---
title: '2.5 The internals of interrupts'
pre: "<i class='fab fa-linux'></i> "
weight: 5
---

Note that the CR's can be accessed with their names. TCCR1A is the Timer/Counter Control Register (of timer/counter1) A. The translation from this name to the correct address is done by **#include <avr/io.h>** line. This include will subsequently load a header file which has all the mappings for the targeted microcontroller. This choice is made through the CLI-arguments that are given in the tool chain.


## Interrupts
In the example above it is up to the programmer to check if the timer has finished. Also for the Arduino example this can be said. The execution of the **delay()** function is also waiting until the delay is over. This waiting for an event is called: **polling**. 


The datasheet of the microcontroller shows the hardware interrupts that are available.

<center><img src="/img/0x_14.png" alt="The interrupts in the Arduino's microcontroller."/></center>

```C
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {

  cli();                      // disable all interrupts

  DDRB = (1<<5);              // set bit as output
  TCCR1A = 0x0;               // set part of "mode of operation"
  TCCR1B = 0x4;               // set part of "mode of operation" & clock prescaler
  TIMSK1 = 0x1;               // enable the "Overflow Interrupt"

  sei();                      // enable all interrupts

  while(1) {
  }
}

ISR(TIMER1_OVF_vect) {
  PORTB ^= (1<<5);
}
```


{{< todo message="Decide whether we want to go into details here about interrupt vectors and ISR's" >}}

{{< todo message="nested interrupts are possible, though it requires user software to re-enable interrupts" >}}



## Take aways:
After studying this chapter you should:

* be able to target specific bits in a register at a specific address through C
* understand how CR's and SR's work
* understand how timers work
* understand what Interrupts are

## "Things" to "think" on:
* 


## Useful links:
* {{< link name="megaAVR Data Sheet" url="http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf" >}}
* {{< link name="Arduino UNO schematic" url="https://content.arduino.cc/assets/UNO-TH_Rev3e_sch.pdf" >}}
