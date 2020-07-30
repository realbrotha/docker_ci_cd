/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* tcpip530 src/tcpip/usr/sbin/rsvpd/rapi.h 1.2                           */
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
/* @(#)20	1.2  src/tcpip/usr/sbin/rsvpd/rapi.h, tcpqos, tcpip530 5/14/99 16:20:21 */
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

#ifndef H_RSVP_RAPI
#define H_RSVP_RAPI

#ifndef OS2
#include <sys/types.h>
#else
#include <types.h>
#endif

#include <sys/socket.h>  /* for sockaddr */
#include <netinet/in.h>  /* for sockaddr_in */

#include "rapi_intserv.h"

#ifndef FLOAT32
#define FLOAT32
typedef float            float32_t;
#endif

typedef struct sockaddr  rapi_addr_t;

/*****************************************************************************/
/*
 *   RAPI Formats
 */

typedef enum {
        RAPI_EMPTY_OTYPE          = 0,   /* empty object               */
        RAPI_FLOWSTYPE_Intserv    = 2,   /* Int-Serv format flowspec   */
        RAPI_FLOWSTYPE_Simplified = 3,   /* Simplified format flowspec */

        RAPI_TSPECTYPE_Intserv    = 17,  /* Int-Serv format tspec      */
        RAPI_TSPECTYPE_Simplified = 18,  /* Simplified format tspec    */

        RAPI_ADSTYPE_Intserv      = 33,  /* Int-Serv format adspec     */
        RAPI_ADSTYPE_Simplified   = 34,  /* Simplified format adspec   */

        RAPI_FILTERFORM_BASE      = 258, /* Simple V4: only sockaddr   */
        RAPI_FILTERFORM_GPI       = 259, /* IPV4 GPI filter format     */
        RAPI_FILTERFORM_BASE6     = 260, /* Simple V6: only sockaddr   */
        RAPI_FILTERFORM_GPI6      = 261  /* IPV6 GPI filter format     */
} rapi_format_t;


/*****************************************************************************/

/*
 *    Generic RAPI Object Header
 */

typedef struct {
    unsigned int             len;        /* actual length in bytes     */
    int                      form;       /* object format              */
} rapi_hdr_t;


/*****************************************************************************/

/*
 *   Filterspec Formats
 */

typedef struct {
        struct sockaddr_in sender;
} rapi_filter_base_t;

typedef struct {
        struct in_addr     sender;
        u_int32_t          gpi;
} rapi_filter_gpi_t;

#ifdef INET6
typedef struct {
        struct sockaddr_in6 sender;
} rapi_filter_base6_t;

typedef struct {
        struct in6_addr     sender;
        u_int32_t           gpi;
} rapi_filter_gpi6_t;
#endif

/*
 *      RAPI Filterspec
 */
typedef struct {
        u_int32_t               len;    /* length of filter, in bytes */
        rapi_format_t           form;   /* filter type */
        union {
            rapi_filter_base_t  base;
            rapi_filter_gpi_t   gpi;    /* not implemented */
#ifdef INET6
            rapi_filter_base6_t base6;
            rapi_filter_gpi6_t  gpi6;   /* not implemented */
#endif
        }   filt_u;                     /* variable length */
} rapi_filter_t;

#define rapi_filt4              filt_u.base.sender
#define rapi_filtbase4_addr     rapi_filt4.sin_addr
#define rapi_filtbase4_port     rapi_filt4.sin_port
#define rapi_filtgpi4           filt_u.gpi
#define rapi_filtgpi4_addr      rapi_filtgpi4.sender
#define rapi_filtgpi4_gpi       rapi_filtgpi4.gpi

#ifdef INET6
#define rapi_filt6              filt_u.base6.sender
#define rapi_filtbase6_addr     rapi_filt6.sin6_addr
#define rapi_filtbase6_port     rapi_filt6.sin6_port
#define rapi_filtgpi6           filt_u.gpi6
#define rapi_filtgpi6_addr      rapi_filtgpi6.sender
#define rapi_filtgpi6_gpi       rapi_filtgpi6.gpi
#endif

/*****************************************************************************/

/*
 *      Flowspec/Tspec Formats
 */

/* service types used for flowspec/tspec simplified format */
typedef enum {
        QOS_TSPEC      = 0,                     /* Generic Tspec           */
        QOS_CNTR_LOAD  = 1,                     /* Controlled-Load service */
        QOS_GUARANTEED = 2                      /* Guaranteed service      */
}   qos_service_t;  /* may need to change -> qos_service_type */

typedef struct {
        float32_t       spec_Tspec_r;           /* Token bucket rate (B/sec) */
        float32_t       spec_Tspec_b;           /* Token bucket depth (B)    */
        float32_t       spec_Tspec_p;           /* Peak data rate (B/sec)    */
        u_int32_t       spec_Tspec_m;           /* Min Policed Unit (B)      */
        u_int32_t       spec_Tspec_M;           /* Max pkt size (B)          */
}   qos_Tspec_body;

/*
 *      Simplified Tspec format
 */
typedef struct {
        qos_service_t   spec_type;               /* qos service type         */
        qos_Tspec_body  xtspec_Tspec;            /* Tspec                    */
}   qos_tspecx_t;

#define xtspec_r        xtspec_Tspec.spec_Tspec_r
#define xtspec_b        xtspec_Tspec.spec_Tspec_b
#define xtspec_p        xtspec_Tspec.spec_Tspec_p
#define xtspec_m        xtspec_Tspec.spec_Tspec_m
#define xtspec_M        xtspec_Tspec.spec_Tspec_M

/*
 *      RAPI Tspec format
 */

typedef struct {
        unsigned int    len;                     /* object len in bytes      */
        rapi_format_t   form;                    /* tspec format             */
        union {
               qos_tspecx_t  qosxt;              /* Simplified format tspec  */
               IS_tspbody_t  ISt;                /* Int-Serv format tspec    */
        }   tspecbody_u;
}   rapi_tspec_t;

#define tspecbody_qosx  tspecbody_u.qosxt
#define tspecbody_IS    tspecbody_u.ISt

/*
 *      Simplified Flowspec format
 */

typedef struct {
        qos_service_t   spec_type;              /* qos service type         */
        qos_Tspec_body  xspec_Tspec;            /* Tspec                    */
        float32_t       xspec_R;                /* Guaranteed Rate (B/sec)  */
        u_int32_t       xspec_S;                /* Slack term (sec)         */
}   qos_flowspecx_t;

#define xspec_r         xspec_Tspec.spec_Tspec_r
#define xspec_b         xspec_Tspec.spec_Tspec_b
#define xspec_p         xspec_Tspec.spec_Tspec_p
#define xspec_m         xspec_Tspec.spec_Tspec_m
#define xspec_M         xspec_Tspec.spec_Tspec_M

/*
 *      RAPI Flowspec
 */

typedef struct {
        unsigned int    len;                /* object len in bytes        */
        rapi_format_t   form;               /* flowspec format            */
        union {
                qos_flowspecx_t  qosx;      /* Simplified flowspec format */
                IS_specbody_t    IS;        /* Int-serv format            */
        }               specbody_u;
}   rapi_flowspec_t;

#define specbody_qosx   specbody_u.qosx
#define specbody_IS     specbody_u.IS


/*****************************************************************************/

/*
 *   Adspec Formats
 */

typedef struct {
        /*
         *  General adspec parameters
         */
        u_int8_t        xaspec_flags;          /* see flags below             */
        u_int16_t       xaspec_hopcnt;         /* num Int-Serv aware hops     */
        float32_t       xaspec_path_bw;        /* min path band width (B/s)   */
        u_int32_t       xaspec_min_latency;    /* min path latency (microsec) */
        u_int32_t       xaspec_composed_MTU;   /* composed path MTU           */

        /*
         *  Controlled-Load service adspec parameters
         */
        u_int8_t        xClaspec_flags;        /* see flags below                */
        u_int8_t        xClaspec_override;     /* 1 => over ride all gen. params */
        u_int16_t       xClaspec_hopcnt;       /* num Int-Serv aware hops        */
        float32_t       xClaspec_path_bw;      /* min path band width (B/s)      */
        u_int32_t       xClaspec_min_latency;  /* min path latency (microsec)    */
        u_int32_t       xClaspec_composed_MTU; /* composed path MTU              */

        /*
         *  Guaranteed service adspec parameters
         */
        u_int8_t        xGaspec_flags;         /* see flags below                     */
        u_int32_t       xGaspec_Ctot;          /* total rate dep. err (B)             */
        u_int32_t       xGaspec_Dtot;          /* total rate indep. err (microsec)    */
        u_int32_t       xGaspec_Csum;          /* reshaped rate dep. err (B)          */
        u_int32_t       xGaspec_Dsum;          /* reshaped rate indep. err (microsec) */
        u_int8_t        xGaspec_override;      /* 1 => over ride all gen. params      */
        u_int16_t       xGaspec_hopcnt;        /* num Int-Serv aware hops             */
        float32_t       xGaspec_path_bw;       /* min path band width (B/s)           */
        u_int32_t       xGaspec_min_latency;   /* min path latency (microsec)         */
        u_int32_t       xGaspec_composed_MTU;  /* composed path MTU                   */
} qos_adspecx_t;

/* possible values for flags */
#define XASPEC_FLG_BRK  0x01   /* break in service                        */
#define XASPEC_FLG_IGN  0x02   /* ignore : do not include this service    */
#define XASPEC_FLG_PARM 0x04   /* params present : include service params */


/*
 *      RAPI Adspec
 */

typedef struct {
        unsigned int    len;              /* object len in bytes      */
        rapi_format_t   form;             /* adspec format            */
        union {
                qos_adspecx_t adsx;       /* Simplified adspec format */
                IS_adsbody_t  ISa;        /* Int-Serv adspec format   */
        }               adsbody_u;
}   rapi_adspec_t;

#define adspecbody_qosx adsbody_u.adsx
#define adspecbody_IS   adsbody_u.ISa


/*****************************************************************************/

/*
 *    Policy Formats
 */

typedef struct {
    char        name[1];

} rapi_policy_name_string_t;

typedef enum {
    RAPI_POLICYF_INTEGRITY        =  0x00000001,
    RAPI_POLICYF_GLOBAL           =  0x00000002,
    RAPI_POLICYF_RESP             =  0x00000004
} rapi_policy_flags_t;


/*
 *    RAPI Policy
 */

typedef struct {
    u_int32_t               len;            /* actual length in bytes */
    rapi_format_t           form;           /* policy data format */
    rapi_policy_flags_t     flags;
    union {
        rapi_policy_name_string_t    namestring;

    } pol_u;

} rapi_policy_t;

/*****************************************************************************/

/*
 *      Reservation style ids
 */
typedef enum {
        RAPI_RSTYLE_WILDCARD = 1,       /* STYLE_ID_WF */
        RAPI_RSTYLE_FIXED = 2,          /* STYLE_ID_FF */
        RAPI_RSTYLE_SE = 3              /* STYLE_ID_SE */
} rapi_styleid_t;

/*
 *      Reservation style extension
 *
 *      This structure is currently undefined; in the future, it will allow
 *      passing style-specific parameters for possible new styles.
 */
typedef void rapi_stylex_t;

/*
 *      Registration flags
 */


/*****************************************************************************/

/*
 *   RAPI client handle
 */

typedef unsigned int rapi_sid_t;
#define NULL_SID        0       /* Error return from rapi_session */


/*****************************************************************************/

/*
 *   RAPI User callback function
 */

typedef enum {
        RAPI_PATH_EVENT   = 1,
        RAPI_RESV_EVENT   = 2,
        RAPI_PATH_ERROR   = 3,
        RAPI_RESV_ERROR   = 4,
        RAPI_RESV_CONFIRM = 5
} rapi_eventinfo_t;


typedef int  ((*rapi_event_rtn_t) (
        rapi_sid_t,              /* Which sid generated event    */
        rapi_eventinfo_t,        /* Event type                   */
        rapi_styleid_t,          /* Style ID                     */
        int,                     /* Error code                   */
        int,                     /* Error value                  */
        rapi_addr_t *,           /* Error node address           */
        unsigned int,            /* Error flags                  */
#define RAPI_ERRF_InPlace  0x01  /*   Left resv in place        */
#define RAPI_ERRF_NotGuilty 0x02 /*   This rcvr not guilty      */

        int,                     /* Number of filter specs/sender*/
                                 /*      templates in list       */
        rapi_filter_t *,         /* Filter spec/sender templ list*/
        int,                     /* Number of flowspecs/Tspecs   */
        rapi_flowspec_t *,       /* Flowspec/Tspec list          */
        int,                     /* Number of adspecs            */
        rapi_adspec_t *,         /* Adspec list                  */
        void *                   /* Client supplied arg          */
));


/*****************************************************************************/

/*
 *      RAPI External Functions
 */
rapi_sid_t rapi_session(
        rapi_addr_t *,          /* Session: (Dst addr, port), net order */
        int,                    /* Protocol id                          */
        int,                    /* Flags - not defined                  */
#define RAPI_USE_INTSERV  0x1   /* Use Int-Serv format in upcalls       */
#define RAPI_GPI_SESSION  0x8   /* Use GPI format - not implemented     */
        rapi_event_rtn_t,       /* Address of callback rtn - optional   */
        void *,                 /* App argument to callback - optional  */
        int *                   /* error return code                    */
);

int rapi_sender(
        rapi_sid_t,             /* Session ID                              */
        int,                    /* Flags - for traffic control             */
#define TC_QOS_POLICE     0x2   /* turn policing on                        */
#define TC_QOS_NOPOLICE   0x4   /* turn policing off                       */
#define TC_QOS_SHAPE      0x8   /* turn shaping on                         */
#define TC_QOS_NOSHAPE    0x10  /* turn shaping off                        */
        rapi_addr_t *,          /* Local host: (Src addr, port), net order */
        rapi_filter_t *,        /* Sender template - not supported         */
        rapi_tspec_t *,         /* Sender Tspec                            */
        rapi_adspec_t *,        /* Sender Adspec                           */
        rapi_policy_t *,        /* Sender policy data - not supported      */
        int                     /* TTL of multicast data                   */
);

int rapi_reserve(
        rapi_sid_t,             /* Session ID                      */
        int,                    /* Flags - not defined             */
#define RAPI_REQ_CONFIRM  0x20  /* Request confirmation */
        rapi_addr_t *,          /* Recv host addr - optional       */
        rapi_styleid_t,         /* Style ID                        */
        rapi_stylex_t *,        /* Style extension - not supported */
        rapi_policy_t *,        /* Receiver policy - not supported */
        int,                    /* # of filter specs               */
        rapi_filter_t *,        /* List of filter specs            */
        int,                    /* # of flowspecs                  */
        rapi_flowspec_t *       /* List of flowspecs               */
);

int rapi_release(rapi_sid_t     /* Session ID */);

int rapi_getfd(rapi_sid_t       /* Session ID */);

int rapi_dispatch(void);

int rapi_version(void);

/*      Formatting routines
 */
void    rapi_fmt_flowspec(rapi_flowspec_t *, char *, int);
void    rapi_fmt_tspec(rapi_tspec_t *, char *, int);
void    rapi_fmt_adspec(rapi_adspec_t *, char *, int);
void    rapi_fmt_filtspec(rapi_filter_t *, char *, int);


/*****************************************************************************/

/*
 *      RAPI Error Codes
 */
#define RAPI_ERR_OK             0       /* No error                     */
#define RAPI_ERR_INVAL          1       /* Invalid parameter            */
#define RAPI_ERR_MAXSESS        2       /* Too many sessions            */
#define RAPI_ERR_BADSID         3       /* Sid out of legal range.      */
#define RAPI_ERR_N_FFS          4       /* Wrong n_filter/n_flow for style*/
#define RAPI_ERR_BADSTYLE       5       /* Illegal reservation style    */
#define RAPI_ERR_SYSCALL        6       /* Some sort of syscall err; see errno*/
#define RAPI_ERR_OVERFLOW       7       /* Parm list overflow           */
#define RAPI_ERR_MEMFULL        8       /* Not enough memory            */
#define RAPI_ERR_NORSVP         9       /* Daemon doesn't respond/exist.*/
#define RAPI_ERR_OBJTYPE        10      /* Object type error            */
#define RAPI_ERR_OBJLEN         11      /* Object length error          */
#define RAPI_ERR_NOTSPEC        12      /* No sender tspec in rapi_sendr*/
#define RAPI_ERR_INTSERV        13      /* Intserv format error         */
#define RAPI_ERR_GPI_CONFLICT   14      /* IPSEC: Conflicting C-type    */
#define RAPI_ERR_BADPROTO       15      /* IPSEC: Protocol not AH|ESP   */
#define RAPI_ERR_BADVDPORT      16      /* IPSEC: vDstPort is zero      */
#define RAPI_ERR_GPISESS        17      /* IPSEC: Other param error     */

/*  The following occur only asynchronously, as the error value when
 *      error code = 20
 */
#define RAPI_ERR_BADSEND        21      /* Sender addr not my interface */
#define RAPI_ERR_BADRECV        22      /* Recv addr not my interface   */
#define RAPI_ERR_BADSPORT       23      /* Sport != 0 but Dport == 0    */

#define RAPI_ERR_UNSUPPORTED    254
#define RAPI_ERR_UNKNOWN        255

/*
 *      RSVP Error Codes
 */
#define RSVP_Err_NONE           0       /* RESV: Confirmation                */
#define RSVP_Err_ADMISSION      1       /* RESV: Admission control failure   */
#define RSVP_Err_POLICY         2       /* RESV: Policy control failure      */
#define RSVP_Err_NO_PATH        3       /* RESV: No path information         */ 
#define RSVP_Err_NO_SENDER      4       /* RESV: No sender information       */
#define RSVP_Err_BAD_STYLE      5       /* RESV: Conflicting style           */
#define RSVP_Err_UNKNOWN_STYLE  6       /* RESV: Unknown style               */
#define RSVP_Err_BAD_DSTPORT    7       /* Conflicting dest port in Session  */
#define RSVP_Err_BAD_SNDPORT    8       /* PATH: Conflicting src port        */
#define RSVP_Err_BAD_FILTER     9       /* RESV: Ambiguous filter spec       */
#define RSVP_Err_PREEMPTED      12      /* Service preempted                 */
#define RSVP_Err_UNKN_OBJ_CLAS  13      /* Unknown object class              */
#define RSVP_Err_UNKNOWN_CTYPE  14      /* Unknown object C-type             */
#define RSVP_Err_API_ERROR      20      /* API Client error                  */
#define RSVP_Err_TC_ERROR       21      /* Traffic control error             */
#define RSVP_Err_TC_SYS_ERROR   22      /* Traffic control system error      */
#define RSVP_Err_RSVP_SYS_ERROR 23      /* RSVP system error                 */

#endif /* H_RSVP_RAPI */
