	.section	.rodata
.stab:	.ascii	"f(7)=%d\n\0\0\0\0\0\0\0\0"
	.text
	.globl	main
	.type	main, @function
main:
.L1: #     1:3C332018     ENT  0
	pushq %rbp
	movq %rsp, %rbp
	subq $0, %rsp
.L3: #     3:3C332028     LEA  2
	movq $2, %rax
	leaq (%rbp,%rax,8), %rax
.L5: #     5:3C332038     LI  
	movq 0(%rax), %rax
.L6: #     6:3C332040     PSH 
	pushq %rax
.L7: #     7:3C332048     IMM  0
	movq $0, %rax
.L9: #     9:3C332058     LE  
	popl %rbx
	le %rbx, %rax

.L10: #    10:3C332060     BZ   15:3C332088
	cmp $0, %rax
	jeq .L15
.L12: #    12:3C332070     IMM  0
	movq $0, %rax
.L14: #    14:3C332080     LEV 
	popq %rbp
	ret
.L15: #    15:3C332088     LEA  2
	movq $2, %rax
	leaq (%rbp,%rax,8), %rax
.L17: #    17:3C332098     LI  
	movq 0(%rax), %rax
.L18: #    18:3C3320A0     PSH 
	pushq %rax
.L19: #    19:3C3320A8     IMM  1
	movq $1, %rax
.L21: #    21:3C3320B8     EQ  
	popl %rbx
	eq %rbx, %rax

.L22: #    22:3C3320C0     BZ   27:3C3320E8
	cmp $0, %rax
	jeq .L27
.L24: #    24:3C3320D0     IMM  1
	movq $1, %rax
.L26: #    26:3C3320E0     LEV 
	popq %rbp
	ret
.L27: #    27:3C3320E8     LEA  2
	movq $2, %rax
	leaq (%rbp,%rax,8), %rax
.L29: #    29:3C3320F8     LI  
	movq 0(%rax), %rax
.L30: #    30:3C332100     PSH 
	pushq %rax
.L31: #    31:3C332108     IMM  1
	movq $1, %rax
.L33: #    33:3C332118     SUB 
	popl %rbx
	sub %rbx, %rax

.L34: #    34:3C332120     PSH 
	pushq %rax
.L35: #    35:3C332128     JSR  1:3C332018
	call .L1
.L37: #    37:3C332138     ADJ  1
	
.L39: #    39:3C332148     PSH 
	pushq %rax
.L40: #    40:3C332150     LEA  2
	movq $2, %rax
	leaq (%rbp,%rax,8), %rax
.L42: #    42:3C332160     LI  
	movq 0(%rax), %rax
.L43: #    43:3C332168     PSH 
	pushq %rax
.L44: #    44:3C332170     IMM  2
	movq $2, %rax
.L46: #    46:3C332180     SUB 
	popl %rbx
	sub %rbx, %rax

.L47: #    47:3C332188     PSH 
	pushq %rax
.L48: #    48:3C332190     JSR  1:3C332018
	call .L1
.L50: #    50:3C3321A0     ADJ  1
	
.L52: #    52:3C3321B0     ADD 
	popl %rbx
	add %rbx, %rax

.L53: #    53:3C3321B8     LEV 
	popq %rbp
	ret
.L54: #    54:3C3321C0     LEV 
	popq %rbp
	ret
.L55: #    55:3C3321C8     ENT  0
	pushq %rbp
	movq %rsp, %rbp
	subq $0, %rsp
.L57: #    57:3C3321D8     ADDR 0:3C2F1010
	leaq .stab(%rip), %rax
	addq $0,%rax
.L59: #    59:3C3321E8     PSH 
	pushq %rax
.L60: #    60:3C3321F0     IMM  7
	movq $7, %rax
.L62: #    62:3C332200     PSH 
	pushq %rax
.L63: #    63:3C332208     JSR  1:3C332018
	call .L1
.L65: #    65:3C332218     ADJ  1
	
.L67: #    67:3C332228     PSH 
	pushq %rax
.L68: #    68:3C332230     PRTF
	popq %rsi
	popq %rdi
	call printf@PLT
.L69: #    69:3C332238     ADJ  2
	
.L71: #    71:3C332248     LEV 
	popq %rbp
	ret
