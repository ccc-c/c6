# C6 -- 700 行的 C 語言編譯器

* 原作者 -- Robert Swierczek, https://github.com/rswier/
* 原專案 -- https://github.com/rswier/c4
* 修改者 -- 陳鍾誠

## 使用方式

建議在 Linux 下編譯本專案 (WSL 亦可，Windows 的 MinGW 比較容易有錯)

```
$ sudo apt update
$ sudo apt install gcc-multilib

$ make
gcc -w -g -m32 c6.c -o c6
gcc -w -g -m32 genasm.c -o genasm
gcc -w -g -m32 jit.c -o jit -ldl

$ ./c6 test/hello.c
hello, world
exit(0) cycle = 9

$ ./c6 test/sum.c
sum(10)=55
exit(0) cycle = 303

$ ./c6 test/fib.c
f(7)=13
exit(8) cycle = 920
```

## 自我編譯

```
$ ./c6 c6.c test/fib.c
f(7)=13
exit(8) cycle = 920
exit(8) cycle = 147464

$ ./c6 c6.c c6.c test/fib.c
f(7)=13
exit(8) cycle = 920
exit(8) cycle = 147464
exit(8) cycle = 24476550
```

## 印出組合語言 (堆疊機)

```
$ ./c6 -s test/hello.c
1: #include <stdio.h>
2:
3: int main()
4: {
5:   printf("hello, world\n");
    1:F7D47014     ENT  0
    3:F7D4701C     ADDR 0:F7D06010
    5:F7D47024     PSH
    6:F7D47028     PRTF
    7:F7D4702C     ADJ  1
6: }
    9:F7D47034     LEV
```

## 印出執行過程

```
$ ./c6 -d test/hello.c
    1:F7C5E014     ENT  0
    3:F7C5E01C     ADDR 0:F7C1D010
    5:F7C5E024     PSH
    6:F7C5E028     PRTF
hello, world
    7:F7C5E02C     ADJ  1
    9:F7C5E034     LEV
 -67586:F7C1C008     PSH
 -67585:F7C1C00C     EXIT
exit(13) cycle = 8
```