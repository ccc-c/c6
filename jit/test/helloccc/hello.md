```
wsl> make
gcc -w -g -D__C6__ c6.c -o c6
gcc -w -g    jit/jit.c   -o jit/jit
wsl> ./c6 -s jit/test/hello.c
could not open(jit/test/hello.c)
wsl> ./c6 -s jit/test/hello/hello.c
1: #include <stdio.h>
2:
3: int main()
4: {
5:   printf("hello, world\n");
    1:5F388018     ENT  0
    3:5F388028     ADDR 0:5F347010
    5:5F388038     PSH
    6:5F388040     PRTF
    7:5F388048     ADJ  1
6: }
    9:5F388058     LEV
```