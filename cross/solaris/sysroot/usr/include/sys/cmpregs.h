/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_CMPREGS_H
#define	_CMPREGS_H

#pragma ident	"@(#)cmpregs.h	1.2	04/08/24 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#define	ASI_CMP_SHARED		0x41	/* shared CMP registers */
#define	ASI_CMP_PER_CORE	0x63	/* core-local CMP registers */

/*
 * Core ID Register
 *
 *   |-----------------------|
 *   |MAX_CORE_ID|---|CORE_ID|
 *   |-----------------------|
 *    21       16     5     0
 */
#define	ASI_CORE_ID		0x10	/* ASI 0x63, VA 0x10 */
#define	COREID_MASK		0x3f


/*
 * Error Steering Register
 *
 *   |-------|
 *   |CORE_ID|
 *   |-------|
 *    5     0
 */
#define	ASI_CMP_ERROR_STEERING	0x40	/* ASI 0x41, VA 0x40 */

/*
 * Core Running
 *
 *   |------------------------------|
 *   |       |core running (status) |
 *   |------------------------------|
 *            1                    0
 */
#define	ASI_CORE_RUNNING_STATUS	0x58	/* ASI 0x41, VA 0x58 */
#define	ASI_CORE_RUNNING_RW	0x50	/* ASI 0x41, VA 0x50 */

#ifdef	__cplusplus
}
#endif

#endif /* _CMPREGS_H */