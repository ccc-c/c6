# 簡介 -- C4 編譯器 

[C4](https://github.com/rswier/c4) 是 [Robert Swierczek](https://github.com/rswier/) 寫的一個小型 C 語言編譯器，全部 527 行的原始碼都在 [c4.c](https://github.com/cccbook/c4/blob/master/c4.c) 裏 。

C4 編譯完成後，會產生一種《堆疊機機器碼》放在記憶體內，然後 [虛擬機](vm) 會立刻執行該機器碼。

以下是 C4 編譯器的用法，C4 可以進行《自我編譯》:

```
gcc -m32 -o c4 c4.c  (you may need the -m32 option on 64bit machines)
./c4 test/hello.c
./c4 -s test/hello.c

./c4 c4.c test/hello.c
./c4 c4.c c4.c test/hello.c
```

C4 在 Windows / Linux / MAC 中都可以執行，在 windows 必須在有支援 open, read 這些 POSIX 檔案函式庫環境下才能編譯！

您也可以閱讀 [更詳細的 C4 說明書](./README.md) 以進一步學習 C4。







