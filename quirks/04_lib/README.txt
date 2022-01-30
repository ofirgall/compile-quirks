#######################

We have a 2nd function of sum `sum_abs` which using `my_abs` to absolute the numbers.
We can compile and see the output
`gcc main.c sum.c my_abs.c && ./a.out`

Lets compile each source to object.
`gcc main.c -c`
`gcc sum.c -c`
`gcc my_abs.c -c`

We can take a look at each object file but we won't see anything new.

#######################

`sum` is dependent on `my_abs`
Let's say we want to ship `sum` as one file and not both of the files.
We can ship both of them as library (archive).
To pack them both as library we are going to use `ar` tool (short for archive)
`ar cr libsum.a sum.o my_abs.o` this will create `libsum.a`

Now we can "link" with `libsum.a` instead.
`gcc main.c libsum.a`
`gcc main.o libsum.a`

This is the "wrong" way to link with a library.
The right way is using the "-l" flag and "-L" flag
"-L" - Tells the linker where to find the library.
"-l" - Tells the linker which libraries to search for.

Let's link it.
`gcc main.o -L. -lsum`
Notice we used 'sum' and not 'libsum.a' the reason the linker expands `sum` to `libsum.a` is the libraries naming conventions, libraries can be either shared(.so)/static(.a) and can have revision numbers `libfoo.so.1.2.3`.

#######################

Libraries order is weird.
Let's change sum behavior, change the `+` to `-` and compile it.
`gcc sum.c -c`

Lets create `false_sum/libsum.a` with the `-` behavior
`mkdir false_sum && ar cr false_sum/libsum.a sum.o my_abs.o`

Now lets link and execute with different order.
`gcc main.o libsum.a false_sum/libsum.a && ./a.out`
`gcc main.o false_sum/libsum.a libsum.a && ./a.out`

The same "issue" is with "-L" flag too.
`gcc main.o -L. -lsum -Lfalse_sum && ./a.out`
`gcc main.o -Lfalse_sum -L. -lsum && ./a.out`
