# jit

```
wsl> gcc -w -DOS=LINUX jit.c -o jit
wsl> ./jit test/hello/hello.vm
        .section        .rodata
.LC0:   .string "hello, world
"
#     1:21533018     ENT  0
#     3:21533028     ADDR 0:214F2010
#     5:21533038     PSH
#     6:21533040     PRTF
#     7:21533048     ADJ  1
#     9:21533058     LEA  0
```