---
title: '2.2: Bare metal Arduino'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

When the going gets tough, the tough get going. Sometimes you need to drop the mock-up and dive down to bare metal.

{{<figure src="https://i.stack.imgur.com/C0cRL.jpg" title="image source: stackexchange.com">}}




## First things first ... a beating heart

Compile the code below and flash it on the Arduino, both of which can be done through the **Makefile**. This code can be found under **ex1.c**. The required setup on the breadboard should look something like this:

{{<figure src="/img/tinkercad/tinkercad_example1.png">}}

```C
#include <avr/io.h>

/* BIT MANIPULATION MACROS */
#define BIT(x) (0x01 << (x%8))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (BIT(m)))
#define bit_clear(p,m) ((p) &= ~(BIT(m)))
#define bit_toggle(p,m) ((p) ^= (BIT(m)))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))

/* PHYSICAL CONNECTIONS */
#define HEARTBEAT_LED 7

int main(void) {
  int i,j;
  
  // set data directions
  bit_set(DDRD, HEARTBEAT_LED);

  /*loop*/ for/*ever*/ (;;) {
    bit_set(PORTD, HEARTBEAT_LED); // LED off
    for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");
    bit_clear(PORTD, HEARTBEAT_LED);  // LED off
    for(j=0;j<1600;j++) for(i=0;i<1600;i++) asm("nop");
  }

  return 0;
}

```

{{< todo message="complete the correct path inside the VM" >}}. 

#### What is happening in this code ? 

The approach in the C code is not too different from the Arduino IDE approach. The direction bit of the LED is set to *output*: `bit_set(PORTD, HEARTBEAT_LED_BIT);` In the *Loop* function, 4 statements are repeated forever:

1. toggle the LED ON, 
2. wait for half the period, 
3. toggle the LED OFF,
4. wait half the period again. 

These pseudo functions are actually **macros**. These are defined in the file *helper.h* which is included on the first line of the C-file.

{{% task %}}
Try to understand the <b>BIT MANIPULATION FUNCTIONS</b> macros:

* BIT(x)
* LONGBIT(x)
* bit_get(p,m)
* bit_set(p,m)
* bit_clear(p,m)
* bit_toggle(p,m)
* bit_write(c,p,m)

{{% /task %}}

The **avr/io.h** file makes searching for specific addresses in the memory space superfluous. When taking a closer look in this file, lines 271 and 272 read:

```
#elif defined (__AVR_ATmega328P__)
#  include <avr/iom328p.h>
```

So the actual included defines come from: **avr/iom328p.h**. This file contains **all** the defines to ease the address-to-name mapping.

{{% task %}}
1. Try to find out **HOW** the selection of the correct file in io.h is done.<br/>
2. Make a new program that adds a blinking LED to a different port.
3. Modify the new program so there is a phase shift of 90° between both blinking lights.
{{% /task %}}




## Translation micro controller Arduino
Unfortunately for us, the mapping between the micro controller ports and the Arduino ports are not one-to-one. The image below summarises these mappings. If you want more insights, check the [Arduino UNO schematic](https://content.arduino.cc/assets/UNO-TH_Rev3e_sch.pdf).


{{<figure src="https://roboticsbackend.com/wp-content/uploads/2019/01/arduino_schematics_pins.jpg">}}

