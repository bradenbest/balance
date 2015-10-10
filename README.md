# balance2

This is a complete redesign of the [older Balance tool](https://github.com/bradenbest/balance/tree/master).

Now that I know what I'm doing in C, it's a hell of a lot more stable. No warnings, no segfaults, valgrind seal of approval.

## Compiling

To compile,

    $ cd src && make

This will compile balance without colors, which will print ugly crap like `[0;37;40mHello[0m` since Windows doesn't understand ANSI escapes.

...not to imply that this works in Windows. I mean, it probably *does* work, since I only really used `stdio` and `stdlib` but I haven't tested it in Windows. Who knows, the `getenv("HOME")` line could be what derails the whole thing.

To compile with color, edit the makefile and edit the `-DUSE_COLOR` macro.

## Installing

To install,

    $ sudo make install
