
#include <sys/inttypes.h>

#include <odmi.h>

#ifndef _H_cfgodm
#define _H_cfgodm


struct PdDv {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char type[16];
#ifndef  __cplusplus
 	char class[16];
#else
 	char Class[16];
#endif
	char subclass[16];
	char prefix[16];
	char devid[16];
	short base;
	short has_vpd;
	short detectable;
	short chgstatus;
	short bus_ext;
	short fru;
	short led;
	short setno;
	short msgno;
	char catalog[16];
	char DvDr[16];
	char Define[256];
	char Configure[256];
	char Change[256];
	char Unconfigure[256];
	char Undefine[256];
	char Start[256];
	char Stop[256];
	short inventory_only;
	char uniquetype[48];
	};
#define PdDv_Descs 25

extern struct Class PdDv_CLASS[];
#define get_PdDv_list(a,b,c,d,e) (struct PdDv * )odm_get_list(a,b,c,d,e)

struct PdCn {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char uniquetype[48];
	char connkey[16];
	char connwhere[16];
	};
#define PdCn_Descs 3

extern struct Class PdCn_CLASS[];
#define get_PdCn_list(a,b,c,d,e) (struct PdCn * )odm_get_list(a,b,c,d,e)

struct PdAt {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char uniquetype[48];
	char attribute[16];
	char deflt[256];
	char values[256];
	char width[16];
	char type[8];
	char generic[8];
	char rep[8];
	short nls_index;
	};
#define PdAt_Descs 9

extern struct Class PdAt_CLASS[];
#define get_PdAt_list(a,b,c,d,e) (struct PdAt * )odm_get_list(a,b,c,d,e)

struct PdPathAt {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char uniquetype[48];
	char attribute[16];
	char deflt[256];
	char values[256];
	char generic[4];
	char rep[4];
	short nls_index;
	};
#define PdPathAt_Descs 7

extern struct Class PdPathAt_CLASS[];
#define get_PdPathAt_list(a,b,c,d,e) (struct PdPathAt * )odm_get_list(a,b,c,d,e)

struct PdAtXtd {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char uniquetype[48];
	char attribute[16];
	char classification[16];
	char sequence[16];
	char *operation;
	char *operation_value;
	char *description;
	char *list_cmd;
	char *list_values_cmd;
	char *change_cmd;
	char *help;
	char *nls_values;
	};
#define PdAtXtd_Descs 12

extern struct Class PdAtXtd_CLASS[];
#define get_PdAtXtd_list(a,b,c,d,e) (struct PdAtXtd * )odm_get_list(a,b,c,d,e)

struct Config_Rules {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	short phase;
	short seq;
	__long32_t boot_mask;
	char rule[256];
	};
#define Config_Rules_Descs 4

extern struct Class Config_Rules_CLASS[];
#define get_Config_Rules_list(a,b,c,d,e) (struct Config_Rules * )odm_get_list(a,b,c,d,e)

struct CuDv {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char name[16];
	short status;
	short chgstatus;
	char ddins[16];
	char location[16];
	char parent[16];
	char connwhere[16];
	struct PdDv *PdDvLn;	/* link */
	struct listinfo *PdDvLn_info;	/* link */
	char PdDvLn_Lvalue[48];	/* link */
	};
#define CuDv_Descs 8

extern struct Class CuDv_CLASS[];
#define get_CuDv_list(a,b,c,d,e) (struct CuDv * )odm_get_list(a,b,c,d,e)

struct CuDep {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char name[16];
	char dependency[16];
	};
#define CuDep_Descs 2

extern struct Class CuDep_CLASS[];
#define get_CuDep_list(a,b,c,d,e) (struct CuDep * )odm_get_list(a,b,c,d,e)

struct CuAt {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char name[16];
	char attribute[16];
	char value[256];
	char type[8];
	char generic[8];
	char rep[8];
	short nls_index;
	};
#define CuAt_Descs 7

extern struct Class CuAt_CLASS[];
#define get_CuAt_list(a,b,c,d,e) (struct CuAt * )odm_get_list(a,b,c,d,e)

struct CuDvDr {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char resource[12];
	char value1[20];
	char value2[20];
	char value3[20];
	};
#define CuDvDr_Descs 4

extern struct Class CuDvDr_CLASS[];
#define get_CuDvDr_list(a,b,c,d,e) (struct CuDvDr * )odm_get_list(a,b,c,d,e)

struct CuVPD {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char name[16];
	short vpd_type;
	char vpd[512];
	};
#define CuVPD_Descs 3

extern struct Class CuVPD_CLASS[];
#define get_CuVPD_list(a,b,c,d,e) (struct CuVPD * )odm_get_list(a,b,c,d,e)

struct CuPath {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char name[16];
	char parent[16];
	char *connection;
	char *alias;
	short path_status;
	short path_id;
	};
#define CuPath_Descs 6

extern struct Class CuPath_CLASS[];
#define get_CuPath_list(a,b,c,d,e) (struct CuPath * )odm_get_list(a,b,c,d,e)

struct CuPathAt {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char name[16];
	short path_id;
	char attribute[16];
	char *value;
	};
#define CuPathAt_Descs 4

extern struct Class CuPathAt_CLASS[];
#define get_CuPathAt_list(a,b,c,d,e) (struct CuPathAt * )odm_get_list(a,b,c,d,e)

struct CuData {
	__long32_t _id;
	__long32_t _reserved;
	__long32_t _scratch;
	char name[16];
	char resource[32];
	char key[32];
	char *value1;
	char *value2;
	};
#define CuData_Descs 5

extern struct Class CuData_CLASS[];
#define get_CuData_list(a,b,c,d,e) (struct CuData * )odm_get_list(a,b,c,d,e)

#endif /* _H_cfgodm */


