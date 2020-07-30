/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/sys/vminfo.h 1.19.3.3                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1991              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)19	1.19.3.3  src/bos/kernel/sys/vminfo.h, sysvmm, bos53S, s2008_35D4 8/25/08 11:38:30 */

#ifndef _H_VMINFO
#define _H_VMINFO

/*
 * COMPONENT_NAME: (SYSVMM) Virtual Memory Manager
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27, 83
 *
 */
#include <sys/types.h>

/* Information shown by vmstat command.
 */
struct vminfo {
	uint	pgexct; 	/* count of page faults     		*/
	uint	pgrclm; 	/* count of page reclaims 		*/
	uint	lockexct;	/* count of lockmisses	    		*/
	uint	backtrks;    	/* count of backtracks	    		*/
	uint	pageins;	/* count of pages paged in  		*/
	uint	pageouts;	/* count of pages paged out 		*/
	uint	pgspgins;	/* count of page ins from paging space	*/
	uint	pgspgouts;	/* count of page outs from paging space */
	uint	numsios;	/* count of start I/Os	    		*/
	uint	numiodone;	/* count of iodones	    		*/
	uint	zerofills;      /* count of zero filled pages 		*/
	uint	exfills;        /* count of exec filled pages		*/
	uint	scans;      	/* count of page scans by clock 	*/
	uint	cycles;      	/* count of clock hand cycles		*/
	uint	pgsteals;      	/* count of page steals	   		*/
	uint	freewts;      	/* count of free frame waits		*/
	uint	extendwts;      /* count of extend XPT waits		*/
	uint	pendiowts;      /* count of pending I/O waits  		*/
	uint	pings;		/* count of ping-pongs: source => alias */
	uint	pongs;		/* count of ping-pongs: alias => source */
	uint	pangs;		/* count of ping-pongs: alias => alias  */
	uint	dpongs;		/* count of ping-pongs: alias page delete */
	uint	wpongs;		/* count of ping-pongs: alias page writes */
	uint	cachef;		/* count of ping-pong cache flushes	*/
	uint	cachei;		/* count of ping-pong cache invalidates	*/

        /*
         * the next fields need to be computed by vmgetinfo
         * system call, else their value will be inaccurate.
         */
        rpn64_t numfrb;         /* number of pages on free list */
        rpn64_t numclient;      /* number of client frames */
        rpn64_t numcompress;    /* no of frames in compressed segments */
        rpn64_t numperm;        /* number frames non-working segments */
        rpn64_t maxperm;        /* max number of frames non-working */
	rpn64_t memsizepgs;     /* real memory size in 4K pages  */
	rpn64_t numvpages;      /* accessed virtual pages */	
        rpn64_t minperm;        /* no fileonly page steals */
        rpn64_t minfree;        /* minimun pages free list (fblru) */
        rpn64_t maxfree;        /* maxfree pages free list (fblru) */
	rpn64_t maxclient;      /* max number of client frames */
#ifndef RPTYPES
#define RPTYPES         2
#endif
	rpn64_t rpgcnt[RPTYPES];/* repaging cnt */
	rpn64_t numpout;	/* number of fblru page-outs        */
	rpn64_t numremote;	/* number of fblru remote page-outs */
	rpn64_t numwseguse;	/* count of pages in use for working seg */
	rpn64_t numpseguse;	/* count of pages in use for persistent seg */
	rpn64_t numclseguse;	/* count of pages in use for client seg */
	rpn64_t numwsegpin;	/* count of pages pinned for working seg */
	rpn64_t numpsegpin;	/* count of pages pinned for persistent seg */
	rpn64_t numclsegpin;	/* count of pages pinned for client seg */
	uint    lgpg_size;	/* Hardware large page size */
	rpn64_t lgpg_cnt;	/* Total number of large pages on the system */
	rpn64_t lgpg_numfrb;	/* Number of large pages on the freelist(s) */
	rpn64_t lgpg_inuse;	/* Number of large pages in use */
	rpn64_t lgpg_hi;	/* Large page high water count */
	rpn64_t numralloc;	/* number of remote allocations */
	cnt64_t numspecsegs;	/* number of special dataseg id's */
	cnt64_t numspecfree;	/* number of free special dataseg id's */
	cnt64_t specsegshi;	/* special dataseg id's high water count */
	
	/* Current number of free paging space blocks, and the thresholds
	 * when SIGDANGER and SIGKILL signals will be sent to processes.
	 */
	rpn64_t psfreeblks;	/* number of free paging space blocks */
	rpn64_t npswarn;	/* threshold when SIGDANGER is sent */
	rpn64_t npskill;	/* threshold when SIGKILL is sent */
	rpn64_t normlmbmem;	/* #nonremoveable pages for DR. */ 
	rpn64_t	pfrsvdblks;	/* number of system reserved blocks */
	rpn64_t	pfavail;	/* number of pages available for pinning */
	rpn64_t	pfpinavail;	/* app-level num pages avail for pinning */
	rpn64_t nreplaced[RPTYPES]; /* number of pages replaced         */
	rpn64_t nrepaged[RPTYPES];  /* number of pages repaged          */
	rpn64_t minpgahead;	/* min number of pageahead pages        */
	rpn64_t maxpgahead;	/* max number of pageahead pages        */
	rpn64_t numpermio;	/* number of fblru non-w.s. pageouts    */
	cnt64_t hisid;		/* max index + 1 of sids ever used      */
	cnt64_t hiesid;		/* max index + 1 of esids ever used,
				 * always set to -1 on 64 bit kernel 	*/
	rpn64_t system_pgs;	/* pages on SCBs marked V_SYSTEM	*/
	rpn64_t nonsys_pgs;	/* pages on SCBs not marked V_SYSTEM	*/
	rpn64_t unmngd_pgs;	/* pages not on SCBs			*/

	uint	memgrd_succ_pgs;/* pages memguard successfully removed	*/
	uint	memgrd_fail_pgs;/* pages memguard failed to remove	*/

	rpn64_t	___unused53[4];	/* keep offsets the same on 53 as 61	*/

	size64_t memavailable;  /* # bytes mem avail w/o paging working */
};

extern struct vminfo vmminfo;

#define vmpf_pgexct		vmminfo.pgexct
#define vmpf_pgrclm		vmminfo.pgrclm
#define vmpf_lockexct		vmminfo.lockexct
#define vmpf_backtrks		vmminfo.backtrks
#define vmpf_pageins		vmminfo.pageins
#define vmpf_pageouts		vmminfo.pageouts
#define vmpf_pgspgins		vmminfo.pgspgins
#define vmpf_pgspgouts		vmminfo.pgspgouts
#define vmpf_numsios		vmminfo.numsios
#define vmpf_numiodone		vmminfo.numiodone
#define vmpf_zerofills		vmminfo.zerofills
#define vmpf_exfills		vmminfo.exfills
#define vmpf_scans		vmminfo.scans
#define vmpf_cycles		vmminfo.cycles
#define vmpf_pgsteals		vmminfo.pgsteals
#define vmpf_freewts		vmminfo.freewts
#define vmpf_extendwts		vmminfo.extendwts
#define vmpf_pendiowts		vmminfo.pendiowts
#define vmpf_pings		vmminfo.pings
#define vmpf_pangs		vmminfo.pangs
#define vmpf_pongs		vmminfo.pongs
#define vmpf_dpongs		vmminfo.dpongs
#define vmpf_wpongs		vmminfo.wpongs
#define vmpf_cachef		vmminfo.cachef
#define vmpf_cachei		vmminfo.cachei
#define vmpf_numfrb		vmminfo.numfrb
#define vmpf_numclient		vmminfo.numclient
#define vmpf_numcompress	vmminfo.numcompress
#define vmpf_numperm		vmminfo.numperm
#define vmpf_maxperm		vmminfo.maxperm
#define vmpf_memsizepgs		vmminfo.memsizepgs
#define vmpf_minperm		vmminfo.minperm
#define vmpf_minfree		vmminfo.minfree
#define vmpf_maxfree		vmminfo.maxfree
#define vmpf_maxclient		vmminfo.maxclient
#define vmpf_rpgcnt		vmminfo.rpgcnt
#define vmpf_numpout		vmminfo.numpout
#define vmpf_numremote		vmminfo.numremote
#define vmpf_numwseguse		vmminfo.numwseguse
#define vmpf_numpseguse		vmminfo.numpseguse
#define vmpf_numclseguse	vmminfo.numclseguse
#define vmpf_numwsegpin		vmminfo.numwsegpin
#define vmpf_numpsegpin		vmminfo.numpsegpin
#define vmpf_numclsegpin	vmminfo.numclsegpin
#define vmpf_numvpages		vmminfo.numvpages
#define vmpf_psfreeblks		vmminfo.psfreeblks
#define vmpf_npswarn		vmminfo.npswarn
#define vmpf_npskill		vmminfo.npskill
#define vmpf_normlmbmem		vmminfo.normlmbmem
#define vmpf_pfrsvdblks		vmminfo.pfrsvdblks
#define vmpf_pfavail		vmminfo.pfavail
#define vmpf_pfpinavail		vmminfo.pfpinavail
#define vmpf_lgpg_cnt		vmminfo.lgpg_cnt
#define vmpf_lgpg_size		vmminfo.lgpg_size
#define vmpf_lgpg_numfrb	vmminfo.lgpg_numfrb
#define vmpf_lgpg_inuse		vmminfo.lgpg_inuse
#define vmpf_lgpg_hi		vmminfo.lgpg_hi
#define vmpf_numspecsegs	vmminfo.numspecsegs
#define vmpf_numspecfree	vmminfo.numspecfree
#define vmpf_specsegshi		vmminfo.specsegshi
#define vmpf_numralloc		vmminfo.numralloc
#define vmpf_nreplaced		vmminfo.nreplaced
#define vmpf_nrepaged		vmminfo.nrepaged
#define vmpf_minpgahead		vmminfo.minpgahead
#define vmpf_maxpgahead		vmminfo.maxpgahead
#define vmpf_numpermio		vmminfo.numpermio
#define vmpf_hisid		vmminfo.hisid
#define vmpf_hiesid		vmminfo.hiesid
#define vmpf_system_pgs		vmminfo.system_pgs
#define vmpf_nonsys_pgs		vmminfo.nonsys_pgs
#define vmpf_unmngd_pgs		vmminfo.unmngd_pgs
#define vmpf_memgrd_succ_pgs	vmminfo.memgrd_succ_pgs
#define vmpf_memgrd_fail_pgs	vmminfo.memgrd_fail_pgs

/* struct for VMINFO64 */
struct vminfo64 {
	uint64_t pgexct; 	/* count of page faults     		*/
	uint64_t pgrclm; 	/* count of page reclaims 		*/
	uint64_t lockexct;	/* count of lockmisses	    		*/
	uint64_t backtrks;    	/* count of backtracks	    		*/
	uint64_t pageins;	/* count of pages paged in  		*/
	uint64_t pageouts;	/* count of pages paged out 		*/
	uint64_t pgspgins;	/* count of page ins from paging space	*/
	uint64_t pgspgouts;	/* count of page outs from paging space */
	uint64_t numsios;	/* count of start I/Os	    		*/
	uint64_t numiodone;	/* count of iodones	    		*/
	uint64_t zerofills;	/* count of zero filled pages 		*/
	uint64_t exfills;	/* count of exec filled pages		*/
	uint64_t scans;		/* count of page scans by clock 	*/
	uint64_t cycles;	/* count of clock hand cycles		*/
	uint64_t pgsteals;	/* count of page steals	   		*/
	uint64_t freewts;	/* count of free frame waits		*/
	uint64_t extendwts;	/* count of extend XPT waits		*/
	uint64_t pendiowts;	/* count of pending I/O waits  		*/
        /*
         * the next fields need to be computed by vmgetinfo
         * system call, else their value will be inaccurate.
         */
        rpn64_t numfrb;         /* number of pages on free list */
        rpn64_t numclient;      /* number of client frames */
        rpn64_t numcompress;    /* no of frames in compressed segments */
        rpn64_t numperm;        /* number frames non-working segments */
        rpn64_t maxperm;        /* max number of frames non-working */
	rpn64_t memsizepgs;     /* real memory size in 4K pages  */
	rpn64_t numvpages;      /* accessed virtual pages */	
        rpn64_t minperm;        /* no fileonly page steals */
        rpn64_t minfree;        /* minimun pages free list (fblru) */
        rpn64_t maxfree;        /* maxfree pages free list (fblru) */
	rpn64_t maxclient;      /* max number of client frames */
#ifndef RPTYPES
#define RPTYPES         2
#endif
	rpn64_t rpgcnt[RPTYPES];/* repaging cnt */
	rpn64_t numpout;	/* number of fblru page-outs        */
	rpn64_t numremote;	/* number of fblru remote page-outs */
	rpn64_t numwseguse;	/* count of pages in use for working seg */
	rpn64_t numpseguse;	/* count of pages in use for persistent seg */
	rpn64_t numclseguse;	/* count of pages in use for client seg */
	rpn64_t numwsegpin;	/* count of pages pinned for working seg */
	rpn64_t numpsegpin;	/* count of pages pinned for persistent seg */
	rpn64_t numclsegpin;	/* count of pages pinned for client seg */
	psize_t lgpg_size;	/* Hardware large page size */
	rpn64_t lgpg_cnt;	/* Total number of large pages on the system */
	rpn64_t lgpg_numfrb;	/* Number of large pages on the freelist(s) */
	rpn64_t lgpg_inuse;	/* Number of large pages in use */
	rpn64_t lgpg_hi;	/* Large page high water count */
	rpn64_t numralloc;	/* number of remote allocations */
	cnt64_t numspecsegs;	/* number of special dataseg id's */
	cnt64_t numspecfree;	/* number of free special dataseg id's */
	cnt64_t specsegshi;	/* special dataseg id's high water count */
	
	/* Current number of free paging space blocks, and the thresholds
	 * when SIGDANGER and SIGKILL signals will be sent to processes.
	 */
	rpn64_t psfreeblks;	/* number of free paging space blocks */
	rpn64_t npswarn;	/* threshold when SIGDANGER is sent */
	rpn64_t npskill;	/* threshold when SIGKILL is sent */
	rpn64_t normlmbmem;	/* #nonremoveable pages for DR. */ 
	rpn64_t	pfrsvdblks;	/* number of system reserved blocks */
	rpn64_t	pfavail;	/* number of pages available for pinning */
	rpn64_t	pfpinavail;	/* app-level num pages avail for pinning */
	rpn64_t nreplaced[RPTYPES]; /* number of pages replaced         */
	rpn64_t nrepaged[RPTYPES];  /* number of pages repaged          */
	rpn64_t minpgahead;	/* min number of pageahead pages        */
	rpn64_t maxpgahead;	/* max number of pageahead pages        */
	rpn64_t numpermio;	/* number of fblru non-w.s. pageouts    */
	cnt64_t hisid;		/* max index + 1 of sids ever used      */
	cnt64_t hiesid;		/* max index + 1 of esids ever used,
				 * always set to -1 on 64 bit kernel 	*/
	rpn64_t system_pgs;	/* pages on SCBs marked V_SYSTEM	*/
	rpn64_t nonsys_pgs;	/* pages on SCBs not marked V_SYSTEM	*/
	rpn64_t unmngd_pgs;	/* pages not on SCBs			*/

	uint64_t memgrd_succ_pgs;/* pages memguard successfully removed	*/
	uint64_t memgrd_fail_pgs;/* pages memguard failed to remove	*/

	rpn64_t	___unused53[4];	/* keep offsets the same on 53 as 61	*/

	size64_t memavailable;  /* # bytes mem avail w/o paging working */
};

struct vminfo_psize {
	psize_t psize;          /* IN: page size                        */

	/* The rest of this struct is output from vmgetinfo()           */

	uint64_t attr;          /* bitmap of page size's attributes     */

       /* Page size attributes reported in the vminfo_psize.attr field: */
#define VM_PSIZE_ATTR_PAGEABLE       0x1  /* page size supports paging  */
	
	uint64_t pgexct; 	/* count of page faults     		*/
	uint64_t pgrclm; 	/* count of page reclaims 		*/
	uint64_t lockexct;	/* count of lockmisses	    		*/
	uint64_t backtrks;    	/* count of backtracks	    		*/
	uint64_t pageins;	/* count of pages paged in  		*/
	uint64_t pageouts;	/* count of pages paged out 		*/
	uint64_t pgspgins;	/* count of page ins from paging space	*/
	uint64_t pgspgouts;	/* count of page outs from paging space */
	uint64_t numsios;	/* count of start I/Os	    		*/
	uint64_t numiodone;	/* count of iodones	    		*/
	uint64_t zerofills;     /* count of zero filled pages 		*/
	uint64_t exfills;       /* count of exec filled pages		*/
	uint64_t scans;      	/* count of page scans by clock 	*/
	uint64_t cycles;      	/* count of clock hand cycles		*/
	uint64_t pgsteals;      /* count of page steals	   		*/
	uint64_t freewts;      	/* count of free frame waits		*/
	uint64_t extendwts;     /* count of extend XPT waits		*/
	uint64_t pendiowts;     /* count of pending I/O waits  		*/

        /*
         * the next fields need to be computed by vmgetinfo
         * system call, else their value will be inaccurate.
         */
	rpn64_t numframes;      /* # of real memory frames of this psize */
        rpn64_t numfrb;         /* number of pages on free list */
        rpn64_t numclient;      /* number of client frames */
        rpn64_t numcompress;    /* no of frames in compressed segments */
        rpn64_t numperm;        /* number frames non-working segments */
	rpn64_t numvpages;      /* accessed virtual pages */	
        rpn64_t minfree;        /* minimun pages free list (fblru) */
        rpn64_t maxfree;        /* maxfree pages free list (fblru) */
#ifndef RPTYPES
#define RPTYPES         2
#endif
	rpn64_t rpgcnt[RPTYPES];/* repaging cnt */
	rpn64_t numpout;	/* number of fblru page-outs        */

	rpn64_t numremote;	/* number of fblru remote page-outs */
	rpn64_t numwseguse;	/* count of pages in use for working seg */
	rpn64_t numpseguse;	/* count of pages in use for persistent seg */
	rpn64_t numclseguse;	/* count of pages in use for client seg */
	rpn64_t numwsegpin;	/* count of pages pinned for working seg */
	rpn64_t numpsegpin;	/* count of pages pinned for persistent seg */
	rpn64_t numclsegpin;	/* count of pages pinned for client seg */
	rpn64_t numpgsp_pgs;    /* # of wseg pages with allocated paging space */
	
	rpn64_t numralloc;	/* number of remote allocations */
	rpn64_t	pfrsvdblks;	/* number of system reserved blocks */
	rpn64_t	pfavail;	/* number of pages available for pinning */
	rpn64_t	pfpinavail;	/* app-level num pages avail for pinning */
	rpn64_t numpermio;	/* number of fblru non-w.s. pageouts    */

	rpn64_t system_pgs;	/* pages on SCBs marked V_SYSTEM	*/
	rpn64_t nonsys_pgs;	/* pages on SCBs not marked V_SYSTEM	*/

	rpn64_t	___unused53[3];	/* keep offsets the same on 53 as 61	*/

	size64_t memavailable;  /* # bytes mem avail w/o paging working */
};
extern struct vminfo_psize vmminfo_psizes[];

/* Macros for referencing variables in vminfo_psize.
 */
#define VMPFPS_REF(p)           vmminfo_psizes[(p)]
#define vmpfps_psize(p)         VMPFPS_REF(p).psize
#define vmpfps_attr(p)          VMPFPS_REF(p).attr
#define vmpfps_pgexct(p)        VMPFPS_REF(p).pgexct
#define vmpfps_pgrclm(p)	VMPFPS_REF(p).pgrclm
#define vmpfps_lockexct(p)	VMPFPS_REF(p).lockexct
#define vmpfps_backtrks(p)	VMPFPS_REF(p).backtrks
#define vmpfps_pageins(p)	VMPFPS_REF(p).pageins
#define vmpfps_pageouts(p)	VMPFPS_REF(p).pageouts
#define vmpfps_pgspgins(p)	VMPFPS_REF(p).pgspgins
#define vmpfps_pgspgouts(p)	VMPFPS_REF(p).pgspgouts
#define vmpfps_numsios(p)	VMPFPS_REF(p).numsios
#define vmpfps_numiodone(p)	VMPFPS_REF(p).numiodone
#define vmpfps_zerofills(p)	VMPFPS_REF(p).zerofills
#define vmpfps_exfills(p)	VMPFPS_REF(p).exfills
#define vmpfps_scans(p)		VMPFPS_REF(p).scans
#define vmpfps_cycles(p)	VMPFPS_REF(p).cycles
#define vmpfps_pgsteals(p)	VMPFPS_REF(p).pgsteals
#define vmpfps_freewts(p)	VMPFPS_REF(p).freewts
#define vmpfps_extendwts(p)	VMPFPS_REF(p).extendwts
#define vmpfps_pendiowts(p)	VMPFPS_REF(p).pendiowts
#define vmpfps_numfrb(p)	VMPFPS_REF(p).numfrb
#define vmpfps_numclient(p)	VMPFPS_REF(p).numclient
#define vmpfps_numcompress(p)	VMPFPS_REF(p).numcompress
#define vmpfps_numperm(p)	VMPFPS_REF(p).numperm
#define vmpfps_minfree(p)       VMPFPS_REF(p).minfree
#define vmpfps_maxfree(p)       VMPFPS_REF(p).maxfree
#define vmpfps_rpgcnt(p,y)	VMPFPS_REF(p).rpgcnt[(y)]
#define vmpfps_numpout(p)  	VMPFPS_REF(p).numpout
#define vmpfps_numframes(p)	VMPFPS_REF(p).numframes
#define vmpfps_numremote(p)  	VMPFPS_REF(p).numremote
#define vmpfps_numwseguse(p)	VMPFPS_REF(p).numwseguse
#define vmpfps_numpseguse(p)	VMPFPS_REF(p).numpseguse
#define vmpfps_numclseguse(p)	VMPFPS_REF(p).numclseguse
#define vmpfps_numwsegpin(p)	VMPFPS_REF(p).numwsegpin
#define vmpfps_numpsegpin(p)	VMPFPS_REF(p).numpsegpin
#define vmpfps_numclsegpin(p)	VMPFPS_REF(p).numclsegpin
#define vmpfps_numpgsp_pgs(p)   VMPFPS_REF(p).numpgsp_pgs
#define vmpfps_numvpages(p)	VMPFPS_REF(p).numvpages
#define vmpfps_pfrsvdblks(p)	VMPFPS_REF(p).pfrsvdblks
#define vmpfps_pfavail(p)	VMPFPS_REF(p).pfavail
#define vmpfps_pfpinavail(p)	VMPFPS_REF(p).pfpinavail
#define vmpfps_numralloc(p)	VMPFPS_REF(p).numralloc
#define vmpfps_numpermio(p)	VMPFPS_REF(p).numpermio
#define vmpfps_system_pgs(p)	VMPFPS_REF(p).system_pgs
#define vmpfps_nonsys_pgs(p)	VMPFPS_REF(p).nonsys_pgs

/* Paging space information returned by swapqry() system call
 */
struct pginfo
{
	dev_t	devno;		/* device number		*/
	uint size;		/* size in PAGESIZE blocks	*/
	uint free;		/* # of free PAGESIZE blocks	*/
	uint	iocnt;		/* number of pending i/o's	*/
};

#ifdef _KERNEL

/* 32bit application representation of pginfo structure */

struct pginfo32
{

	dev32_t devno;          /* device number                */        
	uint    size;           /* size in PAGESIZE blocks      */
	uint    free;           /* # of free PAGESIZE blocks    */
	uint    iocnt;          /* number of pending i/o's      */

};

/* 64bit application representation of pginfo structure */

struct pginfo64
{
        dev64_t devno;          /* device number                */
        uint    size;           /* size in PAGESIZE blocks      */
        uint    free;           /* # of free PAGESIZE blocks    */
        uint    iocnt;          /* number of pending i/o's      */

};

#endif

/* Output of VMSHMID_TO_VMID command */
struct vmshmid_to_vmid
{
	int    shmid;       /* INPUT: shared memory id */
	int    num_vmids;   /* INPUT: size of vmids array*/
	                    /* OUTPUT: number vmids copied */
	vmid64_t  *vmids;   /* OUTPUT: where vmids are copied */
} ;


/*  struct to report page information for the VM_PAGE_INFO command
 */
struct vm_page_info {
	uint64_t addr;		/* IN: address on which to report */
	size64_t pagesize;	/* OUT: size of page backing addr */
};

/* struct to report the system's IPC limits
 */
struct ipc_limits {
	/* Semaphore limits */
	size64_t semmni;	/* max # of semaphore id's */
	size64_t semmsl;	/* max # of semaphores per sem id */
	size64_t semopm;	/* max # of op's per semop() call */
	size64_t semvmx;	/* max value of a semaphore */
	size64_t semume;	/* max # of undo entries per proc */
	size64_t semaem;	/* adjust on exit max value */

	/* Message limits */
	size64_t msgmax;	/* max message size */
	size64_t msgmnb;	/* max # of bytes per queue */
	size64_t msgmni;	/* max # of message queue id's */
	size64_t msgmnm;	/* max # of messages per queue id */

	/* Shared memory limits */
	size64_t shmmni;	/* max # of shared memory id's */
	size64_t shmmax64;	/* 64bit proc max shm region size */
	uint     shmmax32;	/* 32bit proc max shm region size */
	uint     shmmin;	/* min shared memory region size */
	size64_t shmseg64;	/* max # of shm segs per 64bit proc */
	uint     shmseg32;	/* max # of shm segs per 32bit proc
				 * (non-extended shm) */
};

/* vmgetinfo system call */
extern  int     vmgetinfo (void *out, int command, int arg);

#ifdef _KERNEL
#if defined( __64BIT_KERNEL) || defined(__FULL_PROTO)
extern  int     kvmgetinfo(void *out, int command, int arg);
#endif /* __64BIT_KERNEL || __FULL_PROTO */
#endif /* _KERNEL */

/* command values: */
#define VMINFO          0
#define VMSHMID_TO_VMID 1
#define VMINFO_ABRIDGED	2
#define VMGETMEMPVARS	3
#define VMSETMEMPVARS	4
#define VMGETKERVARS	5
#define VMSETKERVARS	6
#define VM_PAGE_INFO    7
#define VMPERF		8
#define IPC_LIMITS      9
#define BOSBOOT_VARS	10
/* values 11-99 are reserved for internal use. */

#define VM_NEW_HEAP_PSIZE 100 /* advisory psize for future sbrk allocs */
#define VM_STAGGER_DATA	  101 /* stagger the present sbreak value */
#define VMINFO_GETPSIZES  102 /* report a system's supported page sizes */
#define VMINFO_PSIZE      103 /* report statistics for a page size */
#define VMINFO64	  104 /* VMINFO with all 64 bit fields */
#define VMINFO64_SLOW	  105 /* VMINFO64 but slow scb-walk */

#ifdef _NO_PROTO
        extern  blkcnt_t psdanger();
        extern  int swapoff();
        extern  int swapon();
        extern  int swapqry();
#else
        extern  blkcnt_t psdanger(int);
        extern  int swapoff(char *);
        extern  int swapon(char *);
        extern  int swapqry(char *, struct pginfo *);
#endif

#endif /* _H_VMINFO */
