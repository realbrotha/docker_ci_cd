/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/tokenring_mibs.h 1.8                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)65	1.8  src/bos/kernel/sys/tokenring_mibs.h, snmp, bos530 11/11/03 15:53:34 */
/*
 * COMPONENT_NAME: (SNMP) Simple Network Management Protocol Daemon
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1993, 1994
 * All Rights Reserved
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Licensed Material - Property of IBM
 *
 * FILE:        /usr/include/sys/tokenring_mibs.h
 */

#ifndef _H_TokenRing_MIBS
#define _H_TokenRing_MIBS

#include <sys/machine.h>
#include <sys/generic_mibs.h>


typedef struct  Dot5Entry  {
#define TOKEN_COMMANDS		30
	unsigned short  commands;	/* dot5Commands */
#define TR_MIB_NO_OP	1
#define TR_MIB_OPEN	2
#define TR_MIB_RESET	3
#define TR_MIB_CLOSE	4

#define TOKEN_RING_STATUS	31
	__ulong32_t   ring_status;	/* dot5RingStatus */
#define TR_MIB_NOPROBLEM		0
#define TR_MIB_RINGRECOVERY  		32
#define TR_MIB_SINGLESTATION		64
#define TR_MIB_REMOVE_RX		256
#define TR_MIB_RESERVED			512
#define TR_MIB_AUTOREMOVAL_ERR		1024
#define TR_MIB_LOBEWIREFAULT		2048
#define TR_MIB_TX_BEACON		4096
#define TR_MIB_SOFT_ERR			8192
#define TR_MIB_HARD_ERROR		16384
#define TR_MIB_SIGNAL_LOSS		32768
#define TR_MIB_NO_STATUS		131072

#define TOKEN_RING_STATE	32
	unsigned short  ring_state;	/* dot5RingState */
#define TR_MIB_OPENED		1
#define TR_MIB_CLOSED		2
#define TR_MIB_OPENING		3
#define TR_MIB_CLOSING		4
#define TR_MIB_OPENFAILURE	5
#define TR_MIB_RINGFAILURE	6

#define TOKEN_RING_OSTATUS	33
	unsigned short  ring_ostatus;	/* dot5RingOpenStatus */
#define TR_MIB_NOOPEN			1	/* no open attempted */
#define TR_MIB_BADPARAM		2
#define TR_MIB_LOBEFAILED		3
#define TR_MIB_SIGNALLOSS		4
#define TR_MIB_INSERTIONTIMEOUT	5
#define TR_MIB_RINGFAILED		6
#define TR_MIB_BEACONING		7
#define TR_MIB_DUPLICATEMAC		8
#define TR_MIB_REQUESTFAILED		9
#define TR_MIB_REMOVERECEIVED		10
#define TR_MIB_LASTOPEN			11      /* last open successful */

#define TOKEN_RING_SPEED	34
	unsigned short  ring_speed;	/* dot5RingSpeed */
#define TR_MIB_UNKNOWN		1
#define TR_MIB_ONEMEGABIT	2
#define TR_MIB_FOURMEGABIT	3
#define TR_MIB_SIXTEENMEGABIT	4
#define TR_MIB_HUNDREDMEGABIT	5

#define TOKEN_UPSTREAM		35
	unsigned char   upstream[6];	/* dot5UpStream */
	unsigned short  participate;	/* dot5ActMonParticipate */
#define TR_MIB_TRUE	1
#define TR_MIB_FALSE	2

#define TOKEN_FUNCTIONAL	36
	unsigned char   functional[6];	/* dot5Functional */
}  Dot5Entry_t;


/* The Statistics Table */
typedef struct  Dot5StatsEntry  {
#define TOKEN_LINE_ERRS		40
	__ulong32_t  line_errs;		/* dot5StatsLineErrors */

#define TOKEN_BURST_ERRS	41
	__ulong32_t  burst_errs;	/* dot5StatsBurstErrors */

#define TOKEN_AC_ERRS		42
	__ulong32_t  ac_errs;		/* dot5StatsACErrors */

#define TOKEN_ABORT_ERRS	43
	__ulong32_t  abort_errs;	/* dot5StatsAbortTransErrors */

#define TOKEN_INT_ERRS		44
	__ulong32_t  int_errs;		/* dot5StatsInternalErrors */

#define TOKEN_LOSTFRAMES	45
	__ulong32_t  lostframes;	/* dot5StatsLostFrameErrors */

#define TOKEN_RX_CONGESTION	46
	__ulong32_t  rx_congestion;	/* dot5StatsReceiveCongestions */

#define TOKEN_FRAMECOPIES	47
	__ulong32_t  framecopies;	/* dot5StatsFrameCopiedErrors */

#define TOKEN_TOKEN_ERRS	48
	__ulong32_t  token_errs;	/* dot5StatsTokenErrors */

#define TOKEN_SOFT_ERRS		49
	__ulong32_t  soft_errs;		/* dot5StatsSoftErrors */

#define TOKEN_HARD_ERRS		50
	__ulong32_t  hard_errs;		/* dot5StatsHardErrors */

#define TOKEN_SIGNAL_LOSS	51
	__ulong32_t  signal_loss;	/* dot5StatsSignalLoss */

#define TOKEN_TX_BEACONS	52
	__ulong32_t  tx_beacons;	/* dot5StatsTransmitBeacons */

#define TOKEN_RECOVERYS		53
	__ulong32_t  recoverys;		/* dot5StatsRecoverys */

#define TOKEN_LOBEWIRES		54
	__ulong32_t  lobewires;		/* dot5StatsLobeWires */

#define TOKEN_REMOVES		55
	__ulong32_t  removes;		/* dot5StatsRemoves */

#define TOKEN_SINGLES		56
	__ulong32_t  singles;		/* dot5StatsSingles */

#define TOKEN_FREQ_ERRS		57
	__ulong32_t  freq_errs;		/* dot5StatsFreqErrors */
} Dot5StatsEntry_t;


/* The Timer Table */
typedef struct  Dot5TimerEntry {
#define TOKEN_RETURN_REPEAT	60
	__ulong32_t  return_repeat;	/* dot5TimerReturnRepeat */

#define TOKEN_HOLDING		61
	__ulong32_t  holding;		/* dot5TimerHolding */

#define TOKEN_QUEUE_PDU		62
	__ulong32_t  queue_pdu;		/* dot5TimerQueuePDU */

#define TOKEN_VALID_TX		63
	__ulong32_t  valid_tx;		/* dot5TimerValidTransmit */

#define TOKEN_NO_TOKEN		64
	__ulong32_t  no_token;		/* dot5TimerNoToken */

#define TOKEN_ACTIVE_MON	65
	__ulong32_t  active_mon;	/* dot5TimerActiveMon */

#define TOKEN_STANDBY_MON	66
	__ulong32_t  standby_mon;	/* dot5TimerStandbyMon */

#define TOKEN_ERR_REPORT	67
	__ulong32_t  err_report;	/* dot5TimerErrorReport */

#define TOKEN_BEACON_TX		68
	__ulong32_t  beacon_tx;		/* dot5TimerBeaconTransmit */

#define TOKEN_BEACON_RX		69
	__ulong32_t  beacon_rx;		/* dot5TimerBeaconReceive */
} Dot5TimerEntry_t;

typedef struct token_ring_mib  {
	Dot5Entry_t		Dot5Entry;
	Dot5StatsEntry_t	Dot5StatsEntry;
	Dot5TimerEntry_t	Dot5TimerEntry;
}  token_ring_mib_t;

typedef struct token_ring_all_mib  {
	generic_mib_t		Generic_mib;
	token_ring_mib_t	Token_ring_mib;
} token_ring_all_mib_t;

/* 802.5 Interface Tests */
#define TR_MIB_testInsertFunc    	1

/* 802.5 Hardware Chip Sets -- Dot5ChipSets */
/* IBM 16/4 Mb/s */
#if BYTE_ORDER==BIG_ENDIAN
#define TR_MIB_IBM16		"\000\000\000\012\000\000\000\001\000\000\000\003\000\000\000\006\000\000\000\001\000\000\000\002\000\000\000\001\000\000\000\012\000\000\000\011\000\000\000\004\000\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
#else
#define TR_MIB_IBM16		"\012\000\000\000\001\000\000\000\003\000\000\000\006\000\000\000\001\000\000\000\002\000\000\000\001\000\000\000\012\000\000\000\011\000\000\000\004\000\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
#endif /* BYTE_ORDER==BIG_ENDIAN */

/* TI 4Mb/s */
#if BYTE_ORDER==BIG_ENDIAN
#define TR_MIB_TITMS380		"\000\000\000\012\000\000\000\001\000\000\000\003\000\000\000\006\000\000\000\001\000\000\000\002\000\000\000\001\000\000\000\012\000\000\000\011\000\000\000\004\000\000\000\002\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
#else
#define TR_MIB_TITMS380		"\012\000\000\000\001\000\000\000\003\000\000\000\006\000\000\000\001\000\000\000\002\000\000\000\001\000\000\000\012\000\000\000\011\000\000\000\004\000\000\000\002\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
#endif /* BYTE_ORDER==BIG_ENDIAN */

/* TI 16/4 Mb/s */
#if BYTE_ORDER==BIG_ENDIAN
#define TR_MIB_TITMS380C16 	"\000\000\000\012\000\000\000\001\000\000\000\003\000\000\000\006\000\000\000\001\000\000\000\002\000\000\000\001\000\000\000\012\000\000\000\011\000\000\000\004\000\000\000\003\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
#else
#define TR_MIB_TITMS380C16	"\012\000\000\000\001\000\000\000\003\000\000\000\006\000\000\000\001\000\000\000\002\000\000\000\001\000\000\000\012\000\000\000\011\000\000\000\004\000\000\000\003\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
#endif /* BYTE_ORDER==BIG_ENDIAN */

#endif  /* _H_TokenRing_MIBS */
