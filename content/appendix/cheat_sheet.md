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
| ls | list (show content of current directory) - typical parameters: `-lha` (longform, human readable, all files) |
| history | show a history of used commands. Re-execute with `![number]`. |
| alias | make a shorthand command for another, longer command |
| clear | clears all text from terminal window |

### CLI tools

| command | goal |
|---|---|
| man | show text manual for another command (exit by pressing `q`) |
| mkdir | make (create) a directory |
| touch | create a file |
| rm | remove a file/directory - typical params: `-rf` (recursive, force) |
| cat | print raw file contents to terminal output |
| head | print the first few lines of raw file contents to the terminal output - typical parameters: `-n 15` (number of lines is 15) |
| tail | print the last few lines of raw file contents to the terminal output - typical parameters: `-n 15` (number of lines is 15) |
| grep | search for content in a file |
| find | search for content in a file |
| awk | scripting language to filter strings/file contents |
| vi | powerful editor with a steep learning curve (FYI: exiting is through: ESCAPE then ":q!") |
| nano | slightly simpler editor which is easier to control |
| chmod | change modifiers of a file (r/w/x/d) |
| time | record time it takes to run another command or give resource usage |

### Compiling

| command | goal |
|---|---|
| gcc | GNU C Compiler - params: `-c`, `-o`, ... |
| make | Execute a `Makefile` - params: `[target]` |
| ./[filepath] | execute a compiled file/program |

### System administration

| command | goal |
|---|---|
| lsusb | list USB devices |
| ps | report a snaptshot of the current processes - typical parameters: `-aux` |
| pstree | display a tree of processes |
| kill | send a signal to a process - typical parameters: `-9 PID` (kill signal, process id (get from `ps`)) |
| bg | send process to the background |
| fg | retrieve process to the background |
| jobs | list processes in the background |
| ssh | secure shell - remote access to another computer via command line |
