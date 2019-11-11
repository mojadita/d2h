# d2h -- dump hex binary ieee-752 floating point numbers.

This program allows you to see how floating point numbers are
stored in memory, according to the rules of IEEE-752 binary
format.

## Compilation

Just run

```
make
```

in the main directory of d2h.

## Running

The program is called with the following syntax:

```
Usage: d2h [ options ... ] [ file ... ]
Options:
  -m mode.  The possible modes are strings in the set 
     {"flt-le", "flt-be", "dbl-le", "dbl-be"} meaning
     dbl to use double numbers and flt to use float
     number.  'le' means little-endian while 'be' means
     big-endian numbers.  Default is "flt-be".
  -v Be verbose.  Program prints to 'stderr' input filenames,
     as they are processed.
  -?, -h
     Help.  Shows this help screen.
```

If no files are specified, the program runs interactively,
printing the converted input as soon it is recognized.

**Input format:** to convert from binary to floating point, just
input four hex numbers for `float` single precision numbers,
while eight hex numbers are used for `double` double precision
numbers.  If you input a single floating point in the input, it
is scanned as a `float` or `double`, depending on the mode
selected.  Conversion is made and output it done in hex mode.

Enjoy it!!
