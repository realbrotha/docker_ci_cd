#ifndef GCC_TM_H
#define GCC_TM_H
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
# include "config/rs6000/rs6000.h"
# include "config/rs6000/aix.h"
# include "config/rs6000/aix53.h"
# include "config/rs6000/xcoff.h"
# include "config/rs6000/aix-stdint.h"
# include "config/rs6000/option-defaults.h"
# include "config/initfini-array.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE && !defined USED_FOR_TARGET
# include "insn-flags.h"
#endif
# include "defaults.h"
#endif /* GCC_TM_H */
