	.section	.rodata
.stab:	.ascii	"sum(10)=%d\n\0\0\0\0\0"
	.text
	.globl	main
	.type	main, @function
main:
.L1: #     1:93009018     ENT  2
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
.L3: #     3:93009028     LEA  -1
	movq $-1, %rax
	leaq (%rbp,%rax,8), %rax
.L5: #     5:93009038     PSH 
	pushq %rax
.L6: #     6:93009040     IMM  0
	movq $0, %rax
.L8: #     8:93009050     SI  
	pushq %rax
.L9: #     9:93009058     LEA  -2
	movq $-2, %rax
	leaq (%rbp,%rax,8), %rax
.L11: #    11:93009068     PSH 
	pushq %rax
.L12: #    12:93009070     IMM  1
	movq $1, %rax
.L14: #    14:93009080     SI  
	pushq %rax
.L15: #    15:93009088     LEA  -2
	movq $-2, %rax
	leaq (%rbp,%rax,8), %rax
.L17: #    17:93009098     LI  
	movq 0(%rax), %rax
.L18: #    18:930090A0     PSH 
	pushq %rax
.L19: #    19:930090A8     LEA  2
	movq $2, %rax
	leaq (%rbp,%rax,8), %rax
.L21: #    21:930090B8     LI  
	movq 0(%rax), %rax
.L22: #    22:930090C0     LE  
	popl %rbx
	le %rbx, %rax

.L23: #    23:930090C8     BZ   52:930091B0
	cmp $0, %rax
	jeq .L52
.L25: #    25:930090D8     LEA  -1
	movq $-1, %rax
	leaq (%rbp,%rax,8), %rax
.L27: #    27:930090E8     PSH 
	pushq %rax
.L28: #    28:930090F0     LEA  -1
	movq $-1, %rax
	leaq (%rbp,%rax,8), %rax
.L30: #    30:93009100     LI  
	movq 0(%rax), %rax
.L31: #    31:93009108     PSH 
	pushq %rax
.L32: #    32:93009110     LEA  -2
	movq $-2, %rax
	leaq (%rbp,%rax,8), %rax
.L34: #    34:93009120     LI  
	movq 0(%rax), %rax
.L35: #    35:93009128     ADD 
	popl %rbx
	add %rbx, %rax

.L36: #    36:93009130     SI  
	pushq %rax
.L37: #    37:93009138     LEA  -2
	movq $-2, %rax
	leaq (%rbp,%rax,8), %rax
.L39: #    39:93009148     PSH 
	pushq %rax
.L40: #    40:93009150     LI  
	movq 0(%rax), %rax
.L41: #    41:93009158     PSH 
	pushq %rax
.L42: #    42:93009160     IMM  1
	movq $1, %rax
.L44: #    44:93009170     ADD 
	popl %rbx
	add %rbx, %rax

.L45: #    45:93009178     SI  
	pushq %rax
.L46: #    46:93009180     PSH 
	pushq %rax
.L47: #    47:93009188     IMM  1
	movq $1, %rax
.L49: #    49:93009198     SUB 
	popl %rbx
	sub %rbx, %rax

.L50: #    50:930091A0     JMP  15:93009088
	jmp .L15
.L52: #    52:930091B0     LEA  -1
	movq $-1, %rax
	leaq (%rbp,%rax,8), %rax
.L54: #    54:930091C0     LI  
	movq 0(%rax), %rax
.L55: #    55:930091C8     LEV 
	popq %rbp
	ret
.L56: #    56:930091D0     LEV 
	popq %rbp
	ret
.L57: #    57:930091D8     ENT  0
	pushq %rbp
	movq %rsp, %rbp
	subq $0, %rsp
.L59: #    59:930091E8     ADDR 0:92FC8010
	leaq .stab(%rip), %rax
	addq $0,%rax
.L61: #    61:930091F8     PSH 
	pushq %rax
.L62: #    62:93009200     IMM  10
	movq $10, %rax
.L64: #    64:93009210     PSH 
	pushq %rax
.L65: #    65:93009218     JSR  1:93009018
	call .L1
.L67: #    67:93009228     ADJ  1
	
.L69: #    69:93009238     PSH 
	pushq %rax
.L70: #    70:93009240     PRTF
	popq %rsi
	popq %rdi
	call printf@PLT
.L71: #    71:93009248     ADJ  2
	
.L73: #    73:93009258     IMM  0
	movq $0, %rax
.L75: #    75:93009268     LEV 
	popq %rbp
	ret
.L76: #    76:93009270     LEV 
	popq %rbp
	ret
