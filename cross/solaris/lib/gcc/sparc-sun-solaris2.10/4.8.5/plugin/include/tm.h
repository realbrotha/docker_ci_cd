#ifndef GCC_TM_H
#define GCC_TM_H
#define TARGET_CPU_DEFAULT (TARGET_CPU_v9)
#ifndef LIBC_GLIBC
# define LIBC_GLIBC 1
#endif
#ifndef LIBC_UCLIBC
# define LIBC_UCLIBC 2
#endif
#ifndef LIBC_BIONIC
# define LIBC_BIONIC 3
#endif
#ifdef IN_GCC
# include "options.h"
# include "insn-constants.h"
# include "config/sparc/biarch64.h"
# include "config/usegas.h"
# include "config/usegld.h"
# include "config/vxworks-dummy.h"
# include "config/sparc/sparc.h"
# include "config/dbxelf.h"
# include "config/elfos.h"
# include "config/sparc/sysv4.h"
# include "config/sol2.h"
# include "config/sparc/sol2.h"
# include "config/sol2-10.h"
# include "config/sol2-bi.h"
# include "config/sparc/tso.h"
# include "config/initfini-array.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE && !defined USED_FOR_TARGET
# include "insn-flags.h"
#endif
# include "defaults.h"
#endif /* GCC_TM_H */
