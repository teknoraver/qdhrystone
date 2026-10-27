# QDhrystone

QDhrystone is a Qt front end for the [Dhrystone](https://en.wikipedia.org/wiki/Dhrystone) benchmark.
It runs the benchmark once, and then one instance per CPU core in parallel, and shows both scores.

The benchmark, in `dhrystone/`, is built into the same executable:
the GUI runs it by launching itself once per core, as Dhrystone can't run in threads.

## Build

Requirements: CMake 3.19 or newer and Qt 6 (Widgets).

```
cmake -B build
cmake --build build
```

## License

Copyright (C) 2015 Matteo Croce

QDhrystone is released under the GNU General Public License version 3 or later, see [COPYING](COPYING).

The Dhrystone benchmark in `dhrystone/` comes from [benchs](https://github.com/teknoraver/benchs),
it was written by Reinhold P. Weicker and modified by Steven Pemberton and Matteo Croce.
