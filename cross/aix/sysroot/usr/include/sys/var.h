/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/var.h 1.14.4.1                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)25       1.14.4.1  src/bos/kernel/sys/var.h, sysios, bos53L, l2007_04A4 12/11/06 07:14:58 */
/*
 * COMPONENT_NAME: (SYSIOS) IO subsystems
 *
 * FUNCTIONS: var.h 
 *
 * ORIGINS: 3, 27, 83
 *
 *                  -- (                            when
 * combined with the aggregated modules for this product)
 * OBJECT CODE ONLY SOURCE MATERIALS
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1994
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 * 
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_VAR
#define _H_VAR

#include <sys/types.h>

/*
 * Header structure for var structure.
 */
struct var_hdr
{
        __ulong32_t var_vers;   /* version number of var structure      */
        __ulong32_t var_gen;    /* generation number of var structure   */
        __ulong32_t var_size;   /* size of the of the var structure     */
                                /* returned by the sysconfig syscall    */
};

/*
 * Structure for base kernel parameters, on the 32-bit kernel
 * RW in comment indicates a Read-Write variable alterable by sysconfig
 * RO in comment indicates a Read-Only variable not alterable by sysconfig
 */
struct var {
	struct var_hdr	var_hdr;	/* cfgvar header information	    */

	int		v_bufhw;	/* RW: buffer pool high-water mark  */
	int     	v_mbufhw;	/* RW: max. mbufs high water mark   */
	int		v_maxup;	/* RW: max. # of user processes     */
	int		v_iostrun;	/* RW: enable disk i/o history      */
	int		v_leastpriv;	/* RW: least privilege enablement   */
	int		v_autost;	/* RW: automatic boot after halt    */
	int		v_maxpout;	/* RW: # of file pageouts at which  */
					/*     waiting occurs		    */
	int		v_minpout;	/* RW: # of file pageout at which   */
					/*     ready occurs		    */
	int		v_memscrub;	/* RW: memory scrubbing enabled	    */

	int		v_lock;		/* RO: # entries in record lock table*/
	__cptr32 	ve_lock;	/* RO: ptr to end of recordlock table*/
	int		v_file;		/* RO: # entries in open file table  */
	__cptr32 	ve_file;	/* RO: ptr to end of open file table */
	int		v_proc;		/* RO: max # of system processes     */
	__cptr32 	ve_proc; 	/* RO: process table high water mark */
	int		v_clist;	/* RO: # of cblocks in cblock array  */
	int		v_thread;	/* RO: max # of system threads	     */
	__cptr32	ve_thread;	/* RO: thread table high water mark  */
	__cptr32	vb_proc;	/* RO: beginning of process table    */
	__cptr32	vb_thread;	/* RO: beginning of thread table     */
	int		v_ncpus;	/* RO: number of active CPUs	     */
	int		v_ncpus_cfg;	/* RO: number of processor configured*/
	int		v_fullcore;	/* RW: full core enabled (true/false)*/
	char		v_initlvl[4];	/* RW: init level		     */
	char		v_pre430core;	/* RW: Use pre-430 core (true/false) */
	int		v_xmgc;		/* RW: xmalloc garbage collect delay */
	int             v_cpuguard;	/* RW: CPU Guarding Mode (true/false)*/
	int		v_ncargs;	/* RW: length of args,env for exec() */
	int             v_pre520tune;	/* RW: Use pre-520 Tuning Mode (t/f) */
	long long       v_hardstack;	/* RW: Hard stack max for 64-bit app */
	int		v_xmdbg_segs;	/* RW: Number of XMDBG segments      */
	int		v_max_logname;	/* RW: Maximum login name length     */
	int		v_num_xmfrecs;	/* RW: Number of XM free records     */
	long long       v_sed_config;	/* RW: SED config	*/
	long long	v_acl_config;	/* RW: ACL config                    */
};

/*
 * Structure for base kernel parameters, for the 64-bit kernel
 * RW in comment indicates a Read-Write variable alterable by sysconfig
 * RO in comment indicates a Read-Only variable not alterable by sysconfig
 */
struct kernvars {
	struct var_hdr	var_hdr;	/* cfgvar header information	    */

	long long	v_bufhw;	/* RW: buffer pool high-water mark  */
	long long     	v_mbufhw;	/* RW: max. mbufs high water mark   */
	long long	v_maxup;	/* RW: max. # of user processes     */
	long long	v_maxpout;	/* RW: # of file pageouts at which  */
					/*     waiting occurs		    */
	long long	v_minpout;	/* RW: # of file pageout at which   */
					/*     ready occurs		    */
	int		v_iostrun;	/* RW: enable disk i/o history      */
	int		v_leastpriv;	/* RW: least privilege enablement   */
	int		v_autost;	/* RW: automatic boot after halt    */
	int		v_memscrub;	/* RW: memory scrubbing enabled	    */

	long long	v_lock;		/* RO: # entries in record lock table*/
	__cptr64 	ve_lock;	/* RO: ptr to end of recordlock table*/
	long long	v_file;		/* RO: # entries in open file table  */
	__cptr64 	ve_file;	/* RO: ptr to end of open file table */
	long long	v_proc;		/* RO: max # of system processes     */
	__cptr64 	ve_proc; 	/* RO: process table high water mark */
	long long	v_clist;	/* RO: # of cblocks in cblock array  */
	long long	v_thread;	/* RO: max # of system threads	     */
	__cptr64	ve_thread;	/* RO: thread table high water mark  */
	__cptr64	vb_proc;	/* RO: beginning of process table    */
	__cptr64	vb_thread;	/* RO: beginning of thread table     */
	int		v_ncpus;	/* RO: number of active CPUs	     */
	int		v_ncpus_cfg;	/* RO: number of processor configured*/
	int		v_fullcore;	/* RW: full core enabled (true/false)*/
	char		v_initlvl[4];	/* RW: init level		     */
	int		v_coreformat;	/* RW: Core File Format: 	     */
	int		v_xmgc;		/* RW: xmalloc garbage collect delay */
	int             v_cpuguard;     /* RW: CPU Guarding Mode (true/false)*/
	int		v_ncargs;	/* RW: length of args,env for exec() */
	int             v_pre520tune;	/* RW: Use pre-520 Tuning Mode (t/f) */
	long long       v_hardstack;	/* RW: Hard stack max for 64-bit app */
	int		v_xmdbg_segs;	/* RW: Number of XMDBG segments      */
	int		v_max_logname;	/* RW: Maximum login name length     */
	int		v_num_xmfrecs;	/* RW: Number of XM free records     */
	long long       v_sed_config;	/* RW: SED config */
	long long	v_acl_config;	/* RW: ACL config                    */
};

#define	SYSCONFIG_VARSIZE  ((int)&((struct var *)0)->v_lock)  
#define MIN_XMFRECS	   4096	/* minimum limit of xmfree rec's */

#ifdef _KERNEL
#ifdef __64BIT_KERNEL
extern struct kernvars v;
#else
extern struct var v;
#endif /* __64BIT_KERNEL */
#endif /* _KERNEL */

/* 
   This structure may be used by the caller of the sys_parm
   system call.  It indicates the shape of the returned 
   data when sys_parm is used to get data from the kernel
   sys_parm always returns data that has a size of long long.
 */

struct vario 
{
    union v
    {
	struct { 
	  long long value;
	} v_bufhw;
	struct { 
	  long long value;
	} v_mbufhw;
	struct { 
	  long long value;
	} v_maxup;
	struct { 
	  long long value;
	} v_maxpout;
	struct { 
	  long long value;
	} v_minpout;
	struct {
	  int	fill;
	  int	value;
	} v_iostrun;
	struct {
	  int	fill;
	  int	value;
	} v_leastpriv;
	struct {
	  int	fill;
	  int	value;
	} v_autost;
	struct {
	  int	fill;
	  int	value;
	} v_memscrub;
	struct {
	  long long value;
	} v_lock;		
	struct {
	  __cptr64 value;
	} ve_lock;
	struct {
	  long long value;
	} v_file;
	struct {
	  __cptr64 value;
	} ve_file;
	struct {
	  long long value;
	} v_proc;
	struct {
	  __cptr64 value; 	
	} ve_proc;
	struct {
	  long long value;
	} v_clist;
	struct {
	  long long value;
	} v_thread;	
	struct {
	  __cptr64 value; 	
	} ve_thread;
	struct {
	  __cptr64 value; 	
	} vb_proc;
	struct {
	  __cptr64 value; 	
	} vb_thread;	
	struct {
	  int	fill;
	  int	value;
	} v_ncpus;
	struct {
	  int	fill;
	  int	value;
	} v_ncpus_cfg;	
	struct {
	  int	fill;
	  int	value;
	} v_fullcore;
	struct {
	  int	fill;
	  char	value[4];
	} v_initlvl;
	struct {
	  int	fill;
#ifdef __64BIT_KERNEL
	  int	value;
#else
	  char  fill2[3];
	  char  value;
#endif
	} v_coreformat;
	struct {
	  int	fill;
	  int	value;
	} v_xmgc;
	struct {
	  int	fill;
	  int	value;
	} v_cpuguard;
	struct {
	  int	fill;
	  int	value;
	} v_ncargs;
	struct {
	  int	fill;
	  int	value;
	} v_pre520tune;
	struct { 
	  int	fill;
	  int	value; /* always specified in number of segments */
	} v_hardstack;
	struct { 
	  int	fill;
	  int	value;
	} v_xmdbg_segs;
	struct {
  	  int	fill;
  	  int	value;
	} v_max_logname;
	struct {
	  int fill;
	  int value;
	} v_num_xmfrecs;
	struct { 
	  long long value;
	} v_sed_config;
	struct {
	  long long value;
	} v_acl_config;
	struct {
	  int fill;
	  int value;
	} turbo_acct;
    } v;
};

/* prototype for sys_parm system call */
int sys_parm(int cmd,int parmflag,void *uptr);
/* cmd: Get or Set the parameter */
/* parmflag: which parameter to act on */
/* uptr: pointer to user space to get/put the parameter */

/* commands */
#define SYSP_GET 0
#define SYSP_SET 1

/* 
 * RW variables in var/kernvars structures.
 * Note: Add new #defines to the end to preserve binary compat.
 */
#define SYSP_V_BUFHW            0
#define SYSP_V_MBUFHW           1
#define SYSP_V_MAXUP            2
#define SYSP_V_IOSTRUN          3
#define SYSP_V_LEASTPRIV        4
#define SYSP_V_AUTOST           5
#define SYSP_V_MAXPOUT          6
#define SYSP_V_MINPOUT          7
#define SYSP_V_MEMSCRUB         8
#define SYSP_V_FULLCORE         9
#define SYSP_V_INITLVL          10
#define SYSP_V_PRE430CORE	11
#define SYSP_V_COREFORMAT	11
#define SYSP_V_XMGC		12
#define SYSP_V_CPUGUARD		13
#define SYSP_V_NCARGS         	14
#define SYSP_V_PRE520TUNE	15
#define SYSP_V_HARDSTACK	16
#define SYSP_V_XMDBG_SEGS	17
#define SYSP_V_MAX_LOGNAME	18
#define SYSP_V_NUM_XMFRECS	19
#define SYSP_V_SED_CONFIG	20
#define SYSP_V_ACL_CONFIG       21
#define SYSP_V_TURBO_ACCT	22
#define SYSP_MAX_RW		SYSP_V_TURBO_ACCT

/* 
 * RO variables in var/kernvars structures 
 * Note: Add new #defines to the end to preserve binary compat.
 */
#define SYSP_V_LOCK             1024
#define SYSP_VE_LOCK            1025
#define SYSP_V_FILE             1026
#define SYSP_VE_FILE            1027
#define SYSP_V_PROC             1028
#define SYSP_VE_PROC            1029
#define SYSP_V_CLIST            1030
#define SYSP_V_THREAD           1031
#define SYSP_VE_THREAD          1032
#define SYSP_VB_PROC            1033
#define SYSP_VB_THREAD          1034
#define SYSP_V_NCPUS            1035
#define SYSP_V_NCPUS_CFG        1036

/* core types for v_coreformat */
#define	VAR_CORE43	0	/* 0 => use new core format */
#define	VAR_COREPRE43	1	/* 1 => use old core format */

#endif	/* _H_VAR */

