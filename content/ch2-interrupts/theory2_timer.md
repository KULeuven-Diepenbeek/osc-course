---
title: '2.3 The timer'
pre: "<i class='fab fa-linux'></i> "
weight: 3
---

With our sleeves rolled up and dirt all the way up to our elbows, it's time to grab a coffee and do so reading/studying again. In this section **interrupts** will be introduced through the use of a timer.

A lot of applications that are built using an Arduino need some sense of **time**. As mentioned earlier the ATMega has 3 dedicated timers on chip: two 8-bit timers and one 16-bit timer. Through these timers the concept of time can be implemented.


## 16-bit Timer
One component that is in almost every microcontroller is a Timer/counter. This timer/counter can be used for many things: stopwatch, wave generation, timing, ... The block diagram of the 16-bit timer/counter in the Arduino is shown here. Next to this 16-bit timer/counter there are 2 8-bit timer/counters available. The documentation reports registers like TCNTn and OCnB. The letter n is a placeholder for the number of the timer. In the case of the micro controller on the Arduino, the 16-bit counter results in **n = 1**.

{{<figure src="/img/0x_12.png" title="Block Diagram of the 16-bit counter in the Arduino microcontroller">}}

During **normal operation** the counter simply *counts* from 0x0 to its maximum value.. The left-side image below shows what happens to the 16-bit value **TCNT1**. The counter can also be used in a different mode: **Clear-timer-on-compare (CTC)**. In this mode the timer starts again at 0x0000, but only counts to a certain value. When this value is reached, the counter resets and starts over. The right-side image below shows the CTC mode with the cap at **0x7FFF** and at <span style="color:red">**0x3FFF**</span>.

<div style="display: flex; flex-direction: row; align-items: center;">
  <div style="width: 50%">
    {{<figure src="/img/jo/timer_normal.jpg" title="Value of TCNT during normal operation of the 16-bit counter." width="200%">}}
  </div>
  <div style="width: 50%">
    {{<figure src="/img/jo/timer_ctc.jpg" title="Value of TCNT during clear-timer-on-compare (CTC) operation of the 16-bit counter." width="200%">}}
  </div>
</div>

The value to which the timer counts in CTC mode can be set through the register **OCR1A**: the **O**utput **C**ompare **R**egister of timer **1** named **A**. As can be seen in the block diagram, there is a comparator in the *Timer* block that compares TCNT1 and OCR1A. The result of this comparator can be evaluated in the control logic. By configuring the timer this control logic can be altered.

{{% task %}}
What is the frequency at which the counter reaches its maximum value in **normal** mode ?
{{% /task %}}


## Timer frequency

To determine the frequency at which the counter operates a quick visit to the datasheet holds the answer. The **clk<sub>T1</sub>** can be generated from an external or internal clock source: **clk<sub>I/O</sub>**. This incoming clock goes through a prescaler which can be set  by the Clock Select bits (CS12, CS11, and CS10).

<div style="display: flex; flex-direction: row; align-items: center;">
  <div style="width: 50%">
    {{<figure src="/img/clock_distribution.png" title="Clock Distribution (source: Datasheet)">}}
  </div>
  <div style="width: 50%">
    {{<figure src="/img/timer_cs1x.png" title="Clock Select bits for prescaler cconfiguration (source: Datasheet)">}}
  </div>
</div>

To introduce a clock, a {{< link name="crystal oscillator" url="https://en.wikipedia.org/wiki/Crystal_oscillator" >}} is used. The one on the Arduino UNO board runs at a frequency of 16'000'000 Hz or 16 MHz. This is frequency at which the CPU is working, often referred to as the _clock speed_. Given that frequency, and the value of the pre-scaler, clock frequency at which the counter operates can be calculated.


{{< todo message="die inline mathjax sucks" >}}

{{% mathjax %}}
f_{clk_{T1}} = { f_{clk_{I/O}} \over prescaler_{T1}} = { 16e6 \over 2^{10}} = 15'625 Hz
{{% /mathjax %}}



Because the counter needs 2<sup>16</sup> clock ticks to reach its maximum, this maximum will be reached every \\( 2^{16} \over 15625 \\) = 4.19 s. If a LED were to be toggled every time the counter reaches its maximum, the frequency of the toggling LED would be (**2** * 4.19 s)<sup>-1</sup> = 0.119 Hz.

{{<figure src="/img/jo/timer_time.jpg" title="Value of TCNT during clear-timer-on-compare (CTC) operation of the 16-bit counter." width="50%">}}



## Polling vs Interrupt

Before you put down your coffee to get back to work let's discuss polling first. A nice illustration of polling is shown below.

{{< youtube id="O_sO39FXL68" >}}
&nbsp;

Our toddler is **polling** her father. Another example of polling is shown below. This clip however, ends with an **interrupt**.

{{< youtube id="18AzodTPG5U" >}}
&nbsp;

Would it not be nice that the CPU could just continue working on something else until a certain event occurs eg. the timer reaching its maximum value ? In the second example (the one with the cartoon), the _co-pilot interrupts what the _processor_ was doing.

An **interrupt** is a signal that goes to the processor signalling a certain event. There are two sources for this interrupt: hardware and software. The timer that reaches his maximum count and signals this to the processor is an example of a h**ardware interrupt**. An example for a **software interrupt** could be an attempt of a division by zero.

## Configuring the timer.

As can be seen from the block diagram 6 (4+2) registers are available for interaction with the software:


* **TCCRnA:** Timer/Counter Control Register for counter n OCR A (also available for B)
* **OCRnA:** Output Compare Register A for counter n (also available for B)
* **TCNTn:** Timer/counter value for counter n
* **ICRn:** Input capture something something

{{< todo message="ICRn" >}}

However, before getting into the details of configuring and using the Timer, the clock has be considered.



The timer has a hardware prescaler. Such a prescaler divides the frequency of the clock with a certain power of 2 and allows the developer to choose a more suitable frequency. With this clock, the timer can be configured to divide the incoming frequency by 1024 (= 2<sup>10</sup>). This sets the incoming clock frequency to 16__x__10<sup>6</sup> / 2<sup>10</sup> = 15'325 Hz.

When the Timer/counter is running, it can count bi-directionally. This counter is a hardware component that you also are (or soon: will be) able to described in an HDL. There are multiple modes of operation in which the Timer/Counter can operate. With each mode of operation a certain waveform is generated.

<center><img src="/img/0x_13.png" alt="The different modes of operation to which the Timer/Counter can be configured"/></center>

Now let's configure the timer so it can be used to overcome the need for the **delay()** function. In the **Normal** mode of operation, the timer/counter counts to 0xFFFF. This means the MSB toggles at a frequency of approximately 2 Hz (15'325 Hz / 0xFFFF * 2 ). The C-code that is required to achieve this is shown below.


```C
#include <avr/io.h>

int main(void) {

  unsigned char x;

  DDRB = (1<<5);            // set PORTB_5 as output
  TCCR1A = 0x0;             // set part of "mode of operation"
  TCCR1B = 0x4;             // set part of "mode of operation" & clock prescaler

  while(1) {
                            // read and shift MSB of 16-bit wide counter
    x = (unsigned char)((TCNT1 & 0x8000)>>15);
                            // shift and write the LED
    PORTB = (PORTB & 0b11011111) | (x<<5);
  }
}
```

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
