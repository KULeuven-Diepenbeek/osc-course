---
title: '9.3: Paging'
pre: "<i class='fas fa-book'></i> "
weight: 3
draft: true
---

A memory management technique that is used both in Linux and all other main operating systems is **paging**. The core of the concept is similar to segmentation: The main memory is divided into pieces. These pieces are mapped to the hardware and give the programmer the illusion of having a continuous memory space. However, internally these pieces might be spread all over the hardware.

With segmentation there might be the following issue: we need to allocate a segment of 1024 bytes. There are still 2000 open spaces, but none of them is larger than 1000 bytes. When this happens ... **we have a problem**. 

{{% figure src="/img/mem/ss_mem_segmvspage.png" title="The pieces of memory with segmentation (left) and paging (right)" %}}

With paging, this issue can be overcome. When paging is used, the **memory is divided into equally sized pieces** (see image above). As the tools are aware of this, the issue of having a too-large-a piece will not occur any more. Another benefit is that *finding* a new location for a piece becomes easier. The puzzling has become much easier.

This fragmentation in the memory space happens both in the logical address space and in the physical address space. Off course the size of the pieces is the same in both. These newly created pieces have different names, however. A piece in the logical address space is called a **page**, whereas a piece in the physical address space is called a **frame**.

{{% figure src="/img/mem/ss_mem_paging.png" title="The fragmentation of the logical and physical address space with paging" %}}

rewrite:
This rather simple idea has great functionality and wide ramifications.
For example, the logical address space is now totally separate from the physical
address space, so a process can have a logical 64-bit address space even though
the system has less than 264 bytes of physical memory.

For paging to work, hardware assistance is required. Every address that is generated in the logical address space is again *secretly* split in two pieces. The first piece is the **page number** (p) and the second piece is the **page offset** (d). Similar to the segment table earlier, there exists a **page table** for every process. This page table stores the base address of each page in the physical memory. The page offset is than added to the page baseaddress to finally have a physical memory address. Let's define the size of the logical address space as 2<sup>m</sup>, and a page size as
2<sup>n</sup> bytes. The m-n most left-most bits of the logical address define the page number, and the n remaining bytes form the page offset.



<div class="multicolumn">
  <div style="width: 30%">
    {{% figure src="/img/mem/ss_mem_paging_logicaladdress.png" %}}
  </div>
  <div>
    {{% figure src="/img/mem/ss_mem_paginghw.png" title="Paging hardware" %}}
    {{% dinobook %}}
  </div>
</div>

Both the page size and the frame size are defined by the supporting **hardware**. As hardware is involved this (typically) dictates that the sizes are powers of 2. The page size varies between 512 bytes and 1 GB per page. 

## Let's do some math

In a hypothetical 4-bit system the processor can address 2<sup>4</sup> different addresses. Each logical address has a length of 4 bits. The made-up environment has a page size of 4 bytes, and has 32 bytes of physical memory available. With the definitions as declared above,this comes down to:

* m = 4
* n = 2


physical memory of 32 bytes (8 pages)

As a concrete (although minuscule) example, consider the memory in
Figure 8.12. Here, in the logical address, n= 2 and m = 4. Using a page size
of 4 bytes and a , we show how the
programmer’s view of memory can be mapped into physical memory. Logical
address 0 is page 0, offset 0. Indexing into the page table, we find that page 0

is in frame 5. Thus, logical address 0 maps to physical address 20 [= (5 × 4) +
0]. Logical address 3 (page 0, offset 3) maps to physical address 23 [= (5 × 4) +
3]. Logical address 4 is page 1, offset 0; according to the page table, page 1 is
mapped to frame 6. Thus, logical address 4 maps to physical address 24 [= (6
× 4) + 0]. Logical address 13 maps to physical address 9.
You may have noticed that paging itself is a form of dynamic relocation.
Every logical address is bound by the paging hardware to some physical
address. Using paging is similar to using a table of base (or relocation) registers,
one for each frame of memory.
When we use a paging scheme, we have no external fragmentation: any free
frame can be allocated to a process that needs it. However, we may have some
internal fragmentation. Notice that frames are allocated as units. If the memory
requirements of a process do not happen to coincide with page boundaries,
the last frame allocated may not be completely full. For example, if page size
is 2,048 bytes, a process of 72,766 bytes will need 35 pages plus 1,086 bytes. It
will be allocated 36 frames, resulting in internal fragmentation of 2,048 − 1,086
= 962 bytes. In the worst case, a process would need n pages plus 1 byte. It
would be allocated n + 1 frames, resulting in internal fragmentation of almost
an entire frame.
If process size is independent of page size, we expect internal fragmentation
to average one-half page per process. This consideration suggests that small
page sizes are desirable. However, overhead is involved in each page-table
entry, and this overhead is reduced as the size of the pages increases. Also,
disk I/O is more efficient when the amount data being transferred is larger
(Chapter 10). Generally, page sizes have grown over time as processes, data
sets, and main memory have become larger. Today, pages typically are between
4 KB and 8 KB in size, and some systems support even larger page sizes. Some
CPUs and kernels even support multiple page sizes. For instance, Solaris uses
page sizes of 8 KB and 4 MB, depending on the data stored by the pages.
Researchers are now developing support for variable on-the-fly page size.
Frequently, on a 32-bit CPU, each page-table entry is 4 bytes long, but that
size can vary as well. A 32-bit entry can point to one of 232 physical page frames.
If frame size is 4 KB (212), then a system with 4-byte entries can address 244 bytes
(or 16 TB) of physical memory. We should note here that the size of physical
memory in a paged memory system is different from the maximum logical size


So using pages:

* provides separation between the logical and physical address spaces
* aids in memory protection
* lessens the fragmentation and puzzling efforts
* requires specialised hardware