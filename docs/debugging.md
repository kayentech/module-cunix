## GDB: The GNU Project Debugger
GDB, the GNU Project debugger, allows you to see what is going on inside another program while it executes or what another program was doing at the moment it crashed.

GDB can do four main kinds of things (plus other things in support of these) to help you catch bugs in the act:

Start your program, specifying anything that might affect its behavior.<br/>
Make your program stop on specified conditions.<br/>
Examine what has happened, when your program has stopped.<br/>
Change things in your program, so you can experiment with correcting the effects of one bug and go on to learn about another.<br/>
Those programs might be executing on the same machine as GDB (native), on another machine (remote), or on a simulator.<br/>

## Valgrind: Memory error detector
Valgrind is a flexible program for debugging and profiling Linux executables. It consists of a core, which provides a synthetic CPU in software, and a series of debugging and profiling tools. The architecture is modular, so that new tools can be created easily and without disturbing the existing structure.



* [gdb man](https://www.cs.cmu.edu/~gilpin/tutorial/)
* [Valgrind man](https://www.mankier.com/1/valgrind#)
