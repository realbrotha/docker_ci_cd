/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/kernel/sys/auditk.h 1.36                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)69       1.36  src/bos/kernel/sys/auditk.h, syssaud, bos53A, a2004_39C5 9/20/04 17:01:20 */

/*
 * COMPONENT_NAME: (SYSSAUD) Auditing Management
 *
 * FUNCTIONS: auditk.h for audit kernel definitions
 *
 * ORIGINS: 27 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */                                                                   
/*
 *   LEVEL 1,  5 Years Bull Confidential Information
 */

#ifndef _H_AUDITK
#define _H_AUDITK

#include	<sys/audit.h>
#include	<sys/sleep.h>
#include	<sys/types.h>
#include	<sys/lockl.h>

/*
 * this file describes auditing structures private to the kernel
 */

#define	MAX_ANAMES	32
#define	ALL_CLASS	31
#define MAX_EVNTSIZ	16
#define MAX_EVNTNUM	16
#define MAX_PATHSIZ	256
#define HASHLEN 	256
#define MAX_TABSIZ 	98304

/* this is the format of base event entries in the kernel symbol table */
struct	base_events{
	char		be_name[16];
	__ulong32_t	be_bitmap;
	struct	base_events	*be_next;
	struct	base_events	*be_prev;
};

typedef	struct	{
	struct file	*file;
	int		fd;
	int		EventCount;
	int		ByteCount;
} audit_BinInfo;

struct audit_anchor_t {
	tid_t	lock;
	int 	error;
};

/*
** The following structures are used in the kernel only.
*/
#ifdef _KERNEL

/*
** Defines an audit class for a 32-bit user space.  Used when passing
** data to a 64-bit kernel space.
*/
typedef struct audit_class32
{
  __cptr32 ae_name;
  __cptr32 ae_list;
  int      ae_len;
};

/*
** Defines an audit class for a 32-bit user space.  Used when passing
** data to a 32-bit user space.
*/
typedef struct audit_class64
{
  ptr64 ae_name;
  ptr64 ae_list;
  int   ae_len;
};

#define	ALL_SIZE64	   (sizeof( struct audit_class64 ) + 5)
#define	ALL_SIZE32	   (sizeof( struct audit_class32 ) + 5)

#endif      /* _KERNEL */



extern  Complex_lock	audit_lock;
extern  Simple_lock	audit_w_lock;
extern  Simple_lock	audit_q_lock;
extern	Simple_lock	audit_stream_lock;
extern	struct	base_events	*be_symtab;
extern	audit_BinInfo	audit_Bin;
extern	audit_BinInfo	audit_Next;
extern	struct  base_events *hashtab[HASHLEN];
extern  struct	audit_anchor_t audit_anchor;
extern	long	audit_threshold;
extern	long	audit_size;
extern	int	audit_flag;
extern	int	audit_EventThreshold;	/* Num of events before fsync() */
extern	int	audit_ByteThreshold;	/* Num of bytes before fsync()  */

/*
** Length of 64 and 32-bit audit data.
*/
extern	int	be_total_len64;
extern	int	be_total_len32;

extern	int	audit_panic;
extern  tid_t   audobj_block;
extern  int     auditevent_block;
extern 	int     oevent_total;
extern 	int     object_total;
extern	int	nevents;
extern	int   	cevent;
extern	int	(*auditdev)(int, char *, int);
extern 	char	*audit_getname();
extern	char	class_names[MAX_ANAMES][16];
extern	void	prochadd();
extern 	void	prochdel();

#define	audit_is_on(id) \
	(be_symtab[(id)].be_bitmap & U.U_procp->p_pvprocp->pv_auditmask)

#define audit_svc(){\
struct uthread *ut = curthread->t_uthreadp;\
if (ut->ut_audsvc) \
        if((ut->ut_audsvc)->svcnum){\
		lock_read(&audit_lock);\
                if(U.U_procp->p_pvprocp->pv_auditmask & \
		be_symtab[(ut->ut_audsvc)->svcnum].be_bitmap) {\
			lock_done(&audit_lock);\
                        audit_svcfinis(); \
		} else\
			lock_done(&audit_lock);\
                ut->ut_audsvc->svcnum = 0; \
        } \
}

/* generate an "arbitrary" audit record from within the kernel */
#define	_auditlog(event,result,buf,len) {\
		if(audit_flag & AUDIT_ON) {\
			static int	_id; \
			if(_id == 0)_id = audit_klookup(event); \
			if((_id > 0) && audit_is_on(_id)) \
				audit_write(_id, result, buf, len); \
		} \
	}

#define _ResetBinInfo(b) { b.fd = -1; b.file = NULL;\
			   b.EventCount = b.ByteCount = 0;}

#define	TCBMOD	 1
#define	TCBLEAK  2
#define	PRIVFAIL 3
#define	PRIVUSE  4

int *getufdp(void);
int audit_klog(char *event,int *svcnum,int status,struct aud_rec_cb *ah, \
								int taillen);
int audit_kwrite(char *event,int *svcnum,int error,struct aud_rec_cb *ah, ...);
void audit_socket(int error, struct aud_rec_cb *ah, int fd, \
	int domain, struct socket *so, int type, int protocol);
void audit_soclose(int error, struct aud_rec_cb *ah, int fd, struct socket *so);
void audit_socketpair(int error, int fd0,int fd1, int domain, int type,
								int protocol);
void audit_bind(int error, struct aud_rec_cb *ah, int fd, struct socket *so,
							struct mbuf *nam);
void audit_listen(int error, struct aud_rec_cb *ah, int fd, struct socket *so,
								int qlimit);
void audit_accept(int error, struct aud_rec_cb *ah, int fd, struct socket *so);
void audit_connect(int error, struct aud_rec_cb *ah, int fd, struct socket *so,
							struct mbuf *fnam);
void audit_shutdown(int error, struct aud_rec_cb *ah, int fd, struct socket *so,
							int how);
void audit_recv(int error, struct aud_rec_cb *ah, int fd, struct socket *so);
void audit_send(int error, struct aud_rec_cb *ah, int fd, struct socket *so);
void audit_setopt(int error, struct aud_rec_cb *ah, int fd, struct socket *so,
					int level, int option, struct mbuf *m);
#endif /* _H_AUDITK */

