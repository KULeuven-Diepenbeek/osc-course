---
title: '9.1: Memory management'
pre: "<i class='fas fa-book'></i> "
weight: 1
---

At multiple times we referred to the registers in processor. These 16 (or at least in that order of magnitude) registers don't suffice to run the complex tasks that are running on our devices. More space is needed !!!

What good is additional space is you can't access it ? As we do in real life we give every house an address. This provides an unambiguous way of **addressing** :wink: every single house.

In modern computers and embedded systems there is a large amount of memory available. All memory locations are uniquely addressed. 

{{% task %}}
How many addresses are there on a modern computer/laptop ? How does this relate to a "64-bit" processor ?
<br/>
<br/>
<div class="solution" id="div_q811" style="visibility: hidden">
  <b>Answer:</b><br/>
  <p>
    The processor of a modern computer is often referred to as a **64-bit** processor. While this number reflects the internal bus size, typically it also implies that the address bus is 64 bits wide.<br/>
    The number of available addresses hence is 2<sup>64</sup>. If we assume a binary order of magnitude, that comes down to 2<sup>24+10+10+10+10</sup> addresses, or 2<sup>24</sup> terabyte or **16 exabyte**.
  </p>
  <br/>
  <p>
    For the sake of correctness, this should be 16 exbibyte. Similarly, 1024 bits is officially a kibibyte, where we typically call this a kilobyte. More information on this can be found on [Wikipedia](https://en.wikipedia.org/wiki/Kibibyte).
  </p>
</div>

<input value="Toggle solution" type="button" style="margin: 0 auto;" onclick="toggleAnswer('q811', 1)"/>
{{% /task %}}

### The flat earth of Arduino

On small systems-on-chip (SOCs) that do not run an operating system, the world of memory addresses looks flat.

<div class="multicolumn">
  <div class="column">
    {{% figure src="/img/mem/ss_mem_flat.png" title="Flat earth view on memory." %}}
  </div>
  <div class="column">
    {{% figure src="https://cdn.mos.cms.futurecdn.net/8wRq3AgggbXphqRxapGWbZ-650-80.jpg" title="Image source: Getty" %}}
  </div>
</div>

If an 8-bit processor, like the ATMega 328p on the Arduino Uno, is assumed the complete memory space covers 2<sup>8</sup> = 256 addresses. On every address an 8-bit value is stored.

### Let's share

<div class="multicolumn">
  <div class="column">
    The purpose of an OS is to run multiple, different tasks on a one piece of hardware. With the flat earth memory approach this becomes cumbersome. A simple solution would be to <b>share</b> the complete memory in multiple chunks. One chunk for each task. 
    <br/>
    <br/>
    It is the responsibility of the OS to make sure that each process stays within it own share. Often this is referred to with <b>memory protection</b>.
    {{% figure src="/img/mem/ss_mem_meltdown_spectre.png" title="Meltdown and Spectre - Two attacks that got access to other process's memory." %}}
    <br/>
    Some computer hackers try the most insane techniques to get access to another process's memory. Exactly this has recently been shown in the Meltdown and Spectre attacks. 
  </div>
  <div class="column">
    {{% figure src="/img/mem/ss_mem_logical.png" title="The complete memory space, divided to one chunk per process." %}}
  </div>
</div>

To keep an eye on that everybody stays within its context the following approach is used. Each task gets a **base address**. This address gives the start of that process's context. The second parameter is the **limit** which gives the size of the context. When a process is scheduled the OS loads the base register and the limit register with the correct values. The **check** that the OS has to monitor is that the address of the accessed memory falls within the interval of the base address PLUS the limit. If this condition does not hold, there might (un-)intentional error. The OS will handle this error.

{{% figure src="/img/mem/ss_mem_logical_BA_LMT.png" title="Base address register and limit register in logical addressing." %}}


The two registers that store the base and limit addresses can only be written by the OS. Moreover, these registers can only be written by processes from the **kernel-space** because the operation is done through a special privileged instruction. The context that is assigned to a specific task is called a **logical address space**.


### Address Binding

<div class="multicolumn">
  <div class="column">
    <p>When software is written, it is done from a certain point of abstraction with respect to the hardware. The <b>C</b> language has a relatively low level of abstraction (close to the hardware) whereas <b>Java</b> has a higher level of abstraction (further from the hardware). Luckily, in <b>C</b> we don't have to bother ourselves with physical addresses.</p>
    <p>Variables are declared in C with statements like: {{< highlight c >}}      int my_score;{{< /highlight >}} The compiler and the linker take care of the rest. Due to the underlying OS the required number of bytes can be <b>reserved</b>.</p>
    {{< highlight c >}}
      #include <stdio.h>

      int main(void) {
        short i;
        short my_array[4];
        long a_long_value;
        ...
      }
    {{< /highlight >}}
    <p>Apart from registers that need to be mapped, there are also functions that require mapping. There typically are three moments in time when this mapping can be done: </p>
    <ul>
      <li>at compile time</li>
      <li>at load time</il>
      <li>at execution time</il>
    </ul>
  </div>
  <div class="column">
    {{% figure src="/img/mem/ss_mem_binding.png" %}}

  </div>
</div>

When the mapping is done during **compile** time, it should be possible to know in which register a certain value is stored. Also the puzzle with functions has to be made. Therefore, all functions should be known which typically is not the case.

When the mapping is done at **load** time, relocatable code is generated by the compiler. The addressing is done relatively. In the example above it could be stated that the first element of *my_array* is at the memory address of *i*, incremented with the size of a short (2 bytes). When such a program is run, the binding to memory address is done when the program loads. When the start address becomes known, all other address can be resolved.

Finally, when (part of) the mapping is done while **executing** the program, the binding is done when it is required. This requires an additional hardware component: **memory-management unit**. Nevertheless, this option of binding at execution time is used by most general-purpose operating systems.


### The memory-management unit

The address that is used by the CPU is the **logical address** or **virtual address**, the address that is actually used in hardware is the **physical address**. The mapping between logical and physical addresses is typically done with the memory-management unit (MMU). 

The first approach the MMU can use is the one similar to the base and limit registers, as seen above.

{{% figure src="/img/mem/ss_mem_mmu.png" title="The MMU"%}}
{{% dinobook %}}

The CPU 'sends' is logical address to the MMU. The MMU then adds a value to "relocate" the address. The address that comes out of the MMU is a physical address that can be used by the hardware to find the memory location. Because things not need to get more complicate, the register in the MMU is called the **relocation register**.

There are more approaches the MMU can use. They will be discussed later.

### Segmentation

Most programmers, ourselves included, think of memory like this long-stretched, linear addressable chunk of highway that is solely here for us (if only it were so) :smile:. We have seen that all the memory is split into multiple **segments** that might vary in size. Don't make the mistake of thinking that your program gets a single nicely demarcated *field* of memory. Our (simple) program also gets segmented.

<div class="multicolumn">
  <div>
    {{% figure src="/img/mem/ss_mem_non_segmented.jpg" height="413px" title="Continuous image" %}}
  </div>

  <div>
    {{% figure src="/img/mem/ss_mem_segmented.jpg" height="413px" title="Segmented image" %}}
  </div>
</div>

The different segments are made, based on the **sections** that were discussed [earlier](http://localhost:1313/osc-course/ch8-stack/stackvsheap/#program-memory): text, data, bss, stack, ... So instead of seeing a program as **a single piece** of the memory-puzzle, it actually breaks down into multiple pieces. All of those puzzle pieces should be mapped , but the will be spread out all over the memory space.

As mentioned before, the puzzling is done by the development tools and the OS. For us, the programmer, it still feels like our very own private highway. With the segments that we are introducing, the job of the puzzler becomes even harder. Luckily there is dedicated hardware to assist. All the segments are collected in the **segment table**. Similarly as above, each segment has as base and a limit. 

{{% figure src="/img/mem/ss_mem_segmhw.png" title="Segmentation hardware" %}}

{{% dinobook %}}


The address that the programmer sees *secretly* consists of two parts: a segment number (s) and an offset (d). The segment number (s) will be used as an address in the segment table. Through this table the base address of the segment can be found. The offset number (d) will be used to define an offset within this segment and is simply added to the base address.

If the sum of the base address and the offset falls within the segment limit, everything is fine. Otherwise the operating system will catch this error.

{{% task %}}
What, *oh what*, could be the name of the error that the OS produces if the sum of the base address and the offset does **not** fall within the segment limit ?
{{% /task %}}

