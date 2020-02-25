---
title: '6.x: Remainder'
pre: "<i class='fas fa-book'></i> "
weight: 10
draft: true
---



## Out of fuel ? Take a Shell

When a user logs in on a Linux computer, typically one of the following approaches is used:

* a login through a Graphical User Interface (GUI)
* a login through a Command Line Interface (CLI)

For a desktop/laptop that is running Linux the GUI approach is typically used. On those systems there are **terminal emulators** which emulate the CLI. Many flavours of these terminals are available: gnome-terminal, xterm, konsole, ...

{{<figure src="http://linuxcommand.org/images/adventure_powerterm_gnome_terminal_with_tabs.png" title="Example of a Terminal emulator">}}

For embedded systems the CLI is more appropriate. The GUI approach is not discussed here. 







When a CLI is used, a **shell** is started. The shell is a small program that translates commands, given by the user, and gives these translations to the OS. As always, there are many flavours of shells: sh, bash, ksh, zsh, ... 

Once the shell is running and the user asks to create new processes, all of these newly create processes will have the shell as a parent process. 

{{<todo message="Elaborate on ... ?">}}

* daemons
* services
* foreground / background
  Would be good, because CTRL-Z is a SIGTSTP signal wich **suspends** the process. Maybe just give the teaser towards the next chapter ?
* ssh