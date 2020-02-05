---
title: '1. Integrated C exercise'
pre: "<i class='fas fa-pen-square'></i> "
weight: 2
draft: true
---

**Download the start project here**: [c-integrated-start.c](/exercises/c-integrated-start.c).

The following functions are given:

1. `showList()` prints the values of a list (no need to modify this)
2. `clearList()` clears objects and frees memory (no need to modify this)
3. `createRandomNode()` creates a new object with a random value
4. `createListOfItems()` creates a list of x random objects
5. `main()` bootstraps everything. 

### 1. Commandline compiling

Create a simplified `Makefile` which does the following when executing the command `make`:

1. Clean up any left object files
2. Compile the exercise
3. Run the exercise

### 2. Create two lists

This program makes a list of 10 _objects_, instances of the `node` struct, in a linked list. Each object has a random number as it's _value_. In this exercise, you have to extend the program such that the list will be _split up_ into two lists: one with objects that have an _even_ value, one with objects that have an _uneven_ value. The objects have to continue to exist, but have to be relinked. It is of paramount importance **not to** make copies of objects!

### 3. Refer to previous objects

Extend the structure such that not only a pointer to the next value is available, but also to the previous one. Currently, the structure looks like this:

```C
typedef struct node {
  char value;
  struct node* next;
} T_node;
```

A third variable should be added called `previous`. Think about which of the above functions you need to modify in order to set the correct values. This is essentially creating a **double-linked list** instead of a single-linked one. 

Change the `main()` and `showList()` functions such that they keep track of and print the **TAIL** of the list instead of the **HEAD**, using your newly created variable. 
