	.file	"loop_invariants.c"
# GNU C17 (Ubuntu 11.3.0-1ubuntu1~22.04) version 11.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"fast"
.LC3:
	.string	"Done. sum = %15.3f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
# loop_invariants.c:10:   double * data = (double*) malloc(N*N*sizeof(double));
	movl	$1, %esi	#,
	movl	$800000000, %edi	#,
	call	calloc@PLT	#
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC1(%rip), %rdi	#, tmp104
# loop_invariants.c:10:   double * data = (double*) malloc(N*N*sizeof(double));
	movq	%rax, %rbp	# tmp114, data
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	call	puts@PLT	#
	movq	%rbp, %rcx	# data, ivtmp.10
	movq	%rbp, %rdx	# data, ivtmp.26
	xorl	%esi, %esi	# ivtmp.25
	movsd	.LC2(%rip), %xmm2	#, tmp113
	leaq	800000000(%rbp), %rdi	#, _22
.L3:
# loop_invariants.c:21:     tmp = i*N/7.7;
	pxor	%xmm1, %xmm1	# tmp105
# loop_invariants.c:21:     tmp = i*N/7.7;
	xorl	%eax, %eax	# ivtmp.13
# loop_invariants.c:21:     tmp = i*N/7.7;
	cvtsi2sdl	%esi, %xmm1	# ivtmp.25, tmp105
# loop_invariants.c:21:     tmp = i*N/7.7;
	divsd	%xmm2, %xmm1	# tmp113, tmp
	.p2align 4,,10
	.p2align 3
.L2:
# loop_invariants.c:23:       data[iN + j] += tmp + j;
	pxor	%xmm0, %xmm0	# tmp107
	cvtsi2sdl	%eax, %xmm0	# ivtmp.13, tmp107
	addsd	%xmm1, %xmm0	# tmp, tmp108
# loop_invariants.c:23:       data[iN + j] += tmp + j;
	addsd	(%rdx,%rax,8), %xmm0	# MEM[(double *)_48 + ivtmp.13_37 * 8], tmp109
	movsd	%xmm0, (%rdx,%rax,8)	# tmp109, MEM[(double *)_48 + ivtmp.13_37 * 8]
# loop_invariants.c:22:     for(j = 0; j<N; j++)
	addq	$1, %rax	#, ivtmp.13
	cmpq	$10000, %rax	#, ivtmp.13
	jne	.L2	#,
# loop_invariants.c:19:   for(i = 0; i<N; i++) {
	addq	$80000, %rdx	#, ivtmp.26
	addl	$10000, %esi	#, ivtmp.25
	cmpq	%rdx, %rdi	# ivtmp.26, _22
	jne	.L3	#,
# loop_invariants.c:36:   sum = 0;
	pxor	%xmm0, %xmm0	# sum
.L4:
# loop_invariants.c:38:     sum += data[i];
	addsd	(%rcx), %xmm0	# MEM[(double *)_1], sum
# loop_invariants.c:37:   for(i = 0; i < N*N; i++)
	addq	$8, %rcx	#, ivtmp.10
	cmpq	%rcx, %rdi	# ivtmp.10, _22
	jne	.L4	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC3(%rip), %rsi	#, tmp111
	movl	$1, %edi	#,
	movl	$1, %eax	#,
	call	__printf_chk@PLT	#
# loop_invariants.c:41:   free(data);
	movq	%rbp, %rdi	# data,
	call	free@PLT	#
# loop_invariants.c:44: }
	xorl	%eax, %eax	#
	popq	%rbp	#
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	-858993459
	.long	1075760332
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
