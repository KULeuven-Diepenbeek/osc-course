---
title: '2: Interrupts'
pre: "<i class='fab fa-linux'></i> "
weight: 2
---

<!--
&laquo;&nbsp;[Back to Table of Content](/)<br/>

<hr/>
&raquo;&nbsp;[Naar de labo opgave](#oef)
-->


## 1.1 Arduino UNO

The Arduino UNO is an open-source microcontroller board. It is powered by an _off-the-shelf_ ATMega microcontroller from [Microchip](https://www.microchip.com/design-centers/8-bit/avr-mcus). The datasheet for this family of microcontrollers can be found [here](http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf).

{{<figure src="https://store-cdn.arduino.cc/usa/catalog/product/cache/1/image/520x330/604a3538c15e081937dbfbd20aa60aad/a/0/a000066_featured_4.jpg" title="An Arduino UNO">}}

The datasheet contains a block diagram of the AVR architecture. Nonetheless, most of these components could be found in many other components as well.

{{<figure src="http://exploreembedded.com/wiki/images/thumb/f/fc/AVR_Architecture.GIF/409px-AVR_Architecture.GIF" title="Block diagram of the AVR Architecture">}}

The image should be familiar to students that took up the _Elektronische systemen_ course at KU Leuven. :smile: The upper right component that is attached to the 8-bit data bus is the Interrupt Unit. This component is the topic of this chapter. Before diving into the details, a number of independent topics are explained first. Through these topics the concept of interrupts is introduced by using the 8-bit timer that is present on the Arduino UNO.


## 1.2 Bare metal programming on the Arduino UNO

Programming the Arduino UNO can be easily done with **Arduino IDE**. This user friendly environment is a very nice entry point for new users of microcontrollers. 

{{<figure src="/img/0x_02.png" title="The Arduino IDE">}}

Future engineers, however, should be able to understand what is going on behind the curtain. After all, magic doesn't exist.

### Bit manipulation
When bare metal programming a microcontroller it is often required to start poking specific bit. A quick refresh on how to achieve this is given here. In contrast with the software world, hardware engineers start counting from the right (instead of the left) and from 0 (instead of 1).

<center><img src="/img/endianness.png" height=320 alt="Endianness and approaches in hardware and software"/></center>

Assume a variable that consists of 8 bits (eg. unsigned char x), which experts sometimes refer to as a **byte**. Setting he rightmost bit ( the least significant bit (**LSB**)) to '1' can be done easily.

```C
  unsigned char x;
  x = 1;
```

Setting the fifth bit (starting from the right), might be a bit cumbersome. FYI: the number 2 to the power 5 (for fifth position) equals to 32.

```C
  unsigned char x;
  x = 32;
```

More experienced C programmers might be inclined to use [shift operators](https://en.wikipedia.org/wiki/Bitwise_operations_in_C#Shift_operators).

```C
  unsigned char x;
  x = (1 << 5);
```

Next to the shift operator, [bitwise operators](https://en.wikipedia.org/wiki/Bitwise_operations_in_C#Bitwise_operators) are also heavily used for setting and/or clearing certain bits. The logical functions AND (&), OR(|) and NOT(\~) can be used as efficient tools for bit fiddling.

:heavy_exclamation_mark: :exclamation: :dragon: Beware of the <span style="color: green; font-weight: bold;">dragons</span> :dragon: :exclamation: :heavy_exclamation_mark:.

```C
  unsigned char x, y;
  ...
  x = (1 << 5);
  y = y | (1 << 5);
  ...
  x = (1 << 5);
  y = (1 << 4);
  if(x && y) { printf("YES\n"); } else { printf("NO\n");
  if(x & y)  { printf("YES\n"); } else { printf("NO\n");
```

<div class="exercise">
  <h1>Exercise</h1>
  Write a line of C-code that:
  <ul>
    <li>sets the 3rd byte to '1' and all others to '0'</li>
    <li>sets the 4th and 5th byte to '1' and all others to '0'</li>
  </ul>
</div>

### Hello hardware, this is software speaking
A frequently used way of communication between hardware and software is through memory-mapped registers. Such a register can be read or written by software at a certain address. This register serves as driver (in the hardware sense) for inputs of a certain hardware component.

When a register is written by software and read (or driving) hardware, such a register is sometimes called a **command register** (CR). When a register is written (or driven) by hardware and read by the software, such a register is sometimes refered to with a **status register** (SR).

Going through the datasheet of the microcontroller on the Arduino many CRs can be found. Section 36 summarises these registers on more than 3 pages. An example is shown below.

<center><img src="/img/0x_03.png"/></center>

The register above can be accessed from software on address register 0x7A. When the software writes to this register **ALL** 8 bits are written. This is important to remember to avoid one of the <span style="color: green; font-weight: bold;">dragons</span> described above. This register serves as a CR and SR for the control of the Analog-to-Digital Converter. 

As can be learned from the datasheet, the MSB of this register is used to enable or disable the hardware ADC through software instructions.


### Two beating hearts
As mentioned above, simply cross compiling for the targeted microcontroller allows for programming the Arduino UNO in C, outside of the Arduino IDE.

Here two examples are shown to make a blinking light. The first example uses the Arduino IDE, the second example uses plain C.

The code in the Arduino IDE would look something like this:

```C
void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}
```

This snippet of C code is wrapped by the **IDE** into a complete C program. Through the tool chain that is applied a lot of _magic_ happens that hides certain more complex aspects from the programmer. 

Writing the same program in C for the Arduino is a bit less aesthetic.

```C
volatile unsigned int *ADDRESS_DDR_B = (volatile unsigned int*) 0x0000024;
volatile unsigned int *ADDRESS_PORT_B = (volatile unsigned int*) 0x0000025;

void setup()
{
  *ADDRESS_DDR_B |= (1 << 5);
}

void loop()
{
  int i, j;

  *ADDRESS_PORT_B = *ADDRESS_PORT_B | (1 << 5);
  for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");

  *ADDRESS_PORT_B = *ADDRESS_PORT_B & ~(1 << 5);
  for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");
}

int main(void) {
  setup();
  while(1) {
    loop();
  }
}
```

A number of things can be said about both examples.

1. Addresses and bit positions have to be looked up in the datasheet;
2. The "Setup and Loop"-function approach can be mimicked.
3. The **delay(x)** function is missing

Of course the C program can be written more dense. But, in the end, there is not too much difference between both pieces of code.

## 16-bit Timer
One component that is in almost every microcontroller is a Timer/counter. This timer/counter can be used for many things: stopwatch, wave generation, timing, ... The block diagram of the 16-bit timer/counter in the Arduino is shown here. Next to this 16-bit timer/counter there are 2 8-bit timer/counters available.

<center><img src="/img/0x_12.png" alt="Block Diagram of an 8-bit counter in the Arduino microcontroller"/></center>

As can be seen from the block diagram 6 (4+2) registers are available for interaction with the software:

* **TCCRnA:** Timer/Counter Control Register for counter n OCR A (also available for B)
* **OCRnA:** Output Compare Register A for counter n (also available for B)
* **TCNTn:** Timer/counter value for counter n
* **ICRn:** Input capture something something

{{< todo message="ICRn" >}}

However, before getting into the details of configuring and using the Timer, the clock has be considered.

To introduce a concept of time, a [crystal oscillator](https://en.wikipedia.org/wiki/Crystal_oscillator) is used. The one on the Arduino UNO board runs at a frequency of 16'000'000 Hz or 16 MHz. This is frequency at which the CPU is working, often referred to as the _clock speed_.

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
In the example above it is up to the programmer to check if the timer has finished. Also for the Arduino example this can be said. The execution of the **delay()** function is also waiting until the delay is over. This waiting for an event is called: **polling**. A nice illustration for this is shown below.

{{< youtube id="O_sO39FXL68" >}}
&nbsp;

Another example is given by a cartoon.

{{< youtube id="18AzodTPG5U" >}}
&nbsp;

Would it not be nice that the CPU could just continue working on something else until a certain event occurs. In the second example (the one with the cartoon), the _co-pilot interrupts what the _processor_ was doing.

An **interrupt** is a signal that goes to the processor signaling a certain event. There are two sources for this interrupt: hardware and software. The timer that reaches his maximum count and signals this to the processor is an example of a hardware interrupt. An example for a software interrupt could be an attempt of a division by zero.

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
* [megaAVR Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf)
* [Arduino UNO schematic](https://content.arduino.cc/assets/UNO-TH_Rev3e_sch.pdf)
