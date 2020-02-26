---
title: '3.2: The Ancient Library'
pre: "<i class='fas fa-vial'></i> "
weight: 4
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
#define SIZE 4
Book* create_books() {
    // ??
}

void print_books(Book* library) {
    // ??
}

int main() {
    Book* library = create_books();
    print_books(library);               // should print the above list ([title], by [author])
    return 0;
}
```

### 2. Linking things together

The strcuture you provided can be expanded with a third property: `Book* next`, pointing to the next element in the row. That way, when looping through all books, we simply need to follow the 'next' pointer, until a `NULL` is reached, indicating the end of the library. This technique makes it possible to loop through things **without knowing it's size**! 

Rework your implementation by removing the `#define SIZE 4` statement, and by relying on the `next` pointer in the `print_books()` method. 

Tips:

1. What should the value of `next` be when creating the book instances in `create_books()`? What should that function return? A handle to what?
2. You can use `while(ptr) { ... }` instead of a `for` loop. The value within the `while()` statement always evaluates to `true`, unless a "nullpointer" (a value of `0` or `NULL`) is detected. That is exactly what we want. 
3. Another method to ease use of the `malloc()` statements might come in handy, such as `Book* create_book(char* title, char* author)`.

### 3. Cleaning up the library

The place looks dusty, doesn't it? <br/>
Also, the books seem to be placed in a random order. Why don't we take the time, now that we are here and enjoy the green glow, to order these books alphabetically **by author**? You can ignore the surnames, simply sort on the property `author`. That is, the expected output of your program should be:

<pre>
Beyond the depths of the Underdark, by Drizzt Do'Urden
Ancient Aberrations and how to prevent them, by Elminster Aumar
Killing people with cows: the ins and outs of Wild Magic, by Neera
Cleaning the streets Beyond the Gate, by Ulder Ravengard
</pre>

Create and call `void sort_books(Book* library)` before printing them.

{{<mermaid>}}
graph LR;
    H{head}
    T{tail}
    A[book 1]
    B[book 2]
    C[book 3]
    D[book 4]
    N>NULL]

    A -->|next| B
    B -->|next| C
    C -->|next| D
    D -->|next| N

    H --> A
    T --> B
{{< /mermaid >}}


Tips:

1. Use the [strcmp()](https://www.tutorialspoint.com/c_standard_library/c_function_strcmp) function from `<string.h>` to compare two strings.
2. Sorting a _linked list_ is not as difficult as you might think. You will need some sort of _swapping_ function. Take a look at the above drawing. If book 4 needs to be first, how do you swap it with book 1, **while keeping the links intact**? 
3. Use _recursion_ to repeatedly call `sort_books()` within the same function. Which book should be placed in the beginning? What should you process next? Think in terms of _head_ and _tail_. 

### 4. Wild Surge! ASC/DESC

> A sudden gust of wind enters the old library. You immediately halt what you were doing to carefully listen if imminent threats are upon you and your party. A cloaked figure swings open a side-door and starts casting a spell that sounds very unfamiliar to you. _Praeses, Alia, Fero..._ An alteration, but which one?! Quick, hide the books! But alas, it was too late... <br/>
While the spell completes, you hear the figure cursing "_annoying wild surges!_". The voice sounds like a woman. She rushes off, but the part of her face you were able to catch in the glimpse of an eye seems oddly familiar... Suddenly, you know it. The book! The cow book! That was the author! Neera... 

Neera managed to completely reverse our sorting strategy, sorting Z to A instead of A to Z. She used a function pointer to encapsulate `strcmp()`. The following is your main function:

```C
int main() {
    Book* library = create_books();
    neera_encounter();  // changes a function pointer from asc to desc

    sort_books(library);
    print_books(library);   // prints Z -> A
    return 0;
}
```

Create a function pointer that is initialized to the address of your ascending sorter. Neera her Wild Magic switches this to the address of a descending sorter. That pointer will be used inside `sort_books()` instead of `strcmp()`.

Tips:

1. Re-read [chapter 3 (pointers)](/ch3-pointers)!
2. You will need two extra functions, `asc()` and `desc()`, besides `neera_encounter()`.

### 5. Do you rest until fully healed? 

> The rumble of Neera's spell made your head rush and you fill dizzy. Maybe it would be better for you and your party to stay for the night and set up camp. During the night, you make the time to write up on the past events. It looks like it will be quite a thick book, something new to add to the old library. Now, should you add the book at the beginning of the row, or all the way at the end?

Create a function called `void add_book(Book* library, Book* book)`, that adds a new book to **the end** of the library.

{{<mermaid>}}
graph LR;
    new(<strong>new book</strong>)
    A[book 1]
    B[book 2]
    N>NULL]    

    B -.->|next| new
    new -->|next| N
    A -->|next| B
{{< /mermaid >}}

That was quite simple, wasn't it? What if we want it to add new books to **the beginning** of the library? You cannot change the `Book* library` pointer as it is copied over by-value. For this to work, we need to change the signature to a _pointer of a pointer_: `void add_book(Book** library, Book* book)`.

Use the following main function to test your code:

```C
int main() {
    Book* library = create_books();
    Book* newbook = create_book("My adventures", "The Hero");
    // add newbook to the library. But how? 
    print_books(library);
    return 0;
}
```

