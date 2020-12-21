	.file	"q2.c"
	.text
	.comm	mat_A,900000000,32
	.comm	mat_B,900000000,32
	.comm	sum,900000000,32
	.section	.rodata
.LC0:
	.string	"Running in sequential mode."
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	sequential_add
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.globl	parallel_addition
	.type	parallel_addition, @function
parallel_addition:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	%eax, -20(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L4
.L9:
	movl	-20(%rbp), %eax
	imull	$1250, %eax, %eax
	cltq
	movq	%rax, -16(%rbp)
	jmp	.L5
.L8:
	movq	$0, -8(%rbp)
	jmp	.L6
.L7:
	movq	-16(%rbp), %rax
	imulq	$15000, %rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	leaq	mat_A(%rip), %rax
	movl	(%rdx,%rax), %edx
	movq	-16(%rbp), %rax
	imulq	$15000, %rax, %rcx
	movq	-8(%rbp), %rax
	addq	%rcx, %rax
	leaq	0(,%rax,4), %rcx
	leaq	mat_B(%rip), %rax
	movl	(%rcx,%rax), %eax
	leal	(%rdx,%rax), %ecx
	movq	-16(%rbp), %rax
	imulq	$15000, %rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	leaq	sum(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	addq	$1, -8(%rbp)
.L6:
	cmpq	$14999, -8(%rbp)
	jbe	.L7
	addq	$1, -16(%rbp)
.L5:
	movl	-20(%rbp), %eax
	addl	$1, %eax
	imull	$1250, %eax, %eax
	cltq
	cmpq	%rax, -16(%rbp)
	jb	.L8
	addl	$1, -24(%rbp)
.L4:
	cmpl	$99, -24(%rbp)
	jle	.L9
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	parallel_addition, .-parallel_addition
	.globl	sequential_addition
	.type	sequential_addition, @function
sequential_addition:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L11
.L16:
	movq	$0, -16(%rbp)
	jmp	.L12
.L15:
	movq	$0, -8(%rbp)
	jmp	.L13
.L14:
	movq	-16(%rbp), %rax
	imulq	$15000, %rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	leaq	mat_A(%rip), %rax
	movl	(%rdx,%rax), %edx
	movq	-16(%rbp), %rax
	imulq	$15000, %rax, %rcx
	movq	-8(%rbp), %rax
	addq	%rcx, %rax
	leaq	0(,%rax,4), %rcx
	leaq	mat_B(%rip), %rax
	movl	(%rcx,%rax), %eax
	leal	(%rdx,%rax), %ecx
	movq	-16(%rbp), %rax
	imulq	$15000, %rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	leaq	sum(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	addq	$1, -8(%rbp)
.L13:
	cmpq	$14999, -8(%rbp)
	jbe	.L14
	addq	$1, -16(%rbp)
.L12:
	cmpq	$14999, -16(%rbp)
	jbe	.L15
	addl	$1, -20(%rbp)
.L11:
	cmpl	$99, -20(%rbp)
	jle	.L16
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	sequential_addition, .-sequential_addition
	.globl	generateMatrix
	.type	generateMatrix, @function
generateMatrix:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	$0, -16(%rbp)
	jmp	.L18
.L21:
	movq	$0, -8(%rbp)
	jmp	.L19
.L20:
	call	rand@PLT
	movl	%eax, %ecx
	movslq	%ecx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movq	-16(%rbp), %rax
	imulq	$15000, %rax, %rcx
	movq	-8(%rbp), %rax
	addq	%rcx, %rax
	leaq	0(,%rax,4), %rcx
	leaq	mat_A(%rip), %rax
	movl	%edx, (%rcx,%rax)
	call	rand@PLT
	movl	%eax, %ecx
	movslq	%ecx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movq	-16(%rbp), %rax
	imulq	$15000, %rax, %rcx
	movq	-8(%rbp), %rax
	addq	%rcx, %rax
	leaq	0(,%rax,4), %rcx
	leaq	mat_B(%rip), %rax
	movl	%edx, (%rcx,%rax)
	addq	$1, -8(%rbp)
.L19:
	cmpq	$14999, -8(%rbp)
	jbe	.L20
	addq	$1, -16(%rbp)
.L18:
	cmpq	$14999, -16(%rbp)
	jbe	.L21
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	generateMatrix, .-generateMatrix
	.section	.rodata
.LC3:
	.string	"Time taken : %.10f seconds.\n"
	.text
	.globl	sequential_add
	.type	sequential_add, @function
sequential_add:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime@PLT
	leaq	-64(%rbp), %rax
	movl	$0, %ecx
	leaq	sequential_addition(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movq	-64(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime@PLT
	movq	-32(%rbp), %rdx
	movq	-48(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm1
	movsd	.LC1(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -56(%rbp)
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm0
	movapd	%xmm0, %xmm1
	addsd	-56(%rbp), %xmm1
	movsd	.LC2(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC3(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L23
	call	__stack_chk_fail@PLT
.L23:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	sequential_add, .-sequential_add
	.globl	parallel_add
	.type	parallel_add, @function
parallel_add:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-144(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime@PLT
	movl	$0, -172(%rbp)
	movq	$0, -168(%rbp)
	jmp	.L25
.L26:
	movl	-172(%rbp), %eax
	cltq
	movq	%rax, %rcx
	leaq	-112(%rbp), %rax
	movq	-168(%rbp), %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	leaq	parallel_addition(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	addl	$1, -172(%rbp)
	addq	$1, -168(%rbp)
.L25:
	cmpq	$11, -168(%rbp)
	jbe	.L26
	movq	$0, -160(%rbp)
	jmp	.L27
.L28:
	movq	-160(%rbp), %rax
	movq	-112(%rbp,%rax,8), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	addq	$1, -160(%rbp)
.L27:
	cmpq	$11, -160(%rbp)
	jbe	.L28
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime@PLT
	movq	-128(%rbp), %rdx
	movq	-144(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm1
	movsd	.LC1(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -152(%rbp)
	movq	-120(%rbp), %rdx
	movq	-136(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm0
	movapd	%xmm0, %xmm1
	addsd	-152(%rbp), %xmm1
	movsd	.LC2(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC3(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L29
	call	__stack_chk_fail@PLT
.L29:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	parallel_add, .-parallel_add
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1104006501
	.align 8
.LC2:
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
