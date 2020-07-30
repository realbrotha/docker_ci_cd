/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/audio.h 1.5.1.3                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,2000          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)22	1.5.1.3  src/bos/kernel/sys/audio.h, sysxacpa, bos530 8/11/00 14:02:19 */
/*
 * COMPONENT_NAME: SYSXACPA - Multimedia Audio Capture and Playback Adapter
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991, 2000
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_AUDIO
#define _H_AUDIO

#include <sys/param.h>

/* These are the defined ioctl control operations */
#define AUDIO_INIT               0     /* initialize adapter characteristics */
#define AUDIO_STATUS             1     /* obtain current adapter status */
#define AUDIO_CONTROL            2     /* change adapter characteristics */
#define AUDIO_BUFFER             3     /* query buffer status */
#define AUDIO_LOAD               4     /* load DSP code */
#define AUDIO_WAIT               5     /* let kernel write buffers drain */
#define AUDIO_SET_CHANNELS       10    /* control hardware settings */
#define AUDIO_GET_CHANNELS       11    /* query hardware settings */
#define AUDIO_CHANNEL_STATUS     12    /* query current hardware state */
#ifdef AUDIO_ENABLE_NOTIFY
#define AUDIO_NOTIFY             13    /* request signal at event */
#endif /* AUDIO_ENABLE_NOTIFY */
#define AUDIO_SET_GAIN           14    /* change capture gain */
#define AUDIO_MODIFY_LIMITS      20    /* change settings for limits */
#define AUDIO_MASTER_VOLUME      21    /* master volume in percentage */

#define AUDIO_LOAD_PATH   MAXPATHLEN   /* max # of chars in DSP path */

/* This is the definition for information about a sampling rate. */
typedef struct _audio_init
{
  int srate;                           /* the sampling rate in Hz */
  int bits_per_sample;                 /* the number of bits per sample */
  int bsize;                           /* block size for this rate */
  int mode;                            /* PCM, ADPCM, ADPCMS, etc. */
  int channels;                        /* number of audio channels */
  int position_resolution;             /* smallest increment for position */
  char loadpath[AUDIO_LOAD_PATH];      /* path of DSP code to be loaded */
  unsigned int flags;                  /* variable, fixed, etc. */
  unsigned int operation;              /* the desired operation */
  int rc;                              /* return code for requested op */
  int slot_number;                     /* slot number of the adapter */
  int device_id;                       /* adapter identification number */
  unsigned int reserved;               /* reserved pointer */
} audio_init;

/* These are the defined values for audio_init.mode. */
#define AUDIO_ADPCM              1               
#define AUDIO_PCM                2              
#define AUDIO_MU_LAW             3     /* mu-law */
#define AUDIO_A_LAW              5
#define AUDIO_SOURCE_MIX         6
#define AUDIO_IMA_ADPCM          13
#define AUDIO_ANALOG_MIX         50

/* The following defines can be used as input information in */
/* audio_init.flags. */
#define AUDIO_FIXED              ( 1 << 0 )    /* fixed length data */
#define AUDIO_LEFT_ALIGNED       ( 1 << 1 )    /* variable length data */
#define AUDIO_RIGHT_ALIGNED      ( 1 << 2 )    /* variable length data */
#define AUDIO_TWOS_COMPLEMENT    ( 1 << 3 )    /* 2's complement data */
#define AUDIO_SIGNED             ( 1 << 4 )    /* unsigned data */
#define AUDIO_BIG_ENDIAN         ( 1 << 5 )    /* high order bit is to */
                                               /* the left [MSB] */

/* The following flags are returned by AUDIO_INIT as output information */
/* in audio_init.flags. */
#define AUDIO_PITCH              ( 1 << 20 )   /* picth is supported */
#define AUDIO_INPUT              ( 1 << 21 )   /* input is supported */
#define AUDIO_OUTPUT             ( 1 << 22 )   /* output is supported */
#define AUDIO_MONITOR            ( 1 << 23 )   /* monitor is supported */
#define AUDIO_VOLUME             ( 1 << 24 )   /* volume is supported */
#define AUDIO_VOLUME_DELAY       ( 1 << 25 )   /* volume delay is supported */
#define AUDIO_BALANCE            ( 1 << 26 )   /* balance is supported */
#define AUDIO_BALANCE_DELAY      ( 1 << 27 )   /* balance delay is supported */
#define AUDIO_TREBLE             ( 1 << 28 )   /* treble control is supported */
#define AUDIO_BASS               ( 1 << 29 )   /* bass control is supported */
#define AUDIO_BESTFIT_PROVIDED   ( 1 << 30 )   /* best fit returned */
#define AUDIO_LOAD_CODE          ( 1 << 31 )   /* DSP load needed */

/* These are the defined values for audio.init.operation. */
#define AUDIO_PLAY               1
#define AUDIO_RECORD             2

/* These are the defined values for audio_init.rc. */
#define AUDIO_NO_PLAY            1     /* DSP code can't do play requests */
#define AUDIO_NO_RECORD          2     /* DSP code can't do record requests */
#define AUDIO_INVALID_REQUEST    4     /* request was invalid */
#define AUDIO_CONFLICT           5     /* conflict with open's flags */
#define AUDIO_OVERLOADED         6     /* out of DSP MIPS or memory */

#define AUDIO_IGNORE            -1     /* ignore this field */

/* These are the defined values for audio_init.device_id. */
#define AUDIO_MACPA              2     /* this is the supported adapter */
#define AUDIO_BASE_4231          0x100 /* CS4231 codec on the planar */
#define AUDIO_MCA_4231           0x101 /* CS4231 codec on an adapter */

#define AUDIO_INIT_BUFFER_REQUEST  100 /* request for additional */
                                       /* device initialization */

typedef struct _audio_init_buf_req
{
  int buffer_size;                     /* user-specified size of kernel */
                                       /* queue for this operation */
  int play_block_count;                /* # of blocks to accumulate */
                                       /* before starting playback */
  int play_lower_limit;                /* unblock select only when this */
                                       /* number of bytes remains in the */
                                       /* playback kernel buffer */
  int cap_upper_limit;                 /* unblock select when this number */
                                       /* of bytes is in the capture */
                                       /* kernel buffer */
  int byte_count;                      /* unblock select when this number of */
                                       /* bytes has been processed */
  int return_code;                     /* 0 if no error; non-zero otherwise */
} audio_init_buf_req;

/* This is used when changing the adapter state. */
typedef struct _audio_change
{
  void *dev_info;                      /* ptr to device dependent info */
  int input;                           /* the new input source */
  int output;                          /* the new output */
  int monitor;                         /* the new monitor state */
  int volume;                          /* the new volume level */
  int volume_delay;                    /* the new volume delay */
  int balance;                         /* the new balance */
  int balance_delay;                   /* the new balance delay */
  int treble;                          /* the new treble state */
  int bass;                            /* the new bass state */
  int pitch;                           /* the new pitch state */
} audio_change;

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

/* These are the values defined for audio_change.input. */
#define AUDIO_HIGH_GAIN_MIKE     0
#define AUDIO_LINE_1             1
#define AUDIO_LINE_2             2
#define AUDIO_LINES_1AND2        3
#define AUDIO_LOW_GAIN_MIKE      4
#define AUDIO_AUX1               100
#define AUDIO_AUX2               101
#define AUDIO_AUX1_LEFT          206
#define AUDIO_AUX1_RIGHT         207
#define AUDIO_AUX2_LEFT          208
#define AUDIO_AUX2_RIGHT         209
#define AUDIO_RECORD_MONITOR     250
#define AUDIO_ALL_LINES          0xFFFFFFF

/* These are the values defined for audio_change.output. */
#define AUDIO_EXTERNAL_SPEAKER      1   /* external speaker */
#define AUDIO_INTERNAL_SPEAKER      2   /* internal speaker */
#define AUDIO_OUTPUT_1              4   /* first output */
#define AUDIO_INTERNAL_SPEAKER_ON   10  /* turn on codec to internal spkr */
#define AUDIO_INTERNAL_SPEAKER_OFF  11  /* turn off codec to internal spkr */
#define AUDIO_INTERNAL_AUDIO_ON     12  /* turn on all internal audio */
#define AUDIO_INTERNAL_AUDIO_OFF    13  /* turn off all internal audio */

/* These are the values defined for audio_change.monitor. */
#define AUDIO_MONITOR_OFF           0  /* no monitoring */
#define AUDIO_MONITOR_UNCOMPRESSED  1  /* uncompressed monitoring */
#define AUDIO_MONITOR_COMPRESSED    2  /* compressed monitoring */

/* This is the definition for information about the adapter's current state. */
typedef struct _audio_status
{
  int srate;                           /* the sampling rate in Hz */
  int bits_per_sample;                 /* the number of bits per sample */
  int bsize;                           /* block size for this rate */
  int mode;                            /* PCM, ADPCM, MU_LAW, etc. */
  int channels;                        /* number of audio channels */
  unsigned int flags;                  /* various flags */
  unsigned int operation;              /* the current operation in progress */
  audio_change change;                 /* status of input, output, etc. */
} audio_status;

/* These are the values defined for operation. */
#define AUDIO_STOPPED            0     /* no operation is in progress */
#define AUDIO_PLAYING            1     /* playback mode is on */
#define AUDIO_RECORDING          2     /* record mode is on */
#define AUDIO_UNINITIALIZED      0xFFFFFFFF  /* adapter is uninitialized */

/* This is the definition that defines an AUDIO_CONTROL request. */
typedef struct _audio_control
{
  unsigned int ioctl_request;          /* the desired ioctl request */
  void *request_info;                  /* the request specifics */
  unsigned int position;               /* # of units before executing it */
  int return_code;                     /* contains any error code */
} audio_control;

/* These are the values defined for audio_control.ioctl_request. */
#define AUDIO_CHANGE             0     /* change adapter characteristics */
#define AUDIO_START              1     /* start new operation */
#define AUDIO_STOP               2     /* stop current operation */
#define AUDIO_PAUSE              3     /* suspend the current operation */
#define AUDIO_RESUME             4     /* resume a suspended operation */

/* This is the definition for information about the buffer state. */
typedef struct _audio_buffer
{
  unsigned int flags;                  /* indicates whether error occurred */
  unsigned int read_buf_size;          /* # of bytes in read queue */
  unsigned int write_buf_size;         /* # of bytes in write queue */
  unsigned int read_buf_time;          /* # of milliseconds in read queue */
  unsigned int write_buf_time;         /* # of milliseconds in write queue */
  unsigned int read_buf_max;           /* max # of bytes ever in read queue */
  unsigned int write_buf_max;          /* max # of bytes ever in write queue */
  unsigned int position;               /* # of milliseconds since last START */
  unsigned int position_type;          /* type of unit associated with */
                                       /* the position field */
  int read_buf_cap;                    /* max capacity of read queue */
  int write_buf_cap;                   /* max capacity of write queue */
  int request_buf_cap;                 /* max number of requests that can be */
                                       /* enqueued */
} audio_buffer;

/* These are the possible error states that can be flagged in */
/* audio_buffer.flags. */
#define AUDIO_UNDERRUN           ( 1 << 0 )  /* indicates underflow occurred */
#define AUDIO_OVERRUN            ( 1 << 1 )  /* indicates overflow occurred */
#define AUDIO_FIFO_UNDERRUN      ( 1 << 2 )  /* indicates underflow occurred */
#define AUDIO_FIFO_OVERRUN       ( 1 << 3 )  /* indicates overflow occurred */

/* These are the possible meanings for audio_buffer.position_type. */
#define AUDIO_POS_MSECS       0              /* position value is milliseconds */

/* This is the structure used in conjunction with the AUDIO_LOAD command. */
/* When used, the application loads the file specified by the device */
/* driver into the memory buffer described by the audio_load structure. */
typedef struct _audio_load
{
  char *buffer;                        /* ptr to buffer where code has */
                                       /* been loaded */
  unsigned int size;                   /* number of bytes in buffer */
  unsigned int flags;                  /* contains flags about buffer */
} audio_load;

#define AUDIO_LOAD_START         1     /* 1st part of buffer to load */
#define AUDIO_LOAD_END           2     /* last part of buffer to load */

/* Number of channel types */
#define AUDIO_MAX_TABLE_SIZE     30

/* Mute flags */
#define AUDIO_INPUT_MUTE_OFF     0
#define AUDIO_INPUT_MUTE_ON      1
#define AUDIO_OUTPUT_MUTE_OFF    2
#define AUDIO_OUTPUT_MUTE_ON     3

/* Structures used in conjunction with the AUDIO_SET_CHANNELS ioctl. */
typedef struct _audio_channel_setting
{
  unsigned int channel_type;           /* channel specification */
  unsigned int channel;                /* left, right channel */
  unsigned int channel_gain;           /* gain or attenuation level */
  unsigned int gain_delay;             /* milliseconds delay */
  unsigned int mute;                   /* mute on or off */
} audio_channel_setting;

typedef struct _audio_channels_list
{
  int size;                            /* number of elements */
  audio_channel_setting *csptr;        /* address of first */
                                       /* audio_channel_setting element */
} audio_channels_list;

/* Structure used in conjunction with the AUDIO_GET_CHANNELS ioctl. */
typedef struct _audio_get_channels
{
  unsigned int device_owner;           /* ID of the device owner */
  int device_id;                       /* device id */
  unsigned int driver_version;         /* driver software version number */
  unsigned int channel_count;          /* number of initialized entries */
                                       /* in channel_type[] upon return */
  unsigned int channel_type[AUDIO_MAX_TABLE_SIZE]; /* channel specification */
  unsigned int support[AUDIO_MAX_TABLE_SIZE];  /* bit field of the hardware */
                                       /* functions available on a channel */
  unsigned int rate_count;             /* number of initialized entries */
                                       /* in rates[] upon return */
  unsigned int rates[AUDIO_MAX_TABLE_SIZE];  /* table of supported sampling rates */
  unsigned int format_count;           /* number of initialized entries in */
                                       /* formats[] upon return */
  unsigned int formats[AUDIO_MAX_TABLE_SIZE];  /* table of supported data formats */
  int return_code;                     /* specific error return code */
  unsigned int reserved;
} audio_get_channels;

/* audio_get_channels.device_id values */
#define AUDIO_BASE_4231          0x100
#define AUDIO_ADAPTER_4231       0x101

/* valid audio_get_channels.channel_type values */
#define AUDIO_HIGH_GAIN_MIC      0
#define AUDIO_LOW_GAIN_MIC       1
#define AUDIO_LINE1_IN           10
#define AUDIO_MONO_IN            50
#define AUDIO_AUX1_IN            60
#define AUDIO_AUX2_IN            61
#define AUDIO_HOST_INPUT         90
#define AUDIO_LINE1_OUT          100
#define AUDIO_MONO_OUT           140
#define AUDIO_HOST_OUTPUT        160

/* valid audio_get_channels.support values */
#define AUDIO_LEFT_CHANNEL       ( 1 << 0 )   /* left channel is available */
#define AUDIO_RIGHT_CHANNEL      ( 1 << 1 )   /* right channel is available */
#define AUDIO_MUTE               ( 1 << 2 )   /* mute can be set */
#define AUDIO_GAIN               ( 1 << 3 )   /* gain level can be set */
#define AUDIO_GAIN_DELAY         ( 1 << 4 )   /* gain delay can be set */

typedef struct _audio_channel_status
{
  unsigned int channel_count;  /* number of initialized entries */
                               /* in the table of inputs and outputs. */
  unsigned int channel_type[AUDIO_MAX_TABLE_SIZE]; /* channel specification */
  unsigned int channel[AUDIO_MAX_TABLE_SIZE];      /* left or right channel */
  unsigned int gain[AUDIO_MAX_TABLE_SIZE];         /* gain setting */
  unsigned int gain_delay[AUDIO_MAX_TABLE_SIZE];   /* gain delay setting */
  unsigned int mute[AUDIO_MAX_TABLE_SIZE];         /* mute on or off setting */
  int master_volume;                         /* setting for master volume */
  int return_code;                           /* error return code */
  unsigned int reserved;
} audio_channel_status;

/* The following defines are used in conjunction with poll(). */
/* They are in addition to POLLIN, POLLOUT, and POLLPRI. */
#define POLL_AUDIO_DATA_MOVEMENT 0x0100  /* data movement has occurred */
#define POLL_AUDIO_BUFFER_LIMIT  0x0200  /* buffer limit reached */
#define POLL_AUDIO_INTERRUPT     0x0400  /* interrupt has occurred */

#ifdef AUDIO_ENABLE_NOTIFY
/* The following defines are used with the AUDIO_NOTIFY ioctl */
#define AUDIO_BYTE_MOVEMENT    (1<<0)  /* notification based on byte movement */
#define AUDIO_TIME_MOVEMENT    (1<<1)  /* notification based on time passage */
#define AUDIO_PLAY_LOWER_LIMIT (1<<2)  /* notify when play buffer has only */
                                       /* specified number of bytes left */
#define AUDIO_CAP_UPPER_LIMIT  (1<<3)  /* notify when capture buffer now */
                                       /* contains specified number of bytes */
#define AUDIO_UNDERRUN_EVENT   (1<<4)  /* notify upon underrun condition */
#define AUDIO_OVERRUN_EVENT    (1<<5)  /* notify upon overrun condition */

typedef struct _audio_notify
{
  unsigned int notify_event;    /* the notification event type */
  int signal;                   /* the signal to be used for notification */
  unsigned int interval;        /* the interval of the notification event */
  int return_code;              /* error return code */
} audio_notify;
#endif /* AUDIO_ENABLE_NOTIFY */

/* This structure is used with the AUDIO_SET_GAIN ioctl. */
typedef struct _audio_set_gain
{
  signed int left_gain;           /* gain setting for left channel */
  signed int right_gain;          /* gain setting for right channel */
} audio_set_gain;

/* This is the definition for information about a track's settings. */
typedef struct _audio_track_info
{
  unsigned short master_volume;   /* the master volume setting */
  unsigned short dither_percent;  /* 0 - 100 are valid percentages */
  unsigned short reserved[3];     /* reserved fields */
} audio_track_info;


/*  Potential Name Collisions
 *  The audio.h header file has been shipping in /usr/include/sys for a 
 *  long time.  Many of the symbols that have been defined in it (below) 
 *  include very common names for which name collisions are likely.  This 
 *  version is written such that existing code, using the old symbols, will 
 *  be compatible.  If name collisions occur, define the symbol 
 *  __AUDIO_AVOID_COLLISIONS and use the new names defined above.
 */
#ifndef __AUDIO_AVOID_COLLISIONS

#define LOAD_PATH               AUDIO_LOAD_PATH
#define ADPCM                   AUDIO_ADPCM
#define PCM                     AUDIO_PCM
#define MU_LAW                  AUDIO_MU_LAW
#define A_LAW                   AUDIO_A_LAW
#define SOURCE_MIX              AUDIO_SOURCE_MIX

#define FIXED                   AUDIO_FIXED
#define LEFT_ALIGNED            AUDIO_LEFT_ALIGNED
#define RIGHT_ALIGNED           AUDIO_RIGHT_ALIGNED
#define TWOS_COMPLEMENT         AUDIO_TWOS_COMPLEMENT
#define SIGNED                  AUDIO_SIGNED

#define PITCH                   AUDIO_PITCH
#define INPUT                   AUDIO_INPUT
#define OUTPUT                  AUDIO_OUTPUT
#define MONITOR                 AUDIO_MONITOR
#define VOLUME                  AUDIO_VOLUME
#define VOLUME_DELAY            AUDIO_VOLUME_DELAY
#define BALANCE                 AUDIO_BALANCE
#define BALANCE_DELAY           AUDIO_BALANCE_DELAY
#define TREBLE                  AUDIO_TREBLE
#define BASS                    AUDIO_BASS
#define BESTFIT_PROVIDED        AUDIO_BESTFIT_PROVIDED
#define LOAD_CODE               AUDIO_LOAD_CODE

#define PLAY                    AUDIO_PLAY
#define RECORD                  AUDIO_RECORD

#define NO_PLAY                 AUDIO_NO_PLAY
#define NO_RECORD               AUDIO_NO_RECORD
#define INVALID_REQUEST         AUDIO_INVALID_REQUEST
#define CONFLICT                AUDIO_CONFLICT
#define OVERLOADED              AUDIO_OVERLOADED

#define MACPA                   AUDIO_MACPA

#define HIGH_GAIN_MIKE          AUDIO_HIGH_GAIN_MIKE
#define LINE_1                  AUDIO_LINE_1
#define LINE_2                  AUDIO_LINE_2
#define LINES_1AND2             AUDIO_LINES_1AND2
#define LOW_GAIN_MIKE           AUDIO_LOW_GAIN_MIKE
#define ALL_LINES               AUDIO_ALL_LINES

#define EXTERNAL_SPEAKER        AUDIO_EXTERNAL_SPEAKER
#define INTERNAL_SPEAKER        AUDIO_INTERNAL_SPEAKER
#define OUTPUT_1                AUDIO_OUTPUT_1

#define MONITOR_OFF             AUDIO_MONITOR_OFF
#define MONITOR_UNCOMPRESSED    AUDIO_MONITOR_UNCOMPRESSED
#define MONITOR_COMPRESSED      AUDIO_MONITOR_COMPRESSED

#define STOPPED                 AUDIO_STOPPED
#define PLAYING                 AUDIO_PLAYING
#define RECORDING               AUDIO_RECORDING
#define UNINITIALIZED           AUDIO_UNINITIALIZED

#define POS_MSECS               AUDIO_POS_MSECS

#define LOAD_START              AUDIO_LOAD_START
#define LOAD_END                AUDIO_LOAD_END

#endif


/*  The following header file provides compatibility for applications 
 *  that wrote directly to the audio device driver using the audio.h
 *  file as defined by Ultimedia Services for AIX (which was NOT the 
 * version shipping as /usr/include/sys/audio.h).
 */
#ifdef __COMPAT_WITH_UMS_AUDIO_H
#include <sys/audio_ums_compat.h>
#endif

#endif /* _H_AUDIO */
