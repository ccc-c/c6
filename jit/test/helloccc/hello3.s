	.section	.rodata
.LC0:
	.string	"hello %s\n"
	.text
	.globl	main
	.type	main, @function
main:
    # ENT 1
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
    # ??
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
    # ADDR name 
	movl	$6513507, -12(%rbp)
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
    # ADDR LC0
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
    # printf()
	call	printf@PLT
	movl	$0, %eax
    # ADJ 2
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L3
.L3:
    # LEV
	leave
	ret
