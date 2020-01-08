---
title: '1.6: Splitting up Code'
pre: "<i class='fas fa-vial'></i> "
weight: 6
---

### Building with Makefiles

It is time to split up our Orc exercise code into different parts:

{{<mermaid>}}
graph TD
    E{Executable}
    A[main.c]
    AA>main.o]
    B[orcs.c]
    BB>orcs.o]
    D[orcs.h]
    
    E --> AA
    E --> BB

    AA --> A
    AA --> D

    BB --> B
    BB --> D
{{< /mermaid >}}

Create four different files:

1. orcs.h - this is where your struct definition resides.
2. orcs.c - this is where your methods related to orcs reside. Include the orc header file.
3. main.c - this is where your main method resides. Include the orc header file.
4. Makefile - builds everything. Create a `compile`, `link`, and `clean` target.

{{% task %}}
Compile both C files with separate `gcc -c` commands, merging them together with a third command, as seen in the previous section. 
{{% /task %}}

When you think you can manage using the `gcc` command in the commandline, automate everything by leveraging the power of Makefiles. 
