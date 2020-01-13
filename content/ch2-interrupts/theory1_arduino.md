---
title: '2.1 Arduino UNO'
pre: "<i class='fab fa-linux'></i> "
weight: 1
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

Setting the sixth bit, might be a bit cumbersome. First the result of 2<sup>5</sup> has to be calculated. After googling the result, the programmer can write:

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


{{% task %}}
1. What will be the printed output of the C-code above ?
<br/><br/>
2. Write a line of C-code that:
  <ul>
    <li>sets the 3rd bit to '1' and all others to '0' (resulting in "00000100")</li>
    <li>sets the 4th and 5th byte to '1' and all others to '0(resulting in "00011000")'</li>
  </ul>
{{% /task %}}


### Hello hardware, this is software speaking
A frequently used way of communication between hardware and software is through memory-mapped registers. Such a register can be **read or written** by software at a certain **address**. This register serves as driver (in the hardware sense) for inputs of a specific hardware component.

When a register is written by software and read by (or driving) hardware, such a register is sometimes called a **command register (CR)**. When a register is written (or driven) by hardware and read by the software, such a register is sometimes referred to with a **status register (SR)**.

Going through the {{< link name="datasheet" url="http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf" >}} of the microcontroller on the Arduino many CRs can be found. Section 36 summarises these registers on more than 3 pages. An example of a register that serves both as a CR and as a SR for controlling of the Analog-to-Digital Converter is shown below. As can be learned from the datasheet, the MSB of this register is used to enable or disable the hardware ADC through software instructions.

{{< figure src="/img/0x_03.png" title="Example of a CR in the ATMega microcontroller." >}}



{{% notice warning %}}
The register above can be accessed from software on address register 0x7A. When the software writes to this register **ALL** 8 bits are written. This is important to remember to avoid one of the <span style="color: green; font-weight: bold;">dragons</span> described above.
{{% /notice %}}


### Two beating hearts
As mentioned above, simply cross compiling for the targeted microcontroller allows for programming the Arduino UNO in C, outside of the Arduino IDE. Here two examples are shown to make a blinking light. The first example is for use through the Arduino IDE, the second example uses plain C in bare metal.

```C
void setup()
{
  pinMode(7, OUTPUT);
}

void loop()
{
  digitalWrite(7, HIGH);
  delay(500);
  digitalWrite(7, LOW);
  delay(500);
}
```

This snippet of C code is wrapped by the **IDE** into a complete C program. Through the tool chain that is applied a lot of **magic** happens that hides certain more complex aspects from the programmer. Writing the same program in bare metal C for the Arduino is a bit less aesthetic.

```C
#include <avr/io.h>

#define HEARTBEAT_LED 7

int main(void) {
  int i, j;

  /* setup */
  DDRD |= (1 << HEARTBEAT_LED);

  /*loop*/ for/*ever*/ (;;) {
    PORTD |= (1 << HEARTBEAT_LED);
    for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");
    PORTD &= ~(1 << HEARTBEAT_LED);
    for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");
  }
 
  return 0;
}

```

{{% notice note %}}
The C-file above can be found in the Virtual Machine as **example1.c**
{{% /notice %}}

A number of things should be pointed out.

1. Addresses and bit positions have to be known up front. these are defined in the **io.h** header file. If this file would not exist the addresses can be found in the datasheet.
2. The "Setup and Loop"-function approach can be mimicked, but this is not required.
3. The **delay(x)** function is missing, but this will be addressed later.


