---
title: 'Lab x: Baremetal Arduino'
---

## Let's strip to bare-metal

When the going gets tough, the tough get going. Sometimes you need to drop the mock-up and dive down to bare metal.

{{<figure src="/img/spacex_spaceship.jpeg" title="image source: businessinsider.com">}}


## First things first ... a beating heart

Compile the code below and flash it on the Arduino, both of which can be done through the **Makefile**.{{< todo message="make the Makefile uniform" >}} This code can be found under **ex1.c**... {{< todo message="complete the correct path inside the VM" >}}. 

The required setup on the breadboard should look something like this:

{{<figure src="/img/tinkercad/tinkercad_example1.png">}}

```C
#include "helper.h"

#define HEARTBEAT_LED_DIR  DDRD      // '1' is output
#define HEARTBEAT_LED_PORT PORTD
#define HEARTBEAT_LED_BIT  PORTD7

int main(void) {

  /* setup() */
  bit_set(HEARTBEAT_LED_DIR, BIT(HEARTBEAT_LED_BIT));

  /* loop() */
  for/*ever*/ (;;) {
    bit_set(HEARTBEAT_LED_PORT, BIT(HEARTBEAT_LED_BIT));
    _delay_ms(1000);
    bit_clear(HEARTBEAT_LED_PORT, BIT(HEARTBEAT_LED_BIT));
    _delay_ms(1000);
}}
```

#### What is happening in this code ? 

The approach in the C code is not too different from the Arduino IDE approach. The direction bit of the LED is set to *output*: `bit_set(HEARTBEAT_LED_DIR, BIT(HEARTBEAT_LED_BIT));` In the *Loop* function, 4 statements are repeated forever: 1) toggle the LED ON, 2) wait for half the period, 3) toggle the LED OFF, and 4) wait half the period again. These **pseudo** functions are actually macros. These are defined in the file *helper.h* which is included on the first line. {{< todo message="are these the correct words ? Wouter ?<br/>Should we make separate directory for these helper files ?" >}} 

{{<task>}}
Try to understand the <b>BIT MANIPULATION FUNCTIONS</b> in the helper.h file:
<ul>
  <li>bit_get(p,m)</li>
  <li>bit_set(p,m)</li>
  <li>bit_clear(p,m)</li>
  <li>bit_flip(p,m)</li>
  <li>bit_write(c,p,m)</li>
  <li>BIT(x)</li>
  <li>LONGBIT(x)</li>
</ul>
{{< /task >}}

The **helper.h** file itself includes **avr/io.h**. When taking a closer look on this file, lines 271 and 272 read:
 ```
#elif defined (__AVR_ATmega328P__)
#  include <avr/iom328p.h>
```
So the actual include is from: **avr/iom328p.h**. This file contains **all** the defines to ease the address-to-name mapping.
eg. #define DDRD \_SFR_IO8(0x0A)

{{<task>}}
1. Try to find out <b>HOW</b> the selection in io.h is done.<br/>
2. Make a new program that moves the blinking light to a different port.
<br/><b>TIP:</b> don't move the LED, just add another one. We'll need 2 LEDS for the next exercise.
{{< /task >}}



#### Translation micro controller Arduino
Unfortunately for us, the mapping between the micro controller ports and the Arduino ports are not one-to-one. The small table below summarises a number of mappings. If you want more insights, check the [Arduino UNO schematic](https://content.arduino.cc/assets/UNO-TH_Rev3e_sch.pdf).


{{<figure src="https://roboticsbackend.com/wp-content/uploads/2019/01/arduino_schematics_pins.jpg">}}



## Multiple tasks

Let's assume that one task is the original blinking LED which oscillates at 0.5 Hz. Now we want a second application which oscillates 3 times every second.

{{<task>}}
Make two different LEDs oscillate at different frequencies
<ul>
  <li>one LED oscillates at 0.5 Hz</li>
  <li>one LED oscillates at 3 Hz</li>
</ul>
{{< /task >}}


## Start the countdown in ... 3 ... 2 ... 1 ...

The bare-metal rocket on the top of this page needs to be launched. Because of the huge amount of exhaust it should be triggered after a countdown. This gives the poor operator sufficient time to get to a safe distance.

{{<task>}}
After the launch button is pressed, a countdown is started. The countdown starts at 10 and goes to 0. Once the countdown is ongoing, the 0.5 Hz LED should flash. In the final 3 seconds, the second 3 Hz LED should join the show. When the countdown reaches 0, both LEDs should stay on.
{{< /task >}}


Pull-up resistor: https://www.youtube.com/watch?v=wxjerCHCEMg


