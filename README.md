This is a very simple example of **tinycc**'s dynamic compilation feature.

Your C application can compile another C source file(s). You can play around with this running:

```
make
./main target.c
```

You should see two strings being printed. Keep the app running and edit strings in the `target.c`
file. The running application should start printing the new strings.

I'll hopefully update this with checking if the file was modified, instead of running the basic
`while` loop.

## Contents of this repo

This example should be self contained. You should need to install anything for it to work. The files
listed below can be fetched from the **tinycc** build directory. Just clone the **tinycc** repo and
build it.

- `lib/libtcc1.a` - a runtime dependency necessary for JIT (just-in-time compilation).
- `lib/libtcc.a` - a compile time dependency. This gets linked statically.
- `include/libtcc.h` - header for the **tinycc** API.
- `include/tcclib.h` - header runtime `libtcc1.a` runtime dependency.
