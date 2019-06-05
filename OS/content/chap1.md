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

 {{.TableOfContents}} 

## 1.1 Bare metal programming on the Arduino UNO

Programming the Arduino UNO can be easily done with **Arduino IDE**. This user friendly environment is a very nice entry point for new users of microcontrollers. Future engineers, however, should be able to understand what is going on behind the curtain. After all, the Arduino UNO board uses an _off-the-shelf_ ATMega microcontroller from [Microchip](https://www.microchip.com/design-centers/8-bit/avr-mcus).

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

:heavy_exclamation_mark: :exclamation: :dragon: Beware of the dragons :dragon: :exclamation: :heavy_exclamation_mark:

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
