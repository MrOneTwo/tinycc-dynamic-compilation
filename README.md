This is a very simple example of tinycc's dynamic compilation feature.

Your C application can compile another C source file(s). You can play around with this running:

```
make
./main target.c
```

You should see two strings being printed. Keep the app running and edit strings in the `target.c`
file. The running application should start printing the new strings.

I'll hopefully update this with checking if the file was modified, instead of running the basic
`while` loop.
