---
title: '9.3: Paging'
pre: "<i class='fas fa-book'></i> "
weight: 3
---

A memory management technique that is used both in Linux and all other main operating systems is **paging**. The core of the concept is similar to segmentation: The main memory is divided into pieces. These pieces are mapped to the hardware and give the programmer the illusion of having a continuous memory space. However, internally these pieces might be spread all over the hardware.

With segmentation there might be the following issue: we need to allocate a segment of 1024 bytes. There are still 2000 open spaces, but none of them is larger than 1000 bytes. When this happens ... **we have a problem**. 

{{% figure src="/img/mem/ss_mem_segmvspage.png" title="The pieces of memory with segmentation (left) and paging (right)" %}}

With paging, this issue can be overcome. When paging is used, the **memory is divided into equally sized pieces** (see image above). As the tools are aware of this, the issue of having a too-large-a piece will not occur any more. Another benefit is that *finding* a new location for a piece becomes easier. The puzzling has become much easier.

In contrast with segmentation, paging does not result in external fragmentation. Any frame can be assigned to any process that needs one. However, internal fragmentation is to be expected.


This fragmentation in the memory space happens both in the logical address space and in the physical address space. Off course the size of the pieces is the same in both. These newly created pieces have different names, however. A piece in the logical address space is called a **page**, whereas a piece in the physical address space is called a **frame**.

{{% figure src="/img/mem/ss_mem_paging.png" title="The fragmentation of the logical and physical address space with paging" %}}



For paging to work, hardware assistance is required. Every address that is generated in the logical address space is again *secretly* split in two pieces. The first piece is the **page number** (p) and the second piece is the **page offset** (d). Similar to the segment table earlier, there exists a **page table** for every process. This page table stores the base address of each page in the physical memory. The page offset is than added to the page base address to finally have a physical memory address. The size of the logical address space is defined as 2<sup>m</sup>, and a page size as
2<sup>n</sup> bytes. The m-n left-most bits of the logical address define the page number, and the n remaining bits form the page offset.

{{% notice warning %}}
Answer this question before you continue. If you can't answer the question, find the answer in the text above!<br/><br/><b>How many active **page tables** are there in a single system ?</b>
{{% /notice %}}

<div class="multicolumn">
  <div style="width: 30%">
    {{% figure src="/img/mem/ss_mem_paging_logicaladdress.png" %}}
  </div>
  <div>
    {{% figure src="/img/mem/ss_mem_paginghw.png" title="Paging hardware" %}}
    {{% dinobook %}}
  </div>
</div>

Both the page size and the frame size are defined by the supporting **hardware**. As hardware is involved this (typically) dictates that the sizes are powers of 2. The <u>page size</u> could theoretically vary between 512 bytes and 1 GB per page. On a 32-bit processor each <u>page-table entry</u> is typically 4 bytes long.


While the idea of paging is relatively simple, the effects however are not. With a strict decoupling between the logical an physical address spaces, one does not put any restrictions on the other. A 64-bit processor, capable of addressing 2<sup>64</sup> (= 1.8 x 10<sup>19</sup>) different memory locations, can run on a physical memory with less than 264 bytes. (We're not guaranteeing it'll run smoothly, though :smile:).


## Let's do some numbers

In a hypothetical 4-bit system the processor can address 2<sup>4</sup> different addresses. Each logical address has a length of 4 bits. The made-up environment has a page size of 4 bytes, and has 32 bytes of physical memory available. The page table for a certain program would be defined as: {5, 6, 1, 2}. With the definitions as declared above, this comes down to:

* m = 4
* n = 2
* physical memory is 8 frames
* page table: {5, 6, 1, 2}

The logical address 0x0 (0b0000) can be seen as a concatenation of 0b00 and 0b00. This means that the logical address refers to the content on page 0 and offset 0.

The page table tells us that page 0 is mapped to frame 5. Because frames and pages have an equal size, frame 5 also contains 4 bytes. Because the offset is 0, the physical address on which the logical address 0x0 is mapped is 0x14.

This can be calculated as follows: a frame is 4 bytes, and we're looking for frame number 5, this gives us 5 x 4 = 20 = 0x14. Finally the offset has to be added. For logical address 0x0, this is 0. The final physical address hence is 0x14 + 0x0 = 0x14.

Logical address 0x3 (0b0011) has the same page (page 0), but has an offset of 3. The physical address to which logical address 0x3 is mapped, hence is 0x17. 


{{% task %}}
Given the hypothetical system as described above, what would be the corresponding physical address for the logical addresses 4, and 15?
<br/>
<br/>
<div class="solution" id="div_q941" style="visibility: hidden">
  <b>Answer:</b><br/>
  <p>
    Logical address 4 (page 1, offset 0) maps to physical address 24 [= (<b>6</b> × 4) + 0] = 0x18
    <br/>    
    Logical address 15 (page 3, offset 3) maps to physical address 11 [= (<b>2</b> × 4) + 3] = 0x0B
  </p>
</div>

<input value="Toggle solution" type="button" style="margin: 0 auto;" onclick="toggleAnswer('q941', 1)" />

{{% /task %}}



## Hierarchy

Take an off-the-shelf 32-bit processor that can address 2<sup>32</sup> different locations with a page size of 4 kB (=2<sup>12</sup>). If we assume that an entry in the page table has 4 bytes we can calculate the size of the page table: 

* the page table on this system has 2<sup>32</sup> / 2<sup>12</sup> = 2<sup>20</sup> entries
* each entry is 4 = 2<sup>2</sup> bytes
* the total size hence is 2<sup>20</sup> * 2<sup>2</sup> = 2<sup>22</sup> bytes
* 2<sup>22</sup> bytes = 2<sup>12</sup> kB = 2<sup>2</sup> MB = 4 MB

Having to store a 4 MB page table for **every process** is a bit much. Too much!! When the scheduler performs a task switch, it has to copy this, remember ?

There exist multiple techniques to solve this issue. One solution will be discussed here, as discussing them all would take us too far. 


<div class="multicolumn">
  <div class="column">
    {{% figure src="/img/mem/ss_mem_paging_2levelpaging.png" title="A two-level page-table scheme"%}}
    {{% dinobook %}}
  </div>
  <div class="column">
    <p>One way to overcome large page tables is to use a <b>two-level paging</b> algorithm. This technique uses paging for page tables. The page number in the example above is 20 bits. Using the same technique again, the page number gets split into two 10-bit addresses.</p>
    {{% figure src="/img/mem/ss_mem_paging_2levelpaging_address.png" %}}
    <p>With this setting, p<sub>1</sub> is the index into the outer page. Similarly, p<sub>2</sub> is the index into the inner page. When the physical address is to be searched from a logical address, first the outer tables needs to be examined using p<sub>1</sub>. With the inner table found, the base address could searched for using p<sub>2</sub>. Finally the page offset is added to the base address to end up with the mapped physical address.</p>
    <p>The translation from logical to physical address happens from the outer page, inward. Therefore this scheme is known as <b>a forward-mapped page table</b>.</p>
  </div>
</div>

## Throw in some more bits
Paging gives us a nice page table. This could be considered as a table of contents, or the index at the back of a book. For our young(er than us) students, the following clarification:

<div class="multicolumn">
  <div>
    {{% figure src="/img/mem/pile-of-books-159866.jpg" title="A book. Source: G.I."%}}
    <p style="text-align: center">A book is a collection of e-readers, held together with rope or glue.</p>
  </div>
  <div style="width: 30%">
    {{% figure src="http://authormaps.com/wp-content/uploads/2011/07/page_138n.jpg" title="The index of a book" height="50%" %}}
    <p style="text-align: center">A page table for finding content in a book.</p>
  </div>
</div>

Additional information could be stored in the page table. One common bit of meta-data that is stored is a **protection bit**. Depending on whether the bit is set, the page can be read-only or read-write. Another bit that is added is the **valid bit**. From the name it should be clear that a valid bit shows whether the associated page is valid or not. A reason for setting resetting this bit is that the process is not using all the entries in the page table. Entries that are unused have a valid bit that is set to 0. Although more bits could be or are available, the last one touched here is the **modified bit**. This bit indicates that its associated block of memory has been modified and has not been saved to storage yet. It is also often referred to as the **dirty bit**.

{{% notice info %}}
Have you ever wondered why you should **eject** a USB stick ? One of the reasons is the **Dirty bit**. It might happen that you have written data to the USB stick, by writing to its physical memory addresses, but the data has not reached its destination yet. Off course, cache memory also play a role. It has a similar dirty bit.
{{% /notice %}}

## In summary

So, using pages:

* provides separation between the logical and physical address spaces
* requires specialised hardware
* aids in memory protection
* lessens the fragmentation and puzzling efforts