---
title: '2: Pointers and arrays'
---

In the schematic examples below, the following concepts can be explicitly distinguished:

1. The **name** of a variable
2. The **value** of a variable

And the following implicitly:

1. The **type** of a variable
2. The **adres** of a variable

The **type** of a variable determines the amount of memory that is freed up to be able to save the value. The value is either a current value or an address that refers to a different value. Each variable has a unique address. Variables can therefore refer to each other.

{{<mermaid>}}
graph TD;
    A[varname<br/>value]
    B{varname<br/>address}
{{< /mermaid >}}

This example visualises the instruction `int a = 5`:

{{<mermaid>}}
graph TD;
    A[a<br/>5]
{{< /mermaid >}}

Where the type, `int`, reserves a few bytes depending on the target platform (`sizeof(int)`), on a specific address. We can mainpulate the address itself - this is essential when working with arrays.

### "Compound" types

C uses a _pass-by-value_ system to pass variables to functions. This means that the value is copied, and that function cannot make changes to the original value. That is something positive: **separation of concerns**.

When we think of our person example of [chapter 1](/theory/c/chap1), that struct is therefore always copied. That can be very inefficient, depending on the size of the data! To avoid this, we use a "pointer": a reference to the current data. Objects are _passed by-reference_ by default in Java - so in C we have to do something extra for this.

Instead of `is_old(struct Person person)` the signature becomes `is_old(struct Person * person)` (note the added asterik *). We have two options for reading a value here:

1. _"dereferencing"_ the pointer: asking for the real value, behind the reference. Following the arrow where it points towards, so to speak.
2. Ask for members of the pointer using "`.`".

Because in C, the `.` operator takes precedence over `*`, we have to add brackets to combine both: `(*person).age`. It is annoying to constantly have to use brackets, so the creators came up with an alternative, the `->` operator: `person->age`.

{{% notice note %}}
`(*pointervariable).property` equals to `pointervariable->property`.
{{% /notice %}}

In Java properties are accessed using the dot operator `.`.

### Pointer types

A pointer is a "changeable" reference to a variable. Pointers have their own memory address on the stack and can refer to something else at any time: they are not constant. They are recognizable by `*` after variable type.

```C
#include <stdio.h>

int main() {
    int young = 10;
    int old = 80;
    int *age = &young;
    age = &old;

    printf("%d\n", *age);
    printf("%d\n", age);
}
```

{{% ex %}}
What will be printed in the above example?
{{% /ex %}}

{{<mermaid>}}
graph LR;
    A{*age} -->|after first assignment| B[young<br/>10]
    A --> |after second assignment| C[old<br/>80]
{{< /mermaid >}}


Merk op dat we hier toch nog `&` gebruiken! Dit is geen referentie type maar de _address-of_ operator om het adres van de variabele jong vast te krijgen. Een pointer verwijst naar een adres, niet naar een waarde.

Wat is de output van `printf("%d", leeftijd);`? 1389434244! Huh? We drukken het **adres** van de pointer af, niet waar de pointer naar verwijst. Om dat te doen heb je weer de `*` operator nodig: `printf("%d", *leetijd);`. Dit noemen we _dereferencen_.

De compiler geeft dit ook aan als warning:

> warning: format specifies type 'int' but the argument has type 'int *' [-Wformat]

Pointers kunnen ook verwijzen naar... pointers naar... pointers naar ... Genoeg keer `*` toevoegen.

```C
int jong = 10;
int *ptr = &jong;
int **ptr_to_ptr = ptr; // compiler error
int **ptr_to_ptr = &ptr;
```

{{<mermaid>}}
graph LR;
    A{"**ptr_to_ptr"} -->|ref| B{"*ptr"}
    B --> |ref| C[jong<br/>10]
{{< /mermaid >}}

Waar wijst een nieuwe pointer naar die nog niet geïnstantieerd is? Naar `0`:

```C
int *ptr;
printf("%d", *ptr); // print 0
```

`NULL` is een platform-afhankelijke macro die in C verwijst naar 0, meestal in de vorm van een void pointer. Een `void*` pointer kan naar eender welk type verwijzen en wordt meestal gebruikt om low-level memory aan te spreken, zoals we zullen zien bij de GBA.

De definitie van een pointer schrijft niet voor waar de `*` precies moet staan: `int* leeftijd` is hetzelfde als `int *leeftijd`. Pas om met dingen als `int* leeftijd, ouderdom`! De laatste veriabele is hier een gewone int, en géén pointer!

Referenties en pointers kan je mixen: `int *&ref_to_ptr = ptr`. Lees de tekenreeks van rechts naar links: "referentie van", "pointer".

#### Functie pointers

Een pointer kan ook verwijzen naar een functie (p247), daarvoor heb je dezelfde signatuur definitie nodig:

```C
#include <stdio.h>

int verhoog(int getal) {
    return getal + 1;
}

int verdubbel(int getal) {
    return getal * 2;
}

int main() {
    int (*op)(int) = &verhoog;

    printf("verhoog 5: %d\n", op(5));
    op = &verdubbel;
    printf("verdubbel 5: %d\n", op(5));
    return 0;
}
```

De definitie van de op pointer ziet er wat vreemd uit, maar de signatuur voorspelt dat we een `int` retourneren (meest links), en dat er één parameter nodig is, ook in de vorm van een `int` (tussen haakjes).

Functie pointers kan je ook als parameter meegeven, bijvoorbeeld met `void exec(int (*op)(int)) {`. Een functie kan een functie (pointer) teruggeven, bijvoorbeeld met `int (*kies_op(int mod))(int) {`. De functie "kies_op" verwacht 1 int parameter en geeft een functie pointer terug die verwijst naar een functie met 1 int parameter en returnvalue int. Om dat warboeltje te vereenvoudigen wordt meestal `typedef` gebruikt:

```C
#include <stdio.h>

typedef int(*func_type)(int);

int verhoog(int getal) {
    return getal + 1;
}

int verdubbel(int getal) {
    return getal * 2;
}

func_type kies_op(int mod) {
    return mod == 0 ? &verhoog : &verdubbel;
}

void exec(int (*op)(int)) {
    printf("exec: %d\n", op(5));
}

int main() {
    exec(kies_op(0));       // print 6
    exec(kies_op(1));       // print 10
    return 0;
}
```

Laten we de Persoon `struct` van [labo 1](/teaching/cpp/labo-1) eens herbekijken in het licht van pointers (en typedefs):

```C
#include <stdio.h>
#include <stdlib.h>

struct Persoon {
    int leeftijd;
    int (*is_oud)();
};

typedef struct Persoon Persoon;

int is_oud(Persoon* this) {
    printf("checking leeftijd van persoon: %d\n", this->leeftijd);
    return this->leeftijd > 60;
}

Persoon* create_persoon(int leeftijd) {
    Persoon* persoon = malloc(sizeof(Persoon));
    persoon->leeftijd = leeftijd;
    persoon->is_oud = &is_oud;

    return persoon;
}

int main() {
    Persoon* jaak = create_persoon(40);

    printf("is jaak oud? %d\n", jaak->is_oud(jaak));
    free(jaak); // niet echt nodig, programma stopt hier toch.
    return 0;
}
```

Vergeet niet dat we nog steeds in C aan het programmeren zijn.

Wat is er veranderd?

1. `Persoon` is een typedef geworden.
2. Pointers zijn gebruikt om struts door te geven. `malloc()` komt kijken om geheugen te reserveren voor een nieuwe persoon. Vergeet niet dat we dit zelf moeten terug vrijgeven met `free()`!
3. Het belangrijkste: een **factory method** `create_persoon` is nodig om een nieuwe persoon te assembleren en de is_oud methode aan de struct te plakken.

Dat ziet er al iets gestroomlijnder uit maar vereist nog steeds te veel boilerplating. Zo'n constructies ga je zelden tegen komen in de praktijk. Ontwikkelaars die graag objecten maken zullen C links laten liggen.

### Praktisch gebruik van pointers

Omdat in C alles _by-value_ doorgegeven wordt, kunnen we met pointers de waarden van variabelen in een functie manipuleren die erbuiten gedeclareerd werd. In Java kan je de waarde van member variabelen in objecten ook wijzigen, maar niet **primitives**! Hoe wissel je twee getallen zonder iets terug te geven?

```C
void swap(int *px, int *py) {
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}
int x = 10, y = 20;
swap(&x, &y);
printf("(%d, %d)\n", x, y); // print (20, 10)
```

Zoiets is ondenkbaar in Java - daar hebben we truckjes voor nodig als een `int[]` dat toch een object is. Natuurlijk is deze implementatie ook **nadelig**: is het wel duidelijk voor de caller dat variabelen gewijzigd worden?
Performante algoritme implementaties profiteren van deze mogelijkheden. Duidelijke domain-driven applicaties niet: daar dient een hogere taal voor.

Pointers en arrays gaan hand-in-hand in C. Op pointers kan je ook operaties als `++` en `--` uitvoeren die de pointer in het geheugen één plaatsje naar links of rechts opschuiven. Met `char *tekst = "sup"` verwijst de pointer naar het eerste karakter:

{{<mermaid>}}
graph TD
    A{*tekst}
    A-->|begin van array|C['s']
    A-.->D['u']
    A-.->E['p']
    A-.->F['\0']
{{< /mermaid >}}

Een eigen `printf("%s", tekst)` zou het overlopen van de pointer kunnen zijn, tot er niets meer is, en karakter per karakter afdrukken:

```C
void print_tekst(char *tekst) {
    while(*tekst != '\0') {
        printf("%c", *tekst);
        tekst++;
    }
}
```

In C is `a[i]` exact hetzelfde als `*(a + i)`!

## Herhaling: let op met syntax!

Zie pagina 53 - symbolen zoals `*` en `&` in C en C++ hebben verschillende betekenissen.  

- `int &r = i;` - & na een type: dit is een reference type
- `int *p;` - * na een type: dit is een pointer type
- `p = &i` - & gebruikt in een experessie als _address-of_ operatie
- `*p = i` - * gebruikt in een expressie als _dereference_ operatie

Vergeet niet dat de eerste regel enkel geldig is in C++.
