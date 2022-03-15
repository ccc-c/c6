
```
$ ./c6 test/sum.c -o test/sum.o
entry=10617432 code=10616976 codeLen=76 data=10879136 dataLen=16
code:
    1     ENT  2
    3     LEA  -1
    5     PSH
    6     IMM  0
    8     SI
    9     LEA  -2
   11     PSH
   12     IMM  1
   14     SI
   15     LEA  -2
   17     LI
   18     PSH
   19     LEA  2
   21     LI
   22     LE
   23     BZ   52
   25     LEA  -1
   27     PSH
   28     LEA  -1
   30     LI
   31     PSH
   32     LEA  -2
   34     LI  
   35     ADD
   36     SI
   37     LEA  -2
   39     PSH
   40     LI
   41     PSH
   42     IMM  1
   44     ADD
   45     SI
   46     PSH
   47     IMM  1
   49     SUB
   50     JMP  15
   52     LEA  -1
   54     LI
   55     LEV
   56     LEV
   57     ENT  0
   59     ADDR 0
   61     PSH
   62     IMM  10
   64     PSH
   65     JSR  1
   67     ADJ  1
   69     PSH
   70     PRTF
   71     ADJ  2
   73     IMM  0
   75     LEV
   76     LEV
data:sum(10)=%d

write code len=608 codeLen*sizeof(int)=608
$ ./c6 -u test/sum.o
entry=10486360 code=10485904 codeLen=76 data=10748064 dataLen=16
code:
    1     ENT  2
    3     LEA  -1
    5     PSH
    6     IMM  0
    8     SI
    9     LEA  -2
   11     PSH
   12     IMM  1
   14     SI
   15     LEA  -2
   17     LI
   18     PSH
   19     LEA  2
   21     LI
   22     LE
   23     BZ   52
   25     LEA  -1
   27     PSH
   28     LEA  -1
   30     LI
   31     PSH
   32     LEA  -2
   34     LI
   35     ADD
   36     SI
   37     LEA  -2
   39     PSH
   40     LI
   41     PSH
   42     IMM  1
   44     ADD
   45     SI
   46     PSH
   47     IMM  1
   49     SUB
   50     JMP  15
   52     LEA  -1
   54     LI
   55     LEV
   56     LEV
   57     ENT  0
   59     ADDR 0
   61     PSH
   62     IMM  10
   64     PSH
   65     JSR  1
   67     ADJ  1
   69     PSH
   70     PRTF
   71     ADJ  2
   73     IMM  0
   75     LEV
   76     LEA  0
data:sum(10)=%d
```
