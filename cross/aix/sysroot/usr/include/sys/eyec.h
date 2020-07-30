#ifndef __H_EYEC_H
#define __H_EYEC_H
#define __EYEC2(__a,__b) (((__a)<< 8) | (__b))
#define __EYEC4(__a,__b,__c,__d) ((__EYEC2(__a,__b) << 16) | __EYEC2(__c,__d))
#define __EYEC8(__a,__b,__c,__d,__e,__f,__g,__h) (((unsigned long long)__EYEC4(__a,__b,__c,__d) << 32) | __EYEC4(__e,__f,__g,__h))
#ifdef __64BIT__
#define EYEC_ERRCODE		0x000000000000EEEEul	/* EEEE */		
#define EYEC_RASR	__EYEC8('r','a','s','r','R','A','S','a') /* rasrRASa */
#define EYEC_RASR_DYING	__EYEC8('r','a','s','r','R','A','S','d') /* rasrRASd */
#define EYEC_RASR_DEAD	__EYEC8('r','a','s','r','R','A','S','f') /* rasrRASf */
#define EYEC_RASP	__EYEC8('r','a','s','p','R','A','S','a') /* raspRASa */
#define EYEC_RASP_DYING	__EYEC8('r','a','s','p','R','A','S','d') /* raspRASd */
#define EYEC_RASP_DEAD	__EYEC8('r','a','s','p','R','A','S','f') /* raspRASf */
#define EYEC_RAST	__EYEC8('t','r','c','b','R','A','S','a') /* trcbRASa */
#define EYEC_RASE	__EYEC8('e','r','r','b','R','A','S','a') /* errbRASa */
#else
#define EYEC_RASR	__EYEC4('r','r','R','a')		/* rrRa */
#define EYEC_RASR_DYING	__EYEC4('r','r','R','d')		/* rrRd */
#define EYEC_RASR_DEAD  __EYEC4('r','r','R','f')		/* rrRf */
#define EYEC_RASP	__EYEC4('r','p','R','a')		/* rpRa */
#define EYEC_RASP_DYING	__EYEC4('r','p','R','d')		/* rpRd */
#define EYEC_RASP_DEAD	__EYEC4('r','p','R','f')		/* rpRf */
#define EYEC_RAST       __EYEC4('t','b','R','a')		/* tbRa */
#define EYEC_RASE	__EYEC4('e','b','R','a')		/* ebRa */
#endif /* __64BIT__ */
#define EYEC_RAS_STAT	__EYEC4('s','t','R','a')		/* stRa */
#define EYEC_RAS_PATHENT	__EYEC4('p','a','R','a')	/* paRa */
#define EYEC_RAS_PATHENT_LAST	__EYEC4('p','a','R','f')	/* paRf */
#define EYEC_KSET_A	__EYEC8('k','s','e','t','R','A','S','a') /* ksetRASa */
#define EYEC_KSET_F	__EYEC8('k','s','e','t','R','A','S','f') /* ksetRASf */
#ifndef _VMM_EYEC
#define _VMM_EYEC
#ifdef __64BIT_KERNEL
#define EYEC_LRUL	__EYEC8('l','r','u','l','V','M','M','i') /* lrulVMMi */
#define EYEC_LRULO	__EYEC8('l','r','u','l','V','M','M','o') /* lrulVMMo */
#define EYEC_LRUST	__EYEC8('l','r','u','V','M','M','s','t') /* lruVMMst */
#else /* ... !__64BIT_KERNEL */
#define EYEC_LRUL	__EYEC4('l','l','V','l')    /* llVl */
#define EYEC_LRULO	__EYEC4('l','l','V','o')    /* llVo */
#define EYEC_LRUST	__EYEC4('l','V','s','t')    /* lVst */
#endif /* __64BIT_KERNEL */
#endif /* _VMM_EYEC */
#ifdef __64BIT_KERNEL
#define EYEC_PVPROC	__EYEC8('p','v','p','r','P','R','O','C') /* pvprPROC */
#define EYEC_PROC	__EYEC8('p','r','o','c','P','R','O','C') /* procPROC */
#define EYEC_PVTHREAD	__EYEC8('p','v','t','h','P','R','O','C') /* pvthPROC */
#define EYEC_THREAD	__EYEC8('t','h','r','d','P','R','O','C') /* thrdPROC */
#else /* __64BIT_KERNEL */
#define EYEC_PVPROC	__EYEC4('p','p','P','R')	/* ppPR */
#define EYEC_PROC	__EYEC4('p','r','P','R')	/* prPR */
#define EYEC_PVTHREAD   __EYEC4('p','t','P','R')	/* ptPR */
#define EYEC_THREAD     __EYEC4('t','h','P','R')	/* thPR */
#endif /* __64BIT_KERNEL */
#ifndef _FS_EYEC
#define _FS_EYEC
#ifdef __64BIT__
#define EYEC_PILE	__EYEC8('p','i','l','e','L','F','S','a') /* pileLFSa */
#define EYEC_PILE_FREE	__EYEC8('p','i','l','e','L','F','S','f') /* pileLFSf */
#define EYEC_SLAB	__EYEC8('s','l','a','b','L','F','S','a') /* slabLFSa */
#define EYEC_SLAB_FREE	__EYEC8('s','l','a','b','L','F','S','f') /* slabLFSf */
#else /* __64BIT__ */
#define EYEC_PILE	__EYEC4('p','i','L','a') /* piLa */
#define EYEC_PILE_FREE	__EYEC4('p','i','L','f') /* piLf */
#define EYEC_SLAB	__EYEC4('s','l','L','a') /* slLa */
#define EYEC_SLAB_FREE	__EYEC4('s','l','L','f') /* slLf */
#endif /* __64BIT__ */
#define EYEC_PBUF_FREE	__EYEC4('b','m','F','R') /* bmFR */
#define EYEC_PBUF_DEAD	__EYEC4('b','m','D','E') /* bmDE */
#define EYEC_PBUF_NEW	__EYEC4('b','m','N','W') /* bmNW */
#define EYEC_PBUF_BUF	__EYEC4('b','m','B','U') /* bmBU */
#define EYEC_PBUF_LOG	__EYEC4('b','m','L','O') /* bmLO */
#define EYEC_PBUF_RAW	__EYEC4('b','m','R','A') /* bmRA */
#define EYEC_PBUF_SNAP	__EYEC4('b','m','S','N') /* bmSN */
#define EYEC_INODE	__EYEC2('i','2') /* i2 */
#define EYEC_INODE_FREE	__EYEC2('I','2') /* I2 */
#define EYEC_TXBLOCK_FREE	__EYEC4('t','b','2','f') /* tb2f */
#define EYEC_TXBLOCK_RESV	__EYEC4('t','b','2','r') /* tb2r */
#define EYEC_TXBLOCK_ALLOC	__EYEC4('t','b','2','a') /* tb2a */
#define EYEC_TXBLOCK_ALLOC_RESV	__EYEC4('t','b','2','A') /* tb2A */
#endif /* _FS_EYEC */
#endif
