---
title: '3.2: Arduino multi frequencies'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

Time to make some harmonics.

{{<figure src="https://upload.wikimedia.org/wikipedia/commons/4/4f/Moodswingerscale.jpg" title="image source: wikipedia.org">}}



## Three's a charm

The example below has to be completed. Three LEDs are placed and defined. If you run the code, the left-most LED starts blinking at 1 Hz. You can choose how you want approach this. Either you search for you very own Arduino and rebuild the design. Or, otherwise, you can use a (webbased) simulator like for example <a href="https://www.tinkercad.com" target="_blank">Tinkercad</a>.

<div style="display: flex; flex-direction: row; align-items: center;">
  <div style="width: 50%">
    {{<figure src="/img/tinkercad/tinkercad_harmonics.png">}}
  </div>
  <div style="width: 50%">
    {{< highlight C  >}}
#define LED_1Hz 7
#define LED_2Hz 6
#define LED_3Hz 5

void setup()
{
  pinMode(LED_1Hz, OUTPUT);
  pinMode(LED_2Hz, OUTPUT);
  pinMode(LED_3Hz, OUTPUT);
}

void loop()
{
  digitalWrite(LED_1Hz, HIGH);
  delay(500);
  digitalWrite(LED_1Hz, LOW);
  delay(500);
}
    {{< / highlight >}}
  </div>
</div>

{{% task %}}
Complete the example so the three LEDs blink at 1 Hz, 2 Hz, and 3 Hz, respectively.
{{% /task %}}

Something to point out is the preciseness of the LEDs. If you'd hold a high-speed camera on the setup and do some precise timing, it becomes clear that the frequencies are not very precise. Take the example of 1 Hz. Executing the **digitalWrite()** function is not instantaneous. As you'll learn in this course, executing a function involves some steps which are overhead. Nonetheless, if lives were at stake, this could be measured very precisely. The additional overhead time could be reduced from the 500 ms, to achieve a better precision.

## Making a second 'application'

A second application that can be run on the Arduino is a Serial port echo service. You know this is a killer-app and could make you millions ;-) 

{{% task %}}
Make a program that can read in a character from the Serial port. The Arduino should simply echo the incoming byte in HEX.
{{% /task %}}

## Merge the two applications

The third exercise is simple, at least on <s>paper</s> screen it is.

{{% task %}}
Merge both programs.
{{% /task %}}

{{% notice warning %}}
What is effect of the additional application on the **preciseness** of the blinking LEDs' frequency ?
{{% /notice %}}