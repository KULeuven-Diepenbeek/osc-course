---
title: '2.1 Arduino UNO'
pre: "<i class='fab fa-linux'></i> "
weight: 21
---

<!--
&laquo;&nbsp;[Back to Table of Content](/)<br/>

<hr/>
&raquo;&nbsp;[Naar de labo opgave](#oef)
-->

The Arduino UNO is an open-source microcontroller board. It is powered by an _off-the-shelf_ ATMega microcontroller from {{< link name="Microchip" url="https://www.microchip.com/design-centers/8-bit/avr-mcus" >}}. The datasheet for this family of microcontrollers can be found {{< link name="here" url="http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf" >}}.


{{<figure src="https://store-cdn.arduino.cc/usa/catalog/product/cache/1/image/520x330/604a3538c15e081937dbfbd20aa60aad/a/0/a000066_featured_4.jpg" title="An Arduino UNO">}}

This datasheet contains a **block diagram** of the AVR architecture. Nonetheless, most of these components could be found in many other microcontrollers as well. The image should be familiar to students that took up the _Elektronische systemen_ course at KU Leuven. :smile: 

<div style="display: flex; flex-direction: row; align-items: center;">
  <div style="width: 50%">
    {{<figure src="http://blog.podkalicki.com/wp-content/uploads/2015/04/avr_architechture.gif" title="Block diagram of the AVR Architecture">}}
  </div>
  <div style="width: 50%">
    The upper right component that is attached to the 8-bit data bus is the Interrupt Unit. This component is the topic of this chapter. Before diving into the details, another topic is explained first: Timer<br/><br/>
    The ATMega microcontroller on the Arduino has, amonst other components, a dedicated Timer. This timer block consists out of 3 timers: two 8-bit timers and a single 16-bit timer. Through the use of the 16-bot timer, the concept of interrupts is illustrated.
  </div>
</div>



### Low Level programming

Programming the Arduino UNO can be easily done with the **Arduino IDE**. This user friendly environment is a very nice entry point for new users of microcontrollers. Future engineers, however, should be able to understand what is going on behind the curtain. After all, **magic** doesn't exist.

{{<figure src="/img/0x_02.png" title="The Arduino IDE">}}

### Bit manipulations
When bare metal programming a microcontroller it is often required to start poking specific bits in a register. A quick background refresh is given first.

<div style="display: flex; flex-direction: row; align-items: center;">
  <div style="width: 50%">
    {{<figure src="/img/endianness.png" title="Endianness and approaches in hardware and software">}}
  </div>
  <div style="width: 50%">
    <h4>Binary</h4>
    Everybody agrees that the hexadecimal number <b>0x41</b> is binary written as <b>01000001</b>. This is interpreted as 1 x 2<sup>6</sup> + 1 x 2<sup>0</sup> = 64 + 1 = 65. The least-significant bit is in the term: 1 x 2<sup>0</sup>.
    <h4>Endianness</h4>
    When this byte is serialised (eg. in an array or in communcation) the question of "Which bit do we write first ?" arises. This is defined as the <b>endianness</b>. Big Endian writes the MSB on the right, while Little Endian writes the LSB on the right.
    <h4>Hardware vs. Software</h4>
    In contrast with the software world, hardware engineers typically start counting from the right (instead of the left). The C code for the assignement above would be:<br/>
    int myvalue[] = {1, 0, 0, 0, 0, 0, 1, 0};
    where in VHDL this assignment would be:<br/>
    myvalue <= "01000001";
    <br/>
    Now both 'worlds' see myvalue[0] as '1'.
  </div>
</div>


Let's explore the bit manipulations. First we assign the value 1 to an 8-bit type variable.

```C
  unsigned char x;
  x = 1;
```
With this line, **x** holds the number "00000001". This means the bytes are represented in Little Endian.

Setting the fifth bit, might be a bit cumbersome. First the result of 2<sup>5</sup> has to be calculated. After googling the result, the programmer can write:

```C
  unsigned char x;
  x = 32;
```

More seasoned C programmers might be inclined to use the {{< link name="shift operator" url="https://en.wikipedia.org/wiki/Bitwise_operations_in_C#Bitwise_operators" >}}: <<. This litteraly takes te value 1 (remember: this is represented as 00000001) and shifts this value 5 positions to the left, while inserting 0's on the right ( 00000001 + 00000 => 00000 + 00100000 =>  00100000).

```C
  unsigned char x;
  x = (1 << 5);
```

Next to the shift operator, {{< link name="bitwise operators" url="https://en.wikipedia.org/wiki/Bitwise_operations_in_C#Bitwise_operators" >}} are also heavily used for setting and/or clearing certain bits. The logical functions AND (&), OR(|) and NOT(\~) can be used as efficient tools for bit fiddling.

:heavy_exclamation_mark: :exclamation: :dragon: Beware of the <span style="color: green; font-weight: bold;">dragons</span> :dragon: :exclamation: :heavy_exclamation_mark:.

```C
  unsigned char x=0, y=0;
  ...
  x = (1 << 5);
  y = y | (1 << 5);
  ...
  x = (1 << 5);
  y = (1 << 4);
  if(x && y) { printf("YES\n"); } else { printf("NO\n"); }
  if(x & y)  { printf("YES\n"); } else { printf("NO\n"); }
  if(x | y)  { printf("YES\n"); } else { printf("NO\n"); }
```


{{<task>}}
1. What will be the printed in the output of the C-code above ?
<br/><br/>
2. Write a line of C-code that:
  <ul>
    <li>sets the 3rd byte to '1' and all others to '0'</li>
    <li>sets the 4th and 5th byte to '1' and all others to '0'</li>
  </ul>
{{< /task >}}


### Hello hardware, this is software speaking
A frequently used way of communication between hardware and software is through memory-mapped registers. Such a register can be **read or written** by software at a certain **address**. This register serves as driver (in the hardware sense) for inputs of a specific hardware component.

When a register is written by software and read by (or driving) hardware, such a register is sometimes called a **command register (CR)**. When a register is written (or driven) by hardware and read by the software, such a register is sometimes refered to with a **status register (SR)**.

Going through the {{< link name="datasheet" url="http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf" >}} of the microcontroller on the Arduino many CRs can be found. Section 36 summarises these registers on more than 3 pages. An example is shown below.

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

To introduce a concept of time, a {{< link name="crystal oscillator" url="https://en.wikipedia.org/wiki/Crystal_oscillator" >}} is used. The one on the Arduino UNO board runs at a frequency of 16'000'000 Hz or 16 MHz. This is frequency at which the CPU is working, often referred to as the _clock speed_.

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
* {{< link name="megaAVR Data Sheet" url="http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf" >}}
* {{< link name="Arduino UNO schematic" url="https://content.arduino.cc/assets/UNO-TH_Rev3e_sch.pdf" >}}
