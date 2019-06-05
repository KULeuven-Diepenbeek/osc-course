---
title: 'Chapter x: Interrupts'
accent: "#008eb3"
disableComments: true
---


&laquo;&nbsp;[Terug naar Software ontwerp in C/C++](/teaching/cpp)<br/>
&raquo;&nbsp;[Naar de labo opgave](#oef)

## De C programmeertaal

De [C taal](https://en.wikipedia.org/wiki/C_(programming_language)) is een  programmeertaal in de jaren '70 ontwikkeld om makkelijk hardware te kunnen aanspreken. C was/is in essentie niet veel meer dan een kleine abstractielaag bovenop assembly.

C is een **imperatieve** programmeertaal. Dat zal je bij het oefenen wel merken: we schrijven instructies als _statements_. Deze regels of statements zijn gestructureerd in functies en `struct` types. Het jammere hier aan is dat er weinig **declarativiteit** aan de pas komt. Omdat C zo weinig om het lijf heeft (low-level), drukken statements bijna altijd uit _hoe_ iets moet werken, in plaats van _wat_ het moet doen.

Toch is **clean code** voor mij van levensbelang en gaan we ook in C ons focussen op _leesbaarheid_. In plaats van getallen in de code gebruiken we `#define`, in plaats van lange statements splitsen we logische blokken op in duidelijke `function` blokken.

C wordt voornamelijk gebruikt in embedded system development, net omdat het zo kort bij de hardware staat. De UNIX, Windows en OSX kernels zijn volledig geschreven in C bijvoorbeeld. Het besturingssysteem van je GSM, smartwatch of (handheld) gaming systeem bouwt verder op C. Enorm veel talen zoals Java (JVM), Python, Ruby en PHP zijn geschreven in C.

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