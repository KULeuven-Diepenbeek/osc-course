---
title: '1. Integrated C exercise'
pre: "<i class='fas fa-pen-square'></i> "
weight: 2
draft: true
---

**Download the start project here**: [c-integrated-start.c](/exercises/c-integrated-start.c).

The program represents a **book**, consisting out of multiple **pages**, of which each page contains (random) **text**, represented as a `char[]`.

The following functions are given:

1. `printBook()` prints all pages of the book (no need to modify this)
2. `clearBook()` clears pages and frees memory (no need to modify this)
3. `createRandomBook()` creates a new book consisting out of `amount` of pages
4. `createRandompage()` creates a new page with random text
5. `main()` bootstraps everything. 

### 1. Commandline compiling

Create a simplified `Makefile` which does the following when executing the command `make`:

1. Clean up any left object files
2. Compile the exercise
3. Run the exercise

This file should also be submitted. 

{{% notice warning %}}
Please submit a **zip file** with your `.c` and `Makefile`. Make sure your `make` commando runs flawlessly and the file names are in order. Submitting files separately will cost you points!
{{% /notice %}}

### 2. Create two "books"

This program makes a book of 10 _pages_, instances of the `page` struct, represented as a linked list. Each object has a random bit of text as it's _text_ value, stolen from the [Lorem Ipsum generator](https://lipsum.com/) (thank you, Cicero). In this exercise, you have to extend the program such that the book will be _split up_ into two books: one with text on pages that start with a _vowel_, and another with text that starts with a consonant. The pages have to continue to exist, but have to be relinked. It is of paramount importance **not to** make copies of objects! (Remember pointers?)

So, output without modifications:

```text
printing the list:
  faucibus
  quam.
  eget,
  elit.
  dui
  ipsum
  faucibus
  neque
  dui,
  velit.
end of the list
the list is empty
```

Output with modifications:

```text
printing the list:
  faucibus
  quam.
  dui
  faucibus
  neque
  dui,
  velit.
end of the list
printing the list:
  eget,
  elit.
  ipsum
end of the list
```

### 3. Refer to previous objects

Extend the structure in such a way that not only a pointer to the next page is available, but also to the previous one. Currently, the structure looks like this:

```C
struct page {
  char text[100];
  struct page* next;
};
```

A third variable should be added called `previous`. Think about which of the above functions you need to modify in order to set the correct values. This is essentially creating a **double-linked list** instead of a single-linked one. 

Change the `main()` and `printBook()` functions such that they keep track of and print the **TAIL** of the list instead of the **HEAD**, using your newly created variable. 
