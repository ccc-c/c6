# jit

## run

```
wsl> ./jit test/hello.vm > test/hello.vm.s
wsl> gcc test/hello.vm.s -o test/hello.vm.o
wsl> ./test/hello.vm.o
hello, world
```

## hello.vm.s

```
	.section	.rodata
.stab:	.ascii	"hello, world\n\0\0\0"
	.text
	.globl	main
	.type	main, @function
main:
#     1:90812018     ENT  0
	pushq %rbp
	movq %rsp, %rbp
	subq $0, %rsp
#     3:90812028     ADDR 0:907D1010
	leaq .stab(%rip), %rax
	addq $0,%rax
#     5:90812038     PSH 
	pushq %rax
#     6:90812040     PRTF
	popq %rdi
	call printf@PLT
#     7:90812048     ADJ  1
	
#     9:90812058     LEV 
	popq %rbp
	ret
```
