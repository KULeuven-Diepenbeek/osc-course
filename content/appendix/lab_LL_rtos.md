---
title: '3.3: The Ancient Library (RTOS)'
pre: "<i class='fas fa-vial'></i> "
weight: 5
---

## The Ancient Library

> Stuff just got interesting: you find yourself inside an extremely old library, where things clearly have not been touched for ages. A green glowing ball rests in the center of the room, giving the books an odd, but compelling color. Do you dare to touch the books? Let us go ahead and clean this place up a bit. ([img src](https://dublin2019.com/3906-2/fantasy-library-art-736x459/))

![Library](/img/labs/library.png)

### 1. Modeling the books

The back of the first row of books is barely readable, but you can distinguish the following titles and authors: 

* _Cleaning the streets Beyond the Gate_, by _Ulder Ravengard_
* _Beyond the depths of the Underdark_, by _Drizzt Do'Urden_
* _Ancient Aberrations and how to prevent them_, by _Elminster Aumar_
* _Killing people with cows: the ins and outs of Wild Magic_, by _Neera_

How should we proceed to model the concept of a book? Right, a `struct`! Keep track of the title and the author using `char*` properties. <br/>
Proceed with caution and whatever you do, do not directly look into the green light! Use the following blueprint:

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef of "book"

// forward declarations
book* create_books(void);
void print_books(book* library);

// main functions
int main() {
    book* library = create_books();
    print_books(library);

    return 0;
}

// other functions
book* create_books(void) {
    // ??
}

void print_books(book* library) {
    // ??
}
```
The structure you provided can be expanded with a third property: `book* next`, pointing to the next element in the row. That way, when looping through all books, we simply need to follow the 'next' pointer, until a `NULL` is reached, indicating the end of the library. This technique makes it possible to loop through things **without knowing it's size**! 

**Tips:** You may **hardcode** the four books mentioned above in the ```create_books()``` function. Pay attention that you keep the order of the entries !!


{{% task %}}
Write the required struct and complete the function bodies of ```create_books()``` and ```print_books()```.
{{% /task %}}



### 2. Cleaning up the library

The place looks dusty, doesn't it? <br/>
Also, the books seem to be placed in a random order. Why don't we take the time, now that we are here and enjoy the green glow, to order these books alphabetically **by author**? You can ignore the surnames, simply sort on the property `author`. That is, the expected output of your program should be:

<pre>
Beyond the depths of the Underdark, by Drizzt Do'Urden
Ancient Aberrations and how to prevent them, by Elminster Aumar
Killing people with cows: the ins and outs of Wild Magic, by Neera
Cleaning the streets Beyond the Gate, by Ulder Ravengard
</pre>

Tips:

0. Use the [strcmp()](https://www.tutorialspoint.com/c_standard_library/c_function_strcmp) function from `<string.h>` to compare two strings.
0. The sorting algorithm that you use is **not** important. You can simply use [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort). However, if you want to use a fancy approach, feel welcome to do so.
0. Sorting **should** be done by moving the **objects**, **not the content** of the objects.
0. For the sake of simplicity, you may assume that the length of the library is fixed to 4.

&nbsp;
```C
int main() {

    book* library = create_books();
    print_books(library);

    library = sort_books(library);
    print_books(library);

    return 0;
}
```

{{% task %}}
Create the function `book* sort_books(book* library)`. Display the original library and then print it again, after applying the ```sort_books()``` function.
{{% /task %}}


### [OPTIONAL] 3. Wild Surge! ASC/DESC

> A sudden gust of wind enters the old library. You immediately halt what you were doing to carefully listen if imminent threats are upon you and your party. A cloaked figure swings open a side-door and starts casting a spell that sounds very unfamiliar to you. _Praeses, Alia, Fero..._ An alteration, but which one?! Quick, hide the books! But alas, it was too late... <br/>
While the spell completes, you hear the figure cursing "_annoying wild surges!_". The voice sounds like a woman. She rushes off, but the part of her face you were able to catch in the glimpse of an eye seems oddly familiar... Suddenly, you know it. The book! The cow book! That was the author! Neera... 

Neera managed to completely mess up our sorting strategy, sorting on the **title** of the book instead of on the **author**. 

```C
int main() {

    book* library = create_books();
    print_books(library);

    library = sort_books(library);
    print_books(library);

    // NEERA ENCOUNTER:
    //   changes a function pointer of sort_books() from sort_books_by_author() to sort_books_by_title()

    library = sort_books(library);
    print_books(library);

    return 0;
}
```


Tips:

1. Re-read [chapter 3 (pointers)](/ch3-pointers)!
2. You will need two extra functions, `sort_books_by_author()` and `sort_books_by_title()`.

{{% task %}}
Changes the function pointer of sort_books() from `sort_books_by_author()` to `sort_books_by_title()`
{{% /task %}}

