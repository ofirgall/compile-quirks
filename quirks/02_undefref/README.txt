#######################

If we try to compile `main.c` without any flags the compiler wouldn't find <sum.h> and throw *compiler* error.
`gcc main.c`

We need to pass `-I<path>` to tell the compiler where to find our header files.
`gcc main.c -Isum`
This will throw *linker* error, "undefined reference to 'sum'"

To solve this issue we need to pass the compiler `sum/sum.c`
`gcc -Isum main.c sum/sum.c`
`gcc -Isum sum/sum.c main.c` - We can reverse the order of the files too

#######################

The way we compiled before is wrong, it tells the compiler to compile all the files to 1 executable.
Its wrong because this way we need to compile *all* the files for each executable.

E.g:
	We have 2 programs foo, and boo, both of them need to use sum.c, if we compile both of them like this.
	`gcc foo.c sum.c`
	`gcc boo.c sum.c`

	We waste time to compile `sum.c` twice, instead we can *compile*it to an object file and *link* it later.
	`gcc sum.c -c` -> Will output sum.o
	`gcc foo.c sum.o`
	`gcc boo.c sum.o`

In large projects with common files it saves alot of time.

#######################

What is `undefined refernce`, lets look at the object file.
There are 2 main tools to examine object files, `objdump` and `readelf`.

Lets take a look at the object file header.
`gcc main.c -c -Isum`
`readelf -h main.o`
We can see some metadata about our object file, to which arch it compiled, which ABI and such.

Lets take a look at the symbols.
`readelf -s main.o`

We will take a deeper look at the next example, for now we will focus on the `UND` mark.
We can see `sum` and `printf` are marked as `UND` which means the `main.o` calls them but don't where they are yet.

Lets take a look at `sum.o` symbols
`gcc sum/sum.c -c`
`readelf -s sum.o`
We can see `sum` isn't `UND` which means the code is there.

When we "compile" `sum.o` and `main.o` we actually just *link* them.
The linker is replacing all the `UND` symbols with the actual address of the function
`gcc main.o sum.o`

#######################

In the symbol table we can see that main doesn't really know how `sum` looks, thats means he doesn't really need the header file.
If we delete the "#include <sum.h>" and compile, the compiler will *warn* us he doesn't know how the functions looks but its ok.

If we examine the object files they will look exactly the same.
