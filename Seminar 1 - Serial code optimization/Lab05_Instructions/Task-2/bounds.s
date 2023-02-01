	.file	"bounds.c"
# GNU C17 (Ubuntu 11.3.0-1ubuntu1~22.04) version 11.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64	
# bounds.c:35: }
	xorl	%eax, %eax	#
	ret	
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.text
	.p2align 4
	.globl	foo
	.type	foo, @function
foo:
.LFB40:
	.cfi_startproc
	endbr64	
# bounds.c:40: 	return j%size;
	movl	%edi, %eax	# tmp88, tmp88
	cltd
	idivl	%esi	# tmp89
# bounds.c:41: }
	movl	%edx, %eax	# tmp86,
	ret	
	.cfi_endproc
.LFE40:
	.size	foo, .-foo
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
