/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/alloc/mpdata.h 1.13                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)91  1.13  src/bos/kernel/alloc/mpdata.h, sysnuma, bos530 12/23/03 12:40:57 */

#ifndef _H_MPDATA
#define _H_MPDATA

#ifdef _KERNEL
#include <sys/seg.h>
#include <sys/processor.h>
#include <sys/types.h>
#ifdef _KERNSYS
#include <alloc/mpdata_priv.h>
#endif

typedef ulong mpdata_t;
typedef mpdata_t mpctr_t;

#ifdef __64BIT__
#define MPDATA_INVALID  0xFFFFFFFFFFFFFFFF
#else /* 32-bit mode */
#define MPDATA_INVALID  0xFFFFFFFF
#endif

void mpdata_init(void);
ulong mpdata_alloc(size_t size);
void mpdata_free(mpdata_t c, size_t size);
#ifndef _KERNSYS
void * kmpdata_get(mpdata_t c);
void * kmpdata_getcpu(mpdata_t c, cpu_t cpu);
void * kmpdata_find(mpdata_t c, void *region);
#define mpdata_get(_c)		kmpdata_get(_c)
#define mpdata_getcpu(_c,_cpu)	kmpdata_getcpu((_c), (_cpu))
#define mpdata_find(_c, _old)	kmpdata_find((_c), (_old))
#endif

/* MPCTR macros */
#define MPCTR_ALLOC() (mpdata_alloc(8))
#define MPCTR_DEALLOC(_c) (mpdata_free((_c), 8))
#define MPCTR_INC(_c) ((*((int *)mpdata_get(_c)))++)
#define MPCTR_ATOMIC_INC(_c) (fetch_and_add(mpdata_get(_c), 1))
#define MPCTR_DEC(_c) ((*((int *)mpdata_get(_c)))--)
#define MPCTR_ATOMIC_DEC(_c) (fetch_and_add(mpdata_get(_c), -1))
#define MPCTR_ADD(_c, _val) ((*((int *)mpdata_get(_c)))+=(_val))
#define MPCTR_ATOMIC_ADD(_c, _val) (fetch_and_add(mpdata_get(_c), (_val)))
#define MPCTR_SUB(_c, _val) ((*((int *)mpdata_get(_c)))-=(_val))
#define MPCTR_ATOMIC_SUB(_c, _val) (fetch_and_add(mpdata_get(_c), -(_val)))
#define MPCTR_CLEAR(_c)					\
	{							\
		void * __temp=NULL;				\
		while (__temp = mpdata_find((_c), __temp))	\
			*((int *)__temp) = 0;			\
	}
#define MPCTR_SUM(_c, _sum)				\
	{							\
		void * __temp=NULL;				\
		(_sum) = 0;					\
		while (__temp = mpdata_find((_c), __temp))	\
			(_sum) += *((int *)__temp);		\
	}
#define MPCTR_COPY(_src, _dest) (mpdata_copy((_src),(_dest),8))
#define MPCTR_ELEM(_c, _cpu) (*((int *)mpdata_getcpu((_c), (_cpu))))

#endif /* _KERNEL */
#endif /* _H_MPDATA */



