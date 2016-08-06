## Zeeduino-XC libraries - various 3rd party Arduino/Wiring libraries

These are various 3rd party libraries written for Wiring and/or Arduino.

There are two types of these libraries:

- "clean" - these do not contain any Atmel specific code or directives and are identical to their originals
- "atmel" - these contain, to the minor extent, Atmel specific code or directives and had to be changed somewhat in order to be portable (see. for example fixes.h header file)

Besides these kinds of libraries, there are the ones which are highly specific to certain Atmel chips. These can not be strictly called Wiring/Arduino libraries. These are actually just a C/C++ code written for Atmel controller(s) and are using Wiring or Arduino IDE simply as a means to compile the code and upload it to the Atmel chip. Good example of this kind of code is GRBL. Of course, these kind of libraries (or applications) are not portable and can't be included here.

