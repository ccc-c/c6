# C4 編譯器的使用方式

## 用 gcc 編譯 C4

```
$ gcc -m32 c4.c -o c4
```

## 範例: hello.c

* [hello.c](../test/hello.c)

```
$ ./c4 test/hello.c
hello, world
exit(0) cycle = 9

$ ./c4 -s test/hello.c       // 加上 -s 參數可以印出組合語言
1: #include <stdio.h>
2:
3: int main()
4: {
5:   printf("hello, world\n");
    ENT  0
    IMM  8454232
    PSH
    PRTF
    ADJ  1
6:   return 0;
    IMM  0
    LEV
7: }
    LEV

$./c4 -d test/hello.c       // 加上 -d 參數可以印出執行過程
1> ENT  0
2> IMM  6946904
3> PSH
4> PRTF
hello, world
5> ADJ  1
6> IMM  0
7> LEV
8> PSH
9> EXIT
exit(0) cycle = 9
```

## 範例: sum.c

* [sum.c](../test/sum.c)

```
$ ./c4 test/sum.c
sum(10)=55
exit(0) cycle = 303
$ ./c4 -s sum.c
1: #include <stdio.h>
2:
3: // sum(n) = 1+2+...+n
4: int sum(int n) {
5:   int s;
6:   int i;
7:   s=0;
    ENT  2
    LEA  -1
    PSH
    IMM  0
    SI
8:   i=1;
    LEA  -2
    PSH
    IMM  1
    SI
9:   while (i <= n) {
    LEA  -2
    LI
    PSH
    LEA  2
    LI
    LE
    BZ   0
10:     s = s + i;
    LEA  -1
    PSH
    LEA  -1
    LI
    PSH
    LEA  -2
    LI
    ADD
    SI
11:     i ++;
    LEA  -2
    PSH
    LI
    PSH
    IMM  1
    ADD
    SI
    PSH
    IMM  1
    SUB
12:   }
13:   return s;
    JMP  11206796
    LEA  -1
    LI
    LEV
14: }
    LEV
15:
16: int main() {
17:   printf("sum(10)=%d\n", sum(10));
    ENT  0
    IMM  11468888
    PSH
    IMM  10
    PSH
    JSR  11206740
    ADJ  1
    PSH
    PRTF
    ADJ  2
18:   return 0;
    IMM  0
    LEV
19: }
    LEV
```

## 範例: fib.c

* [fib.c](../test/fib.c)

```
$ ./c4 test/fib.c
f(7)=13
exit(8) cycle = 920
$ ./c4 -s test/fib.c
1: #include <stdio.h>
2:
3: int f(n) {
4:   if (n<=0) return 0;
    ENT  0
    LEA  2
    LI
    PSH
    IMM  0
    LE
    BZ   0
    IMM  0
    LEV
5:   if (n==1) return 1;
    LEA  2
    LI
    PSH
    IMM  1
    EQ
    BZ   0
    IMM  1
    LEV
6:   return f(n-1) + f(n-2);
    LEA  2
    LI
    PSH
    IMM  1
    SUB
    PSH
    JSR  11403348
    ADJ  1
    PSH
    LEA  2
    LI
    PSH
    IMM  2
    SUB
    PSH
    JSR  11403348
    ADJ  1
    ADD
    LEV
7: }
    LEV
8:
9: int main() {
10:   printf("f(7)=%d\n", f(7));
    ENT  0
    IMM  11665496
    PSH
    IMM  7
    PSH
    JSR  11403348
    ADJ  1
    PSH
    PRTF
    ADJ  2
```
