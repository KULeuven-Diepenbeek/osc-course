---
title: 'Chapter x: Interrupts'
accent: "#008eb3"
disableComments: true
---

<!--
&laquo;&nbsp;[Terug naar Software ontwerp in C/C++](/teaching/cpp)<br/>
&raquo;&nbsp;[Naar de labo opgave](#oef)
-->

## Bit manipulations

Programming the Arduino UNO can be easily done with **Arduino IDE**. This user friendly environment is a very nice entry point for new users of microcontrollers. Future engineers, however, should be able to understand what is going on behind the curtain. After all, the Arduino UNO board uses an _off-the-shelf_ ATMega microcontroller from [Microchip](https://www.microchip.com/design-centers/8-bit/avr-mcus).


### Wat is C++ dan?

Zoals we zullen zien, bevat C weinig mogelijkheden om declaratief te zijn. C++ is de objectenlaag bovenop C die de taal uitbreidt met 'moderne' mogelijkheden tot structureren: inheritance, templating, eenvoudigere libraries (STL), ... De C++ compiler gebruikt gewoon C met laagjes C++ "sugar", zoals de [ANSI C++ Standard](https://isocpp.org/std/the-standard) aangeeft.

De C taal is compact, de C++ taal is dat helaas niet. Kijk zelf maar:

<img src="/img/teaching/cppbooks.jpg" class="bordered" />

Ik neem aan dat ze met '++' het aantal pagina's in handboeken bedoelden. Vergeet niet dat bovenstaande handleiding nog maar een "primer" is.

### Vergelijkingen met Java

```java
import java.io.IOException;
import java.nio.*;

class FileReader {

    @Override
    public String read(String file) throws IOException {
        return new String(Files.readAllBytes(Paths.get(file)));
    }
}

class Main {
    public static void main(String[] args) {
        System.out.println("reading file: ");
        System.out.println(new FileReader().read("sup.txt"));
    }
}
```

Hoe zouden we zoiets in C doen? Dat wordt moeilijk. C heeft geen `class` systeem! De low-level C implementatie is als volgt:

```C