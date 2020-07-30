/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/systemcfg.h 1.38.5.10                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1992,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)29  1.38.5.10  src/bos/kernel/sys/systemcfg.h, sysml, bos53X, x2010_31B1 4/8/10 11:20:12 */

#ifndef _H_SYSTEMCFG
#define _H_SYSTEMCFG
/*
 * COMPONENT_NAME: (SYSML) Kernel Machine Language
 *
 * FUNCTIONS: System Characteristics Identification
 *
 * ORIGINS: 27, 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1992, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 *   LEVEL 1,  5 Years Bull Confidential Information
 */

/*
 * WARNINGS:
 *	The size of this structure will grow in future releases
 *
 *	Do not make this structure larger than 64 words
 *
 *	Do not update without changing systemcfg.m4 and ufcp.m4
 */
extern struct {
	int architecture;	/* processor architecture */
	int implementation;	/* processor implementation */
	int version;		/* processor version */
	int width;		/* width (32 || 64) */
	int ncpus;		/* 1 = UP, n = n-way MP */
	int cache_attrib;	/* L1 cache attributes (bit flags)	*/
				/* bit		0/1 meaning		*/
				/* -------------------------------------*/
				/* 31	 no cache / cache present	*/
				/* 30	 separate I and D / combined    */
	int icache_size;	/* size of L1 instruction cache */
	int dcache_size;	/* size of L1 data cache */
	int icache_asc;		/* L1 instruction cache associativity */
	int dcache_asc;		/* L1 data cache associativity */
	int icache_block;	/* L1 instruction cache block size */
	int dcache_block;	/* L1 data cache block size */
	int icache_line;	/* L1 instruction cache line size */
	int dcache_line;	/* L1 data cache line size */
	int L2_cache_size;	/* size of L2 cache, 0 = No L2 cache */
	int L2_cache_asc;	/* L2 cache associativity */
	int tlb_attrib;		/* TLB attributes (bit flags)		*/
				/* bit		0/1 meaning		*/
				/* -------------------------------------*/
				/* 31	 no TLB / TLB present		*/
				/* 30	 separate I and D / combined    */
	int itlb_size;		/* entries in instruction TLB */
	int dtlb_size;		/* entries in data TLB */
	int itlb_asc;		/* instruction tlb associativity */
	int dtlb_asc;		/* data tlb associativity */
	int resv_size;		/* size of reservation */
	int priv_lck_cnt;	/* spin lock count in supevisor mode */
	int prob_lck_cnt;	/* spin lock count in problem state */
	int rtc_type;		/* RTC type */
	int virt_alias;		/* 1 if hardware aliasing is supported */
	int cach_cong;		/* number of page bits for cache synonym */
	int model_arch;		/* used by system for model determination */
	int model_impl;		/* used by system for model determination */
	int Xint;		/* used by system for time base conversion */
	int Xfrac;		/* used by system for time base conversion */
	int kernel;		/* kernel attributes			    */
				/* bit		0/1 meaning		    */
				/* -----------------------------------------*/
				/* 31	32-bit kernel / 64-bit kernel	    */
				/* 30	non-LPAR      / LPAR                */
				/* 29	old 64bit ABI / 64bit Large ABI     */
				/* 28	non-NUMA      / NUMA                */
				/* 27	UP            / MP                  */
				/* 26	no DR CPU add / DR CPU add support  */
				/* 25	no DR CPU rm  / DR CPU rm  support  */
				/* 24	no DR MEM add / DR MEM add support  */
				/* 23	no DR MEM rm  / DR MEM rm  support  */
	long long physmem;	/* bytes of OS available memory		    */
	int slb_attr;		/* SLB attributes			    */
				/* bit		0/1 meaning		    */
				/* -----------------------------------------*/
				/* 31		Software Manged		    */
	int slb_size;		/* size of slb (0 = no slb)		    */
	int original_ncpus;	/* original number of CPUs		    */
	int max_ncpus;		/* max cpus supported by this AIX image     */
	long long maxrealaddr;	/* max supported real memory address +1     */
	long long original_entitled_capacity;
				/* configured entitled processor capacity   */
				/* at boot required by cross-partition LPAR */
				/* tools.				    */
	long long entitled_capacity; /* entitled processor capacity	    */
	long long dispatch_wheel; /* Dispatch wheel time period (TB units)  */
	int capacity_increment;	/* delta by which capacity can change	    */
	int variable_capacity_weight;	/* priority weight for idle capacity*/
					/* distribution			    */
	int splpar_status;	/* State of SPLPAR enablement		    */
				/*	0x1 => 1=SPLPAR capable; 0=not	    */
				/*	0x2 => SPLPAR enabled 0=dedicated;   */
				/*			     1=shared       */
	int smt_status;		/* State of SMT enablement                  */
				/*    0x1 = SMT Capable  0=no/1=yes         */
				/*    0x2 = SMT Enabled  0=no/1=yes         */
				/*    0x4 = SMT threads bound true 0=no/1=yes */
	int smt_threads;	/* Number of SMT Threads per Physical CPU   */
	int vmx_version;        /* RPA defined VMX version, 0=none/disabled */
	long long sys_lmbsize;	/* Size of an LMB on this system. */
	int num_xcpus;		/* Number of exclusive cpus on line */
	signed char errchecklevel;/* Kernel error checking level */
	char eco_status;	/* extended cache options */
	char pad[2];		/* pad to word boundary		*/
	int dfp_version;        /* RPA defined DFP version, 0=none/disabled */
				/* if MSbit is set, DFP is emulated         */
	short phys_implementation;	/* physical processor implementation */
	short phys_version;	/* physical processor version */
}_system_configuration;

/* function prototype for accessing system configuration fields */
#ifdef  __64BIT__
unsigned long getsystemcfg(int label);
#else
unsigned long long getsystemcfg(int label);
#endif

#ifdef _ALL_SOURCE
#define SC_ARCH 1
#define SC_IMPL 2
#define SC_VERS 3
#define SC_WIDTH 4
#define SC_NCPUS 5
#define SC_L1C_ATTR 6
#define SC_L1C_ISZ 7
#define SC_L1C_DSZ 8
#define SC_L1C_ICA 9
#define SC_L1C_DCA 10
#define SC_L1C_IBS 11
#define SC_L1C_DBS 12
#define SC_L1C_ILS 13
#define SC_L1C_DLS 14
#define SC_L2C_SZ 15
#define SC_L2C_AS 16
#define SC_TLB_ATTR 17
#define SC_ITLB_SZ 18
#define SC_DTLB_SZ 19
#define SC_ITLB_ATT 20
#define SC_DTLB_ATT 21
#define SC_RESRV_SZ 22
#define SC_PRI_LC 23
#define SC_PRO_LC 24
#define SC_RTC_TYPE 25
#define SC_VIRT_AL 26
#define SC_CAC_CONG 27
#define SC_MOD_ARCH 28
#define SC_MOD_IMPL 29
#define SC_XINT 30
#define SC_XFRAC 31
#define SC_KRN_ATTR 32
#define SC_PHYSMEM 33
#define SC_SLB_ATTR 34
#define SC_SLB_SZ 35
#define SC_ORIG_NCPUS 36
#define SC_MAX_NCPUS 37
#define SC_MAX_REALADDR 38
#define SC_ORIG_ENT_CAP 39
#define SC_ENT_CAP 40
#define SC_DISP_WHE 41
#define SC_CAPINC 42
#define SC_VCAPW 43
#define SC_SPLP_STAT 44
#define SC_SMT_STAT 45
#define SC_SMT_TC 46
#define SC_VMX_VER 47
#define SC_LMB_SZ 48
#define SC_MAX_XCPU 49
#define SC_EC_LVL 50
#define SC_ECO_STAT 52
#define SC_DFP_VER 53
#define SC_PHYS_IMP 55
#define SC_PHYS_VER 56
#endif /* _ALL_SOURCE */

/* Values for architecture field
 */
#define POWER_RS	0x0001		/* Power Classic architecture */
#define POWER_PC	0x0002		/* Power PC architecture */
#define IA64		0x0003		/* Intel IA64 architecture */


/* Values for implementation field for POWER_RS and POWER_PC Architectures
 */
#define POWER_RS1	0x0001		/* RS1 class CPU */
#define POWER_RSC	0x0002		/* RSC class CPU */
#define POWER_RS2	0x0004		/* RS2 class CPU */
#define POWER_601	0x0008		/* 601 class CPU */
#define POWER_603	0x0020		/* 603 class CPU */
#define POWER_604	0x0010		/* 604 class CPU */
#define POWER_620	0x0040		/* 620 class CPU */
#define POWER_630	0x0080		/* 630 class CPU */
#define POWER_A35	0x0100		/* A35 class CPU */
#define POWER_RS64II	0x0200		/* RS64-II class CPU */
#define POWER_RS64III	0x0400		/* RS64-III class CPU */
#define POWER_4		0x0800		/* 4 class CPU */
#define POWER_RS64IV	POWER_4		/* 4 class CPU */
#define POWER_MPC7450	0x1000		/* MPC7450 class CPU */
#define POWER_5		0x2000		/* 5 class CPU */
#define POWER_6		0x4000		/* 6 class CPU */

/* Convenient groupings of implementation fields
 */
#define POWER_6_ANDUP	(POWER_6)
#define POWER_5_ANDUP	(POWER_5|POWER_6_ANDUP)
#define POWER_4_ANDUP	(POWER_4|POWER_5_ANDUP)

/* Values for implementation field for IA64 Architectures
 */
#define IA64_M1		0x0001		/* IA64 M1 class CPU (Itanium) */
#define IA64_M2		0x0002		/* IA64 M2 class CPU */

#ifdef _KERNSYS
/* Sets of implementations
 */
#define POWER_RESERVED_2	0x0200		/* source compatability */
#define POWER_RESERVED_3	0x0400		/* source compatability */
#define POWER_RESERVED_4	0x0800		/* future CPU */

#define POWER_RS_ALL (POWER_RS1|POWER_RSC|POWER_RS2)
#define POWER_PC_ALL \
	(POWER_601|POWER_603|POWER_604|POWER_620|POWER_A35|POWER_630| \
	POWER_RS64II|POWER_RS64III|POWER_4|POWER_5|POWER_6|POWER_MPC7450)
#define POWER_PC_DBATS \
(POWER_603|POWER_604|POWER_620|POWER_A35|POWER_630|POWER_RS64II|POWER_RS64III|POWER_MPC7450)
/*
 * These 64-bit machines don't support the user-level SPRG3.
 */
#define NO_U_SPRG3    (POWER_620|POWER_A35|POWER_630|POWER_RS64II)
/*
 * These are CPUs that do not have software managed SLBs
 */
#define POWER_PC_STAB \
 (POWER_620|POWER_A35|POWER_630|POWER_RS64II|POWER_RS64III)

/*
 * These CPUs support ptrace DABR function
 */
#define PTRACE_DABR_SUPPORT (POWER_630|POWER_4|POWER_5|POWER_6)

#define IA64_ALL (IA64_M1 | IA64_M2)

/*
 * These PowerPC CPUs do not support the runlatch facility
 */
#define NO_RUNLATCH             \
        (POWER_601|POWER_603|POWER_604|POWER_620|POWER_630|POWER_MPC7450)

/*
 * Software control for store gathering based on the G bit
 */
#define PPC_STORE_GATHER_WIMG (POWER_5|POWER_6)

#endif /* _KERNSYS */

/* Values for the version field
 */
#define PV_601		0x010001	/* Power PC 601 */
#define PV_601a		0x010002	/* Power PC 601 */
#define PV_603		0x060000	/* Power PC 603 */
#define PV_604		0x050000	/* Power PC 604 */
#define PV_620		0x070000	/* Power PC 620 */
#define PV_630		0x080000	/* Power PC 630 */
#define PV_A35		0x090000	/* Power PC A35 */
#define PV_RS64II	0x0A0000	/* Power PC RS64II */
#define PV_RS64III	0x0B0000	/* Power PC RS64III */
#define PV_4		0x0C0000	/* Power PC 4 */
#define PV_RS64IV	PV_4		/* Power PC 4 */
#define PV_MPC7450	0x0D0000	/* Power PC MPC7450 */
#define PV_4_2		0x0E0000	/* Power PC 4 */
#define PV_4_3          0x0E0001        /* Power PC 4 */
#define PV_5		0x0F0000	/* Power PC 5 */
#define PV_5_2		0x0F0001	/* Power PC 5 */
#define PV_5_3		0x0F0002	/* Power PC 5 */
#define PV_6		0x100000	/* Power PC 6 */
#define PV_6_1		0x100001	/* Power PC 6 DD1.x */
/*
 * The following Compat definitions indicate that the processor is running in
 * a mode that is compatible with the processor family as indicated by the
 * implementation field of the _system_configuration structure.  When running
 * in a compatible mode, BookIV processor features of that processor family
 * can not be assumed to be present or functional.
 */
#define PV_5_Compat	0x0F8000	/* Power PC 5 */
#define PV_6_Compat	0x108000	/* Power PC 6 */
#define PV_RESERVED_2	0x0A0000	/* source compatability */
#define PV_RESERVED_3	0x0B0000	/* source compatability */
#define PV_RS2		0x040000	/* Power RS2 */
#define PV_RS1		0x020000	/* Power RS1 */
#define PV_RSC		0x030000	/* Power RSC */
#define PV_M1		0x008000	/* Intel IA64 M1  */
#define PV_M2		0x008001	/* Intel IA64 M2  */

/*
 * Values for Itanium Stepping Levels
 */
#define ITANIUM_STEP_A	0
#define ITANIUM_STEP_B0	1
#define ITANIUM_STEP_B1	2
#define ITANIUM_STEP_B2	3


/* Values for rtc_type
 */
#define RTC_POWER 1			/* rtc as defined by Power Arch. */
#define RTC_POWER_PC 2			/* rtc as defined by Power PC Arch. */
#define RTC_IA64 3			/* rtc as defined by IA64 Arch. */


/* macros for runtime architecture and implementation checks
 */
/* XXX - for now it is max_ncpus. Later it will be changed to smp_enabled */
#define __mp() (_system_configuration.max_ncpus > 1)
#define __cpu64() (_system_configuration.width == 64)

#define __power_rs() (_system_configuration.architecture == POWER_RS)
#define __power_pc() (_system_configuration.architecture == POWER_PC)
#define __power_set(a) (_system_configuration.implementation & (a))
#define __power_mp() __mp()
#define __power_64() __cpu64()

#define __power_rs1() (_system_configuration.implementation == POWER_RS1)
#define __power_rsc() (_system_configuration.implementation == POWER_RSC)
#define __power_rs2() (_system_configuration.implementation == POWER_RS2)
#define __power_601() (_system_configuration.implementation == POWER_601)
#define __power_603() (_system_configuration.implementation == POWER_603)
#define __power_604() (_system_configuration.implementation == POWER_604)
#define __power_620() (_system_configuration.implementation == POWER_620)
#define __power_630() (_system_configuration.implementation == POWER_630)
#define __power_A35() (_system_configuration.implementation == POWER_A35)
#define __power_RS64II() (_system_configuration.implementation == POWER_RS64II)
#define __power_RS64III() (_system_configuration.implementation == POWER_RS64III)
#define __power_4() (_system_configuration.implementation == POWER_4)
#define __power_RS64IV() (_system_configuration.implementation == POWER_4)
#define __power_mpc7450() (_system_configuration.implementation == POWER_MPC7450)
#define __power_5() (_system_configuration.implementation == POWER_5)
#define __power_6() (_system_configuration.implementation == POWER_6)

#define __power_vmx() (_system_configuration.vmx_version > 0)
#define __power_dfp() (_system_configuration.dfp_version != 0)
#define __power_dfp_native() (_system_configuration.dfp_version > 0)
#define __power_dfp_emul() (_system_configuration.dfp_version < 0)

#define __isia64() (_system_configuration.architecture == IA64)
#define __ia64_set(a) (_system_configuration.implementation & (a))

/* Macros for version checks
 */
#define __power_version_601()           (_system_configuration.version == PV_601)
#define __power_version_601a()          (_system_configuration.version == PV_601a)
#define __power_version_603()           (_system_configuration.version == PV_603)
#define __power_version_604()           (_system_configuration.version == PV_604)
#define __power_version_620()           (_system_configuration.version == PV_620)
#define __power_version_630()           (_system_configuration.version == PV_630)
#define __power_version_A35()           (_system_configuration.version == PV_A35)
#define __power_version_RS64II()        (_system_configuration.version == PV_RS64II)
#define __power_version_RS64III()       (_system_configuration.version == PV_RS64III)
#define __power_version_4()             (_system_configuration.version == PV_4)
#define __power_version_RS64IV()        (_system_configuration.version == PV_RS64IV)
#define __power_version_MPC7450()       (_system_configuration.version == PV_MPC7450)
#define __power_version_4_2()           (_system_configuration.version == PV_4_2)
#define __power_version_4_3()           (_system_configuration.version == PV_4_3)
#define __power_version_5()             (_system_configuration.version == PV_5)
#define __power_version_5_2()           (_system_configuration.version == PV_5_2)
#define __power_version_5_3()           (_system_configuration.version == PV_5_3)
#define __power_version_6()             (_system_configuration.version == PV_6)
#define __power_version_6_1()           (_system_configuration.version == PV_6_1)
#define __power_version_5_Compat()      (_system_configuration.version == PV_5_Compat)
#define __power_version_6_Compat()      (_system_configuration.version == PV_6_Compat)
#define __power_version_RESERVED_2()    (_system_configuration.version == PV_RESERVED_2)
#define __power_version_RESERVED_3()    (_system_configuration.version == PV_RESERVED_3)
#define __power_version_RS2()           (_system_configuration.version == PV_RS2)
#define __power_version_RS1()           (_system_configuration.version == PV_RS1)
#define __power_version_RSC()           (_system_configuration.version == PV_RSC)
#define __power_version_M1()            (_system_configuration.version == PV_M1)
#define __power_version_M2()            (_system_configuration.version == PV_M2)

/* Macros for identifying physical processor
 */

#define PPI4_1	0x35
#define PPI4_2	0x38
#define PPI4_3	0x39
#define PPI4_4	0x3C
#define PPI4_5	0x44
#define PPI5_1	0x3A
#define PPI5_2	0x3B
#define PPI6_1	0x3E
#define PPI7_1	0x3F
#define __phy_proc_imp_4() \
	(_system_configuration.phys_implementation == PPI4_1 || \
	_system_configuration.phys_implementation == PPI4_2 || \
	_system_configuration.phys_implementation == PPI4_3 || \
	_system_configuration.phys_implementation == PPI4_4 || \
	_system_configuration.phys_implementation == PPI4_5)
#define __phy_proc_imp_5() \
	(_system_configuration.phys_implementation == PPI5_1 || \
	_system_configuration.phys_implementation == PPI5_2)
#define __phy_proc_imp_6() (_system_configuration.phys_implementation == PPI6_1)
#define __phy_proc_imp_7() (_system_configuration.phys_implementation == PPI7_1)

/* Macros to determine if running on a 32-bit or 64-bit kernel.
 */

#define __KRN_TYPE_MASK 0x1
#define __LPAR_MASK 0x2
#define __NUMA_MASK 0x8
#define __KRN_UPMP_MASK 0x10
#define __DR_CPU_ADD_MASK	0x20
#define __DR_CPU_RM_MASK	0x40
#define __DR_MEM_ADD_MASK	0x80
#define __DR_MEM_RM_MASK	0x100
#define __DR_MASKS	(__DR_CPU_ADD_MASK | __DR_CPU_RM_MASK |	\
			 __DR_MEM_ADD_MASK | __DR_MEM_RM_MASK)
#define __KERNEL_32() ((_system_configuration.kernel & __KRN_TYPE_MASK) == 0x0)
#define __KERNEL_64() ((_system_configuration.kernel & __KRN_TYPE_MASK) == 0x1)
#define __LPAR() (_system_configuration.kernel & __LPAR_MASK)
#define __DR_CPU_ADD()	(_system_configuration.kernel & __DR_CPU_ADD_MASK)
#define __DR_CPU_RM()	(_system_configuration.kernel & __DR_CPU_RM_MASK)
#define __DR_MEM_ADD()	(_system_configuration.kernel & __DR_MEM_ADD_MASK)
#define __DR_MEM_RM()	(_system_configuration.kernel & __DR_MEM_RM_MASK)
#define __DR_CAPABLE()	(_system_configuration.kernel & __DR_MASKS)
#define __NUMA() (_system_configuration.kernel & __NUMA_MASK)
#define __KERNEL_UP() ((_system_configuration.kernel & __KRN_UPMP_MASK) == 0x0)
#define __KERNEL_MP() (_system_configuration.kernel & __KRN_UPMP_MASK)

/*
 * macros for SPLPAR environment.
 */
#define __SPLPAR_CAPABLE_MASK	      0x1
#define __SPLPAR_ENABLE_MASK	      0x2
#define __SPLPAR_DONATE_CAPABLE_MASK  0x4

#define __SPLPAR()	(_system_configuration.splpar_status &		\
						__SPLPAR_CAPABLE_MASK)
#define __SPLPAR_ENABLED() (_system_configuration.splpar_status &	\
						__SPLPAR_ENABLE_MASK)
#define __DEDICATED()	(!(__SPLPAR_ENABLED()))
#define __SOFT_CAPPED()	(_system_configuration.variable_capacity_weight == 0)
#define __SPLPAR_DONATE() (_system_configuration.splpar_status &            \
                                                __SPLPAR_DONATE_CAPABLE_MASK)

/* Macro to determine if 64-bit ABI is supported.
 */
#define __64BIT_LARGE_ABI_MASK 0x4
#define __64BIT_LARGE_ABI() \
	(_system_configuration.kernel & __64BIT_LARGE_ABI_MASK)

/* Macros for SMT status determination
 */
#define __SMT_CAPABLE_MASK      0x1
#define __SMT_ENABLE_MASK       0x2
#define __SMT_BOUND_MASK	0x4
#define __SMT_ORDER_MASK	0x8
#define __SMT_CAPABLE()  (_system_configuration.smt_status & __SMT_CAPABLE_MASK)
#define __SMT_ENABLED()  (_system_configuration.smt_status & __SMT_ENABLE_MASK)
#define __SMT_BOUND()    (_system_configuration.smt_status & __SMT_BOUND_MASK )
#define __SMT_ORDER()    (_system_configuration.smt_status & __SMT_ORDER_MASK )

/* Macros for extended cache options
 */
#define __ECO_CAPABLE_MASK	0x1
#define __ECO_ENABLE_MASK	0x2
#define __ECO_CAPABLE() (_system_configuration.eco_status & __ECO_CAPABLE_MASK)
#define __ECO_ENABLED() (_system_configuration.eco_status & __ECO_ENABLE_MASK)

#ifdef _KERNSYS
#define __power_sslb() (_system_configuration.slb_attr & 1)

/* Values for spec_hw_present
 */
#define GR20_PRESENT	0x00000001	/* At least one GR processor at   */
					/* DD2.0 level is present on the  */
					/* platform.                      */
#define P6_DD1_PRESENT	0x00000010	/* At least one P6 processor at    */
					/* DD1.x level running in SMT mode */
extern int spec_hw_present;
#define __has_gr20() ((spec_hw_present & GR20_PRESENT) != 0)
#define __has_p6_dd1() ((spec_hw_present & P6_DD1_PRESENT) != 0)

/*
 * These define blocks of values for model_arch and model_impl that
 * are reserved for OEM use.
 */
#define MODEL_ARCH_OEM_START	1024
#define MODEL_ARCH_OEM_END	2047

#define MODEL_IMPL_OEM_START	1024
#define MODEL_IMPL_OEM_END	2047
#endif /* _KERNSYS */

#if defined(_KERNSYS) || defined(_KERNEL)

/* Defines and macros for model specific checks.  These are intended for
 * internal use only.  There is no guarantee made how these function on
 * new models
 */

/*
 * The following are the various System Architectures
 */
#ifdef _RS6K
#define RS6K		1
#define __rs6k() (_system_configuration.model_arch == RS6K)
#else
#define __rs6k() 0
#endif

#ifdef _RSPC
#define RSPC		2
#define __rspc() (_system_configuration.model_arch == RSPC)
#else
#define __rspc() 0
#endif

#ifdef _CHRP
#define CHRP		3
#define __chrp() (_system_configuration.model_arch == CHRP)
#else
#define __chrp() 0
#endif

#ifdef _IA64_SYS
#define IA64_SYS	4
#define __ia64_sys() (_system_configuration.model_arch == IA64_SYS)
#else
#define __ia64_sys() 0
#endif


/**
 ** The following are Implementations of RS6K Architecture Systems
 **/

#ifdef _RS6K_UP_MCA
#define RS6K_UP_MCA	1
#define __rs6k_up_mca() (_system_configuration.model_impl == RS6K_UP_MCA)
#else
#define __rs6k_up_mca() 0
#endif

#ifdef _RS6K_SMP_MCA
#define RS6K_SMP_MCA	2
#define __rs6k_smp_mca() (_system_configuration.model_impl == RS6K_SMP_MCA)
#else
#define __rs6k_smp_mca() 0
#endif


/**
 ** The following are Implementations of RSPC Architecture Systems
 **/

#ifdef _RSPC_UP_PCI
#define RSPC_UP_PCI	3
#define __rspc_up_pci() (_system_configuration.model_impl == RSPC_UP_PCI)
#else
#define __rspc_up_pci() 0
#endif

#ifdef _RSPC_SMP_PCI
#define RSPC_SMP_PCI	4
#define __rspc_smp_pci() (_system_configuration.model_impl == RSPC_SMP_PCI)
#else
#define __rspc_smp_pci() 0
#endif


/**
 ** The following are Implementations of CHRP Architecture Systems
 **/

#ifdef _CHRP_UP_PCI
#define CHRP_UP_PCI	5
#define __chrp_up_pci() (_system_configuration.model_impl == CHRP_UP_PCI)
#else
#define __chrp_up_pci() 0
#endif

#ifdef _CHRP_SMP_PCI
#define CHRP_SMP_PCI	6
#define __chrp_smp_pci() (_system_configuration.model_impl == CHRP_SMP_PCI)
#else
#define __chrp_smp_pci() 0
#endif


/**
 ** The following are Implementations of IA64 Architecture Systems
 **/

#ifdef _IA64_SYS
#define IA64_COM	 7
#define __ia64_com()	(_system_configuration.model_impl == IA64_COM)
#else
#define __ia64_com()	0
#endif

#ifdef _IA64_SYS
#define IA64_SOFTSDV     8
#define __ia64_softsdv() (_system_configuration.model_impl == IA64_SOFTSDV)
#else
#define __ia64_softsdv() 0
#endif



#define __pal() (!__power_rs() && !__rs6k())
#define __DBATS() (__power_set(POWER_PC_DBATS) && !__LPAR())
#endif /* _KERNSYS  || _KERNEL */

#endif /* _H_SYSTEMCFG */
