# QDhrystone

QDhrystone is a Qt front end for the [Dhrystone](https://en.wikipedia.org/wiki/Dhrystone) benchmark.
It runs the benchmark once, and then one instance per CPU core in parallel, and shows both scores.

The benchmark itself is an external program, `dry`, run in batch mode (`dry -b`):
on Linux it must be in the `PATH`, on Windows a prebuilt copy is embedded in the executable.

## Build

Requirements: CMake 3.19 or newer and Qt 6 (Widgets).

```
cmake -B build
cmake --build build
```

## License

Copyright (C) 2015 Matteo Croce

QDhrystone is released under the GNU General Public License version 3 or later, see [COPYING](COPYING).
