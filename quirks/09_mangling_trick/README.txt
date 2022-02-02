#######################

After we know how name mangling works lets try to break the compiler.

Lets compile a `main` that using a `sum` of u64's but the implementation will be `u32`.
Let's take a look at our `main` symbols, using the `-m32` symbols will compile our program to 32bits.
`gcc main.cpp -c -m32`
`readelf -s main.o`
The main is using `_Z5c_sumyy`, which is `c_sum(unsigned long long, unsigned long long)`

Our `sum` exports symbols of `sum`, but what will happen if we change it to `_Z5c_sumyy`.
Let's change the `sum` function to `_Z5c_sumyy` but our function will use u32 instead.
`gcc sum.c -c -m32`
`readelf -s sum.o`

Our `sum` is C but exporting `C++` symbol.
Let's compile and run.
`gcc sum.o main.o -m32 && ./a.out`

The output is weird.. but why? Let's take a look at the assembly.
`objdump -D a.out -M intel`

```
000011cd <main>:
	............
	// `main` thinks `sum` is using 64bit params.
	// Because the program is 32bit it use the stack to pass 64bit params.
    11ee: c7 45 e8 ff ee dd cc    mov    DWORD PTR [ebp-0x18],0xccddeeff // Pushing lower a
    11f5: c7 45 ec bb aa 99 88    mov    DWORD PTR [ebp-0x14],0x8899aabb // Pushing upper a
    11fc: c7 45 f0 77 66 55 44    mov    DWORD PTR [ebp-0x10],0x44556677 // Pushing lower b
    1203: c7 45 f4 33 22 11 00    mov    DWORD PTR [ebp-0xc],0x112233    // Pushing upper b
    120a: ff 75 f4                push   DWORD PTR [ebp-0xc]
    120d: ff 75 f0                push   DWORD PTR [ebp-0x10]
    1210: ff 75 ec                push   DWORD PTR [ebp-0x14]
    1213: ff 75 e8                push   DWORD PTR [ebp-0x18]
    1216: e8 26 00 00 00          call   1241 <_Z5c_sumyy> // Calling our sum
	............

// To look at simpler `sum` let's dissasemble `sum.o`
// `objdump -D sum.o -M intel`
00000000 <_Z5c_sumyy>:
	.................
	10:   81 c3 02 00 00 00       add    ebx,0x2
	16:   83 ec 08                sub    esp,0x8
	19:   ff 75 08                push   DWORD PTR [ebp+0x8]
	1c:   8d 83 00 00 00 00       lea    eax,[ebx+0x0] // Popping sum:a which is `lower a`
	22:   50                      push   eax
	23:   e8 fc ff ff ff          call   24 <_Z5c_sumyy+0x24>
	28:   83 c4 10                add    esp,0x10
	2b:   83 ec 08                sub    esp,0x8
	2e:   ff 75 0c                push   DWORD PTR [ebp+0xc]
	31:   8d 83 0a 00 00 00       lea    eax,[ebx+0xa] // Popping sum:b which `upper a`
	37:   50                      push   eax
	38:   e8 fc ff ff ff          call   39 <_Z5c_sumyy+0x39>
	3d:   83 c4 10                add    esp,0x10
	40:   8b 55 08                mov    edx,DWORD PTR [ebp+0x8]
	43:   8b 45 0c                mov    eax,DWORD PTR [ebp+0xc]
	46:   01 d0                   add    eax,edx
	48:   8b 5d fc                mov    ebx,DWORD PTR [ebp-0x4]
	4b:   c9                      leave
	4c:   c3                      ret
```
