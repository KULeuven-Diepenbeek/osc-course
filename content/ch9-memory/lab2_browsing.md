---
title: '9.4: Simply browsing through pages'
pre: "<i class='fas fa-vial'></i> "
weight: 4
---


{{<figure src="https://upload.wikimedia.org/wikipedia/commons/2/24/Blank_page_intentionally_end_of_book.jpg" title="image source: wikipedia.com">}}

* **Get page size** on your Linux system through a C program

{{% figure src="/img/mem/ss_941.png" title="An example output" %}}

* Assume a system with a 32-bit logical addresses and a 4-kB (4096 bytes) page size. Write a C program that is passed a logical address (in decimal) through a command line argument. Print the page number (p) and the offset (d) for the given address.
    * Try with at least addresses 19986 and 3638136
    * Hint: lookup "bit masking"

{{% figure src="/img/mem/ss_942.png" title="An example output" %}}

* Imagine the following system that is using a 2-level hierarchical page table:
    * 5-bit processor (so physical memory of 32 bytes, starting at 0x00 and ending at 0x1F)
    * page size of 4 bytes (so 8 pages of 4 bytes each)
    * The outer page table has 4 entries, the inner page table has 8 entries
    * The outer page table's values are [3,0,2,1], the inner page table's values are [3,5,6,0,7,4,1,2]
    * Write a program that, given a logical address, returns the physical address by looking it up through the two-level page table
    * Test this with the following inputs and expected outputs:
        * 21 => 0x11
        * 0 => 0x04
        * 27 = 0x1B
        * 10 = 0x0E
        * 3 = 0x07
        * 28 = 0x00
        * 19 = 0X1F
        * 32 => out-of-bounds error

    * Tip: it helps to first make a drawing/sketch/schematic of what this looks like before programming
    * Note: logical addresses will still be 5-bits in length! Think up-front about how the bits should be used! 

    * Extra challenge (optional): add a way to have gaps in your page tables (i.e., for not-yet-allocated pages, so you can simulate page faults to find a new main memory gap and assign that to the page tables dynamically). Track whether a page is already assigned or not using an additional valid/invalid status bit. 
