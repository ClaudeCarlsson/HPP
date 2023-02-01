	.file	"string_loop.c"
# GNU C17 (Ubuntu 11.3.0-1ubuntu1~22.04) version 11.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.p2align 4
	.globl	lowercase
	.type	lowercase, @function
lowercase:
.LFB39:
	.cfi_startproc
	endbr64	
	leaq	100(%rdi), %rax	#, _3
	.p2align 4,,10
	.p2align 3
.L2:
# string_loop.c:14: 	*(p++) |= 0x20;
	addq	$1, %rdi	#, p
# string_loop.c:14: 	*(p++) |= 0x20;
	orb	$32, -1(%rdi)	#, MEM[(char *)p_8 + -1B]
# string_loop.c:13:    for (i = 100; i>0; i--)
	cmpq	%rdi, %rax	# p, _3
	jne	.L2	#,
# string_loop.c:16: }
	ret	
	.cfi_endproc
.LFE39:
	.size	lowercase, .-lowercase
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"done"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB40:
	.cfi_startproc
	endbr64	
	subq	$120, %rsp	#,
	.cfi_def_cfa_offset 128
# string_loop.c:37:       string[i] = 'A';
	movdqa	.LC1(%rip), %xmm0	#, tmp98
# string_loop.c:39:    string[99] = '\0';		/* null-terminate the string */
	movl	$10000000, %ecx	#, ivtmp_1
# string_loop.c:29: {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp104
	movq	%rax, 104(%rsp)	# tmp104, D.3247
	xorl	%eax, %eax	# tmp104
# string_loop.c:37:       string[i] = 'A';
	movl	$16705, %eax	#,
	movb	$65, 98(%rsp)	#, MEM <char[1:99]> [(void *)&string]
	movq	%rsp, %rsi	#, p
	movw	%ax, 96(%rsp)	#, MEM <char[1:99]> [(void *)&string]
	leaq	100(%rsp), %rdx	#, tmp96
# string_loop.c:39:    string[99] = '\0';		/* null-terminate the string */
	movb	$0, 99(%rsp)	#, string[99]
# string_loop.c:37:       string[i] = 'A';
	movaps	%xmm0, (%rsp)	# tmp98, MEM <char[1:99]> [(void *)&string]
	movaps	%xmm0, 16(%rsp)	# tmp98, MEM <char[1:99]> [(void *)&string]
	movaps	%xmm0, 32(%rsp)	# tmp98, MEM <char[1:99]> [(void *)&string]
	movaps	%xmm0, 48(%rsp)	# tmp98, MEM <char[1:99]> [(void *)&string]
	movaps	%xmm0, 64(%rsp)	# tmp98, MEM <char[1:99]> [(void *)&string]
	movaps	%xmm0, 80(%rsp)	# tmp98, MEM <char[1:99]> [(void *)&string]
.L6:
# string_loop.c:29: {
	movq	%rsi, %rax	# p, p
	.p2align 4,,10
	.p2align 3
.L7:
# string_loop.c:14: 	*(p++) |= 0x20;
	addq	$1, %rax	#, p
# string_loop.c:14: 	*(p++) |= 0x20;
	orb	$32, -1(%rax)	#, MEM[(char *)p_12 + -1B]
# string_loop.c:13:    for (i = 100; i>0; i--)
	cmpq	%rdx, %rax	# tmp96, p
	jne	.L7	#,
# string_loop.c:41:    for(i=0; i<numiters; i++)
	subl	$1, %ecx	#, ivtmp_1
	jne	.L6	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC0(%rip), %rdi	#, tmp93
	call	puts@PLT	#
# string_loop.c:48: }
	movq	104(%rsp), %rax	# D.3247, tmp105
	subq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp105
	jne	.L12	#,
	xorl	%eax, %eax	#
	addq	$120, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret	
.L12:
	.cfi_restore_state
	call	__stack_chk_fail@PLT	#
	.cfi_endproc
.LFE40:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.quad	4702111234474983745
	.quad	4702111234474983745
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
