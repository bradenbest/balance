# 0.1.0 [Pre-alpha]

  *Exeriment with json parser (failed)

# 0.2.0

  *Experiment with custom data parser using format [n,n,...] where n is an integer of arbitrary length (failed)

# 0.3.0 [Alpha]

  +Created custom data parser using file format [%05d,%05d...]

# 0.4.0

  +Created struct data with 15 members

# 0.5.0

  +Added file_save() which saves data into file

# 0.6.0

  +Added interface.c containing render()

# 0.7.0

  +Added prompt() to interface.c
  -Removed automatic call to render() in main.c

# 0.8.0 [Beta]

  +Added more functions to interface.c, giving the ability to perform commands such as save, help, exit, etc.

# 0.9.0

  +Added config.h to be included by all .h files
  +Added constant DEBUG_MODE to interface.h

# 0.9.1

  [BUG] config.h was doing wacky stuff to the constants, confusing the program about where the file .balance_data was supposed to be, causing instant segfault upon running
  -removed config.h

# 0.10.0

  +added yellow highlighting to numbers for edit() to make it clearer what should be typed in

# 0.10.1

  [BUG] calling any member of d returned junk like -137560345620 (documented [here](http://stackoverflow.com/questions/22315173/passing-struct-pointer-causes-integer-overflow-for-seemingly-no-reason))
  *changed function calls to properly send d so that saving could be possible from the prompt

# 1.0.0 [Release]

  +added config.h back correctly, using conditions to check which .h file is including it
  +added ability to exit via Ctrl+D

# 1.1.0

  +added constant VERSION
  +started versioning

# 1.2.0

  -removed d->coin_roll_q,d,n, and p in favor of calculating them

# 1.3.0

  +fleshed out calculations, fixed oversights

# 1.4.0

  *changed file format to [%010d,%010d,...] for 32-bit int support (so billionaires can use this too!)

# 1.5.0

  *adjusted saving/loading methods in data.c
  -removed extraneous members from struct data in data.h
  +started keeping archives of versions
  +wrote this changelog, wracking my brain to remember everything I did.

# 1.05

  *changed version numbering format [x.y{.z}] format for sorting considerations
    Explanation:
      x = Major version
      y = Minor version
      z = patch, and is only written if it is > 0 (e.g. 1.5.0 is written 1.05, and 1.5.1 is written 1.05.1)

# 1.06

  -removed constant VERSION; user shouldn't be able to change it willy-nilly
  +added version.c
    +struct version
    +void print_version() to build version string and print it
    +void set_version() to se version string. Version string is now held in version.c, which makes sense.

# 1.06.1

  *changed "v" in "version" to a capital "V"

# 1.06.2

  *changed compare_strings() to work properly

# 1.07

  +added add() function, with entry in help

# 1.7

  *changed versioning back to old method, now format is
    x.y when z is 0 and
    x.y.z when z is > 0

# 1.7.1

  [BUG] "add" wasnt being matched in prompt
    added \n to end of "add"
