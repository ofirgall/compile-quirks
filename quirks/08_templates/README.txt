#######################

Let's take a look how template's symbols works and how static members works.

Let's compile our files.
`gcc main.cpp -c`
`gcc sum.cpp -c`
`gcc main.o sum.o`

The linker raises undefined reference error to our static member of Counter, `Counter<unsigned long>::counter`.
The static member needs memory hence it should be a symbol, to allocate a memory for a static member we use this syntax.
`type Class::member = value;`
We can't place this in the header file, each file that would use this header will create his own symbol and multiple references will raise.

This will create our symbol, we allocate memory for our static member once at `Counter.cpp`.
`gcc Counter.cpp -c`
`readelf -s Counter.o | c++filt`

Let's link it.
`gcc main.o sum.o Counter.o && ./a.out`

#######################

Let's take a look how template symbols works.
We know that `main` and `sum` *including* `Counter.h` which copies *implementation* to each object.
How does the symbol's not colliding and causing "multiple definitions" error.
Let's take a look at the symbol tables.
`readelf -s main.o | c++filt`
`readelf -s sum.o | c++filt`

We can see the template symbols are binded to WEAK which let them override each other as we saw in `05_multidef`
