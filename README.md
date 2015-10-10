# balance2

This is a complete redesign of the [older Balance tool](https://github.com/bradenbest/balance/tree/master).

Now that I know what I'm doing in C, it's a hell of a lot more stable. No warnings, no segfaults, valgrind seal of approval.

## Compiling

To compile,

    $ cd src && make

By default, it will compile with colors turned off. This is for portability with terminals that don't understand ANSI color escapes, and would print something like `[0;37;40mHello[0m` otherwise

To turn colors on, edit `src/makefile` and change the `-DUSE_COLOR` macro to 1, then recompile.

## Installing

To install,

    $ sudo make install
    $ sudo make uninstall
