	.text
	.global main
name:
	.asciz "/bin/sh"
args:
	.quad 0
	.quad 0

main:
	leaq -0x1f(%rip), %rdi
	leaq -0x1e(%rip), %rsi
	movq %rdi, (%rsi)
	movq $0, %rdx
	movq $0x3b, %rax
	syscall
	movq %rax, %rdi
	movq $0x3c, %rax
	syscall

