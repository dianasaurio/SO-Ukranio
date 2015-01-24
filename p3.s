	.file	"p3.c"
	.section	.rodata
.LC0:
	.string	"Segundos: %d\n"
.LC1:
	.string	"Nanosegundos: %ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$48, %esp
	movl	$2000000000, 24(%esp)
	movl	$0, 28(%esp)
	leal	32(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	clock_gettime
	jmp	.L2
.L3:
	addl	$-1, 24(%esp)
	adcl	$-1, 28(%esp)
.L2:
	movl	24(%esp), %eax
	movl	28(%esp), %edx
	orl	%edx, %eax
	testl	%eax, %eax
	jne	.L3
	leal	40(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	clock_gettime
	movl	44(%esp), %edx
	movl	36(%esp), %eax
	cmpl	%eax, %edx
	jge	.L4
	movl	40(%esp), %edx
	movl	32(%esp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	%eax, 16(%esp)
	movl	36(%esp), %edx
	movl	44(%esp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, 20(%esp)
	jmp	.L5
.L4:
	movl	40(%esp), %edx
	movl	32(%esp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, 16(%esp)
	movl	44(%esp), %edx
	movl	36(%esp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, 20(%esp)
.L5:
	movl	16(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	20(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
