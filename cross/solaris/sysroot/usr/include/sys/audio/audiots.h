/*
 * Copyright (c) 2000-2001 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef	_SYS_AUDIOTS_H
#define	_SYS_AUDIOTS_H

#pragma ident	"@(#)audiots.h	1.3	01/03/01 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Header file for the audiots device driver.
 */

/*
 * Values returned by the AUDIO_GETDEV ioctl()
 */
#define	TS_DEV_NAME		"SUNW,audiots"
#define	TS_DEV_CONFIG		"onboard1"
#define	TS_DEV_VERSION_A	"a"		/* grover, sngl strming play */
#define	TS_DEV_VERSION_B	"b"		/* birdsnest, sngl strm play */

/*
 * Driver supported configuration information
 */
#define	TS_NAME			"audiots"
#define	TS_MOD_NAME		"mixer audio driver"

#define	TS_SAMPR4000		(4000)
#define	TS_SAMPR5510		(5510)
#define	TS_SAMPR6620		(6620)
#define	TS_SAMPR8000		(8000)
#define	TS_SAMPR9600		(9600)
#define	TS_SAMPR11025		(11025)
#define	TS_SAMPR16000		(16000)
#define	TS_SAMPR18900		(18900)
#define	TS_SAMPR22050		(22050)
#define	TS_SAMPR27420		(27420)
#define	TS_SAMPR32000		(32000)
#define	TS_SAMPR33075		(33075)
#define	TS_SAMPR37800		(37800)
#define	TS_SAMPR44100		(44100)
#define	TS_SAMPR48000		(48000)

#define	TS_DEFAULT_SR		TS_SAMPR8000
#define	TS_DEFAULT_CH		AUDIO_CHANNELS_MONO
#define	TS_DEFAULT_PREC		AUDIO_PRECISION_8
#define	TS_DEFAULT_ENC		AUDIO_ENCODING_ULAW
#define	TS_DEFAULT_PGAIN	(AUDIO_MAX_GAIN * 3 / 4)
#define	TS_DEFAULT_RGAIN	(127)
#define	TS_DEFAULT_MONITOR_GAIN	(0)
#define	TS_DEFAULT_BAL		AUDIO_MID_BALANCE	/* MUST be mid */
#define	TS_INTS			(175)		/* default interrupt rate */
#define	TS_MIN_INTS		(24)		/* minimum interrupt rate */
#define	TS_MAX_INTS		(2000)		/* maximum interrupt rate */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_AUDIOTS_H */
