# Balance Tool by Braden Best

This is a tool I wrote for myself after getting fed up with using separate calculators + vim + a textfile that I wrote as some kind of spartan money-tracker

It has an uninspired name, but uses no libraries other than the standard library (no dependencies, so compilation is easy-peasy), and was written for a **VERY** specific purpose with **VERY** specific data in mind.

I seriously doubt you could find a use for this unless you need to keep track of:

* money you are saving, and keeping in a "bank" in your home
* money in your wallet
* coins (Quarters, Dimes, Nickels and Pennies, I personally put half-dollars as 50 pennies)
* clock-in times you are getting from your job, so as to track what your next paycheck will be

But if you **actually** have a use for this, then have a blast! Source code is pretty short (about 400 lines), so I am pretty sure you would have no problem going in and fine-tuning it to your needs

## Automatic Installation

Download the latest release from the releases tab, extract the archive, and from a terminal, run `./install`.

After that, make sure you are in your `home` directory (`/home/user`), and then run `balance`.

See note at end of README for more on that quirk.

## Manual Installation

### Configuring

To configure, edit `src/config.c`

After making changes, return to the main directory and re-compile to apply changes

```bash
    $ make install
```

Note: the FILENAME constant must be absolute. That means no bash shortcuts like `~/some-dir` or `$(SOMEPATH)/some-dir`.

### Compiling

```bash
    $ make
```

### Installing (automatically compiles)

```bash
    $ sudo make install
```

### Uninstalling

```bash
    $ sudo make uninstall
```

### Cleaning

```bash
    $ make clean
```

### Running

```bash
    $ balance
```

## A note about the installer

The installer contains a pre-compiled **unstable** build with the default settings. 

It will only run while you are in your home directory. Trying to run it anywhere else will cause a segmentation fault. The installer is meant for people unfamiliar with the `make` build system who want a `right now` solution. If you are familiar with make, then go ahead and follow the manual installation instructions above.
