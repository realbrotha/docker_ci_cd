/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_AUDIO1575_H_
#define	_SYS_AUDIO1575_H_

#pragma ident	"@(#)audio1575.h	1.2	06/08/31 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Header file for the audio1575 device driver
 */

/*
 * Values returned by the AUDIO_GETDEV ioctl()
 */
#define	M1575_DEV_NAME			"SUNW,audio1575"
#define	M1575_DEV_CONFIG		"onboard1"
#define	M1575_DEV_VERSION		"a"

/*
 * Driver supported configuration information
 */
#define	M1575_NAME			"audio1575"
#define	M1575_MOD_NAME			"mixer audio driver"
#define	M1575_SAMPR5510			(5510)
#define	M1575_SAMPR6620			(6620)
#define	M1575_SAMPR8000			(8000)
#define	M1575_SAMPR9600			(9600)
#define	M1575_SAMPR11025		(11025)
#define	M1575_SAMPR16000		(16000)
#define	M1575_SAMPR18900		(18900)
#define	M1575_SAMPR22050		(22050)
#define	M1575_SAMPR27420		(27420)
#define	M1575_SAMPR32000		(32000)
#define	M1575_SAMPR33075		(33075)
#define	M1575_SAMPR37800		(37800)
#define	M1575_SAMPR44100		(44100)
#define	M1575_SAMPR48000		(48000)

#define	M1575_DEFAULT_SR		M1575_SAMPR8000
#define	M1575_DEFAULT_CH		AUDIO_CHANNELS_MONO
#define	M1575_DEFAULT_PREC		AUDIO_PRECISION_8
#define	M1575_DEFAULT_ENC		AUDIO_ENCODING_ULAW
#define	M1575_DEFAULT_PGAIN		(AUDIO_MAX_GAIN * 3/4)
#define	M1575_DEFAULT_RGAIN		(127)
#define	M1575_DEFAULT_MONITOR_GAIN	(0)
#define	M1575_DEFAULT_BAL		AUDIO_MID_BALANCE
#define	M1575_INTS			(175)	/* default interrupt rate */
#define	M1575_MIN_INTS			(25)	/* minimum interrupt rate */
#define	M1575_MAX_INTS			(5000)	/* maximum interrupt rate */

#ifdef	__cplusplus
}
#endif

#endif /* _SYS_AUDIO1575_H_ */
