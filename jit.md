# jit

## build & run

```
$ wsl
wsl> make clean
rm -f c6 genasm jit
wsl> make
gcc -w -g -m32 c6.c -o c6
gcc -w -g -m32 genasm.c -o genasm
gcc -w -g -m32 jit.c -o jit -ldl
wsl> ./jit_test.sh hello
Compile test/hello.c success!
Output: test/hello.vm
hello, world
wsl> ./jit_test.sh sum
Compile test/sum.c success!
Output: test/sum.vm
sum(10)=55
wsl> ./jit_test.sh fib
Compile test/fib.c success!
Output: test/fib.vm
f(7)=13
```
