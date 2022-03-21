#include "../c6.c"

#define emit printf

int obj_toasm(int *entry, int *code, int codeLen, char *data, int dataLen) {
  int *p, i, arg, step, a, t;
  char *dp;
  printf("	.section	.rodata\n.LC0:	.string	\"");
  dp = data;
  while (*dp) {
    if (*dp == '\n') printf("\\n"); else printf("%c", *dp);
    dp++;
  }
  printf("\"\n");
  printf("	.text\n	.globl	main\n	.type	main, @function\nmain:\n");
  pc=code; // 第一個指令沒填入，跳過
  while (pc<code+codeLen-1) {
    printf("# ");
    printInstr(pc, code, data);
    // pc = pc+stepInstr(pc);
    i=*++pc;
	emit("\t");
    // printf("pc=%x i=%x\n", pc, i);
    // if      (i == LEA) { pc++; }                             // load local address 載入區域變數
    // else if (i == IMM) a = *pc++;                                         // load immediate 載入立即值
    if (i == ADDR) { emit("leaq	.LC0(%%rip), %%rax"); pc++; }                                // load address 載入位址
    // else if (i == JMP) pc = (int *)*pc;                                   // jump               躍躍指令
    // else if (i == JSR) { *--sp = (int)(pc + 1); pc = (int *)*pc; }        // jump to subroutine 跳到副程式
    // else if (i == BZ)  pc = a ? pc + 1 : (int *)*pc;                      // branch if zero     if (a==0) goto m[pc]
    // else if (i == BNZ) pc = a ? (int *)*pc : pc + 1;                      // branch if not zero if (a!=0) goto m[pc]
    else if (i == ENT) { emit("pushq %%rbp\n\tmovq %%rsp, %%rbp"); pc++; }     // enter subroutine   進入副程式
    else if (i == ADJ) { pc++; }                                   // stack adjust       調整堆疊
    else if (i == LEV) { emit("popq %%rbp\n\tret"); } // leave subroutine   離開副程式
    // else if (i == LI)  a = *(int *)a;                                     // load int           載入整數
    // else if (i == LC)  a = *(char *)a;                                    // load char          載入字元
    // else if (i == SI)  *(int *)*sp++ = a;                                 // store int          儲存整數
    // else if (i == SC)  a = *(char *)*sp++ = a;                            // store char         儲存字元
    else if (i == PSH) { emit("pushq %%rax"); }                       // push               推入堆疊

    // else if (i == OR)  a = *sp++ |  a; // a = a OR *sp
    // else if (i == XOR) a = *sp++ ^  a; // a = a XOR *sp
    // else if (i == AND) a = *sp++ &  a; // ...
    // else if (i == EQ)  a = *sp++ == a;
    // else if (i == NE)  a = *sp++ != a;
    // else if (i == LT)  a = *sp++ <  a;
    // else if (i == GT)  a = *sp++ >  a;
    // else if (i == LE)  a = *sp++ <= a;
    // else if (i == GE)  a = *sp++ >= a;
    // else if (i == SHL) a = *sp++ << a;
    // else if (i == SHR) a = *sp++ >> a;
    // else if (i == ADD) a = *sp++ +  a;
    // else if (i == SUB) a = *sp++ -  a;
    // else if (i == MUL) a = *sp++ *  a;
    // else if (i == DIV) a = *sp++ /  a;
    // else if (i == MOD) a = *sp++ %  a;

    // else if (i == OPEN) a = open((char *)sp[1], *sp); // 開檔
    // else if (i == READ) a = read(sp[2], (char *)sp[1], *sp); // 讀檔
    // else if (i == WRIT) a = write(sp[2], (char *)sp[1], *sp); // 寫檔
    // else if (i == CLOS) a = close(*sp); // 關檔
    else if (i == PRTF) { // PRTF 後面都跟著 ADJ #參數個數
      // t = sp + pc[1]; // pc[1] 就是取得 #參數個數，於是 t 指向堆疊參數尾端
      emit("popq %%rdi\n\tcall printf@PLT\n\tmovl $0, %%eax");
      // a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]);  // printf("....", a, b, c, d, e)
    }
    // else if (i == MALC) a = (int)malloc(*sp); // 分配記憶體
    // else if (i == FREE) free((void *)*sp); // 釋放記憶體
    // else if (i == MSET) a = (int)memset((char *)sp[2], sp[1], *sp); // 設定記憶體
    // else if (i == MCMP) a = memcmp((char *)sp[2], (char *)sp[1], *sp); // 比較記憶體
    // else if (i == EXIT) { printf("exit(%d) cycle = %d\n", *sp, cycle); return *sp; } // EXIT 離開
    else { emit("unknown instruction = %d!", i); return -1; } // 錯誤處理
    emit("\n");
  }

  // printf("data: start=0x%X length=0x%X\n", data, dataLen);

/*
  dp = data;
  while (dp<data+dataLen) {
    if (*dp == '\n') printf("\\n"); else printf("%c", *dp++);
  }
  printf("\n");
*/
}

int main(int argc, char *argv[]) {
  char *iFile;

  iFile = argv[1];
  fd = open(iFile, 0100000);
  // printf("fd=%d\n", fd);
  init();
  obj_load(fd);
  // printf("pc=%x code=%x codeLen=%x data=%x dataLen=%x\n", pc, code, codeLen, data, dataLen);
  obj_dump(pc, code, codeLen, data, dataLen);
  printf("=========== obj_toasm() ===============\n");
  obj_toasm(pc, code, codeLen, data, dataLen);
  // printf("codeSize=%d\n", codeSize);
}

