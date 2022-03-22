	.file	"sum64.c"
 # GNU C17 (x86_64-posix-seh-rev0, Built by MinGW-W64 project) version 8.1.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 8.1.0, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.18-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: 
 # -iprefix C:/Program Files/CodeBlocks/MinGW/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/
 # -D_REENTRANT sum64.c -mtune=core2 -march=nocona -auxbase-strip sum64.s
 # -fverbose-asm
 # options enabled:  -faggressive-loop-optimizations
 # -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
 # -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
 # -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
 # -fchkp-use-static-bounds -fchkp-use-static-const-bounds
 # -fchkp-use-wrappers -fcommon -fdelete-null-pointer-checks
 # -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
 # -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm -fgnu-runtime
 # -fgnu-unique -fident -finline-atomics -fira-hoist-pressure
 # -fira-share-save-slots -fira-share-spill-slots -fivopts
 # -fkeep-inline-dllexport -fkeep-static-consts -fleading-underscore
 # -flifetime-dse -flto-odr-type-merging -fmath-errno -fmerge-debug-strings
 # -fpeephole -fpic -fplt -fprefetch-loop-arrays -freg-struct-return
 # -fsched-critical-path-heuristic -fsched-dep-count-heuristic
 # -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
 # -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
 # -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
 # -fset-stack-executable -fshow-column -fshrink-wrap-separate
 # -fsigned-zeros -fsplit-ivs-in-unroller -fssa-backprop -fstdarg-opt
 # -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
 # -ftree-cselim -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
 # -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
 # -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
 # -funwind-tables -fverbose-asm -fzero-initialized-in-bss
 # -m128bit-long-double -m64 -m80387 -maccumulate-outgoing-args
 # -malign-double -malign-stringops -mcx16 -mfancy-math-387 -mfentry
 # -mfp-ret-in-387 -mfxsr -mieee-fp -mlong-double-80 -mmmx -mms-bitfields
 # -mno-sse4 -mpush-args -mred-zone -msse -msse2 -msse3 -mstack-arg-probe
 # -mstackrealign -mvzeroupper

	.text
	.globl	sum
	.def	sum;	.scl	2;	.type	32;	.endef
	.seh_proc	sum
sum:
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	movq	%rsp, %rbp	 #,
	.seh_setframe	%rbp, 0
	subq	$16, %rsp	 #,
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)	 # n, n
 # sum64.c:7:   s=0;
	movq	$0, -8(%rbp)	 #, s
 # sum64.c:8:   i=1;
	movq	$1, -16(%rbp)	 #, i
 # sum64.c:9:   while (i <= n) {
	jmp	.L2	 #
.L3:
 # sum64.c:10:     s = s + i;
	movq	-16(%rbp), %rax	 # i, tmp89
	addq	%rax, -8(%rbp)	 # tmp89, s
 # sum64.c:11:     i ++;
	addq	$1, -16(%rbp)	 #, i
.L2:
 # sum64.c:9:   while (i <= n) {
	movq	-16(%rbp), %rax	 # i, tmp90
	cmpq	16(%rbp), %rax	 # n, tmp90
	jle	.L3	 #,
 # sum64.c:13:   return s;
	movq	-8(%rbp), %rax	 # s, _8
 # sum64.c:14: }
	addq	$16, %rsp	 #,
	popq	%rbp	 #
	ret	
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "sum(10)=%d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	movq	%rsp, %rbp	 #,
	.seh_setframe	%rbp, 0
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # sum64.c:16: int main() {
	call	__main	 #
 # sum64.c:17:   printf("sum(10)=%d\n", sum(10));
	movl	$10, %ecx	 #,
	call	sum	 #
	movq	%rax, %rdx	 # _1,
	leaq	.LC0(%rip), %rcx	 #,
	call	printf	 #
 # sum64.c:18:   return 0;
	movl	$0, %eax	 #, _5
 # sum64.c:19: }
	addq	$32, %rsp	 #,
	popq	%rbp	 #
	ret	
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	printf;	.scl	2;	.type	32;	.endef
