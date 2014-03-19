# Balance Tool by Braden Best

This is a tool I wrote for myself after getting fed up with using separate calculators + vim + a textfile that I wrote as some kind of spartan money-tracker

It has an uninspired name, but uses no libraries other than the standard library (no dependencies, so compilation is easy-peasy), and was written for a **VERY** specific purpose with **VERY** specific data in mind.

I seriously doubt you could find a use for this unless you need to keep track of:

* money you are saving, and keeping in a "bank" in your home
* money in your wallet
* coins (Quarters, Dimes, Nickels and Pennies, I personally put half-dollars as 50 pennies)
* clock-in times you are getting from your job, so as to track what your next paycheck will be

But if you **actually** have a use for this, then have a blast! Source code is pretty short (about 400 lines), so I am pretty sure you would have no problem going in and fine-tuning it to your needs

## Configuring

To configure, edit `src/config.h`

After making changes, return to the main directory and re-compile to apply changes

    $ make install

## Compiling

    $ make

## Installing (automatically compiles)

    $ sudo make install

## Uninstalling

    $ sudo make uninstall

## Cleaning

    $ make clean

## Running

    $ balance