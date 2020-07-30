
#include <sys/inttypes.h>

#include <odmi.h>

#ifndef _H_srcobj
#define _H_srcobj


struct SRCsubsys {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char subsysname[30];
	char synonym[30];
	char cmdargs[1024];
	char path[1024];
	__long32_t uid;
	__long32_t auditid;
	char standin[1024];
	char standout[1024];
	char standerr[1024];
	short action;
	short multi;
	short contact;
	__long32_t svrkey;
	__long32_t svrmtype;
	short priority;
	short signorm;
	short sigforce;
	short display;
	short waittime;
	char grpname[30];
	};
#define SRCsubsys_Descs 20

extern struct Class SRCsubsys_CLASS[];
#define get_SRCsubsys_list(a,b,c,d,e) (struct SRCsubsys * )odm_get_list(a,b,c,d,e)

struct SRCsubsvr {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char sub_type[30];
	char subsysname[30];
	short sub_code;
	};
#define SRCsubsvr_Descs 3

extern struct Class SRCsubsvr_CLASS[];
#define get_SRCsubsvr_list(a,b,c,d,e) (struct SRCsubsvr * )odm_get_list(a,b,c,d,e)

struct SRCnotify {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char notifyname[30];
	char notifymethod[256];	/* method */
	};
#define SRCnotify_Descs 2

extern struct Class SRCnotify_CLASS[];
#define get_SRCnotify_list(a,b,c,d,e) (struct SRCnotify * )odm_get_list(a,b,c,d,e)

struct SRCextmeth {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	__long32_t action;
	char subsysname[30];
	char method[1024];
	char methargs[8192];
	char user[30];
	};
#define SRCextmeth_Descs 5

extern struct Class SRCextmeth_CLASS[];
#define get_SRCextmeth_list(a,b,c,d,e) (struct SRCextmeth * )odm_get_list(a,b,c,d,e)

#endif /* _H_srcobj */


