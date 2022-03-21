# hellovm 

```
wsl> gcc -fPIC hellovm2.s -o hellovm2

wsl> ./hellovm2
hello, world

wsl> gcc -c -fPIC hellovm2.s -o hellovm2

wsl> objdump -d hellovm2

hellovm2:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:   f3 0f 1e fa             endbr64
   4:   55                      push   %rbp
   5:   48 89 e5                mov    %rsp,%rbp
   8:   48 8d 05 00 00 00 00    lea    0x0(%rip),%rax        # f <main+0xf>
   f:   50                      push   %rax
  10:   5f                      pop    %rdi
  11:   e8 00 00 00 00          callq  16 <main+0x16>
  16:   b8 00 00 00 00          mov    $0x0,%eax
  1b:   5d                      pop    %rbp
  1c:   c3                      retq
```