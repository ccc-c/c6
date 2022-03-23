// 修改來源 -- https://github.com/EarlGray/c4
// 指令說明 -- https://github.com/EarlGray/c4/blob/master/JIT.md
#define NO_MAIN
#include "./c6.c"
#include <sys/mman.h>
#include <dlfcn.h>
#include <assert.h>

void *dl;
char *je,      // current position in emitted native code
     **jitmap;  // maps c4 bytecode index into native code position
int (*jitmain)();
char *jitmem; // executable memory for JIT-compiled native code

int jit_build() {
  int tmp, i, *cp;

  dl = dlopen(0, RTLD_LAZY | RTLD_GLOBAL); // RTLD_LAZY = 1
  assert(dl);
  // setup jit memory
  //jitmem = mmap(0, poolsz, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
  jitmem = mmap(0, poolsz, 7, 0x1002 | MAP_ANON, -1, 0);
  if (!jitmem) { printf("could not mmap(%d) jit executable memory\n", poolsz); return -1; }

  jitmap = (char **)(jitmem + poolsz / 2);

  // first pass: emit native code
  cp = code + 1; je = jitmem; line = 0;
  while (cp < code+codeLen) {
    i = *cp;
    if (src) {
        // while (line < srcmap[cp - code]) {
        //     line++; printf("% 4d | %.*s", line, linemap[line + 1] - linemap[line], linemap[line]);
        // }
        printf("0x%05x (%p):\t%8.4s", cp - code, je, &op[i * 5]);
        if (i <= ADJ) printf(" 0x%x\n", *(cp + 1)); else printf("\n");
    }
    jitmap[cp - code] = je;  // for later relocation of JMP/JSR/BZ/BNZ
    cp++;
    if (i == LEA) {
      i = 4 * *cp++; if (i < -128 || i > 127) { printf("jit: LEA out of bounds\n"); return -1; }
      *(int*)je = 0x458d; je = je + 2; *je++ = i;  // leal $(4 * n)(%ebp), %eax
    }
    else if (i == ENT) {
      i = 4 * *cp++; if (i < -128 || i > 127) { printf("jit: ENT out of bounds\n"); return -1; }
      *(int *)je = 0xe58955; je = je + 3;  // push %ebp; movl %esp, %ebp
      if (i > 0) { *(int *)je = 0xec83; je = je + 2; *(int*)je++ = i; } // subl $(i*4), %esp
    }
    else if (i == IMM) { *je++ = 0xb8; *(int *)je = *cp++; je = je + 4; } // movl $imm, %eax
    else if (i == ADDR) { *je++ = 0xb8; *(int *)je = *cp++; je = je + 4; } // movl $imm, %eax
    else if (i == ADJ) { i = 4 * *cp++; *(int *)je = 0xc483; je = je + 2; *(int *)je = i; je++; } // addl $(n * 4), %esp
    else if (i == PSH)   *(int *)je++ = 0x50;                    // push %eax
    else if (i == LEV) { *(int *)je = 0xc35dec89; je = je + 4; } // mov %ebp, %esp; pop %ebp; ret
    else if (i == LI)  { *(int *)je = 0x008b;     je = je + 2; } // movl (%eax), %eax
    else if (i == LC)  { *(int *)je = 0x00b60f;   je = je + 3; } // movzbl (%eax), %eax
    else if (i == SI)  { *(int *)je = 0x018959;   je = je + 3; } // pop %ecx; movl %eax, (%ecx)
    else if (i == SC)  { *(int *)je = 0x018859;   je = je + 3; } // pop %ecx; movb %al, (%ecx)
    else if (i == OR)  { *(int *)je = 0xc80959;   je = je + 3; } // pop %ecx; orl %ecx, %eax
    else if (i == XOR) { *(int *)je = 0xc83159;   je = je + 3; } // pop %ecx; xorl %ecx, %eax
    else if (i == AND) { *(int *)je = 0xc82159;   je = je + 3; } // pop %ecx; andl %ecx, %eax
    else if (EQ <= i && i <= GE) {
        *(int*)je=0x0fc13959; je = je + 4; *(int*)je=0x9866c094; // pop %ecx; cmp %ecx, %eax; sete %al; cbw; - EQ
        if      (i == NE)  { *je = 0x95; } // setne %al
        else if (i == LT)  { *je = 0x9c; } // setl %al
        else if (i == GT)  { *je = 0x9f; } // setg %al
        else if (i == LE)  { *je = 0x9e; } // setle %al
        else if (i == GE)  { *je = 0x9d; } // setge %al
        je=je+4; *je++=0x98;  // cwde
    }
    else if (i == SHL) { *(int*)je = 0xe0d39159; je = je + 4; } // pop %ecx; xchg %eax, %ecx; shl %cl, %eax
    else if (i == SHR) { *(int*)je = 0xe8d39159; je = je + 4; } // pop %ecx; xchg %eax, %ecx; shr %cl, %eax
    else if (i == ADD) { *(int*)je = 0xc80159;   je = je + 3; } // pop %ecx; addl %ecx, %eax
    else if (i == SUB) { *(int*)je = 0xc8299159; je = je + 4; } // pop %ecx; xchg %eax, %ecx; subl %ecx, %eax
    else if (i == MUL) { *(int*)je = 0xc1af0f59; je = je + 4; } // pop %ecx; imul %ecx, %eax
    else if (i == DIV) { *(int*)je = 0xf9f79159; je = je + 4; } // pop %ecx; xchg %eax, %ecx; idiv %ecx, %eax
    else if (i == MOD) { *(int*)je = 0xd2319159; je = je + 4; *(int *)je = 0x92f9f7; je = je + 3; }
    else if (i == JMP) { ++cp; *je       = 0xe9;     je = je + 5; } // jmp <off32>
    else if (i == JSR) { ++cp; *je       = 0xe8;     je = je + 5; } // call <off32>
    else if (i == BZ)  { ++cp; *(int*)je = 0x840fc085; je = je + 8; } // test %eax, %eax; jz <off32>
    else if (i == BNZ) { ++cp; *(int*)je = 0x850fc085; je = je + 8; } // test %eax, %eax; jnz <off32>
    else if (i >= OPEN) {
      if      (i == OPEN) tmp = (int)dlsym(dl, "open");
      else if (i == READ) tmp = (int)dlsym(dl, "read");
      else if (i == CLOS) tmp = (int)dlsym(dl, "close");
      else if (i == PRTF) tmp = (int)dlsym(dl, "printf");
      else if (i == MALC) tmp = (int)dlsym(dl, "malloc");
      else if (i == MSET) tmp = (int)dlsym(dl, "memset");
      else if (i == MCMP) tmp = (int)dlsym(dl, "memcmp");
      else if (i == EXIT) tmp = (int)dlsym(dl, "exit");

      if (*cp++ == ADJ) { i = *cp++; } else { printf("no ADJ after native proc!\n"); exit(2); }

      *je++ = 0xb9; *(int*)je = i << 2; je = je + 4;  // movl $(4 * n), %ecx;
      *(int*)je = 0xce29e689; je = je + 4; // mov %esp, %esi; sub %ecx, %esi;  -- %esi will adjust the stack
      *(int*)je = 0x8302e9c1; je = je + 4; // shr $2, %ecx; and                -- alignment of %esp for OS X
      *(int*)je = 0x895af0e6; je = je + 4; // $0xfffffff0, %esi; pop %edx; mov..
      *(int*)je = 0xe2fc8e54; je = je + 4; // ..%edx, -4(%esi,%ecx,4); loop..  -- reversing args order
      *(int*)je = 0xe8f487f9; je = je + 4; // ..<'pop' offset>; xchg %esi, %esp; call    -- saving old stack in %esi
      *(int*)je = tmp - (int)(je + 4); je = je + 4; // <*tmp offset>;
      *(int*)je = 0xf487; je = je + 2;     // xchg %esi, %esp  -- ADJ, back to old stack without arguments
    }
    else { printf("code generation failed for %d!\n", i); return -1; }
  }

  // second pass, relocation
  cp = code + 1;
  while (cp < code+codeLen) {
    je = jitmap[cp - code];
    i = *cp++;
    // ADDR 需不需要 relocate ?? 應該不用，因為 vm 的目的檔已經重定位過了，把參數當常數即可
    if (i == JSR || i == JMP || i == BZ || i == BNZ) {
        tmp = (int)jitmap[(int *)*cp++ - code];
        if      (i == JSR || i == JMP) { je = je + 1; *(int*)je = tmp - (int)(je + 4); }
        else if (i == BZ  || i == BNZ) { je = je + 4; *(int*)je = tmp - (int)(je + 4); }
    }
    else if (i < LEV) { ++cp; }
  }
}

int jit_run(int argc, char *argv[]) {
  // run jitted code
  jitmain = (void *) jitmap[ pc - code ];
  return jitmain(argv, argc); // c4 vm pushes first argument first, unlike cdecl
}

int main(int argc, char *argv[]) {
  char *iFile;

  iFile = argv[1];
  fd = open(iFile, 0100000);
  assert(fd != -1);
  init();
  obj_load(fd);
  // obj_dump(pc, code, codeLen, data, dataLen);
  // src = 1;
  jit_build();
  jit_run(argc, argv);
}

