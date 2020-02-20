---
title: 'Cheat sheet'
---

This cheat sheet summarises a set of commands, so you don't have to Google everything.

## Linux commands

Below is a brief list of Linux commands. Remember that you can get more info on a command by typing "[command] `-h"`, "`man` [command]", or even google the manpage on Google.

### Navigation

| command | goal |
|---|---|
| cd | change directory |
| pwd | 'present working directory' |
| ls | list (show content of current directory) - params: `-la` |
| mkdir | create a directory |
| history | show a history of used commands. Re-execute with `![number]`.
| clear | clears all text from terminal window |

### CLI tools

| command | goal |
|---|---|
| rm | remove a file/directory - params: `-rf` |
| touch | create a file |
| cat | print raw file contents to terminal output |
| grep | search for content in a file |
| vi | powerful editor with a steep learning curve (FYI: exiting is through: ":q!") |
| chmod | change modifiers of a file (r/w/x/d) - params: `+/-[modifier]`

### Compiling

| command | goal |
|---|---|
| gcc | GNU C Compiler - params: `-c`, `-o`, ... |
| make | Execute a `Makefile` - params: `[target]` |

### System administration

| command | goal |
|---|---|
| ps | report a snaptshot of the current processes |
| pstree | display a tree of processes |
| kill | send a signal to a process |
| bg | send process to the background |
| fg | retrieve process to the background |
| jobs | list processes in the background |
