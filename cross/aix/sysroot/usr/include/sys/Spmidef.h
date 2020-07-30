/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* perf53X src/perf/perfagent/usr/include/sys/Spmidef.h 1.20.3.1          */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* OBJECT CODE ONLY SOURCE MATERIALS                                      */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1992,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)98   1.20.3.1  src/perf/perfagent/usr/include/sys/Spmidef.h, perfagent, perf53X, x2010_31A5 6/3/10 08:32:05 */
/*
 * COMPONENT_NAME:   (PERFAGENT) - Performance Agent
 *
 * FUNCTIONS: header file
 *
 * ORIGINS: 30
 *
 *                  -- (                            when
 * combined with the aggregated modules for this product)
 * OBJECT CODE ONLY SOURCE MATERIALS
 * (C) COPYRIGHT International Business Machines Corp. 1992, 1996
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_SPMIDEF
#define _H_SPMIDEF

#ifdef _NO_PROTO
#undef _NO_PROTO
#endif

#include <sys/time.h>
#include <sys/types.h>
#include <values.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/signal.h>

#define  MAJOR_SHM_VER  0
#define  MINOR_SHM_VER  2

#ifndef XM_BOOL
#define XM_BOOL
typedef unsigned char  boolean;
#define true  ((unsigned char) 0xff)
#define false ((unsigned char) 0x00)
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

/*
   Defines for common use
*/
#define  PERFMGR              "perfmgr"
#define  PERFAGENT            "perfagent"
#define  SERVD                "xmtopas"
#define  XMPERF               "xmperf"
#define  ETCDIR               "/etc/perf/"
#define  MGRLPPDIR            "/usr/lpp/perfmgr/"
#define  AGENTLPPDIR          "/usr/lpp/perfagent/"

#define  EXCEPT_NAME_LEN      32
#define  EXCEPT_DESC_LEN      256

/*
   GLOBAL CONSTANTS ---------------------------------------------------
*/

#define SI_MAXNAME 32
#define SI_MAXLNAME 64

/*
   GLOBAL ENUMS -------------------------------------------------------
*/

enum SiInstFreq /* Instantiability */
{
   SiNoInst,   /* Subcontexts never change                             */
   SiCfgInst,  /* Subcontext instances created at Spmi load time       */
   SiContInst, /* System operation changes subcontexts continuously    */
   SiReCfgInst /* Subcontext instances change after reconfiguration    */
};

enum ValType /* field type */
{
   SiCounter,                  /* field is always incremented         */
   SiQuantity                  /* field maintains a level             */
};

enum DataType /* field format */
{
   SiULong,
   SiLong,
   SiUInt,
   SiInt,
   SiUShort,
   SiShort,
   SiChar,        /* currently unsupported */
   SiAddr,        /* supported only for destination field = SiLong */
   SiTimeval,     /* supported only for destination field = SiLong */
   SiFloat,
   SiDouble,
   SiPtr,         /* currently unsupported */
   SiUnsign,
   SiLongLong,
   SiULongLong
};

enum Error /* Error codes recorded by API interface */
{
   SiSuccess = 0,
   SiInvalidCx = 180,
   SiNoShmPtr,
   SiShmemFailed,
   SiAssumedDead,
   SiInstBusy,
   SiNotInst,
   SiNotInit,
   SiBadArgument,
   SiNotFound,
   SiNoValue,
   SiInitFailed,
   SiSmuxFailed,
   SiLocked,
   SiDuplicate,
   SiCallocFailed,
   SiNoLicense,
   SiDeleted,
   SiNoSpace,
   SiOtherErr
};

enum HotExcept { /* Codes to specify exception handling from HotSets */
	SiHotNoException = 0,
	SiHotException,
	SiHotTrap,
	SiHotBoth
};

enum HotFeed { /* Codes to specify response types for data feeds from HotSets */
	SiHotNoFeed = 0,
	SiHotThreshold,
	SiHotAlways
};

enum StatSetListType { /* is this StatSet or Hotset */
   IsStatSet = 1,
   IsHotSet,
   IsDynSet,
   IsStatSet64,
   IsHotSet64
};

/*
   HANDLES ------------------------------------------------------------
*/

/*
   Handles are invented to make sure we can convert shared memory addresses
   in areas allocated by a kernel extension to addresses that can be used by
   applications.
*/
typedef  struct
{
   u_long            refid;
   struct SpmiCx     *ptr;
} spmi_cx_hdl;

typedef  struct
{
   u_long            refid;
   struct SpmiStat   *ptr;
} spmi_stat_hdl;

/*
   The SpmiCxHdl handle is a symbolic pointer to a context.
   To access the SpmiCx structure identified by the handle, use
   the function call SpmiGetCx():
*/
typedef spmi_cx_hdl *   SpmiCxHdl;

/*
   The SpmiStatHdl handle is a symbolic pointer to a statistic.
   To access the SpmiStat structure identified by the handle, use
   the function call SpmiGetStat():
*/

typedef spmi_stat_hdl   * SpmiStatHdl;

/*
   STRUCTURES ---------------------------------------------------------

   The SpmiCx structure describes a node in the data hierarchy.  As seen by an
   application program, an SpmiCx data structure is always an instance of a
   context. The data structure names the context and describes it in the fields
   "name" and "description", respectively.  It also contains a handle that can
   be used to access the parent context (NULL if parent is the Top context),
   and a field describing the instantiability of the context.
*/

struct SpmiCx
{
   char            name[SI_MAXNAME];         /* short name of the context   */
   char            description[SI_MAXLNAME]; /* descriptive name            */
   SpmiCxHdl       parent;                   /* handle of parent context    */
   enum SiInstFreq inst_freq;                /* instantiability of context  */
   u_short         asnno;                    /* ASN.1 number                */
   u_char          deleted;                  /* nonzero if context deleted  */
   u_char          dummy;                    /* alignment                   */
};

/*
   The SpmiStat structure describes a statistics object.  The object always
   describes a single-field counter or level statistic.  The described field
   is typically updated by some system component and the update process is
   typically asynchronous to any requests to read the field.  The field itself
   is not contained in the SpmiStat structure but Spmi functions allow an
   application program to retrieve the field value.

   Like the SpmiCx structure, the SpmiStat structure associates a name and a
   description with the object.  It also defines default scale values, e.g.
   the anticipated low and high range of the field or (in case of a counter
   field) the low and high range of the change anticipated for a one-second
   time period, e.g. the event rate per second.  Finally, two fields describe
   the data type as SiCounter (counter) or SiQuantity (level) and the format
   of the field.  Though the DataType enum defines many field formats, only
   SiLong and SiFloat are currently supported.
*/

struct SpmiStat
{
   char           name[SI_MAXNAME];         /* short name of statistic     */
   char           description[SI_MAXLNAME]; /* descriptive name            */
   long           min;                      /* default low scale value     */
   long           max;                      /* default high scale value    */
   enum ValType   value_type;               /* data type presented to API  */
   enum DataType  data_type;                /* data format presented to API*/
   u_short        asnno;                    /* ASN.1 number                */
   u_short        dummy;                    /* alignment                   */

};

/*
   The SpmiRawStat structure is used by DDS programs to define new
   statistics.
*/
struct SpmiRawStat
{
   char              name[SI_MAXNAME];  /* short name of statistic     */
   char              description[SI_MAXLNAME]; /* descriptive name     */
   long              min;               /* default low scale value     */
   long              max;               /* default high scale value    */
   enum ValType      value_type;        /* data type presented to API  */
   enum DataType     data_type;         /* data format presented to API*/
   u_short           asnno;             /* ASN.1 number                */
   u_short           size;              /* source data field size      */
   int               offset;            /* source data field offset    */
   enum DataType     type;              /* source data field format    */
   int               (*get_fun)();      /* data access function pointer*/
};

/*
   The SpmiCxLink structure is used to traverse the subcontexts of a context,
   using the function calls SpmiFirstCx and SpmiNextCx.  The structure serves
   as a handle when passed on the SpmiNextCx call and contains a single field
   that is the handle of the subcontext.
*/

struct SpmiCxLink
{
   void              *reserved;         /* reserved field              */
   SpmiCxHdl         context;           /* handle of subcontext        */
};

/*
   The SpmiStatLink structure is used to traverse the statistics of a context,
   using the function calls SpmiFirstStat and SpmiNextStat.  The structure
   serves as a handle when passed on the SpmiNextCx call and contains a single
   field that is the handle of the statistic.
*/

struct SpmiStatLink
{
   void              *reserved;         /* reserved field              */
   SpmiStatHdl       stat;              /* handle of statistic         */
};

/*
   NOTE ON API Data Access Structures and Handles

   While traversing the data hierarchy always is anchored off data structures
   defined within the Spmi, the actual access of data values relies on the
   application program to define which data values it is interested in.
   This is implemented through the concept of sets of statistics that are
   defined by an application program through the API and, thus, known to the
   Spmi.  A set of statistics is anchored off a data structure defined as an
   SpmiStatSet structure.  The address of a defined SpmiStatSet structure must
   be passed to Spmi through the API each time the application program needs
   to access the actual data values defined by the structure.

   When Spmi receives a read request for an SpmiStatSet structure, it will
   return the latest value for all the statistics that are members of the set of
   statistics. This reduces the overhead caused by access of kernel structures
   and other system areas and ensures that all data values for the statistics
   within a set are read at the same time.  The set of statistics may consist
   of one or many statistics fields.  Internal data structures for the set is
   built by Spmi in response to API calls from the application program.  The
   API has a simplified look of these structures and perceives them as a
   simple tree structure.

   Each of the data values selected for the set is represented by an
   SpmiStatVals structure.  Whenever Spmi executes a request from the
   application program to read the data values for set. all SpmiStatVals
   structures in the set are updated. The application program will then have
   to traverse the list of SpmiStatVals structures through the SpmiFirstVals()
   and SpmiNextVals() function calls.
*/

/*
   The SpmiStatSet structure is a anchor point for the structures that define
   a set of statistics. The application program is responsible for creating
   the SpmiStatSet, adding and deleting statistics to it, and deleting the
   SpmiStatSet when it is no longer required.  Spmi itself does not remember
   the address of an SpmiStatSet; it depends on the application program to
   supply it.  The structure only holds the time stamp for the most recent
   reading of its associated statistics and the elapsed time since the
   previous reading was done.
*/

struct SpmiStatSet
{
   struct timeval    time;              /* time of current get         */
   struct timeval    time_change;       /* elapsed time since last get */
};

#ifndef __64BIT__
struct SpmiStatSet64
{
   struct timeval    time;              /* time of current get         */
   struct timeval    time_change;       /* elapsed time since last get */
};
#endif

/*
   The SpmiHotSet corrresponds to SpmiStatSet but is used to define sets
   of statistics to be used for monitoring of the highest activity for
   the statistics (hot monitoring).
*/

struct SpmiHotSet
{
   struct timeval    time;              /* time of current get           */
   struct timeval    time_change;       /* elapsed time since last get   */
};

#ifndef __64BIT__
struct SpmiHotSet64
{
   struct timeval    time;              /* time of current get           */
   struct timeval    time_change;       /* elapsed time since last get   */
};
#endif

struct SpmiDynSet
{
   struct timeval    time;              /* time of current get           */
   struct timeval    time_change;       /* elapsed time since last get   */
};

struct SpmiDynVals
{
   void              *reserved;         /* reserved field              */
   SpmiStatHdl       stat;              /* handle of statistic         */
   SpmiCxHdl         grandpa;           /* parent of the peer contexts */
   int		         ref_count;         /* count of identical entries  */
   enum Error        error;             /* error code                  */
   char              *path;             /* path to grandpa context     */
};

/*
   The actual carrier of data values from Spmi to the application program is the

   SpmiStatVals structure.  It contains handles that allow an application to
   access the parent context and the SpmiStat structure of the value.  The
   field "ref_count" maintains a count of the number of times this statistic
   is included in the same set, usually one.  The actual  transfer of data
   values is done in the three last fields:

   val:
      A field used to return the actual value of the counter or level field.
      This field always returns the statistics value as it is maintained by
      the original supplier of the value, except that the field may have been
      converted to a different data format.

   val_change:
      The contents of this field is only well-defined when the statistic gives
      counter data.  The field then returns the difference between the previous
      reading of the counter data and the current reading.  When divided by the
      elapsed time returned in the SpmiStatSet structure, an event rate per
      time unit can be calculated.

   error:
      This field contains zero if Spmi's last attempt of reading the data value
      was successful, otherwise some error code as defined above.
*/

#ifndef __64BIT__
union Value
{
   long    l;
   float   f;
};

union Value64
#else
union Value
#endif
{
   longlong_t     l;
   double         f;
};


#ifndef __64BIT__
struct SpmiStatVals
{
   void              *reserved;         /* reserved field              */
   SpmiStatHdl       stat;              /* handle of statistic         */
   SpmiCxHdl         context;           /* handle of context           */
   int               ref_count;         /* count of simultaneous users */
   union Value       val;               /* counter/level data value    */
   union Value       val_change;        /* delta change if counter data*/
   enum Error        error;             /* error code                  */
};

struct SpmiStatVals64
#else
struct SpmiStatVals
#endif
{
   void              *reserved;         /* reserved field              */
   SpmiStatHdl       stat;              /* handle of statistic         */
   SpmiCxHdl         context;           /* handle of context           */
   int               ref_count;         /* count of simultaneous users */
   longlong_t        reserved2;		/* Alignment Purpose 	       */
   longlong_t        reserved3;		/* Alignment Purpose 	       */
   union Value64     val;               /* counter/level data value    */
   union Value64     val_change;        /* delta change if counter data*/
   enum Error        error;             /* error code                  */
};

/*
   Data structure to define the array elements used to hold the
   responses from reading a hotset
*/
#ifndef __64BIT__
struct SpmiHotItems
{
   char              name[SI_MAXLNAME]; /* name of peer context        */
   union Value       val;               /* counter/level data value    */
   union Value       val_change;        /* delta change if counter data*/
};   

struct SpmiHotItems64
#else
struct SpmiHotItems
#endif
{
   char              name[SI_MAXLNAME]; /* name of peer context        */
   union Value64     val;               /* counter/level data value    */
   union Value64     val_change;        /* delta change if counter data*/
};   

/*
   The SpmiHotVals corrresponds to SpmiStatVals but is used to return sets
   of statistics to be used for monitoring of the highest activity for
   the statistics (hot monitoring).
*/
#ifndef __64BIT__
struct SpmiHotVals
{
   void              *reserved;         /* reserved field              */
   SpmiStatHdl       stat;              /* handle of statistic         */
   SpmiCxHdl         grandpa;           /* parent of the peer contexts */
   int               ref_count;         /* count of simultaneous users */
   enum Error        error;             /* error code                  */
   enum HotExcept    except_type;       /* when to send exceptions     */
   short             trap_no;           /* trap number for SNMP traps  */
   short             severity;          /* severity for exception pckt */
   enum HotFeed      feed_type;         /* when to send data feeds     */
   int               threshold;         /* threshold for what to send  */
   short             frequency;         /* max frequency of exceptions */
   short             max_responses;     /* max  # of responses to send */
   short             avail_resp;        /* # of available hot readings */
   short             count;             /* # of returned hot readings  */
   char              *path;             /* path to grandpa context     */
   struct SpmiHotItems *items;          /* array of returned readings  */
};

struct SpmiHotVals64
#else
struct SpmiHotVals
#endif
{
   void              *reserved;         /* reserved field              */
   SpmiStatHdl       stat;              /* handle of statistic         */
   SpmiCxHdl         grandpa;           /* parent of the peer contexts */
   int               ref_count;         /* count of simultaneous users */
   enum Error        error;             /* error code                  */
   enum HotExcept    except_type;       /* when to send exceptions     */
   short             trap_no;           /* trap number for SNMP traps  */
   short             severity;          /* severity for exception pckt */
   enum HotFeed      feed_type;         /* when to send data feeds     */
   longlong_t        threshold;         /* threshold for what to send  */
   short             frequency;         /* max frequency of exceptions */
   long              max_responses;     /* max  # of responses to send */
   long              avail_resp;        /* # of available hot readings */
   long              count;             /* # of returned hot readings  */
   char              *path;             /* path to grandpa context     */
   struct SpmiHotItems64 *items;          /* array of returned readings  */
};

/*
   Structure to use for creation of context from Dynamic Data Suppliers
*/
typedef struct
{
#ifndef PRE_SUBREL_4
   char           path[SI_MAXLNAME]; /* context path name              */
#else  /* PRE_SUBREL_4 */
   char           path[SI_MAXLNAME];   /* context path name              */
#endif /* PRE_SUBREL_4 */
   char           descr[SI_MAXLNAME];  /* context description            */
   u_short        asnno;               /* ASN.1 number                   */
   u_short        datasize;            /* size of context record         */
   struct SpmiRawStat   *stats;        /* Stat array pointer for context */
   int            num_stats;           /* element count of Stat array    */
   struct SpmiRawStat   *inst_stats;   /* Stat array for multiple        */
                                       /*   instances of this context    */
   int            num_inst_stats;      /* element count for above array  */
   int            (*inst_subs)();      /* function to instantiate context*/
   int            inst_freq;           /* instantiate frequency          */
   u_long         level;               /* relative level (work field)    */
   char           *area;               /* data area pointer              */
   u_long         arealen;             /* length of above data area      */
} cx_create;

/*
   Structure describing shared memory area layout
*/
typedef struct
{
   short              SiShMajor;     /* Major version of shm protocol    */
   short              SiShMinor;     /* Minor version of shm protocol    */
   char               SiShName[64];  /* Path name for shm allocation     */
   char               SiShId;        /* ID for ftok() function           */
   key_t              SiShKey;       /* shared memory key (RSi interface)*/
                                     /* creating process ID (Spmi I/F)   */
   int                SiShMemId;     /* shared memory identifier         */
   u_long             SiShInetAddr;  /* Internet address of owning host  */
   u_short            SiShPortNo;    /* port number to talk to daemon    */
   int                SiShAllocLen;  /* length of allocated area         */
   int                SiShInstBegun; /* instantiations begun             */
   int                SiShInstDone;  /* instantiations completed         */
   int                SiShRefrBegun; /* refreshes begun                  */
   int                SiShRefrDone;  /* refreshes completed              */
   boolean            SiShGoAway;    /* signal supplier to terminate     */
   boolean            SiShAlarmSw;   /* switch to indicate alarm is set  */
   cx_create          *SiShCxTab;    /* pointer to fixed context table   */
   int                SiShCxCnt;     /* count of contexts in above table */
   cx_create          *SiShInstTab;  /* pointer instantiable contexts    */
   int                SiShInstCnt;   /* count of contexts in above table */
   struct SpmiRawStat *SiShStatTab;  /* pointer to consolidated Stats    */
   int                SiShStatCnt;   /* count of Stats in above table    */
   char               *SiShArea;     /* pointer to statistics area       */
   int                SiShAreaLen;   /* length of statistics area        */
   struct timeval     SiShT;         /* time of last area update BY US   */
   struct timeval     SiShPost;      /* time of update of fields below   */
   int                SiShInterval;  /* sample frequency in milliseconds */
   int                SiShSubscrib;  /* current number of values used    */
   struct SpmiCxLink  *SiShAddCx;    /* instantiated contexts to add     */
   struct SpmiCxLink  *SiShActCx;    /* active instantiated contexts     */
   struct SpmiCxLink  *SiShDelCx;    /* contexts to delete               */
   struct SpmiCxLink  *SiShFreeCx;   /* freed contexts                   */
   void               *SiShAlarm;    /* addr of Shm alarm data area      */
   u_long             SiShLock1;     /* lock words to serialize access   */
   u_long             SiShLock2;     /*  .. from multiple threads/CPUs   */
   u_long             SiShRes[4];    /* reserved for future use          */
   char               SiShData;      /* start of data area               */
} SpmiShare;

/*
   Structure describing an exception condition structure
*/
typedef struct
{
   char              host[64];        /* host where exception occurred */
   struct timeval    excp_time;       /* time exception occorred       */
   u_short           trap_no;         /* SNMP generic trap number      */
   u_short           severity;        /* severity code                 */
   u_short           freq;            /* frequence we check for except.*/
   boolean           alert;           /* reserved                      */
   boolean           excep;           /* whether to send on UDP        */
   char              name[EXCEPT_NAME_LEN];  /* user defined name      */
   char              descr[EXCEPT_DESC_LEN]; /* user defined descript. */
} Exception_Rec;

/*
 MACRO OPERATORS ----------------------------------------------------------
*/

#define OFFSET_L(cast,component) ((u_long)&((cast NULL)->component))

#define SIZE_L(cast,component) (sizeof((cast NULL)->component))

#define SZ_OFF(structure, component, type) SIZE_L((struct structure *), \
   component), OFFSET_L((struct structure *), component),  type

#define SZ_OFFT(structure, component, type) SIZE_L((struct structure *), \
   component), OFFSET_L((struct structure *), component),  type

#define STAT_L(ary) sizeof(ary)/sizeof(struct SpmiRawStat)

#define CX_L(ary) sizeof(ary)/sizeof(cx_create)

/*
   FUNCTION PROTOTYPES ---------------------------------------------------
*/

#ifdef _NO_PROTO
SpmiShare *SpmiDInit();
char *SpmiDAddCx();
int SpmiDDelCx();
int SpmiInit();
void SpmiExit();
int SpmiInstantiate();
int SpmiCreateCx();
int SpmiDeleteCx();
SpmiCxHdl SpmiPathGetCx();
struct SpmiCxLink *SpmiFirstCx();
struct SpmiCxLink *SpmiNextCx();
struct SpmiStatLink *SpmiFirstStat();
struct SpmiStatLink *SpmiNextStat();
char *SpmiStatGetPath();
struct SpmiCx *SpmiGetCx();
struct SpmiStat *SpmiGetStat();
struct SpmiStatSet *SpmiCreateStatSet();
struct SpmiStatVals *SpmiPathAddSetStat();
int SpmiFreeStatSet();
int SpmiDelSetStat();
int SpmiGetStatSet();
struct SpmiStatVals *SpmiFirstVals();
struct SpmiStatVals *SpmiNextVals();
float SpmiGetValue();
struct SpmiStatVals *SpmiNextValue();
char * SpmiDdsAddCx();
int SpmiDdsDelCx();
SpmiShare *SpmiDdsInit();
struct SpmiHotSet *SpmiCreateHotSet();
struct SpmiHotVals *SpmiAddSetHot();
int SpmiFreeHotSet();
int SpmiDelSetHot();
int SpmiGetHotSet();
struct SpmiHotVals *SpmiFirstHot();
struct SpmiHotVals *SpmiNextHot();
struct SpmiHotVals *SpmiNextHotItem();

#else

SpmiShare *SpmiDInit(cx_create *, int, cx_create *, int, char *);
char *SpmiDAddCx(ushort, char *, char *, char *, int);
int SpmiDDelCx(char *);
int SpmiInit(int);
void SpmiExit();
int SpmiInstantiate(SpmiCxHdl);
int SpmiCreateCx(char *, char);
int SpmiDeleteCx(SpmiCxHdl);
SpmiCxHdl SpmiPathGetCx(char *, SpmiCxHdl);
struct SpmiCxLink *SpmiFirstCx(SpmiCxHdl);
struct SpmiCxLink *SpmiNextCx(struct SpmiCxLink *);
struct SpmiStatLink *SpmiFirstStat(SpmiCxHdl);
struct SpmiStatLink *SpmiNextStat(struct SpmiStatLink *);
char *SpmiStatGetPath(SpmiCxHdl, SpmiStatHdl, int);
struct SpmiCx *SpmiGetCx(SpmiCxHdl);
struct SpmiStat *SpmiGetStat(SpmiStatHdl);
struct SpmiStatSet *SpmiCreateStatSet();
struct SpmiStatVals *SpmiPathAddSetStat(struct SpmiStatSet *, char *, SpmiCxHdl)
;
int SpmiFreeStatSet(struct SpmiStatSet *);
int SpmiDelSetStat(struct SpmiStatSet *t, struct SpmiStatVals *);
int SpmiGetStatSet(struct SpmiStatSet *, boolean);
struct SpmiStatVals *SpmiFirstVals(struct SpmiStatSet *);
struct SpmiStatVals *SpmiNextVals(struct SpmiStatSet *, struct SpmiStatVals *);
float SpmiGetValue(struct SpmiStatSet *, struct SpmiStatVals *);
struct SpmiStatVals *SpmiNextValue(struct SpmiStatSet *, struct SpmiStatVals *, float *);
char * SpmiDdsAddCx(ushort, char *, char *, int);
int SpmiDdsDelCx(char *);
struct SpmiHotSet *SpmiCreateHotSet();
struct SpmiHotVals *SpmiAddSetHot(struct SpmiHotSet *, char *, SpmiCxHdl,
					int, int, int, int, int, int, int);
int SpmiFreeHotSet(struct SpmiHotSet *);
int SpmiDelSetHot(struct SpmiHotSet *t, struct SpmiHotVals *);
int SpmiGetHotSet(struct SpmiHotSet *, boolean);
struct SpmiHotVals *SpmiFirstHot(struct SpmiHotSet *);
struct SpmiHotVals *SpmiNextHot(struct SpmiHotSet *, struct SpmiHotVals *);
struct SpmiHotVals *SpmiNextHotItem(struct SpmiHotSet *, struct SpmiHotVals *, int *, float *, char **);
SpmiShare * SpmiDdsInit(cx_create *, int, cx_create *, int, char *);

struct SpmiDynSet *SpmiCreateDynSet(char *);
int SpmiFreeDynSet(struct SpmiDynSet *);
struct SpmiDynVals *SpmiAddSetDyn(struct SpmiDynSet *,char *);
int SpmiGetDynSet(struct SpmiDynSet *, boolean);
struct SpmiDynVals *SpmiNextDynItem(struct SpmiDynSet *,struct SpmiDynVals *, int *, double *,char **);
int SpmiDelSetDyn(struct SpmiDynSet *, struct SpmiDynVals *);
struct SpmiDynVals *SpmiFirstDyn(struct SpmiDynSet *);
struct SpmiDynVals *SpmiNextDyn(struct SpmiDynSet *, struct SpmiDynVals *);

struct SpmiStatSet64 *SpmiCreateStatSet64();
int SpmiFreeStatSet64(struct SpmiStatSet64 *);
int SpmiGetStatSet64(struct SpmiStatSet64 *, boolean);
struct SpmiStatVals64 *SpmiPathAddSetStat64(struct SpmiStatSet64 *, char *, SpmiCxHdl);
int SpmiDelSetStat64(struct SpmiStatSet64 *t, struct SpmiStatVals64 *);
struct SpmiStatVals64 *SpmiFirstVals64(struct SpmiStatSet64 *);
struct SpmiStatVals64 *SpmiNextVals64(struct SpmiStatSet64 *, struct SpmiStatVals64 *);
double SpmiGetValue64(struct SpmiStatSet64 *, struct SpmiStatVals64 *);
struct SpmiStatVals64 *SpmiNextValue64(struct SpmiStatSet64 *, struct SpmiStatVals64 *, double *);
int SpmiGetValueStr(struct SpmiStatSet *, struct SpmiStatVals *, char *str, int *size);
int SpmiGetValueStr64(struct SpmiStatSet64 *, struct SpmiStatVals64 *, char *str, int *size);
int SpmiDelSetDynByName(struct SpmiDynSet *, char *) ;

struct SpmiHotSet64 *SpmiCreateHotSet64();
int SpmiFreeHotSet64(struct SpmiHotSet64 *);
int SpmiGetHotSet64(struct SpmiHotSet64 *, boolean);
struct SpmiHotVals64 *SpmiAddSetHot64(struct SpmiHotSet64 *, char *, SpmiCxHdl, int, longlong_t, int, int, int, int, int);
int SpmiDelSetHot64(struct SpmiHotSet64 *t, struct SpmiHotVals64 *);
struct SpmiHotVals64 *SpmiFirstHot64(struct SpmiHotSet64 *);
struct SpmiHotVals64 *SpmiNextHot64(struct SpmiHotSet64 *, struct SpmiHotVals64 *);
struct SpmiHotVals64 *SpmiNextHotItem64(struct SpmiHotSet64 *, struct SpmiHotVals64 *, int *, double *, char **);

#endif   /* _NO_PROTO   */

#endif /* _H_SPMIDEF */
