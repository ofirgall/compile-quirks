### Buildsystem vs Compiler ###

Buildsystem isn't a compiler.
Buildsystem is CMake, Makefile, SCons, that Visual Studio thing, etc.

Buildsystem is generating compiler commands, most build systems will let you `VERBOSE` the commands they are generating.

### The Compiler ###

* From simplification reasons the information might be inaccurate

The "compiler" is divided to 4 steps (tools).

######################################################################################################################################################

                                ┌──────────────────────────────────────────────────────────────────────────────────────────────────┐
                                │                                             GCC                                                  │
                                │                                                                                                  │
   ┌────────────┐ .c/.cpp files │  ┌─────────────┐  PreProccsed Code  ┌────────┐ Assembly Code  ┌─────────┐ Object File   ┌──────┐ │
   │Source Files│───────────────┼─►│Pre-Proccesor│──────────────────► │Compiler├──────────────► │Assembler├─────────────► │Linker├─┼────► ELF
   └────────────┘   main.c      │  │    (cpp)    │      main.i        │ (cc1)  │    main.s      │  (as)   │    main.o     │ (ld) │ │
                    sum.c       │  └─────────────┘      sum.i         └────────┘    sum.s       └─────────┘    sum.o      └──────┘ │   HelloWorld.elf
                                │                                                                                                  │
                                └──────────────────────────────────────────────────────────────────────────────────────────────────┘

######################################################################################################################################################

We can use every tool as itself but its more convenient to use a "pipeline" tool such as `gcc`, we can tell gcc to stop in any step to examine the output.

`gcc main.c -o main.elf` -> Will go through all the steps, Output: main.elf
`gcc main.c -E > main.i` - Will stop after the Pre-Proccesor, Output: main.i
`gcc main.c -S` - Will stop after the Compiler, Output: main.s
`gcc main.c -c` - Will stop after the Assembler, Output: main.o
