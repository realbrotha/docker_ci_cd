/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_FMD_FMRI_H
#define	_FMD_FMRI_H

#pragma ident	"@(#)fmd_fmri.h	1.2	06/03/19 SMI"

#include <sys/types.h>
#include <sys/fm/protocol.h>
#include <libnvpair.h>
#include <errno.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Fault Management Daemon FMRI Scheme Interfaces
 *
 * Note: The contents of this file are private to the implementation of the
 * Solaris system and FMD subsystem and are subject to change at any time
 * without notice.  Applications and drivers using these interfaces will fail
 * to run on future releases.  These interfaces should not be used for any
 * purpose until they are publicly documented for use outside of Sun.
 */

/*
 * The following utility functions (in addition to libnvpair) are provided by
 * fmd to facilitate the implementation of each FMRI scheme library.
 */

struct topo_hdl;

#ifndef	MIN
#define	MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

#ifndef	MAX
#define	MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

extern void *fmd_fmri_alloc(size_t);
extern void *fmd_fmri_zalloc(size_t);
extern void fmd_fmri_free(void *, size_t);

extern int fmd_fmri_set_errno(int);
extern void fmd_fmri_warn(const char *, ...);

extern char *fmd_fmri_auth2str(nvlist_t *);
extern char *fmd_fmri_strescape(const char *);
extern char *fmd_fmri_strdup(const char *);
extern void fmd_fmri_strfree(char *);

extern const char *fmd_fmri_get_rootdir(void);
extern const char *fmd_fmri_get_platform(void);

extern uint64_t fmd_fmri_get_drgen(void);

extern struct topo_hdl *fmd_fmri_topology(int);

/*
 * The following entry points are to be implemented by each scheme:
 */
extern int fmd_fmri_init(void);
extern void fmd_fmri_fini(void);
extern ssize_t fmd_fmri_nvl2str(nvlist_t *, char *, size_t);
extern int fmd_fmri_expand(nvlist_t *);
extern int fmd_fmri_present(nvlist_t *);
extern int fmd_fmri_unusable(nvlist_t *);
extern int fmd_fmri_contains(nvlist_t *, nvlist_t *);
extern nvlist_t *fmd_fmri_translate(nvlist_t *, nvlist_t *);

#ifdef	__cplusplus
}
#endif

#endif	/* _FMD_FMRI_H */
