	.section	.rodata
.LC0:
	.string	"hello, world\n"
	.text
	.globl	main
	.type	main, @function
main:
    # ENT 0
	# endbr64
	pushq	%rbp
	movq	%rsp, %rbp
    # ADDR 0; PSH
	leaq	.LC0(%rip), %rdi
    # PRTF
	call	printf@PLT
	movl	$0, %eax
    # LEV
	popq	%rbp
	ret
