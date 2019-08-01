---
title: 'Lab 2: Pointers and Arrays'
---

## The Ancient Library

Stuff just got interesting: you find yourself inside an extremely old library, where things clearly have not been touched for ages. A green glowing ball rests in the center of the room, giving the books an odd, but compelling color. Do you dare to touch the books? Let us go ahead and clean this place up a bit. ([img src](https://dublin2019.com/3906-2/fantasy-library-art-736x459/))

![Library](/img/labs/library.png)

### 1. Modeling the books

The back of the first row of books is barely readable, but you can distinguish the following titles and authors: 

* _Cleaning the streets Beyond the Gate_, by _Ulder Ravengard_
* _Beyond the depths of the Underdark_, by _Drizzt Do'Urden_
* _Ancient Aberrations and how to prevent them_, by _Elminster Aumar_
* _Killing people with cows: the ins and outs of Wild Magic_, by _Neera_

How should we proceed to model the concept of a book? Right, a `struct`! Keep track of the title and the author using `char[]` properties. <br/>
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

### 2. Cleaning up the library

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