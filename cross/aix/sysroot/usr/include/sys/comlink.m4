# @(#)22	1.12  src/bos/kernel/sys/POWER/comlink.m4, cmdas, bos530 3/31/04 11:01:43
# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos530 src/bos/kernel/sys/POWER/comlink.m4 1.12 
#  
# Licensed Materials - Property of IBM 
#  
# (C) COPYRIGHT International Business Machines Corp. 1985,1990 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
#
# COMPONENT_NAME: (CMDAS) Assembler and Macroprocessor 
#
# ORIGINS: 27
#
#-----------------------------------------------------------------------#
#  NAME:	comlink.m4
#
#  PLATFORM:	RS6000
#
#  FUNCTION:	This file defines equates for the common, cross-language
#		subroutine linkage conventions.
#
#-----------------------------------------------------------------------#

pushdef(`_rs_',ifdef(`__64BIT__',8,4)) dnl # Define register size

#	Stack Register
	.set stk,1			# Stack Register

#	Parameters passed on the stack
	.set stkmin, eval(_rs_ * 14)	# minimum stack frame size
	.set stkmin_32, eval(4 * 14)	# minimum stack frame size, 32bit
	.set stkmin_64, eval(8 * 14)	# minimum stack frame size, 64bit
	# minimum stack frame size rounded to a multiple of 16
	.set stkminalign, eval((_rs_ * 14 + 15) & ~0xF)
	.set stkminalign_32, eval((4 * 14 + 15) & ~0xF)
	.set stkminalign_64, eval((8 * 14 + 15) & ~0xF)

	.set __stkword, eval(_rs_ * 1)  # width of a word on the stack

	.set stkp9, stkmin		# pass parameter word 9 here
	.set stkp9_32, stkmin_32	# pass parameter word 9 here, 32bit
	.set stkp9_64, stkmin_64	# pass parameter word 9 here, 64bit

#	Parameters normally in registers
#	(callee may store them here to get contiguous argument list)
	.set stkp8, eval(_rs_ * 13)
	.set stkp1, eval(_rs_ * 6)

#	Inter-module link area
	.set stktoc,  eval(_rs_ * 5)	# inter-module saved toc pointer
	.set stkret,  eval(_rs_ * 4)	# inter-module saved return addr
	# two reserved words (double words)
	.set stklink, eval(_rs_ * 2)	# link register save area
	.set stkcond, eval(_rs_ * 1)	# condition register save area
	.set stkback, eval(_rs_ * 0)	# backchain to caller's frame

#	Floating point register save area - full save starts with FPR14
	.set stkfpr31, -8		# fpr 31 save area
	.set stkfpr30, -16		# fpr 30 save area
	.set stkfpr29, -24		# fpr 29 save area
	.set stkfpr28, -32		# fpr 28 save area
	.set stkfpr27, -40		# fpr 27 save area
	.set stkfpr26, -48		# fpr 26 save area
	.set stkfpr25, -56		# fpr 25 save area
	.set stkfpr24, -64		# fpr 24 save area
	.set stkfpr23, -72		# fpr 23 save area
	.set stkfpr22, -80		# fpr 22 save area
	.set stkfpr21, -88		# fpr 21 save area
	.set stkfpr20, -96		# fpr 20 save area
	.set stkfpr19, -104		# fpr 19 save area
	.set stkfpr18, -112		# fpr 18 save area
	.set stkfpr17, -120		# fpr 17 save area
	.set stkfpr16, -128		# fpr 16 save area
	.set stkfpr15, -136		# fpr 15 save area
	.set stkfpr14, -144		# fpr 14 save area

#	General purpose register save area
#
#	These are the offsets if no floating point registers
#	were saved, otherwise one must also subtract eight bytes
#	times the number of floating point registers saved.

	.set stkr31, -eval((32-31) * _rs_)	# GPR save area
	.set stkr13, -eval((32-13) * _rs_)	# full save starts with R13

#	GPRs 0-12 are not normally saved, but would go here if they were.
#	These locations are normally used for local variables, but signal
#	delivery code on svc exit saves registers 0-12.

	.set stkr12, stkr13 - _rs_		# R12, not normally saved
	.set stkr0, -eval((32-0) * _rs_)	# R0, not normally saved
	.set stkr1, -eval((32-1) * _rs_)	# R1
	.set stkr2, -eval((32-2) * _rs_)	# R2
	.set stkr3, -eval((32-3) * _rs_)	# R3

#	The following reflect stack frames for routines that have no
#	local variables.
	.set stkpush, stkr13-_rs_	#decr. to here to "buy" a frame
	.set stkpop, 0-stkpush		#incr. to here to release frame
#
#	Exec sets up an initial stack for execexit as described in exec.c
#	The constants below are the offsets to variables in this stack.
#
	.set exstkr0,  0		# offset of r0
	.set extstkr1, eval(_rs_*1)	# offset of r1
	.set extstkr31,eval(_rs_*31)	# offset of r31
	.set exstklr,  eval(_rs_*32)	# offset of link reg
	.set exstkenv, eval(_rs_*33)	# offset of environ pointer
	.set exerrno,  eval(_rs_*34)	# offset of errno

popdef(`_rs_')
