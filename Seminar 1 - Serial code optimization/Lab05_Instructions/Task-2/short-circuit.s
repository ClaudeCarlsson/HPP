	.file	"short-circuit.c"
# GNU C17 (Ubuntu 11.3.0-1ubuntu1~22.04) version 11.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.p2align 4
	.globl	isMostlyTrue
	.type	isMostlyTrue, @function
isMostlyTrue:
.LFB39:
	.cfi_startproc
	endbr64	
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 16
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	call	rand@PLT	#
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	pxor	%xmm0, %xmm0	# tmp89
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	movsd	.LC1(%rip), %xmm1	#, tmp96
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp97, tmp89
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp90
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	xorl	%eax, %eax	# r90
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	cvtss2sd	%xmm0, %xmm0	# tmp90, tmp92
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	comisd	%xmm0, %xmm1	# tmp92, tmp96
	seta	%al	#, r90
# short-circuit.c:9: }
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE39:
	.size	isMostlyTrue, .-isMostlyTrue
	.p2align 4
	.globl	isMostlyFalse
	.type	isMostlyFalse, @function
isMostlyFalse:
.LFB40:
	.cfi_startproc
	endbr64	
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 16
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	call	rand@PLT	#
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	pxor	%xmm0, %xmm0	# tmp89
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	movsd	.LC2(%rip), %xmm1	#, tmp96
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp97, tmp89
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp90
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	xorl	%eax, %eax	# r10
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	cvtss2sd	%xmm0, %xmm0	# tmp90, tmp92
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	comisd	%xmm0, %xmm1	# tmp92, tmp96
	seta	%al	#, r10
# short-circuit.c:15: }
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE40:
	.size	isMostlyFalse, .-isMostlyFalse
	.p2align 4
	.globl	isFiftyFifty
	.type	isFiftyFifty, @function
isFiftyFifty:
.LFB41:
	.cfi_startproc
	endbr64	
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 16
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	call	rand@PLT	#
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	pxor	%xmm0, %xmm0	# tmp88
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	movss	.LC3(%rip), %xmm1	#, tmp94
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp95, tmp88
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp89
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	xorl	%eax, %eax	# r50
	comiss	%xmm0, %xmm1	# tmp89, tmp94
	seta	%al	#, r50
# short-circuit.c:21: }
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE41:
	.size	isFiftyFifty, .-isFiftyFifty
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC4:
	.string	"foo = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB42:
	.cfi_startproc
	endbr64	
	pushq	%r12	#
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
# short-circuit.c:26:    srand (time(NULL));
	xorl	%edi, %edi	#
# short-circuit.c:24: {
	pushq	%rbx	#
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
# short-circuit.c:26:    srand (time(NULL));
	movl	$2000000, %ebx	#, ivtmp_10
# short-circuit.c:24: {
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 32
# short-circuit.c:26:    srand (time(NULL));
	call	time@PLT	#
# short-circuit.c:26:    srand (time(NULL));
	movl	%eax, %edi	# tmp170, _1
	call	srand@PLT	#
	jmp	.L19	#
	.p2align 4,,10
	.p2align 3
.L13:
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	call	rand@PLT	#
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	pxor	%xmm0, %xmm0	# tmp153
# short-circuit.c:36:       if( (isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse()&&isFiftyFifty()))
	movsd	.LC1(%rip), %xmm5	#, tmp186
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp177, tmp153
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp154
	cvtss2sd	%xmm0, %xmm0	# tmp154, tmp156
# short-circuit.c:36:       if( (isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse()&&isFiftyFifty()))
	comisd	%xmm0, %xmm5	# tmp156, tmp186
	jbe	.L16	#,
.L18:
# short-circuit.c:37:          foo += 4;                
	addl	$4, %r12d	#, foo
.L15:
# short-circuit.c:27:    for (i=0; i<2000000; i++)
	subl	$1, %ebx	#, ivtmp_10
	je	.L25	#,
.L19:
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	call	rand@PLT	#
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	pxor	%xmm0, %xmm0	# tmp121
# short-circuit.c:30:       if(isMostlyTrue() || isMostlyFalse())
	movsd	.LC1(%rip), %xmm1	#, tmp180
# short-circuit.c:31:          foo += 1;
	movl	$1, %r12d	#, foo
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp171, tmp121
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp122
	cvtss2sd	%xmm0, %xmm0	# tmp122, tmp124
# short-circuit.c:30:       if(isMostlyTrue() || isMostlyFalse())
	comisd	%xmm0, %xmm1	# tmp124, tmp180
	jbe	.L26	#,
.L9:
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	call	rand@PLT	#
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	pxor	%xmm0, %xmm0	# tmp134
# short-circuit.c:33:       if(isMostlyFalse() && isMostlyTrue())
	movsd	.LC2(%rip), %xmm2	#, tmp182
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp173, tmp134
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp135
	cvtss2sd	%xmm0, %xmm0	# tmp135, tmp137
# short-circuit.c:33:       if(isMostlyFalse() && isMostlyTrue())
	comisd	%xmm0, %xmm2	# tmp137, tmp182
	ja	.L27	#,
.L10:
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	call	rand@PLT	#
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	pxor	%xmm0, %xmm0	# tmp144
# short-circuit.c:36:       if( (isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse()&&isFiftyFifty()))
	movss	.LC3(%rip), %xmm3	#, tmp184
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp175, tmp144
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp145
# short-circuit.c:36:       if( (isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse()&&isFiftyFifty()))
	comiss	%xmm0, %xmm3	# tmp145, tmp184
	ja	.L13	#,
.L16:
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	call	rand@PLT	#
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	pxor	%xmm0, %xmm0	# tmp148
# short-circuit.c:36:       if( (isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse()&&isFiftyFifty()))
	movsd	.LC2(%rip), %xmm4	#, tmp185
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp176, tmp148
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp149
	cvtss2sd	%xmm0, %xmm0	# tmp149, tmp151
# short-circuit.c:36:       if( (isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse()&&isFiftyFifty()))
	comisd	%xmm0, %xmm4	# tmp151, tmp185
	jbe	.L15	#,
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	call	rand@PLT	#
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	pxor	%xmm0, %xmm0	# tmp158
# short-circuit.c:36:       if( (isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse()&&isFiftyFifty()))
	movss	.LC3(%rip), %xmm6	#, tmp187
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp178, tmp158
# short-circuit.c:19:    int r50 = ((float)rand()/RAND_MAX < 0.50)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp159
# short-circuit.c:36:       if( (isFiftyFifty()&&isMostlyTrue()) || (isMostlyFalse()&&isFiftyFifty()))
	comiss	%xmm0, %xmm6	# tmp159, tmp187
	ja	.L18	#,
# short-circuit.c:27:    for (i=0; i<2000000; i++)
	subl	$1, %ebx	#, ivtmp_10
	jne	.L19	#,
.L25:
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	movl	%r12d, %edx	# foo,
	leaq	.LC4(%rip), %rsi	#, tmp162
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	call	__printf_chk@PLT	#
# short-circuit.c:41: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax	#
	popq	%rbx	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L27:
	.cfi_restore_state
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	call	rand@PLT	#
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	pxor	%xmm0, %xmm0	# tmp139
# short-circuit.c:34:          foo += 2;
	movsd	.LC1(%rip), %xmm7	#, tmp183
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp174, tmp139
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp140
# short-circuit.c:34:          foo += 2;
	leal	2(%r12), %eax	#, tmp168
# short-circuit.c:7:    int r90 = ((float)rand()/RAND_MAX < 0.90)?1:0;
	cvtss2sd	%xmm0, %xmm0	# tmp140, tmp142
# short-circuit.c:34:          foo += 2;
	comisd	%xmm0, %xmm7	# tmp142, tmp183
	cmova	%eax, %r12d	# tmp168,, foo
	jmp	.L10	#
	.p2align 4,,10
	.p2align 3
.L26:
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	call	rand@PLT	#
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	pxor	%xmm0, %xmm0	# tmp126
# short-circuit.c:30:       if(isMostlyTrue() || isMostlyFalse())
	movsd	.LC2(%rip), %xmm6	#, tmp181
	xorl	%r12d, %r12d	# foo
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	cvtsi2ssl	%eax, %xmm0	# tmp172, tmp126
# short-circuit.c:13:    int r10 = ((float)rand()/RAND_MAX < 0.10)?1:0;
	mulss	.LC0(%rip), %xmm0	#, tmp127
	cvtss2sd	%xmm0, %xmm0	# tmp127, tmp129
# short-circuit.c:30:       if(isMostlyTrue() || isMostlyFalse())
	comisd	%xmm0, %xmm6	# tmp129, tmp181
	seta	%r12b	#, foo
	jmp	.L9	#
	.cfi_endproc
.LFE42:
	.size	main, .-main
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	805306368
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	-858993459
	.long	1072483532
	.align 8
.LC2:
	.long	-1717986918
	.long	1069128089
	.section	.rodata.cst4
	.align 4
.LC3:
	.long	1056964608
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
