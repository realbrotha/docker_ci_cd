# IBM_PROLOG_BEGIN_TAG 
# This is an automatically generated prolog. 
#  
# bos53Q src/bos/kernel/sys/POWER/asdef.s 1.24.1.10 
#  
# Licensed Materials - Property of IBM 
#  
# COPYRIGHT International Business Machines Corp. 1985,1990 
# All Rights Reserved 
#  
# US Government Users Restricted Rights - Use, duplication or 
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp. 
#  
# IBM_PROLOG_END_TAG 
divert(99)
# @(#)28	1.24.1.10  src/bos/kernel/sys/POWER/asdef.s, cmdas, bos53Q, q2008_05B5 1/28/08 14:50:42
#
# COMPONENT_NAME: (CMDAS) Assembler and Macroprocessor 
#
# FUNCTIONS: 
#
# ORIGINS: 3, 27
#
# XCOFF version

# define the CPU register size in bytes
ifdef(`__64BIT_KERNEL',`define(__RS__,`8')',`define(__RS__,`4')')

# define the CPU registers

        define(r0,0)
        define(r1,1)
        define(r2,2)
        define(r3,3)
        define(r4,4)
        define(r5,5)
        define(r6,6)
        define(r7,7)
        define(r8,8)
        define(r9,9)
        define(r10,10)
        define(r11,11)
        define(r12,12)
        define(r13,13)
        define(r14,14)
        define(r15,15)
        define(r16,16)
        define(r17,17)
        define(r18,18)
        define(r19,19)
        define(r20,20)
        define(r21,21)
        define(r22,22)
        define(r23,23)
        define(r24,24)
        define(r25,25)
        define(r26,26)
        define(r27,27)
        define(r28,28)
        define(r29,29)
        define(r30,30)
        define(r31,31)

#**********************************************************************
#                                                                     *
#   commonly used equates                                             *
#                                                                     *
#**********************************************************************

        define(false,0x04)      # branch false bo
        define(true,0x0c)       # branch true bo
        define(falsectr,0x00)   # dec ctr, branch false and ctr != 0 bo
        define(falzezct,0x02)   # dec ctr, branch false and ctr  = 0 bo
        define(truectr,0x08)    # dec ctr, branch true  and ctr != 0 bo
        define(truezctr,0x0a)   # dec ctr, branch true  and ctr  = 0 bo
        define(always,0x14)     # branch unconditional bo
        define(brctr,0x10)      # dec ctr, branch ctr != 0 bo
        define(brzctr,0x12)     # dec ctr, branch ctr  = 0 bo
        define(lt,0x00)         # less than condition (bit 0)
        define(gt,0x01)         # greater than condition (bit 1)
        define(eq,0x02)         # equal condition (bit 2 from 0)
        define(so,0x03)         # so bit in cr (bit 3)
        define(nolk,0x00)       # no link
        define(lk,0x01)         # link
        define(mq,0x00)         # mq register
        define(xer,0x01)        # fixed point exception register
        define(lr,0x08)         # link register
        define(ctr,0x09)        # count register
        define(tid,0x11)        # tid
        define(dsisr,0x12)      # dsisr
        define(dar,0x13)        # dar
        define(sdr0,0x18)       # storage descriptor pft
        define(sdr1,0x19)       # storage descriptor hat
        define(srr0,0x1a)       # save/restore register 0
        define(srr1,0x1b)       # save/restore register 1

#**********************************************************************
#                                                                     *
#   equates for msr bits                                              *
#                                                                     *
#**********************************************************************

        define(ee,0x8000)       # external interrupt
        define(pr,0x4000)       # problem state
        define(fp,0x2000)       # floating point available
        define(me,0x1000)       # machine check
        define(fe,0x0800)       # floating  point exception enable
        define(al,0x0080)       # alignment check
        define(ip,0x0040)       # prefix
        define(ir,0x0020)       # instruction relocate
        define(dr,0x0010)       # data relocate
        define(idr,0x0030)      # instruction and data relocate
        define(allon,0x00f0)    # all on
        define(off,0x0000)      # mask to set msr off
        define(dis,0x7fff)      # mask to disable


#**********************************************************************
#                                                                     *
#   equates for floating regs                                         *
#                                                                     *
#**********************************************************************

	define(fr0,0)
	define(fr1,1)
	define(fr2,2)
	define(fr3,3)
	define(fr4,4)
	define(fr5,5)
	define(fr6,6)
	define(fr7,7)
	define(fr8,8)
	define(fr9,9)
	define(fr10,10)
	define(fr11,11)
	define(fr12,12)
	define(fr13,13)
	define(fr14,14)
	define(fr15,15)
	define(fr16,16)
	define(fr17,17)
	define(fr18,18)
	define(fr19,19)
	define(fr20,20)
	define(fr21,21)
	define(fr22,22)
	define(fr23,23)
	define(fr24,24)
	define(fr25,25)
	define(fr26,26)
	define(fr27,27)
	define(fr28,28)
	define(fr29,29)
	define(fr30,30)
	define(fr31,31)

# Alternate names
	define(f0,0)
	define(f1,1)
	define(f2,2)
	define(f3,3)
	define(f4,4)
	define(f5,5)
	define(f6,6)
	define(f7,7)
	define(f8,8)
	define(f9,9)
	define(f10,10)
	define(f11,11)
	define(f12,12)
	define(f13,13)
	define(f14,14)
	define(f15,15)
	define(f16,16)
	define(f17,17)
	define(f18,18)
	define(f19,19)
	define(f20,20)
	define(f21,21)
	define(f22,22)
	define(f23,23)
	define(f24,24)
	define(f25,25)
	define(f26,26)
	define(f27,27)
	define(f28,28)
	define(f29,29)
	define(f30,30)
	define(f31,31)

#**********************************************************************
#                                                                     *
#   equates for floating point exception status bits                  *
#                                                                     *
#**********************************************************************

	define(fpxinvalid,0x20000000)
	define(fpxoverflo,0x10000000)
	define(fpxunderfl,0x08000000)
	define(fpxzdiv,   0x04000000)
	define(fpxinex,   0x02000000)
	define(fpxnvsnan, 0x01000000)
	define(fpxnvisi,  0x00800000)
	define(fpxnvidi,  0x00400000)
	define(fpxnvzdz,  0x00200000)
	define(fpxnvimz,  0x00100000)
	define(fpxnvcomp, 0x00080000)
	define(fpxnvrmz,  0x00000800)
	define(fpxnvrmi,  0x00000400)
	define(fpxnvsqr,  0x00000200)
	define(fpxnvcvi,  0x00000100)

#**********************************************************************
#                                                                     *
#   equates for segment regs                                          *
#                                                                     *
#**********************************************************************

        define(sr0,0)
        define(sr1,1)
        define(sr2,2)
        define(sr3,3)
        define(sr4,4)
        define(sr5,5)
        define(sr6,6)
        define(sr7,7)
        define(sr8,8)
        define(sr9,9)
        define(sr10,10)
        define(sr11,11)
        define(sr12,12)
        define(sr13,13)
        define(sr14,14)
        define(sr15,15)

#**********************************************************************
#                                                                     *
#   equates for condition register bit fields			      *
#                                                                     *
#**********************************************************************

        define(cr0,0)
        define(cr1,1)
        define(cr2,2)
        define(cr3,3)
        define(cr4,4)
        define(cr5,5)
        define(cr6,6)
        define(cr7,7)


#**********************************************************************
#                                                                     *
#   equates for condition register bit sub-fields                     *
#                                                                     *
#**********************************************************************

	define(cr0_0,0)
	define(cr0_1,1)
	define(cr0_2,2)
	define(cr0_3,3)

	define(cr1_0,4)
	define(cr1_1,5)
	define(cr1_2,6)
	define(cr1_3,7)

	define(cr2_0,8)
	define(cr2_1,9)
	define(cr2_2,10)
	define(cr2_3,11)

	define(cr3_0,12)
	define(cr3_1,13)
	define(cr3_2,14)
	define(cr3_3,15)

	define(cr4_0,16)
	define(cr4_1,17)
	define(cr4_2,18)
	define(cr4_3,19)

	define(cr5_0,20)
	define(cr5_1,21)
	define(cr5_2,22)
	define(cr5_3,23)

	define(cr6_0,24)
	define(cr6_1,25)
	define(cr6_2,26)
	define(cr6_3,27)

	define(cr7_0,28)
	define(cr7_1,29)
	define(cr7_2,30)
	define(cr7_3,31)

#**********************************************************************
#                                                                     *
#   equates for Vector registers                                      *
#                                                                     *
#**********************************************************************

	define(vr0,0)
	define(vr1,1)
	define(vr2,2)
	define(vr3,3)
	define(vr4,4)
	define(vr5,5)
	define(vr6,6)
	define(vr7,7)
	define(vr8,8)
	define(vr9,9)
	define(vr10,10)
	define(vr11,11)
	define(vr12,12)
	define(vr13,13)
	define(vr14,14)
	define(vr15,15)
	define(vr16,16)
	define(vr17,17)
	define(vr18,18)
	define(vr19,19)
	define(vr20,20)
	define(vr21,21)
	define(vr22,22)
	define(vr23,23)
	define(vr24,24)
	define(vr25,25)
	define(vr26,26)
	define(vr27,27)
	define(vr28,28)
	define(vr29,29)
	define(vr30,30)
	define(vr31,31)

# Alternate names
	define(v0,0)
	define(v1,1)
	define(v2,2)
	define(v3,3)
	define(v4,4)
	define(v5,5)
	define(v6,6)
	define(v7,7)
	define(v8,8)
	define(v9,9)
	define(v10,10)
	define(v11,11)
	define(v12,12)
	define(v13,13)
	define(v14,14)
	define(v15,15)
	define(v16,16)
	define(v17,17)
	define(v18,18)
	define(v19,19)
	define(v20,20)
	define(v21,21)
	define(v22,22)
	define(v23,23)
	define(v24,24)
	define(v25,25)
	define(v26,26)
	define(v27,27)
	define(v28,28)
	define(v29,29)
	define(v30,30)
	define(v31,31)


#
# Conditional definitions for 64-bit assembly source.
ifdef(`__64BIT__',`
	pushdef(_LOAD,`ld')`'dnl
	pushdef(_STORE,`std')`'dnl
	pushdef(_STOREU,`stdu')`'dnl
	pushdef(_LONG,`.llong')`'dnl
	pushdef(`_rs',`8')`'dnl # Define register size
',`
	pushdef(`_LOAD',`lwz')`'dnl
	pushdef(`_STORE',`stw')`'dnl
	pushdef(`_STOREU',`stwu')`'dnl
	pushdef(`_LONG',`.long')`'dnl
	pushdef(`_rs',`4')`'dnl # Define register size
')	

#
# Format: ENTRY(label_name)
#   Where:
#       label_name - is the label to be referenced
# This macro generates the proper naming convention for a code label
#
define( ENTRY,`.$1')



#
# Format: DATA(label_name)
#   Where:
#       label_name - is the label
# This macro generates the proper naming convention for a data label
#
define( DATA,`$1')

#
#	_DF defines the traceback table for R2 dependent assembly programs.
#	It uses the assembler pseudo-op .tbtag, which defines
#	the beginning of the traceback table. 
#
#	Following is the traceback table structure as defined in the
#	sys/debug.h. The seven arguments of the _DF macros are shown below:
#
####### First argument is the bitwise or of the following 8 bitfields,
#
#	unsigned globallink:1	Set if routine is global linkage
#	unsigned is_eprol:1	Set if is out-of-line epilog/prologue
#	unsinged has_tboff:1	Set if offset from start of proc stored
#	unsigned int_proc:1;	Set if routine is internal
#	unsigned has_ctl:1;	Set if routine involves controlled storage
#	unsigned tocless:1;	Set if routine contains no TOC
#	unsigned fp_present:1;  Set if routine performs FP operations
#	unsigned log_abort:1;   Set if routine logs or aborts FP ops
#
######  Second argument is the bitwise or of the following bitfields.
#
#	unsigned int_hndl:1;    Set if routine is interrupt handler
#	unsigned name_present:1;Set if name is present in proc table
#	unsigned uses_alloca:1; Set if alloca used to allocate storage
#	unsigned cl_dis_inv:3;  On-condition directives, see below
#	unsigned saves_cr:1;    Set if procedure saves the condition reg
#	unsigned saves_lr:1;    Set if procedure saves the link reg
#
###### Third argument is the bitwise or of the following bitfields.
#
#	unsigned stores_bc:1;   Set if procedure saves the link reg
#	unsigned spare2:1;      Spare bit
#	unsigned fpr_saved:6;   Number of FPRs saved, max of 32
#
###### Fourth argument is the bitwise or of the following bitfields.
#
#	unsigned spare3:1;      Spare bit
#	unsigned has_vec:1;     Set if optional vector info is present
#	unsigned gpr_saved:6;   Number of GPRs saved, max of 32
#
###### Fifth argument is the bitwise or of the following bitfields.
#
#	unsigned fixedparms:8;  Number of fixed point parameters
#
###### Sixth argument is the bitwise or of the following bitfields.
#
#	unsigned floatparms:7;  Number of floating point parameters
#	unsigned parmsonstk:1;  Set if all parameters placed on stack
#
###### Seventh argument is the bitwise or of the following bitfields.
#
#	unsigned int parminfo;  Order and type encoding of parameters:
#				Left-justified bit-encoding as follows:
#				'0'  ==> fixed parameter
#				'10' ==> single-precision float parameter
#				'11' ==> double-precision float parameter
#
define(_DF, `.align 2
	.tbtag 0x0,0xc,$1,$2,$3,$4,$5,$6,$7,0x0,0x0,0x0,0x0,0x0,0x0,0x0')

#
# Special types of stack frames:
#	_DF_NOFRAME - no stack frame, parameters in registers
#	_DF_START - first stack frame
#	_DF_GLUE - the routine is a global linkage routine
#
define( _DF_NOFRAME,    `0x0,0x0,0x0,0x0,0x0,0x0,0x0')dnl
define( _DF_START,      `0x0,0x0,0x0,0x0,0x0,0x0,0x0')dnl
define( _DF_GLUE,	`0x8,0x0,0x0,0x0,0x0,0x0,0x0')dnl

# Defines for 'lang' byte
define(TB_C,		0)
define(TB_FORTRAN,	1)
define(TB_PASCAL,	2)
define(TB_ADA,		3)
define(TB_PL1,		4)
define(TB_BASIC,	5)
define(TB_LISP,		6)
define(TB_COBOL,	7)
define(TB_MODULA2,	8)
define(TB_CPLUSPLUS,	9)
define(TB_RPG,		10)
define(TB_PL8,		11)
define(TB_ASM,		12)
define(TB_HPJ,		13)
define(TB_OBJECTIVEC,	14)
define(TB_UPC,		15)

# Defines for 'byte3'
define(TB_GLOBALLINK,	0x80)
define(TB_IS_EPROL,	0x40)
define(TB_HAS_TBOFF,	0x20)
define(TB_INT_PROC,	0x10)
define(TB_HAS_CTL,	0x08)
define(TB_TOCLESS,	0x04)
define(TB_FP_PRESENT,	0x02)
define(TB_LOG_ABORT,	0x01)

# Defines for 'byte4'
define(TB_INT_HNDL,		0x80)
define(TB_NAME_PRESENT,		0x40)
define(TB_USES_ALLOCA,		0x20)
define(TB_CL_DIS_INV_MASK,	0x1C)
define(TB_SAVES_CR,		0x02)
define(TB_SAVES_LR,		0x01)

# Defines for the cl_dis_inv field in byte4
define(TB_WALK_ONCOND,    0)	# Walk the stack without restoring state
define(TB_DISCARD_ONCOND, 4)	# Walk the stack and discard
define(TB_INVOKE_ONCOND,  8)	# Invoke a specific system routine

# Defines for 'byte5'
define(TB_STORES_BC,		0x80)
define(TB_FIXUP,		0x40)
define(TB_FPR_SAVED_MASK,	0x3F)

# Defines for 'byte6'
define(TB_HAS_VEC,		0x40)
define(TB_GPR_SAVED_MASK,	0x3F)

# Byte 7 is the fixedparms field.

# Byte 8 values
define(TB_FLOATPARMS_MASK,	0xFE)
define(TB_PARMSONSTK,		0x01)

#  Format: TBTAG(version,lang,byte3,byte4, byte5,byte6,byte7,byte8,
#		fname,
#		flabel,
#		parminfo,
#		alloca_reg,
#		hand_mask,
#		ctl_anchors, ...)
#  Where:
#	version:	trace-back table version: must be 0
#	lang:		Source language.  See definitions above.
#	byte3..byte8:	As defined in <sys/debug.h>.  Symbolic definitions
#			are defined above.
#	fname:		Function name.  If fname does not begin with a double
#			quote, double quotes are added around the name.
#			If present, TB_NAME_PRESENT is set in byte 4.  If
#			omitted or null, TB_NAME_PRESENT is cleared in byte 4.  
#	flabel:		Address of beginning of the function.
#			If present, TB_HAS_TBOFF is set in byte 3.
#			If omitted or null, TB_HAS_TBOFF is cleared in byte 3.
#			The macro computes the tb_offset field from flabel.
#	parminfo:	Order and type encoding of parameters.
#			If omitted or null, the fixedparms field in byte 7
#			and the floatparms field in byte 8 should be 0.
#			If present, either fixedparms or floatparms should
#			be non-zero.
#	alloca_reg:	Register for alloca automatic storage handler mask.
#			If present, TB_USES_ALLOCA is set in byte 4.
#			If omitted or null, TB_USES_ALLOCA is cleared in byte 4.
#	hand_mask:	Interrupt handler mask.
#			If present, TB_INT_HNDL is set in byte 4.
#			If omitted or null, TB_INT_HNDL is cleared in byte 4.
#	ctl_anchors:	Any number of controlled storage anchors.
#			If any exist, TB_HAS_CTL is set in byte 3.
#			Otherwise, TB_HAS_CTL is cleared in byte 3.
#
#	This macro generates a traceback table using .long, .byte, and .short
#	pseudo-ops rather than using the assembler pseudo-op .tbtag,
#	because .tbtag doesn't allow optional fields to be specified.
#
#	All arguments are optional.
#
#	Example:
#	TBTAG(0,TB_C, 0, TB_SAVES_LR, TB_STORES_BC, 0, 2, TB_PARMSONSTK + 2*1,
#		 "main", .main, 0x20000000)

define(TBTAG, `.long	0		# traceback table marker
	.byte	ifelse($1,,0,$1),ifelse($2,,0,$2)
__tbtag((ifelse($3,,0,$3))&~0x28,
	(ifelse($4,,0,$4))&~0xe0,
	.byte	'dnl
`ifelse($5,,0,$5)``,''ifelse($6,,0,$6)``,'''dnl
`ifelse($7,,0,$7)``,''ifelse($8,,0,$8),
	shift(shift(shift(shift(shift(shift(shift(shift($*)))))))))')

define(__tbtag, `pushdef(`_y_',`ifelse(substr(eval(`$#-9'),0,1),-,,
			ifelse(`x'$9,`x',,` | 0x08'))')`''dnl
`	.byte	($1)`'ifelse(`$5',,,` | 0x20')`'_y_
	.byte	($2)`''dnl
`ifelse(`$8',,,` | 0x80')`'ifelse(`$4',,,` | 0x40')`'ifelse(`$7',,,` | 0x20')'
	$3``''dnl
dnl	### Optional parts follow ###
`ifelse($6,,,`
	.long	$6		`#' parminfo')`''dnl
`ifelse($5,,,`
	.long	$-($5)ifelse($6,,-12,-16)	`#' tb_offset')`''dnl
`ifelse($8,,,`
	.long	$8		`#' hand_mask')`''dnl
`ifelse(_y_,,,`
	.long	eval(`$#-8'),shift(shift(shift(shift(shift(
			shift(shift(shift($*))))))))	`#' ctl anchors')`''dnl
`ifelse(`$4',,, `ifelse(substr(`$4',0,1),",`
	.short	eval(len($4)-2); .byte $4	`#' function name',`
	.short	eval(len($4)); .byte "$4"	`#' function name')')`''dnl
`ifelse($7,,,`
	.byte	$7		`#' alloca register')`''dnl
`popdef(`_y_')')

#  Format: 
#    TBTAG_VECEXT(vr_saved, saves_vrsave, has_varargs, vectorparms, vec_present)
#  Where:
#	vr_saved:	number of non-vol Vector registers saved
#	saves_vrsave:	set if VRsave is saved
#	has_varargs:	set if has variable argument list
#	vectorparms:	number of vector parameters
#	vec_present:	set if routine performs vector instructions 
#
#  This macro generates the optional Vector Extension to the traceback
#  table.  This macro must be used immediately following the TBTAG macro, with
#  TB_HAS_VEC set in 'byte 6'.
#
#  Example:
#
#	TBTAG(0,TB_C, 0, TB_SAVES_LR, TB_STORES_BC, TB_HAS_VEC, 2, 
#		TB_PARMSONSTK + 2*1, "main", .main, 0x20000000)
#	TBTAG_VECEXT(4, 1, 0, 2, 1)
#
define(TBTAG_VECEXT, `
	.byte ($1<2)|($2<1)|$3
	.byte ($4<1)|$5
')

#
# S_PROLOG(name) - prolog for a simple routine which
#                   does not call or modify r13-r31
define( S_PROLOG,
        `.csect ENTRY($1[PR])
	 .globl ENTRY($1[PR])')

# FCNDES(name,[label]) - function descriptor for a routine.
#               Where: label - keyword indicates LD entry vs SD of type PR
# .toc is to make sure there is at least on in program so TOC[t0] works
define( FCNDES,
       `.toc
ifdef(`__64BIT__',`
        .csect  $1[DS],3
',`
        .csect  $1[DS],2
')	
        .globl  $1[DS]
ifelse($2x,labelx,
`       ''_LONG``	ENTRY($1)',
`       ''_LONG``	ENTRY($1[PR])')
        '_LONG`	TOC[t0]')',

# S_EPILOG - epilog for S_PROLOG

define( S_EPILOG,
       `br
        _DF(_DF_NOFRAME)')

#
#  PROLOG(fname,GPR, FPR, Framesize)
#
#	fname: name of the function
#	GPR  : the least number of the GPR, (13-32) 32 = no GPRs saved
#	FPR  : the least number of the FPR, (14-32) 32 = no FPRs saved
#	Framesize: the size of the stack to hold the local variables and
#		   function parameters.
#
#	Example:
#	PROLOG(hello,20,17,100)
#
#	Here, hello is the name of the function,
#	this prolog will save GPRs 20 through 31, FPRs 17 through 31,
#	get a local stack area of 100 bytes
#	and will modify the stack size accordingly.
#
define( PROLOG,
     `define(`SAVEstk',eval(('_rs`*14+'_rs`*(32-$2)+8*(32-$3)+$4+15) & ~0xF))dnl
        define(`SAVEgpr',`eval(32-$2)')dnl
	define(`SAVEfpr',`eval(32-$3)')dnl
	define(`SAVEfname',$1)'`
	.csect  ENTRY($1[PR])
	.globl	ENTRY($1[PR])
	mflr	0`'dnl
ifelse($3,32,,`
	`#' Save floating-point registers'dnl
	`SAVEFPR($3)')dnl
ifelse($2,32,,`
	`#' Save general purpose registers'dnl
	'ifdef(`__64BIT__',```SAVEGPR($2,eval(8*(32-$3)))''',```
	stm	$2, -eval(8*(32-$3))-eval(4*(32-$2))(1)''')`)
	`#' Save return address
	'_STORE`	0, 'eval(2 * _rs)`(1)
	`#' Buy stack frame
	'_STOREU`	r1, -SAVEstk'``(1)'
')

#
# EPILOG(fixed params, float params, type info of the parameters)
#
#   	fixed params:  total number of fixed point parameters,
#	float params:  total number of floating point parameters,
#	type	    :  type of each parameter (see linkage convention)
#		       this field is only used for debugger stack trace
#		       back info
#
define( EPILOG,
        `
	`#' Load return address
	'_LOAD`	r0,SAVEstk+'eval(2 * _rs)`(1)
	`#' Free stack frame
	addi	1,1,SAVEstk
	mtlr	0
ifelse(SAVEgpr,0,,`	`#' Restore general purpose registers'dnl
	'ifdef(`__64BIT__',```RESTOREGPR(SAVEgpr,eval(8*SAVEfpr))
''',```
	lm	eval(32-SAVEgpr), -eval(8*SAVEfpr)-eval(4*SAVEgpr)(1)
''')`)dnl
ifelse(SAVEfpr,0,,`	`#' Restore floating-point registers'dnl
	`RESTOREFPR(SAVEfpr)
')dnl
        br
	TBTAG(0,'TB_ASM`,0,'TB_SAVES_LR`,SAVEfpr,SAVEgpr,
		ifelse(eval($1+$2),0,`0,0',`$1,2*$2'),
		SAVEfname,ENTRY(SAVEfname[PR])ifelse(eval($1+$2),0,,`,$3'))
')

#	Save floating point registers
define(`SAVEFPR', `SFPR($1,eval(-8*(32-$1)))')
define(`SFPR', `ifelse(eval(32-$1),0,,`
	stfd	$1,$2(1)SFPR(eval($1+1),eval($2+8))')')

#
#	RESTOREFPR retrieves the floating point registers from the stack.
#
define(`RESTOREFPR', `RFPR(eval(32-$1),eval(-8*$1))')
define(`RFPR', `ifelse(eval(32-$1),0,,`
	lfd	$1,$2(1)RFPR(eval($1+1),eval($2+8))')')

ifdef(`__64BIT__',
#	Save general purpose registers
define(`SAVEGPR', `SGPR($1,eval(-8*(32-$1)),ifelse($2,0,,-$2))')
define(`SGPR', `ifelse(eval(32-$1),0,,`
	std	$1,$3$2(1)SGPR(eval($1+1),eval($2+8),$3)')')

#
# RESTOREGPR restores the general purpose registers from the stack.
#
define(`RESTOREGPR', `RGPR(eval(32-$1),eval(-8*$1),ifelse($2,0,,-$2))')
define(`RGPR', `ifelse(eval(32-$1),0,,`
	ld	$1,$3$2(1)RGPR(eval($1+1),eval($2+8),$3)')')
)

#	(Misnamed) macro to extract a single bit from a register,
#	putting the extracted bit in any GPR.  
define( SETBIT,`rlinm	$1,$2,0,$3,$3')
#	Macro to clear a single bit in a register,
#	putting the result in any GPR.
define( CLRBIT,`rlinm	$1,$2,0,$3+1,$3-1')

# TRAP()

define( TRAP,
       `teq     1,1')


# PTRAP() used for panic_trap()

define( PTRAP,
       `teq     14,14')

# MFSR()

define( MFSR,
       `mfsr    $1,3')

# MTSR()

define( MTSR,
       `mtsr    $1,3')

# MTSPR()

define( MTSPR,
       `mtspr   $1,3')

# MFSPR()

define( MFSPR,
       `mfspr   3,$1')

# LOOP()

define( LOOP,
       `b       $')


# simulate TOCE and LTOC MACRO
# Format: TOCE(labelname,[entry|data])
#    where
#       labelname - the name of the csect to create a toc entry for
#       entry - indicates it is a procedure entry
#       data - indicates it is a procedure's static area
# This macro creates a TOC entry called labelname
#
define(TOCE,
`ifelse($2,entry,
`$1.A:  .tc     ENTRY($1)[tc],ENTRY($1)
        .extern ENTRY($1)',
$2,data,
`$1.S:  .tc     DATA($1)[tc],DATA($1)[ua]
        .extern DATA($1)[ua]',
`errprint(`illegal argument "$2"')')')

#
# Format: TOCL(labelname,[entry|data])
#    where
#       labelname - the name of the csect to create a toc entry for
#       entry - indicates it is a procedure entry
#       data - indicates it is a procedure's static area
# This macro creates a TOC entry called labelname
#
define(TOCL,
`ifelse($2,entry,
`$1.A:  .tc     ENTRY($1)[tc],ENTRY($1)',
$2,data,
`$1.S:  .tc     DATA($1)[tc],DATA($1)',
`errprint(`illegal argument "$2"')')')


# Format: LTOC(regno,labelname,[entry|data])
#    where
#       regno - is the register number to load
#       labelname - is the name of the csect address you want to load
#       entry - indicates it is a procedure entry
#       data - indicates it is a procedure's static area
# This macro loads an address from a TOC entry created by toce above
#
define(LTOC,
`ifelse($3,entry,
`       ''_LOAD``	$1,$2.A(2)',
$3,data,
`       ''_LOAD``	$1,$2.S(2)',
`errprint(`illegal argument "$3"')')')

# Format: LTOCR(regno,labelname,[entry|data],tocr)
#    where
#       regno - is the register number to load
#       labelname - is the name of the csect address you want to load
#       entry - indicates it is a procedure entry
#       data - indicates it is a procedure's static area
#	tocr - indicates register that contains TOC
# This macro loads an address from a TOC entry created by toce/tocl above
# it is used when the toc base is not contained in r2
#
define(LTOCR,
`ifelse($3,entry,
`       ''_LOAD``	$1,$2.A($4)',
$3,data,
`       ''_LOAD``	$1,$2.S($4)',
`errprint(`illegal argument "$3"')')')


#
# Format: TOC_ORIGIN
#
# Usage:
# label: .long TOC_ORIGIN
#    to get the address of this modules TOC
#    generates TOC[tc] for TOC and TOC[tc0] for XCOFF binders
#
define(TOC_ORIGIN,`TOC[t0]')

#
# Format: CSECT(labelname,[PR|RW|RO|TC],align)
#    where
#       labelname - is the name of the csect you want to create
#       [PR|RW|RO|TC] - csect type
#       align - segment alignment
# This macro is used to define csects.  S_PROLOG should be used to declare code
# segments
#
define( CSECT,
`ifelse(x$3,x,                          # no align parameter
    `ifelse($2,PR,
`       .csect  ENTRY($1[PR])',
    $2,RW,
`       .csect  DATA($1[RW])',
    $2,RO,
`       .csect  DATA($1[RO])',
    $2,TC,
`       .csect  DATA($1[TC])',
   `errprint(`illegal argument "$2"')')'
    ,                                  # alignment parameter specified
    `ifelse($2,PR,
`       .csect  ENTRY($1[PR]),$3',
    $2,RW,
`       .csect  DATA($1[RW]),$3',
    $2,RO,
`       .csect  DATA($1[RO]),$3',
    $2,TC,
`       .csect  DATA($1[TC]),$3',
   `errprint(`illegal argument "$2"')')'
 )'
)

popdef(`_LOAD')
popdef(`_STORE')
popdef(`_STOREU')
popdef(`_LONG')
popdef(`_rs')

divert(0)dnl
