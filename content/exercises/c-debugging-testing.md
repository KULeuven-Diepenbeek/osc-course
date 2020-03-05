---
title: '2. Testing in C(++)'
pre: "<i class='fas fa-pen-square'></i> "
weight: 2
draft: false
---

**Download the start project here**: [cpp-testing.cpp](/exercises/cpp-testing.cpp). Remember that in order to run this as a Google Test Suite, you need to compile it using `g++` and bootstrap GTest in a separate `.cpp` file where the `main()` function resides. Go back to the lab notes if you're not sure how to pull this off.

The following code is given:

2. `date` and `period` structs to represent a date and a period of dates in code.
1. `isInPeriod()` which needs to be completed, and takes a pointer of a period struct and a date, to check whether or not the date is inside the period. 

The C++-specific code is kept to a bare minimum, but remember to compile using `g++` because Google Test asks us to do so.

### 1. Commandline compiling

Create a simplified `Makefile` which does the following when executing the command `make`:

1. Clean up any left object files
2. Compile the exercise, using C++ and linking against GTest
3. Run the exercise

The result of the executed start project is the following:

<pre>
Wouters-Air:exercises wgroeneveld$ ./a.out
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from PeriodTest
[ RUN      ] PeriodTest.GoodLuckWithThat
cpp-testing.cpp:23: Failure
      Expected: 0
To be equal to: 1
Add as many TEST cases as you can think of and complete isInPeriod()!
[  FAILED  ] PeriodTest.GoodLuckWithThat (0 ms)
[----------] 1 test from PeriodTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] PeriodTest.GoodLuckWithThat

 1 FAILED TEST
</pre>

### 2. Create Test cases

Replace the single test case called "GoodLuckWithThat" with as many test cases as you can think of to cover all possible cases. What if a date is outside of the period, being in the past, or in the future, or... We expect at least **6 different scenarios** - and of course they have to be unique. A test case which tests the same but with different data is not enough. 

### 3. Implement the isInPeriod method

Only _after creating test cases_, you can move on to the completion of this method. It will return:

- `0` if the given date is not inside the period.
- `1` if the given date is inside the period.

Rerun your tests and make sure everything is passing (not by changing values in your test cases!).

### 4. Is a period overlapping?

Add a new method:

```C
int isPeriodOverlapping(period* one, period* two) {
    return 0;
}
```

Write test cases for this method. Some will fail because it simply returns zero, but let's assume we've got working code here. You do _not need_ to implement this method, only to think about Google Test cases for this one. Write as many `TEST()` cases as you can think of. 
