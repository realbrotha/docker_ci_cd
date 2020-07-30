
#include <sys/inttypes.h>

#include <odmi.h>

#ifndef _H_diagodm
#define _H_diagodm


struct DSMenu {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	short order;
	char comment[80];
	char msgkey[4];
	};
#define DSMenu_Descs 3

extern struct Class DSMenu_CLASS[];
#define get_DSMenu_list(a,b,c,d,e) (struct DSMenu * )odm_get_list(a,b,c,d,e)

struct DSMOptions {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char msgkey[4];
	char *catalogue;
	short order;
	short setid;
	short msgid;
	char *action;
	char Diskette[5];
	};
#define DSMOptions_Descs 7

extern struct Class DSMOptions_CLASS[];
#define get_DSMOptions_list(a,b,c,d,e) (struct DSMOptions * )odm_get_list(a,b,c,d,e)

struct PDiagDev {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char DType[16];
	char DSClass[16];
	short Ports;
	short PSet;
	short PreTest;
	char AttDType[16];
	char AttSClass[16];
	short Conc;
	short SupTests;
	short Menu;
	short DNext;
	char *DaName;
	char Diskette[5];
	char *EnclDaName;
	short SysxFlg;
	char DClass[16];
	};
#define PDiagDev_Descs 16

extern struct Class PDiagDev_CLASS[];
#define get_PDiagDev_list(a,b,c,d,e) (struct PDiagDev * )odm_get_list(a,b,c,d,e)

struct CDiagDev {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char DType[16];
	char Location[16];
	short Port;
	short State;
	short TstLvl;
	short More;
	short RtMenu;
	short NewEntry;
	short SysxTime;
	short Periodic;
	short Frequency;
	};
#define CDiagDev_Descs 11

extern struct Class CDiagDev_CLASS[];
#define get_CDiagDev_list(a,b,c,d,e) (struct CDiagDev * )odm_get_list(a,b,c,d,e)

struct TMInput {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	short exenv;
	short advanced;
	short system;
	short dmode;
	char date[80];
	short loopmode;
	short lcount;
	short lerrors;
	short console;
	char parent[16];
	char parentloc[16];
	char dname[16];
	char dnameloc[16];
	char child1[16];
	short state1;
	char childloc1[16];
	char child2[16];
	short state2;
	char childloc2[16];
	__long32_t pid;
	short cpuid;
	};
#define TMInput_Descs 21

extern struct Class TMInput_CLASS[];
#define get_TMInput_list(a,b,c,d,e) (struct TMInput * )odm_get_list(a,b,c,d,e)

struct FRUB {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char dname[16];
	short ftype;
	short sn;
	short rcode;
	short rmsg;
	char timestamp[80];
	};
#define FRUB_Descs 6

extern struct Class FRUB_CLASS[];
#define get_FRUB_list(a,b,c,d,e) (struct FRUB * )odm_get_list(a,b,c,d,e)

struct FRUs {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char dname[16];
	char fname[16];
	char floc[16];
	short ftype;
	short fmsg;
	short conf;
	struct FRUB *FRUBLn;	/* link */
	struct listinfo *FRUBLn_info;	/* link */
	char FRUBLn_Lvalue[80];	/* link */
	};
#define FRUs_Descs 7

extern struct Class FRUs_CLASS[];
#define get_FRUs_list(a,b,c,d,e) (struct FRUs * )odm_get_list(a,b,c,d,e)

struct FRUB_SRC {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char dname[16];
	char src[33];
	__ulong32_t refc2;
	__ulong32_t refc3;
	__ulong32_t refc4;
	__ulong32_t refc5;
	__ulong32_t refc6;
	__ulong32_t refc7;
	__ulong32_t refc8;
	__ulong32_t refc9;
	__long32_t rmsg;
	char crid[2];
	__ulong32_t plid;
	__long32_t action_flags;
	short subsysid;
	short event_sev;
	__long32_t errlg_seq;
	char timestamp[80];
	};
#define FRUB_SRC_Descs 18

extern struct Class FRUB_SRC_CLASS[];
#define get_FRUB_SRC_list(a,b,c,d,e) (struct FRUB_SRC * )odm_get_list(a,b,c,d,e)

struct FRUs_src {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	__long32_t type;
	char priority[2];
	char loc[80];
	char pn[8];
	char proc_id[8];
	char ccin[5];
	char sn[13];
	struct FRUB_SRC *FRUB_SRCLn;	/* link */
	struct listinfo *FRUB_SRCLn_info;	/* link */
	char FRUB_SRCLn_Lvalue[80];	/* link */
	};
#define FRUs_src_Descs 8

extern struct Class FRUs_src_CLASS[];
#define get_FRUs_src_list(a,b,c,d,e) (struct FRUs_src * )odm_get_list(a,b,c,d,e)

struct MenuGoal {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char dname[16];
	char tbuffer1[1000];
	char tbuffer2[1000];
	};
#define MenuGoal_Descs 3

extern struct Class MenuGoal_CLASS[];
#define get_MenuGoal_list(a,b,c,d,e) (struct MenuGoal * )odm_get_list(a,b,c,d,e)

struct DAVars {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char dname[16];
	char vname[30];
	short vtype;
	char vvalue[30];
	__long32_t ivalue;
	};
#define DAVars_Descs 5

extern struct Class DAVars_CLASS[];
#define get_DAVars_list(a,b,c,d,e) (struct DAVars * )odm_get_list(a,b,c,d,e)

struct PDiagAtt {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char DType[16];
	char DSClass[16];
	char attribute[16];
	char *value;
	char rep[8];
	char DClass[16];
	char *DApp;
	};
#define PDiagAtt_Descs 7

extern struct Class PDiagAtt_CLASS[];
#define get_PDiagAtt_list(a,b,c,d,e) (struct PDiagAtt * )odm_get_list(a,b,c,d,e)

#endif /* _H_diagodm */


