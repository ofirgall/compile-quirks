#######################

Let's take a look at the code.
In `main.c` there is `extern` global_counter and a `static` static_global_counter.
In `sum.c` there is `global_counter` `static_global_counter` and `global_counter_5`.
In addition there is `function_counter` which is static inside a function scope.

Take a look at the code and expect the output.
Compile and compare the your expectations.
`gcc main.c sum.c && ./a.out`

#######################

Now lets take a look at the symbol table of `main` and `sum`.
`readelf -s --wide main.o`

We can see the `UND` functions we are using like the previous example, `sum`, `printf`, `print_counters`, we can also see `global_counter` is `UND` too.

`global_counter` is `UND` because its marked as `extern`, it isn't a function it is a global variable, which requires memory to be saved in.

We can learn from that what is a symbol, a symbol is everything that requires memory, functions, global variables and more.

#######################

A deeper look at the symbol table.

Num: index of the symbol
Value: offset of the symbol from the start of the binary section
Size: the size of the symbol
Type: the type of the symbol (FILE, FUNC, OBJECT[var], NOTYPE[undef ref])
Bind: "scope" of the symbol, and more (GLOBAL, LOCAL)
Vis: visibility of the symbol (we won't talk about it here)
Ndx: The section index of the symbol
Name: The name of the symbol

Let's analyze the symbols of `sum`
`readelf -s --wide sum.o`

- The functions are present.
- The `static` function is binded to `LOCAL` which means the linker won't use it as a reference.
- `global_counter` is binded to `GLOBAL` and resides in in section `X`
- `static_global_counter` is binded to `LOCAL` and resides in section `X`
- `global_counter_5` is binded to `GLOBAL`and resides in secition `Y`
- We can see 2 `function_counter` with suffix, the compiler adds the function id suffix to make it unique for each function, that way it doesn't overrides the symbol.

------

What is section `X` and section `Y`?
Let's take a look at the section table.
`readelf -S sum.o`

Section `X` is `.bss` and section `Y` is `.data`, lets look at the difference.

Common sections:
.text - The actual code
.bss - Global data thats start initialized with zeros
.data - Data with initial value that can be changed while running
.rodata - Read-only data, data with initial value that can't be changed while running, aka `const`

How `.bss` works and why it's not just `.data`, bss is marked as NOBITS (NOLOAD), which means that the actual `.bss` isn't resides in the binary section of the ELF it's just a "reserved" area that the loader (the kernel) will reset the section in runtime, that way we can allocate a lot of data without taking diskspace.
