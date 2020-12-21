	.file	"q2.c"
	.text
	.p2align 4
	.globl	parallel_addition
	.type	parallel_addition, @function
parallel_addition:
.LFB52:
	.cfi_startproc
	endbr64
	imull	$1250, %edi, %edx
	movslq	%edx, %rax
	addl	$1250, %edx
	movslq	%edx, %rdx
	cmpq	%rax, %rdx
	jbe	.L2
	imulq	$60000, %rax, %rdx
	leaq	mat_A(%rip), %rdi
	leaq	sum(%rip), %r8
	leaq	mat_B(%rip), %rcx
	leaq	(%rdx,%rdi), %rsi
	addq	%rdx, %rcx
	addq	%r8, %rdx
	leaq	1250(%rax), %r8
	imulq	$60000, %r8, %r8
	addq	%rdi, %r8
.L5:
	movl	$100, %edi
.L4:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	movdqa	(%rsi,%rax), %xmm0
	paddd	(%rcx,%rax), %xmm0
	movaps	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	$60000, %rax
	jne	.L3
	subl	$1, %edi
	jne	.L4
	addq	$60000, %rsi
	addq	$60000, %rcx
	addq	$60000, %rdx
	cmpq	%r8, %rsi
	jne	.L5
.L2:
	ret
	.cfi_endproc
.LFE52:
	.size	parallel_addition, .-parallel_addition
	.p2align 4
	.globl	sequential_addition
	.type	sequential_addition, @function
sequential_addition:
.LFB53:
	.cfi_startproc
	endbr64
	leaq	mat_A(%rip), %rdx
	leaq	mat_B(%rip), %rsi
	leaq	sum(%rip), %rcx
	leaq	900000000(%rdx), %r8
.L11:
	movl	$100, %edi
.L15:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L12:
	movdqa	(%rdx,%rax), %xmm0
	paddd	(%rsi,%rax), %xmm0
	movaps	%xmm0, (%rcx,%rax)
	addq	$16, %rax
	cmpq	$60000, %rax
	jne	.L12
	subl	$1, %edi
	jne	.L15
	addq	$60000, %rdx
	addq	$60000, %rsi
	addq	$60000, %rcx
	cmpq	%rdx, %r8
	jne	.L11
	ret
	.cfi_endproc
.LFE53:
	.size	sequential_addition, .-sequential_addition
	.p2align 4
	.globl	generateMatrix
	.type	generateMatrix, @function
generateMatrix:
.LFB54:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	mat_B(%rip), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	leaq	mat_A(%rip), %rbx
	leaq	900000000(%rbx), %r12
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
.L18:
	xorl	%r13d, %r13d
	.p2align 4,,10
	.p2align 3
.L19:
	call	rand@PLT
	movslq	%eax, %rdx
	movl	%eax, %ecx
	imulq	$1717986919, %rdx, %rdx
	sarl	$31, %ecx
	sarq	$34, %rdx
	subl	%ecx, %edx
	leal	(%rdx,%rdx,4), %edx
	addl	%edx, %edx
	subl	%edx, %eax
	movl	%eax, (%rbx,%r13,4)
	call	rand@PLT
	movslq	%eax, %rdx
	movl	%eax, %ecx
	imulq	$1717986919, %rdx, %rdx
	sarl	$31, %ecx
	sarq	$34, %rdx
	subl	%ecx, %edx
	leal	(%rdx,%rdx,4), %edx
	addl	%edx, %edx
	subl	%edx, %eax
	movl	%eax, 0(%rbp,%r13,4)
	addq	$1, %r13
	cmpq	$15000, %r13
	jne	.L19
	addq	$60000, %rbx
	addq	$60000, %rbp
	cmpq	%r12, %rbx
	jne	.L18
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE54:
	.size	generateMatrix, .-generateMatrix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"Time taken : %.10f seconds.\n"
	.text
	.p2align 4
	.globl	sequential_add
	.type	sequential_add, @function
sequential_add:
.LFB55:
	.cfi_startproc
	endbr64
	subq	$72, %rsp
	.cfi_def_cfa_offset 80
	xorl	%edi, %edi
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	leaq	16(%rsp), %rsi
	call	clock_gettime@PLT
	xorl	%ecx, %ecx
	leaq	sequential_addition(%rip), %rdx
	xorl	%esi, %esi
	leaq	8(%rsp), %rdi
	call	pthread_create@PLT
	movq	8(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	xorl	%edi, %edi
	leaq	32(%rsp), %rsi
	call	clock_gettime@PLT
	movq	32(%rsp), %rax
	pxor	%xmm0, %xmm0
	subq	16(%rsp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	40(%rsp), %rax
	subq	24(%rsp), %rax
	mulsd	.LC0(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %edi
	movl	$1, %eax
	leaq	.LC2(%rip), %rsi
	addsd	%xmm1, %xmm0
	mulsd	.LC1(%rip), %xmm0
	call	__printf_chk@PLT
	movq	56(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L26
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L26:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE55:
	.size	sequential_add, .-sequential_add
	.section	.rodata.str1.1
.LC3:
	.string	"Running in sequential mode."
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB51:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	xorl	%eax, %eax
	call	sequential_add
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE51:
	.size	main, .-main
	.text
	.p2align 4
	.globl	parallel_add
	.type	parallel_add, @function
parallel_add:
.LFB56:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	xorl	%edi, %edi
	leaq	parallel_addition(%rip), %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	xorl	%ebp, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$152, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 136(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rsi
	leaq	32(%rsp), %rbx
	call	clock_gettime@PLT
	movq	%rbx, %r12
	.p2align 4,,10
	.p2align 3
.L30:
	movq	%rbp, %rcx
	movq	%r12, %rdi
	movq	%r13, %rdx
	xorl	%esi, %esi
	call	pthread_create@PLT
	addq	$1, %rbp
	addq	$8, %r12
	cmpq	$12, %rbp
	jne	.L30
	leaq	96(%rbx), %rbp
	.p2align 4,,10
	.p2align 3
.L31:
	movq	(%rbx), %rdi
	xorl	%esi, %esi
	addq	$8, %rbx
	call	pthread_join@PLT
	cmpq	%rbx, %rbp
	jne	.L31
	xorl	%edi, %edi
	leaq	16(%rsp), %rsi
	call	clock_gettime@PLT
	movq	16(%rsp), %rax
	pxor	%xmm0, %xmm0
	subq	(%rsp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	mulsd	.LC0(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %edi
	movl	$1, %eax
	leaq	.LC2(%rip), %rsi
	addsd	%xmm1, %xmm0
	mulsd	.LC1(%rip), %xmm0
	call	__printf_chk@PLT
	movq	136(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L36
	addq	$152, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L36:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE56:
	.size	parallel_add, .-parallel_add
	.comm	sum,900000000,32
	.comm	mat_B,900000000,32
	.comm	mat_A,900000000,32
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1104006501
	.align 8
.LC1:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (Ubuntu 9.3.0-10ubuntu2) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
