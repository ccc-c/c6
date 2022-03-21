# jit

```
wsl> gcc -g -w -DOS=LINUX jit.c -o jit
wsl> ./jit test/hello/hello.vm
entry: 0xDA0A2018
code: start=0xDA0A2010 length=0xA
    1:DA0A2018     ENT  0
    3:DA0A2028     ADDR 0:DA061010
    5:DA0A2038     PSH
    6:DA0A2040     PRTF
    7:DA0A2048     ADJ  1
    9:DA0A2058     LEV
data: start=0xDA061010 length=0x10
hello, world

=========== obj_toasm() ===============
        .section        .rodata
.LC0:   .string "hello, world\n\0\0\0"
        .text
        .globl  main
        .type   main, @function
main:
#     1:DA0A2018     ENT  0
        pushq %rbp
        movq %rsp, %rbp
#     3:DA0A2028     ADDR 0:DA061010
        leaq    .LC0(%rip), %rax
#     5:DA0A2038     PSH
        pushq %rax
#     6:DA0A2040     PRTF
        popq %rdi
        call printf@PLT
        movl $0, %eax
#     7:DA0A2048     ADJ  1

#     9:DA0A2058     LEV
        popq %rbp
        ret
```