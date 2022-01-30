#######################

6. Multiple def and weak keyword.
Compile with multiple weak methods.
Conflict with lib and object file.
Compile library with weak and show if the library is first its multi def if not its overiding

There are 2 files with function `sum`, one in `sum.c` and one in `math.c`.
Let's compile them and watch the output.
`gcc main.c -c`
`gcc sum.c -c`
`gcc math.c -c`
`gcc main.o sum.o math.o`

The *linker* raise a error for multiple definitions, there are 2 `sum` functions.
On the one hand we want to use our cool sum algorithm from `sum` but in the other hand we want to use `my_abs` from `math`.
How can we do it?

#######################

We can use the attribute `weak`, if we add `__attribute__((weak))` after the deceleration parenthesis.
This will tell the *compiler* to mark the function as WEAK.

After adding the attribute and compiling `math` again, let's take a look at the symbols.
`gcc math.c -c`
`readelf -s math.o`
We can see that sum is binded as "WEAK", this will tell the *linker* to de-prioritize this function and let other override it.

This will use our cool sum algorithm
`gcc main.o math.o sum.o && ./a.out`

Why its needed? Big libraries using thins attribute to let the program override the function call.
Used for hooks, default implementation (override printf for example).

E.g of hooks:
	void my_lib_func()
	{
		pre_my_lib_func();

		// my lib

		post_my_lib_func();
	}

	void pre_my_lib_func() __attribute__((weak))
	{
		// Stub default function
	}

	void post_my_lib_func() __attribute__((weak))
	{
		// Stub default function
	}

#######################

What will happen when there are 2 symbols with weak bindings.
The order of the function will affect the results.
Try it out with 2 weak attributes of both sums and change the order of the object files for the linker.

Weird behavior when 2 same symbols are in a archive.
When both symbols aren't WEAK a multiple definition will raise.
If 1 symbol is weak, the first symbol is used, even if its WEAK!!!!!!
If 2 symbols are weak, the first is used (like before).

`ar cr libmath.a sum.o math.o`
`ar cr libmath.a math.o sum.o`
