#include "./c6.c"

#define emit printf

int obj_toasm(int *entry, int *code, int codeLen, char *data, int dataLen) {
  int *p, i, n, step, a, t;
  char *dp;
  printf("	.section	.rodata\n.stab:	.ascii	\"");
  dp = data;
  while (dp<data+dataLen) {
    if (*dp == '\n')
      printf("\\n");
    else if (*dp == '\0')
      printf("\\0");
    else
      printf("%c", *dp);
    dp++;
  }
  printf("\"\n");
  printf("	.text\n	.globl	main\n	.type	main, @function\nmain:\n");
  pc=code; // 第一個指令沒填入，跳過
  while (pc<code+codeLen-1) {
    emit(".L%d: ", pc+1-code);
    printf("# ");
    printInstr(pc, code, data);
    i=*++pc;
    emit("\t");
    if      (i == LEA) { n=*++pc; emit("movq $%d, %%rax\n\tleaq (%%rbp,%%rax,%d), %%rax", n, sizeof(int));  }
    else if (i == IMM) { n=*++pc; emit("movq $%d, %%rax", n); }
    else if (i == ADDR){ n=*++pc; emit("leaq .stab(%%rip), %%rax\n\taddq $%d,%%rax", (char*)n-data); }
    else if (i == JMP) { n=*++pc; emit("jmp .L%d", (int*)n-code); }
    else if (i == JSR) { n=*++pc; emit("call .L%d", (int*)n-code); }
    else if (i == BZ)  { n=*++pc; emit("cmp $0, %%rax\n\tjeq .L%d", (int*)n-code); }    
    else if (i == BNZ) { n=*++pc; emit("cmp $0, %%rax\n\tjne .L%d", (int*)n-code); } 
    else if (i == ENT) { n=*++pc; emit("pushq %%rbp\n\tmovq %%rsp, %%rbp\n\tsubq $%d, %%rsp", n*sizeof(int)); }
    else if (i == ADJ) { n=*++pc; } // 由於函數 call 已用 popq 處理，所以不需再調整
    else if (i == LEV) { emit("popq %%rbp\n\tret"); }
    else if (i == LI)  { emit("movq 0(%%rax), %%rax"); }
    else if (i == LC)  { emit("movb 0(%%rax), %%al"); }
    else if (i == SI)  { emit("pushq %%rax"); }
    else if (i == SC)  { emit("pushb %%al"); } 
    else if (i == PSH) { emit("pushq %%rax"); }

    else if (i == OR)  { emit("popl %%rbx\n\tor %%rbx, %%rax\n"); }
    else if (i == XOR) { emit("popl %%rbx\n\txor %%rbx, %%rax\n"); }
    else if (i == AND) { emit("popl %%rbx\n\tand %%rbx, %%rax\n"); }
    else if (i == EQ) { emit("popl %%rbx\n\teq %%rbx, %%rax\n"); }
    else if (i == NE) { emit("popl %%rbx\n\tne %%rbx, %%rax\n"); }
    else if (i == LT) { emit("popl %%rbx\n\tlt %%rbx, %%rax\n"); }
    else if (i == GT) { emit("popl %%rbx\n\tgt %%rbx, %%rax\n"); }
    else if (i == LE) { emit("popl %%rbx\n\tle %%rbx, %%rax\n"); }
    else if (i == GE) { emit("popl %%rbx\n\tge %%rbx, %%rax\n"); }
    else if (i == SHL) { emit("popl %%rbx\n\tshl %%rbx, %%rax\n"); }
    else if (i == SHR) { emit("popl %%rbx\n\tshr %%rbx, %%rax\n"); }
    else if (i == ADD) { emit("popl %%rbx\n\tadd %%rbx, %%rax\n"); }
    else if (i == SUB) { emit("popl %%rbx\n\tsub %%rbx, %%rax\n"); }
    else if (i == MUL) { emit("popl %%rbx\n\tmul %%rbx, %%rax\n"); }
    else if (i == DIV) { emit("popl %%rbx\n\tdiv %%rbx, %%rax\n"); }
    else if (i == MOD) { emit("popl %%rbx\n\tmod %%rbx, %%rax\n"); }

    else if (i == OPEN) { emit("popq %%rdi\n\tpopq %%rsi\n\tcall open@PLT"); } // a = open((char *)sp[1], *sp); // 開檔
    else if (i == READ) { emit("popq %%rdi\n\tpopq %%rsi\n\tcall read@PLT"); } // a = read(sp[2], (char *)sp[1], *sp); // 讀檔
    else if (i == WRIT) { emit("popq %%rdi\n\tpopq %%rsi\n\tcall write@PLT"); } //  a = write(sp[2], (char *)sp[1], *sp); // 寫檔
    else if (i == CLOS) { emit("popq %%rdi\n\tcall close@PLT"); } //  a = close(*sp); // 關檔
    else if (i == PRTF) { // PRTF 後面都跟著 ADJ #參數個數
      n = pc[2]; // pc[1] 就是取得 #參數個數，於是 t 指向堆疊參數尾端
      while (n>0) { // 參數前六個放在 rdi,rsi,rcx,rdx,r8, r9
        if (n == 1) emit("popq %%rdi\n\t");
        if (n == 2) emit("popq %%rsi\n\t");
        if (n == 3) emit("popq %%rcx\n\t");
        if (n == 4) emit("popq %%rdx\n\t");
        if (n == 5) emit("popq %%r8\n\t");
        if (n == 6) emit("popq %%r9\n\t");
        n--;
      }
      emit("call printf@PLT");
      // a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]);  // printf("....", a, b, c, d, e)
    }
    else if (i == MALC) { emit("popq %%rdi\n\tcall malloc@PLT"); } // a = (int)malloc(*sp); // 分配記憶體
    else if (i == FREE) { emit("popq %%rdi\n\tcall malloc@PLT"); } //  free((void *)*sp); // 釋放記憶體
    else if (i == MSET) { emit("popq %%rdi\n\tpopq %%rsi\n\tpopq %%rcx\n\tcall memset@PLT"); } //   a = (int)memset((char *)sp[2], sp[1], *sp); // 設定記憶體
    else if (i == MCMP) { emit("popq %%rdi\n\tpopq %%rsi\n\tpopq %%rcx\n\tcall memcmp@PLT"); } //    a = memcmp((char *)sp[2], (char *)sp[1], *sp); // 比較記憶體
    else if (i == EXIT) { emit("popq %%rdi\n\tcall exit@PLT"); } //   { printf("exit(%d) cycle = %d\n", *sp, cycle); return *sp; } // EXIT 離開
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
  // obj_dump(pc, code, codeLen, data, dataLen);
  // printf("=========== obj_toasm() ===============\n");
  obj_toasm(pc, code, codeLen, data, dataLen);
  // printf("codeSize=%d\n", codeSize);
}

