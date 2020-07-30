/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_LIBSVM_H
#define	_LIBSVM_H

#pragma ident	"@(#)libsvm.h	1.3	05/11/22 SMI"


#ifdef	__cplusplus
extern "C" {
#endif


/*
 * The following declarations are for libsvm which provides
 * Solaris Install with a set of interfaces required to upgrade
 * mirrored roots. These are controlled by a Contract PSARC 2000/049
 * and should not be changed without informing Install.
 */

typedef struct {
	char *root_md;		/* metaroot device name */
	int count;		/* number of components in the metadevice */
	char *md_comps[1];	/* array of "ctds" component names */
} svm_info_t;

/* Convertion of MDDB flags */
#define	SVM_DONT_CONV	0x01	/* Don't convert MDDB to devid mode */
#define	SVM_CONV	0x02	/* Convert MDDB to devid mode */


extern int svm_check(char *rootpath);
extern int svm_start(char *rootpath, svm_info_t **svm_infopp,
			int repl_state_flag);
extern int svm_stop();
extern void svm_free(svm_info_t *svm_infop);
extern int svm_is_md(char *device_name);
extern int svm_get_components(char *root_md_device, svm_info_t **svmpp);
extern svm_info_t *svm_alloc();
extern int get_mdcomponents(char *devname, svm_info_t **pp);

#ifdef	__cplusplus
}
#endif

#endif /* _LIBSVM_H */
