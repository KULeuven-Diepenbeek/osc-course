---
title: '4.3: The Middle Way: TDD'
pre: "<i class='far fa-keyboard'></i> "
weight: 3
---

## Test-Driven Development: Google Test

A concept you learned to love in the [Software Engineering Skills](https://kuleuven-diepenbeek.github.io/ses-course/tdd/) course. 

It's concepts and definitions will **not** be repeated here, but we will introduce **Google Test**, a unit testing framework for C/C++ that enables us to write tests to track down bugs and **reduce the amount of time needed dabbling in `gdb`**. That is one of the major advantages of using automated test frameworks.

{{% notice warning %}}
Google Test is a `C++` (11) framework, not a `C` framework! We will be using `g++` instead of `gcc` to compile everything. C++ files are suffixed with `.cpp` instead of `.c`.<br/>
Major differences between both languages exist but will not be needed to know all about in order to write a few simple tests.<br/><br/>
Since `g++` is not installed on the image by default, use `apt install g++` to download and install the toolchain.
{{% /notice %}}

### A. Installation

Most open source libraries require you to download the source code and compile it yourself. For Google Test, we will do exactly that, since we are learning how to work with compiling and making things anyway. We want to only compile _googletest_, and not _googlemock_ - both are part of the same repository. 

- Clone the github repository: [https://github.com/google/googletest/](https://github.com/google/googletest/). We want to build branch `v1.10.x` - the `master` branch is too unstable. Remember how to switch to that branch? Use `git branch -a` to see all branches, and `git checkout -b [name] remotes/origin/[name]` to check it out locally. Verify with `git branch`.
-  `cd googletest`
-  Create a builddir and navigate into it: `mkdir build`, `cd build`
-  Build Makefiles using cmake: `cmake ./../`
-  Build binaries using make: `make`. 

If all goes according to plan, two libraries will have been created:

1. `libgtest.a`
2. `ligbtest_main.a`

In the subfolder `googletest/googletest/build/lib`. 

### B. Usage

Using the library is a matter of doing two things:

#### 1. Adding include folders

You will need a `main()` function to bootstrap the framework:

```c
// main.cpp
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

And another file where our tests reside:

```c
// test.cpp
#include "gtest/gtest.h"

int add(int one, int two) {
    return one + two;
}

TEST(AddTest, ShouldAddOneAndTo) {
    EXPECT_EQ(add(1, 2), 5);
}

TEST(AddTest, ShouldAlsoBeAbleToAddNegativeValues) {
    EXPECT_EQ(add(-1, -1), -2);
}
```

What's important here is the include that refers to a `gtest/gtest.h` file. The gtest directory resides in the include folder of your google test installation directory. That means somehow we have to educate the compiler on **where to look for the includes**! 

{{% notice note %}}
The `-I[directory]` (I = include) flag is used to tell `g++` where to look for includes.
{{% /notice %}}

#### 2. Linking with the compiled libraries


When running the binary `main()` method, Google Test will output a report of which test passed and which test failed:

<pre>
Wouters-MacBook-Air:unittest wgroenev$ ./cmake-build-debug/unittest
[==========] Running 2 tests from 2 test cases.
[----------] Global test environment set-up.
[----------] 1 test from SuiteName
[ RUN      ] SuiteName.TrueIsTrue
[       OK ] SuiteName.TrueIsTrue (0 ms)
[----------] 1 test from SuiteName (0 ms total)

[----------] 1 test from AddTest
[ RUN      ] AddTest.ShouldAddOneAndTo
/Users/wgroenev/CLionProjects/unittest/test.cpp:18: Failure
      Expected: add(1, 2)
      Which is: 3
To be equal to: 5
[  FAILED  ] AddTest.ShouldAddOneAndTo (0 ms)
[----------] 1 test from AddTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 2 test cases ran. (0 ms total)
[  PASSED  ] 1 test.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] AddTest.ShouldAddOneAndTo

 1 FAILED TEST
</pre>

However, before being able to run everything, `InitGoogleTest()` is implemented somewhere in the libraries we just compiled. That means we need to tell the compiler to **link the Google Test libraries** to our own application. 

{{% notice note %}}
Add libraries as arguments to the compiler while linking. Remember to first use the `-c` flag, and afterwards link everything together.
{{% /notice %}}

Bringing everything together:

<pre>
Wouters-MacBook-Air:debugging wgroeneveld$ g++ -I$GTEST_DIR/include -c gtest-main.cpp
Wouters-MacBook-Air:debugging wgroeneveld$ g++ -I$GTEST_DIR/include -c gtest-tests.cpp
Wouters-MacBook-Air:debugging wgroeneveld$ g++ gtest-main.o gtest-tests.o $GTEST_DIR/build/lib/libgtest.a $GTEST_DIR/build/lib/libgtest_main.a
Wouters-MacBook-Air:debugging wgroeneveld$ ./a.out -lpthread
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from AddTest
[ RUN      ] AddTest.ShouldAddOneAndTo    
</pre>

As you can see, it can be handy to create a shell variable `$GTEST_DIR` that points to your own Google Test directory. To do that, edit the `.bashrc` file in your `~` (home) folder. Remember that files starting with a dot are hidden by default, so use the `-a` flag of the `ls` command. Add the line:

`GTEST_DIR=/hone/[user]/googletest/googletest`

And reopen all terminals. Verify the above using `echo $GTEST_DIR`, it should print out the path. 

{{% notice note %}}
The `-lpthread` linking flag tells the compiler to link the standard threading libraries along with anything else, that are needed by GTest internally. We will get back on these in [chapter 6](/ch6-tasks). <br/>
Without this flag, you will get the following errors: "ld returned 1 exit status, undefined reference to pthread_[fn]"
{{% /notice %}}

### C. 'Debugging' with GTest

Going back to the crackme implementation, a simplified method that verifies input is the following:

```c
int verify(char* pwd) {
    // return 1 if verified against a pre-determined password, 0 otherwise.
}
```

{{% task %}}
Write a set of tests for the above method - **BEFORE** implementing it yourself! Time to hone your TDD skills acquired from the course 'Software Engineering Skills'. Simply copy it into the test file, or include it from somewhere else.<br/> You should at least have the following edge cases:

- right password entered
- wrong password entered
- empty password (what about `NULL` or `""`?)

Use the GTest macro `EXPECT_TRUE` and `EXPECT_FALSE`. These correspond to JUnit's `AssertTrue()` and `AssertFalse()`.

Again, watch out with the order in which parameters should be passed (expected/actual)! See [Google Test Primer](https://github.com/google/googletest/blob/master/googletest/docs/primer.md).
{{% /task %}}
