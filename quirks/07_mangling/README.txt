#######################

One of C++ features are functions overloading, but how does it work?
Let's compile our `main` that uses `sum` with int and `sum` with double.
`gcc main.cpp -c`
`gcc sum.cpp -c`
`gcc sum.o main.o && ./a.out`

Let's take a deeper look in our object files.
`readelf -s sum.o`

We have 2 `sum` symbols but with weird names.. `_Z3sumii` and `_Z3sumdd`.
The addition to the names called "name mangling", it can decoded with `c++filt`.
`echo _Z3sumii | c++filt`
`readelf -s sum.o | c++filt`

The name mangling is used to tell the linker what is the exact type of the function.
When we look at the `main` symbols we can see it expects the same symbols.
`readelf -s main.o | c++filt`

We can also notice when the *linker* raises undefined reference error it tells which parameters the function has.
`gcc main.cpp`

```
main.cpp:(.text+0x1e): undefined reference to `sum(int, int)'
/usr/bin/ld: main.cpp:(.text+0x4e): undefined reference to `sum(double, double)'
```

Name mangling is used to scope our functions using prefixes for classes, namespaces, enum class and such.

#######################

Let's try to use a C function in our C++ main, uncomment the line that using `c_sum` and compile.
`gcc c_sum.c -c`
`gcc main.cpp -c`
`gcc main.o sum.o c_sum.o`

The linker raises undefined reference to `c_sum(int, int)`, notice it has params.
Let's take a look at the symbol tables.
`readelf -s main.o`
`readelf -s c_sum.o`

`main.o` expects `_Z5c_sumii` but `c_sum.o` defines `c_sum`, the linker can't resolve this.

To tell the compiler that our `main` want to use `c_sum` from C code we need to add, `extern "C"` at the deceleration.

One way to do that is wrap the `#include "c_sum.h"` with `extern "C"`:
	extern "C"
	{
		#include "c_sum.h"
	}

Its recommended to use it when we use library that we can't touch.

The better way to do it is inside the "library", add `extern "C"` when using C++:
	#ifdef __cplusplus
	extern "C" {
	#endif

	int c_sum(int a, int b);

	#ifdef __cplusplus
	} // extern "C"
	#endif

Now let's compile our files and watch the symbols.
`gcc main.cpp -c`
`readelf -s main.o`
`gcc main.o sum.o c_sum.o`

Note: The same rules applies to global variables which are symbols too.
