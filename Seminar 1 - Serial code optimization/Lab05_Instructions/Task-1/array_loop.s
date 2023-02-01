	.file	"array_loop.c"
# GNU C17 (Ubuntu 11.3.0-1ubuntu1~22.04) version 11.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.p2align 4
	.globl	digits2int
	.type	digits2int, @function
digits2int:
.LFB39:
	.cfi_startproc
	endbr64	
# array_loop.c:10:    int *zend = z + N-1;
	movslq	%esi, %rsi	# tmp101, N
# array_loop.c:9:    int zi = 0;
	xorl	%eax, %eax	# <retval>
# array_loop.c:10:    int *zend = z + N-1;
	leaq	-4(%rdi,%rsi,4), %rcx	#, zend
	.p2align 4,,10
	.p2align 3
.L2:
# array_loop.c:13:       zi = 10*zi + *z;
	leal	(%rax,%rax,4), %edx	#, tmp96
# array_loop.c:13:       zi = 10*zi + *z;
	movl	(%rdi), %eax	# MEM[(int *)z_6], MEM[(int *)z_6]
# array_loop.c:14:       z++;
	addq	$4, %rdi	#, z
# array_loop.c:13:       zi = 10*zi + *z;
	leal	(%rax,%rdx,2), %eax	#, <retval>
# array_loop.c:15:    } while(z <= zend);
	cmpq	%rdi, %rcx	# z, zend
	jnb	.L2	#,
# array_loop.c:17: }
	ret	
	.cfi_endproc
.LFE39:
	.size	digits2int, .-digits2int
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"zi = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB40:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
# array_loop.c:38:    int* z = (int*)malloc(N*sizeof(int));
	movl	$20, %edi	#,
	call	malloc@PLT	#
# array_loop.c:41:       z[i] = i;
	movl	$100000000, %edi	#, ivtmp_8
# array_loop.c:38:    int* z = (int*)malloc(N*sizeof(int));
	movq	%rax, %rbp	# tmp103, z
# array_loop.c:41:       z[i] = i;
	movabsq	$4294967296, %rax	#, tmp105
	movq	%rax, 0(%rbp)	# tmp105, MEM <unsigned long> [(int *)z_13]
	leaq	20(%rbp), %rsi	#, _6
	movabsq	$12884901890, %rax	#, tmp106
	movq	%rax, 8(%rbp)	# tmp106, MEM <unsigned long> [(int *)z_13 + 8B]
	movl	$4, 16(%rbp)	#, MEM[(int *)z_13 + 16B]
	.p2align 4,,10
	.p2align 3
.L8:
	movq	%rbp, %rax	# z, z
	xorl	%ecx, %ecx	# pretmp_37
# array_loop.c:9:    int zi = 0;
	xorl	%edx, %edx	# zi
	jmp	.L7	#
	.p2align 4,,10
	.p2align 3
.L11:
# array_loop.c:13:       zi = 10*zi + *z;
	movl	(%rax), %ecx	# MEM[(int *)z_25], pretmp_37
.L7:
# array_loop.c:13:       zi = 10*zi + *z;
	leal	(%rdx,%rdx,4), %edx	#, tmp97
# array_loop.c:14:       z++;
	addq	$4, %rax	#, z
# array_loop.c:13:       zi = 10*zi + *z;
	leal	(%rcx,%rdx,2), %edx	#, zi
# array_loop.c:15:    } while(z <= zend);
	cmpq	%rax, %rsi	# z, _6
	jne	.L11	#,
# array_loop.c:45:    for(i=0; i<numiters; i++)
	subl	$1, %edi	#, ivtmp_8
	jne	.L8	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC0(%rip), %rsi	#, tmp99
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	call	__printf_chk@PLT	#
# array_loop.c:51:    free(z);
	movq	%rbp, %rdi	# z,
	call	free@PLT	#
# array_loop.c:54: }
	xorl	%eax, %eax	#
	popq	%rbp	#
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE40:
	.size	main, .-main
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
