---
title: '2.5 The internals of interrupts'
pre: "<i class='fab fa-linux'></i> "
weight: 5
---

{{% figure src="/img/jo/disassembly.jpg" title="Source: G.I."%}}

## The internals

Now that you have an understanding of how interrupts work, let's dive a bit deeper into the interal workings.

The processor has a hardware component that allows hardware interrupts. When a certain event occurs the corresponding **wire** goes high. This makes one (or more) bits of this **interrupt vector** *high*. This triggers the internal **Interrupt unit**. The image below shows the available interrupts for the AT Mega.

{{<figure src="/img/0x_14.png" title="The interrupt vector. Source: Datasheet">}}

When an **Interrupt Request** is triggered and the interrupt is allowed, the processor will jump to another function in program. This function is called the **Interrupt Service Routine**. When this function is finished, the processor continues with the next instruction that would have been executed before the interrupt occured.

When looking at the image above, vector number 14 (or 13, if we start counting at 0x0) should look familiar: **TIMER1_OVF**. Below there are two screenshots of disassembled code. The example on the left is showing an example on a binary that doesn't have interrupts. In that example it is clear that the complete interrupt vector is empty. The example on the right is showing an interrupt vector that has an entry on position 13. Whenever this signal goes *high*, the processor jumps to the function at address 0x90.

<div style="display: flex; flex-direction: row; align-items: center;">
  <div style="width: 50%" class="highlight">
    {{<figure src="/img/inter_inter_without.png" title="The interrupt vector without an ISR" width="100%">}}
  </div>
  <div style="width: 50%">
    {{<figure src="/img/inter_inter_with.png" title="The interrupt vector with an ISR">}}
    {{<figure src="/img/inter_inter_with2.png" title="The interrupt service routine">}}
  </div>
</div>

To **de-compile** a binary the Makefile can also be used. This is not so by default, but if you add this to the Makefile, you can :smiley:. `make od t=filename` The *filename* should be replaced with the actual filename of the binary.


{{% task %}}
What happens if we have an in(-terrupt)ception, read as: an interrupt while an interrupt is being handled ?
{{% /task %}}

<!-- todo message="nested interrupts are possible, though it requires user software to re-enable interrupts" -->

Finally, it is pointed out that there is a **global interrupt mask**. This mask can be (de-)activated to disable/enable **all** interrupts. In the AVR world this can be done through two simple functions: 

* **sei()** enables the global interrupt mask
* **cli()** disables the global interrupt mask

For the sake of completeness, it is pointed out that Interrupts can also be used in the Arduino IDE.

## Take aways
After studying this chapter you should:

* be able to target specific bits in a register
* understand how CR's and SR's work
* understand how timers work
* understand what Interrupts are
* be able to use Interrupts


## Useful links:
* {{< link name="megaAVR Data Sheet" url="http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf" >}}
* {{< link name="Arduino UNO schematic" url="https://content.arduino.cc/assets/UNO-TH_Rev3e_sch.pdf" >}}
