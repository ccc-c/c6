* https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_chapter/as_7.html#SEC72

.ascii "string"...
.ascii expects zero or more string literals (see section Strings) separated by commas. It assembles each string (with no automatic trailing zero byte) into consecutive addresses.

.asciz "string"...
.asciz is just like .ascii, but each string is followed by a zero byte. The "z" in `.asciz' stands for "zero".

```
wsl> gcc -g -w -DOS=LINUX jit.c -o jit
wsl> ./jit test/hello/hello.vm
entry: 0x6332C018
code: start=0x6332C010 length=0xA 
    1:6332C018     ENT  0
    3:6332C028     ADDR 0:632EB010
    5:6332C038     PSH
    6:6332C040     PRTF
    7:6332C048     ADJ  1
    9:6332C058     LEV
data: start=0x632EB010 length=0x10
hello, world

=========== obj_toasm() ===============
        .section        .rodata
.LC0:   .string "hello, world\n"
        .text
        .globl  main
        .type   main, @function
main:
#     1:6332C018     ENT  0
        pushq %rbp
        movq %rsp, %rbp
#     3:6332C028     ADDR 0:632EB010
        leaq    .LC0(%rip), %rax
#     5:6332C038     PSH
        pushq %rax
#     6:6332C040     PRTF
        popq %rdi
        call printf@PLT
        movl $0, %eax
#     7:6332C048     ADJ  1

#     9:6332C058     LEV
        popq %rbp
        ret
```



byte array:

https://stackoverflow.com/questions/39557010/int-vs-byte-for-creating-an-array-on-gnu-assembler