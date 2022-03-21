	.section	.rodata
.LC0:
	.string	"hello, world\n"
	.text
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.LC0(%rip), %rdi
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	ret
