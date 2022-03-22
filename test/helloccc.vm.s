	.section	.rodata
.stab:	.ascii	"ccc\0\0\0\0\0hello %s\n\0\0\0\0\0\0\0"
	.text
	.globl	main
	.type	main, @function
main:
#     1:64EBE018     ENT  1
.L1:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
#     3:64EBE028     LEA  -1
.L3:
	movq $-1, %rax
	leaq (%rbp,%rax,8), %rax
#     5:64EBE038     PSH 
.L5:
	pushq %rax
#     6:64EBE040     ADDR 0:64E7D010
.L6:
	leaq .stab(%rip), %rax
	addq $0,%rax
#     8:64EBE050     SI  
.L8:
	pushq %rax
#     9:64EBE058     ADDR 8:64E7D018
.L9:
	leaq .stab(%rip), %rax
	addq $8,%rax
#    11:64EBE068     PSH 
.L11:
	pushq %rax
#    12:64EBE070     LEA  -1
.L12:
	movq $-1, %rax
	leaq (%rbp,%rax,8), %rax
#    14:64EBE080     LI  
.L14:
	movq 0(%rax), %rax
#    15:64EBE088     PSH 
.L15:
	pushq %rax
#    16:64EBE090     PRTF
.L16:
	popq %rsi
	popq %rdi
	call printf@PLT
#    17:64EBE098     ADJ  2
.L17:
	
#    19:64EBE0A8     LEV 
.L19:
	popq %rbp
	ret
