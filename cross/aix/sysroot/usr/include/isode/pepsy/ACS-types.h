/* @(#)52	1.3  src/tcpip/usr/lib/libisode/ACS-types.h, isodelib7, tcpip530 4/5/93 13:32:01 */
/*
 * COMPONENT_NAME: (ISODELIB7) ISODE Libraries, Release 7
 *
 * FUNCTIONS: free_ACS_AARE__apdu free_ACS_AARQ__apdu free_ACS_ABRT__apdu 
 *    free_ACS_ABRT__source free_ACS_ACSE__apdu free_ACS_AE__invocation__id 
 *    free_ACS_AE__title free_ACS_AP__invocation__id free_ACS_Associate__result
 *    free_ACS_Associate__source__diagnostic free_ACS_Association__information 
 *    free_ACS_RLRE__apdu free_ACS_RLRQ__apdu free_ACS_Release__request__reason
 *    free_ACS_Release__response__reason
 *
 * ORIGINS: 60
 *
 * FILE:	src/tcpip/usr/lib/libisode/ACS-types.h
 */


/* automatically generated by pepsy 6.0 #108 (oilers.netmgmt.austin.ibm.com), do not edit! */

#ifndef	_module_ACS_defined_
#define	_module_ACS_defined_

#ifndef	PEPSY_VERSION
#define	PEPSY_VERSION		2
#endif

#include <isode/psap.h>
#include <isode/pepsy.h>
#include <isode/pepsy/UNIV-types.h>

#include <isode/pepsy/ACS_defs.h>

#define	type_ACS_Application__context__name	OIDentifier
#define	free_ACS_Application__context__name	oid_free

#define	type_ACS_AP__title	PElement
#define	free_ACS_AP__title	pe_free

#define	type_ACS_AE__qualifier	PElement
#define	free_ACS_AE__qualifier	pe_free

#define	type_ACS_Implementation__data	type_UNIV_GraphicString
#define	free_ACS_Implementation__data	free_UNIV_GraphicString

struct type_ACS_ACSE__apdu {
    int         offset;
#define	type_ACS_ACSE__apdu_aarq	1
#define	type_ACS_ACSE__apdu_aare	2
#define	type_ACS_ACSE__apdu_rlrq	3
#define	type_ACS_ACSE__apdu_rlre	4
#define	type_ACS_ACSE__apdu_abrt	5

    union {
        struct type_ACS_AARQ__apdu *aarq;

        struct type_ACS_AARE__apdu *aare;

        struct type_ACS_RLRQ__apdu *rlrq;

        struct type_ACS_RLRE__apdu *rlre;

        struct type_ACS_ABRT__apdu *abrt;
    }       un;
};
#define	free_ACS_ACSE__apdu(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZACSE_apduACS], &_ZACS_mod, 1)

struct type_ACS_AARQ__apdu {
    PE      protocol__version;
#define	bits_ACS_protocol__version	"\020\01version1"
#define	bit_ACS_protocol__version_version1	0

    struct type_ACS_Application__context__name *application__context__name;

    struct type_ACS_AP__title *called__AP__title;

    struct type_ACS_AE__qualifier *called__AE__qualifier;

    struct type_ACS_AP__invocation__id *called__AP__invocation__id;

    struct type_ACS_AE__invocation__id *called__AE__invocation__id;

    struct type_ACS_AP__title *calling__AP__title;

    struct type_ACS_AE__qualifier *calling__AE__qualifier;

    struct type_ACS_AP__invocation__id *calling__AP__invocation__id;

    struct type_ACS_AE__invocation__id *calling__AE__invocation__id;

    struct type_ACS_Implementation__data *implementation__information;

    struct type_ACS_Association__information *user__information;
};
#define	free_ACS_AARQ__apdu(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZAARQ_apduACS], &_ZACS_mod, 1)

struct type_ACS_AARE__apdu {
    PE      protocol__version;
#define	bits_ACS_protocol__version	"\020\01version1"
#define	bit_ACS_protocol__version_version1	0

    struct type_ACS_Application__context__name *application__context__name;

    integer     result;
#define	int_ACS_result_accepted	0
#define	int_ACS_result_rejected__permanent	1
#define	int_ACS_result_rejected__transient	2

    struct type_ACS_Associate__source__diagnostic *result__source__diagnostic;

    struct type_ACS_AP__title *responding__AP__title;

    struct type_ACS_AE__qualifier *responding__AE__qualifier;

    struct type_ACS_AP__invocation__id *responding__AP__invocation__id;

    struct type_ACS_AE__invocation__id *responding__AE__invocation__id;

    struct type_ACS_Implementation__data *implementation__information;

    struct type_ACS_Association__information *user__information;
};
#define	free_ACS_AARE__apdu(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZAARE_apduACS], &_ZACS_mod, 1)

struct type_ACS_RLRQ__apdu {
    integer     optionals;
#define	opt_ACS_RLRQ__apdu_reason (000000001)

    integer     reason;
#define	int_ACS_reason_normal	0
#define	int_ACS_reason_urgent	1
#define	int_ACS_reason_user__defined	30

    struct type_ACS_Association__information *user__information;
};
#define	free_ACS_RLRQ__apdu(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZRLRQ_apduACS], &_ZACS_mod, 1)

struct type_ACS_RLRE__apdu {
    integer     optionals;
#define	opt_ACS_RLRE__apdu_reason (000000001)

    integer     reason;
#define	int_ACS_reason_normal	0
#define	int_ACS_reason_not__finished	1
#define	int_ACS_reason_user__defined	30

    struct type_ACS_Association__information *user__information;
};
#define	free_ACS_RLRE__apdu(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZRLRE_apduACS], &_ZACS_mod, 1)

struct type_ACS_ABRT__apdu {
    integer     abort__source;
#define	int_ACS_abort__source_acse__service__user	0
#define	int_ACS_abort__source_acse__service__provider	1

    struct type_ACS_Association__information *user__information;
};
#define	free_ACS_ABRT__apdu(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZABRT_apduACS], &_ZACS_mod, 1)

struct type_ACS_ABRT__source {
    integer     parm;
#define	int_ACS_ABRT__source_acse__service__user	0
#define	int_ACS_ABRT__source_acse__service__provider	1
};
#define	free_ACS_ABRT__source(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZABRT_sourceACS], &_ZACS_mod, 1)

struct type_ACS_AE__title {
    struct type_ACS_AP__title *title;

    struct type_ACS_AE__qualifier *qualifier;
};
#define	free_ACS_AE__title(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZAE_titleACS], &_ZACS_mod, 1)

struct type_ACS_AE__invocation__id {
    integer     parm;
};
#define	free_ACS_AE__invocation__id(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZAE_invocation_idACS], &_ZACS_mod, 1)

struct type_ACS_AP__invocation__id {
    integer     parm;
};
#define	free_ACS_AP__invocation__id(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZAP_invocation_idACS], &_ZACS_mod, 1)

struct type_ACS_Associate__result {
    integer     parm;
#define	int_ACS_Associate__result_accepted	0
#define	int_ACS_Associate__result_rejected__permanent	1
#define	int_ACS_Associate__result_rejected__transient	2
};
#define	free_ACS_Associate__result(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZAssociate_resultACS], &_ZACS_mod, 1)

struct type_ACS_Associate__source__diagnostic {
    int         offset;
#define	type_ACS_Associate__source__diagnostic_acse__service__user	1
#define	type_ACS_Associate__source__diagnostic_acse__service__provider	2

    union {
        integer     acse__service__user;
#define	int_ACS_acse__service__user_null	0
#define	int_ACS_acse__service__user_no__reason__given	1
#define	int_ACS_acse__service__user_application__context__name__not__supported	2
#define	int_ACS_acse__service__user_calling__AP__title__not__recognized	3
#define	int_ACS_acse__service__user_calling__AP__invocation__identifier__not__recognized	4
#define	int_ACS_acse__service__user_calling__AE__qualifier__not__recognized	5
#define	int_ACS_acse__service__user_calling__AE__invocation__id__not__recognized	6
#define	int_ACS_acse__service__user_called__AP__title__not__recognized	7
#define	int_ACS_acse__service__user_called__AP__invocation__identifier__not__recognized	8
#define	int_ACS_acse__service__user_called__AE__qualifier__not__recognized	9
#define	int_ACS_acse__service__user_called__AE__invocation__id__not__recognized	10

        integer     acse__service__provider;
#define	int_ACS_acse__service__provider_null	0
#define	int_ACS_acse__service__provider_no__reason__given	1
#define	int_ACS_acse__service__provider_no__common__acse__version	2
    }       un;
};
#define	free_ACS_Associate__source__diagnostic(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZAssociate_source_diagnosticACS], &_ZACS_mod, 1)

struct type_ACS_Association__information {
        struct	type_UNIV_EXTERNAL	*EXTERNAL;

        struct type_ACS_Association__information *next;
};
#define	free_ACS_Association__information(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZAssociation_informationACS], &_ZACS_mod, 1)

struct type_ACS_Release__request__reason {
    integer     parm;
#define	int_ACS_Release__request__reason_normal	0
#define	int_ACS_Release__request__reason_urgent	1
#define	int_ACS_Release__request__reason_user__defined	30
};
#define	free_ACS_Release__request__reason(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZRelease_request_reasonACS], &_ZACS_mod, 1)

struct type_ACS_Release__response__reason {
    integer     parm;
#define	int_ACS_Release__response__reason_normal	0
#define	int_ACS_Release__response__reason_not__finished	1
#define	int_ACS_Release__response__reason_user__defined	30
};
#define	free_ACS_Release__response__reason(parm)\
	(void) fre_obj((char *) parm, _ZACS_mod.md_dtab[_ZRelease_response_reasonACS], &_ZACS_mod, 1)
#endif
