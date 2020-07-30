/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* tcpip530 src/tcpip/usr/sbin/rsvpd/rapi_intserv.h 1.2                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)71	1.2  src/tcpip/usr/sbin/rsvpd/rapi_intserv.h, tcpqos, tcpip530 5/14/99 16:20:28 */
/*
 *   COMPONENT_NAME: tcpqos
 *
 *   FUNCTIONS:
 *
 *   ORIGINS: 27
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1999
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
**      rapi_intserv.h
**
**      This file contains definitions of the Integrated Service parameters.
**      These parameters are typically defined by the IETF Integrated Service
**      Working Group. The actual structures and structure names are defined
**      in the Open Group RAPI Standard and are to be used by the application
**      library.
**
**      All fields are in HOST order.
**
**
**      Copyright IBM.  All Rights Reserved.
**
*/

#ifndef H_RAPI_INTSERV
#define H_RAPI_INTSERV

#ifndef OS2
#include <sys/types.h>
#else
#include <types.h>
#endif

#ifndef FLOAT32
#define FLOAT32
typedef float      float32_t;
#endif

#define wordsof(x) (((x)+3)/4)    /* number of 32-bit words */

/*
 *    Integrated Service Numbers
 */

#define GENERAL_INFO           1
#define GUARANTEED_SERV        2
#define CONTROLLED_LOAD_SERV   5

/*
 *    Int-Serv Parameter IDs
 */
enum int_serv_wkp {
    IS_WKP_HOP_CNT        = 4,
    IS_WKP_PATH_BW        = 6,
    IS_WKP_MIN_LATENCY    = 8,
    IS_WKP_COMPOSED_MTU   = 10,
    IS_WKP_TB_TSPEC       = 127    /* token-bucket TSPEC parameter */
};

#define INTSERV_VERS_MASK       0xf0
#define INTSERV_VERSION0        0
#define Intserv_Version(x)      (((x)&ismh_version&INTSERV_VERS_MASK)>>4)
#define Intserv_Version_OK(x)   (((x)->ismh_version&INTSERV_VERS_MASK)== \
                                INTSERV_VERSION0)
/*
 *    Main Header
 */

typedef struct {
    u_int8_t    ismh_version;      /* version                                   */
    u_int8_t    ismh_unused;       /* not used                                  */
    u_int16_t   ismh_len32b;       /* num of 32-bit words excluding this header */
}   IS_main_hdr_t;


/*
 *    Service Header
 */

typedef struct {
    u_int8_t    issh_service;      /* service number                            */
    u_int8_t    issh_flags;        /* flags - see below                         */
    u_int16_t   issh_len32b;       /* num of 32-bit words excluding this header */
}   IS_serv_hdr_t;

#define ISSH_BREAK_BIT   0x80      /* service break flag                        */

/*
 *    Parameter Header
 */

typedef struct {
    u_int8_t    isph_parm_num;     /* parameter number                          */
    u_int8_t    isph_flags;        /* flags - see below                         */
    u_int16_t   isph_len32b;       /* num of 32-bit words excluding this header */
}   IS_parm_hdr_t;

#define ISPH_FLG_INV     0x80      /* invalid flag                              */

/*
 *    Useful Macros
 */
#define Set_Main_Hdr(p, len)       {(p)->ismh_version  = INTSERV_VERSION0; \
                                    (p)->ismh_unused   = 0; \
                                    (p)->ismh_len32b   = wordsof(len);}
#define Set_Serv_Hdr(p, s, len)    {(p)->issh_service  = (s); \
                                    (p)->issh_flags    = 0; \
                                    (p)->issh_len32b   = wordsof(len);}
#define Set_Param_Hdr(p, id, len)  {(p)->isph_parm_num = (id); \
                                    (p)->isph_flags    = 0; \
                                    (p)->isph_len32b   = wordsof(len);}
#define Set_Break_Bit(p)           ((IS_serv_hdr_t *)p)->issh_flags |= ISSH_BREAK_BIT
#define Next_Main_Hdr(p)           (IS_main_hdr_t *)((u_int32_t *)(p)+1+(p)->ismh_len32b)
#define Next_Serv_Hdr(p)           (IS_serv_hdr_t *)((u_int32_t *)(p)+1+(p)->issh_len32b)
#define Next_Parm_Hdr(p)           (IS_parm_hdr_t *)((u_int32_t *)(p)+1+(p)->isph_len32b)
#define Non_Is_Hop                 ((IS_serv_hdr_t *)p)->issh_flags&ISSH_BREAK_BIT

/*
 *    Generic Tspec
 */

#define TB_MAX_RATE             40e12           /* Bytes/sec    */
#define TB_MIN_RATE             1               /* Bytes/sec    */
#define TB_MAX_DEPTH            250e9           /* Bytes        */
#define TB_MIN_DEPTH            1               /* Bytes        */
#define TB_MAX_PEAK             0x7f800000      /* +ve infinity */

typedef struct {
    float32_t    TB_Tspec_r;       /* token bucket rate in bytes/sec  */
    float32_t    TB_Tspec_b;       /* token bucket depth in bytes     */
    float32_t    TB_Tspec_p;       /* token bucket peak in bytes/sec  */
    u_int32_t    TB_Tspec_m;       /* min policed unit in bytes       */
    u_int32_t    TB_Tspec_M;       /* max packet size in bytes        */
}   TB_Tsp_parms_t;

typedef struct {
    IS_serv_hdr_t    gen_Tspec_serv_hdr;   /* GENERAL_INFO, length    */
    IS_parm_hdr_t    gen_Tspec_parm_hdr;   /* IS_WKP_TB_TSPEC         */
    TB_Tsp_parms_t   gen_Tspec_parms;      /* tspec values            */
}   gen_Tspec_t;

#define gtspec_r       gen_Tspec_parms.TB_Tspec_r
#define gtspec_b       gen_Tspec_parms.TB_Tspec_b
#define gtspec_p       gen_Tspec_parms.TB_Tspec_p
#define gtspec_m       gen_Tspec_parms.TB_Tspec_m
#define gtspec_M       gen_Tspec_parms.TB_Tspec_M
#define gtspec_parmno  gen_Tspec_parm_hdr.isph_parm_num
#define gtspec_flags   gen_Tspec_parm_hdr.isph_flags
#define gtspec_len32b  gen_Tspec_parm_hdr.isph_len32b
#define gtspec_len     (sizeof(gen_Tspec_t)-sizeof(IS_serv_hdr_t))


/*
 *    Controlled-Load Service
 */

typedef struct {
    IS_serv_hdr_t    CL_spec_serv_hdr;     /* CONTROLLED_LOAD_SERV, 0, len */
    IS_parm_hdr_t    CL_spec_parm_hdr;     /* IS_WKP_TB_SPEC               */
    TB_Tsp_parms_t   CL_spec_parms;        /* tspec values                 */
}   CL_flowspec_t;

#define CLspec_r       CL_spec_parms.TB_Tspec_r
#define CLspec_b       CL_spec_parms.TB_Tspec_b
#define CLspec_p       CL_spec_parms.TB_Tspec_p
#define CLspec_m       CL_spec_parms.TB_Tspec_m
#define CLspec_M       CL_spec_parms.TB_Tspec_M
#define CLspec_parmno  CL_spec_parm_hdr.isph_parm_num
#define CLspec_flags   CL_spec_parm_hdr.isph_flags
#define CLspec_len32b  CL_spec_parm_hdr.isph_len32b
#define CLspec_len     (sizeof(CL_flowspec_t)-sizeof(IS_serv_hdr_t))


/*
 *    Guaranteed Service
 */

enum {
    IS_GUAR_RSPEC        = 130,
    GUAR_ADSPARM_C       = 131,
    GUAR_ADSPARM_D       = 132,
    GUAR_ADSPARM_Ctot    = 133,
    GUAR_ADSPARM_Dtot    = 134,
    GUAR_ADSPARM_Csum    = 135,
    GUAR_ADSPARM_Dsum    = 136
};

typedef struct {
    float32_t        Guar_R;               /* guaranteed rate in bytes/sec */
    u_int32_t        Guar_S;               /* slack term in microsecs      */
}   guar_Rspec_t;

typedef struct {
    IS_serv_hdr_t    Guar_serv_hdr;        /* GUARANTEED, 0, length        */
    IS_parm_hdr_t    Guar_Tspec_hdr;       /* IS_WKP_TB_TSPEC              */
    TB_Tsp_parms_t   Guar_Tspec_parms;     /* GENERIC Tspec parameters     */
    IS_parm_hdr_t    Guar_Rspec_hdr;       /* IS_GUAR_RSPEC                */
    guar_Rspec_t     Guar_Rspec;           /* Guaranteed Rspec parameters  */
}   Guar_flowspec_t;

#define Gspec_r        Guar_Tspec_parms.TB_Tspec_r
#define Gspec_b        Guar_Tspec_parms.TB_Tspec_b
#define Gspec_p        Guar_Tspec_parms.TB_Tspec_p
#define Gspec_m        Guar_Tspec_parms.TB_Tspec_m
#define Gspec_M        Guar_Tspec_parms.TB_Tspec_M
#define Gspec_R        Guar_Rspec.Guar_R
#define Gspec_S        Guar_Rspec.Guar_S
#define Gspec_T_parmno Guar_Tspec_hdr.isph_parm_num
#define Gspec_T_flags  Guar_Tspec_hdr.isph_flags
#define Gspec_T_len32b Guar_Tspec_hdr.isph_len32b
#define Gspec_R_parmno Guar_Rspec_hdr.isph_parm_num
#define Gspec_R_flags  Guar_Rspec_hdr.isph_flags
#define Gspec_R_len32b Guar_Rspec_hdr.isph_len32b
#define Gspec_len      (sizeof(Guar_flowspec_t)-sizeof(IS_serv_hdr_t))

typedef struct {
    IS_serv_hdr_t    Gads_serv_hdr;        /* GUARANTEED, x, length        */
    IS_parm_hdr_t    Gads_Ctot_hdr;        /* GUAR_ADSPARM_Ctot            */
    u_int32_t        Gads_Ctot;
    IS_parm_hdr_t    Gads_Dtot_hdr;        /* GUAR_ADSPARM_Dtot            */
    u_int32_t        Gads_Dtot;
    IS_parm_hdr_t    Gads_Csum_hdr;        /* GUAR_ADSPARM_Csum            */
    u_int32_t        Gads_Csum;
    IS_parm_hdr_t    Gads_Dsum_hdr;        /* GUAR_ADSPARM_Dsum            */
    u_int32_t        Gads_Dsum;
}   Gads_parms_t;

/*
 *   Basic Adspec
 */

typedef struct {
    IS_serv_hdr_t    gen_parm_hdr;         /* GENERAL_INFO, length         */
    IS_parm_hdr_t    gen_parm_hopcnt_hdr;  /* IS_WKP_HOP_CNT               */
    u_int32_t        gen_parm_hopcnt;
    IS_parm_hdr_t    gen_parm_pathbw_hdr;  /* IS_WKP_PATH_BW               */
    float32_t        gen_parm_path_bw;
    IS_parm_hdr_t    gen_parm_minlat_hdr;  /* IS_WKP_MIN_LATENCY           */
    u_int32_t        gen_parm_min_latency;
    IS_parm_hdr_t    gen_parm_compmtu_hdr; /* IS_WKP_COMPOSED_MTU          */
    u_int32_t        gen_parm_composed_MTU;
}   genparm_parms_t;

typedef struct {
    IS_serv_hdr_t    mads_hdr;             /* <service>, 1, length = 0     */
}   Min_adspec_t;


/*
 *   Integrated Services Flowspec
 */

typedef struct {
    IS_main_hdr_t      spec_mh;
    union {
      CL_flowspec_t    CL_spec;            /* Controlled-Load service      */
      Guar_flowspec_t  G_spec;             /* Guaranteed service           */
    }   spec_u;
}   IS_specbody_t;

#define ISmh_len32b    spec_mh.ismh_len32b
#define ISmh_version   spec_mh.ismh_version
#define ISmh_unused    spec_mh.ismh_unused


/*
 *   Integrated Services Tspec
 */

typedef struct {
    IS_main_hdr_t      st_mh;
    union {
      gen_Tspec_t      gen_stspec;         /* Generic Tspec                */
    }   tspec_u;
}   IS_tspbody_t;

#define IStmh_len32b   st_mh.ismh_len32b
#define IStmh_version  st_mh.ismh_version
#define IStmh_unused   st_mh.ismh_unused


/*
 *   Integrated Services Adspec
 */
#define MAX_OPT_ADSPEC_SIZE  sizeof(Gads_parms_t)+sizeof(Min_adspec_t)+2*sizeof(genparm_parms_t)

typedef struct {
    IS_main_hdr_t      adspec_mh;
    genparm_parms_t    adspec_genparms;
    /* may be followed by service specific fragments */
}   IS_adsbody_t;


#endif  /* H_RAPI_INTSERV */
