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
    # ADDR 0
	leaq	.LC0(%rip), %rax
    # PSH
    pushq   %rax
    # PRTF
    popq    %rdi
	call	printf@PLT
	movl	$0, %eax
    # ADJ   1
    #   已經用 pop 處理完了
    # LEV
	popq	%rbp
	ret
