---
title: 'Chapter x: Interrupts'
accent: "#008eb3"
disableComments: true
---

&laquo;&nbsp;[Back to Table of Content](/toc)<br/>

<hr/>
<!--
&raquo;&nbsp;[Naar de labo opgave](#oef)
-->

# Chapter 1: Interrupts

 {{.TableOfContents}} 

## 1.1 Arduino UNO

The Arduino UNO is an open-source microcontroller board. It is powered by an _off-the-shelf_ ATMega microcontroller from [Microchip](https://www.microchip.com/design-centers/8-bit/avr-mcus). The datasheet for this family of microcontrollers can be found [here](http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf).

<center><img src="https://store-cdn.arduino.cc/usa/catalog/product/cache/1/image/520x330/604a3538c15e081937dbfbd20aa60aad/a/0/a000066_featured_4.jpg" height=320/></center>

The datasheet contains a block diagram of the AVR architecture. Nonetheless, most of these components could be found in many other components as well.

<center><img src="/img/0x_11.png"/></center>

The image should be familiar to students that took up the _Elektronische systemen_ course at KU Leuven. :smile: The upper right component that is attached to the 8-bit data bus is the Interrupt Unit. This component is the topic of this chapter. Before diving into the details, a number of independent topics are explained first. Through these topics the concept of interrupts is introduced by using the 8-bit timer that is present on the Arduino UNO.




## 1.2 Bare metal programming on the Arduino UNO

Programming the Arduino UNO can be easily done with **Arduino IDE**. This user friendly environment is a very nice entry point for new users of microcontrollers. 

<center><img src="/img/0x_02.png"/></center>

Future engineers, however, should be able to understand what is going on behind the curtain. 

### Bit manipulation
When bare metal programming a microcontroller it is often required to start poking specific bit. A quick refresh on how to achieve this is given here. In contrast with the software world, hardware engineers start counting from the right (instead of the left) and from 0 (instead of 1).

<center><img src="/img/0x_01.jpg" height=320/></center>

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

Next to the shift operator, [bitwise operators](https://en.wikipedia.org/wiki/Bitwise_operations_in_C#Bitwise_operators) are also heavily used for setting and/or clearing certain bits. The logical functions AND (&), OR(|) and NOT(~) can be used as efficient tools for bit fiddling.

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

### Hello hardware, this is software speaking
A heavily used way of communication between hardware and software is through memory-mapped registers. Such a register can be read or written by software at a certain address. This register serves as driver (in the hardware sense) for inputs of a certain hardware component.

When a register is written by software and read (or driving) hardware, such a register is sometimes called a **command register** (CR). When a register is written (or driven) by hardware and read by the software, such a register is sometimes refered to with a **status register** (SR).

Going through the datasheet of the microcontroller on the Arduino many CRs can be found. Section 36 summarises these registers on more than 3 pages. An example is shown below.

<center><img src="/img/0x_03.png"/></center>

The register above can be accessed from software on address register 0x7A. When the software writes to this register **ALL** 8 bits are written. This is important to remember to avoid one of the <span style="color: green; font-weight: bold;">dragons</span> described above. This register serves as a CR and SR for the control of the Analog-to-Digital Converter. 

As can be learned from the datasheet, the MSB of this register is used to enable or disable the ADC.





### Two beating hearts
As mentioned above, simply cross compiling for the targeted microcontroller allows for programming the Arduino UNO in C.

When using the Arduino IDE, this is fairly simple. The code would look something like this:

```C
void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
```

This snippet of C code is wrapped by the **IDE** into a complete C program. Through the toolchain a lot of _magic_ happens that hides certain more complex aspects for the programmer. Writing the same program in C for the Arduino is a bit less aesthetic.

```C
#include <avr/io.h>

void setup()
{
  DDRB |= (1 << 5);
  // or in a shorter form:  DDRD |= PORTD6;
  // or even with helper.h: bit_set(DDRD, PORTD6);
}

void loop()
{
  int i, j;

  PORTB = PORTB | (1 << 5);
  for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");

  PORTB = PORTB & ~(1 << 5);
  for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");
}

int main(void) {
  setup();
  while(1) {
    loop();
  }
}
```


<!--
<center><img src="/img/placeholder.png" height=240/></center>
-->

## 8-bit Timer

<center><img src="/img/0x_12.png"/></center>