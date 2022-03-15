

windows 中 open 後 read 會讀不完全，於是

```cpp
int obj_load(int fd) {
  int *codep, *entry, len;
  char *datap;
  read(fd, &entry, sizeof(int));
  read(fd, &codep, sizeof(int));
  read(fd, &codeLen, sizeof(int));
  read(fd, &datap, sizeof(int));
  read(fd, &dataLen, sizeof(int));
  len = read(fd, code0, codeLen*sizeof(int)); // 這裡會讀不完全，然後就變成檔案結束了。
  printf("read code len=%d codeLen*sizeof(int)=%d\n", len, codeLen*sizeof(int));
  len = read(fd, data0, dataLen);
  printf("read data len=%d\n", len);
  pc = code0 + (entry-codep);
  obj_relocate(code0, codeLen, codep, datap, code0, data0);
}
```

所以目前只能在 linux 當中跑。
