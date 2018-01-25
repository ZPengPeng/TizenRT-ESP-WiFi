/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/****************************************************************************
 * include/sys/types.h
 *
 *   Copyright (C) 2007-2009, 2011-2012, 2014 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __INCLUDE_SYS_TYPES_H
#define __INCLUDE_SYS_TYPES_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>
#include <tinyara/compiler.h>

#ifndef __ASSEMBLY__
#include <stdint.h>
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Alternative values for type bool (for historic reasons) */

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* NULL is usually defined in stddef.h (which includes this file) */

#ifndef NULL
/* SDCC is sensitive to NULL pointer type conversions, and C++ defines
 * NULL as zero
 */

#if defined(SDCC) || defined(__cplusplus)
#define NULL (0)
#else
#define NULL ((void*)0)
#endif
#endif

/* POSIX-like OS return values: */

#if !defined(__cplusplus)
#undef  ERROR
#define ERROR -1
#endif

#undef  OK
#define OK 0

/* HPUX-like MIN/MAX value */

#define PRIOR_RR_MIN      0
#define PRIOR_RR_MAX    255
#define PRIOR_FIFO_MIN    0
#define PRIOR_FIFO_MAX  255
#define PRIOR_OTHER_MIN   0
#define PRIOR_OTHER_MAX 255

/* Scheduling Priorities.  NOTE:  Only the idle task can take
 * the true minimum priority. */

#define SCHED_PRIORITY_MAX     255
#define SCHED_PRIORITY_DEFAULT 100
#define SCHED_PRIORITY_MIN       1
#define SCHED_PRIORITY_IDLE      0

/****************************************************************************
 * Type Declarations
 ****************************************************************************/

#ifndef __ASSEMBLY__

typedef unsigned long __kernel_size_t;

#ifdef CONFIG_ENABLE_IOTIVITY

typedef int wint_t;
typedef unsigned short __kernel_sa_family_t;
typedef unsigned short __u16;

/*****************************************************************
 *      Link layer specific messages.
 ****/

/* struct ifinfomsg
 * passes link level specific information, not dependent
 * on network protocol.
 */

struct ifinfomsg {
	unsigned char ifi_family;
	unsigned char __ifi_pad;
	unsigned short ifi_type;	/* ARPHRD_* */
	int ifi_index;				/* Link index   */
	unsigned ifi_flags;			/* IFF_* flags  */
	unsigned ifi_change;		/* IFF_* change mask */
};
#endif

typedef unsigned int __u32;

/* Floating point types */

typedef float float32;
#ifndef CONFIG_HAVE_DOUBLE
typedef float double_t;
typedef float float64;
#else
typedef double double_t;
typedef double float64;
#endif

/* Misc. scalar types */

/* mode_t is an integer type used for file attributes.  mode_t needs
 * to be at least 16-bits but, in fact must be sizeof(int) because it is
 * pased via varargs.
 */

typedef unsigned int mode_t;

/* size_t is used for sizes of memory objects.
 * ssize_t is used for a count of bytes or an error indication.
 *
 * REVISIT: size_t belongs in stddef.h
 */

#ifdef CONFIG_SMALL_MEMORY

typedef uint16_t size_t;
typedef int16_t ssize_t;
typedef uint16_t rsize_t;

#else							/* CONFIG_SMALL_MEMORY */

typedef uint32_t size_t;
typedef int32_t ssize_t;
typedef uint32_t rsize_t;

#endif							/* CONFIG_SMALL_MEMORY */

/* uid_t is used for user IDs
 * gid_t is used for group IDs.
 */

typedef int16_t uid_t;
typedef int16_t gid_t;

/* dev_t is used for device IDs */

typedef uint16_t dev_t;

/* ino_t is used for file serial numbers */

typedef uint16_t ino_t;

/* pid_t is used for process IDs and process group IDs. It must be signed because
 * negative PID values are used to represent invalid PIDs.
 */

typedef int16_t pid_t;

/* id_t is a general identifier that can be used to contain at least a pid_t,
 * uid_t, or gid_t.
 */

typedef int16_t id_t;

/* Unix requires a key of type key_t defined in file sys/types.h for requesting
 * resources such as shared memory segments, message queues and semaphores. A key
 * is simply an integer of type key_t
 */

typedef int16_t key_t;

/* Signed integral type of the result of subtracting two pointers */

typedef intptr_t ptrdiff_t;

#ifndef CONFIG_WCHAR_BUILTIN
/* Wide, 16-bit character types.  wchar_t is a built-in type in C++ and
 * its declaration here may cause compilation errors on some compilers
 * if -DCONFIG_WCHAR_BUILTIN is not included in the CXXFLAGS.
 *
 * REVISIT: wchar_t belongs in stddef.h
 */

typedef uint16_t wchar_t;
#endif

/* blkcnt_t and off_t are signed integer types.
 *
 *   blkcnt_t is used for file block counts.
 *   off_t is used for file offsets and sizes.
 *   fpos_t is used for file positions.
 *
 * Hence, all should be independent of processor architecture.
 */

typedef uint32_t blkcnt_t;
typedef int32_t off_t;
typedef off_t fpos_t;

#ifdef CONFIG_HAVE_LONG_LONG
/* Large file versions */

typedef int64_t off64_t;
typedef int64_t fpos64_t;
#endif

/* blksize_t is a signed integer value used for file block sizes */

typedef int16_t blksize_t;

/* Network related */

typedef unsigned int socklen_t;
typedef uint16_t sa_family_t;

/* Used for system times in clock ticks */

typedef uint32_t clock_t;

/* The type useconds_t shall be an unsigned integer type capable of storing
 * values at least in the range [0, 1000000]. The type suseconds_t shall be
 * a signed integer type capable of storing values at least in the range
 * [-1, 1000000].
 */

typedef uint32_t useconds_t;
typedef int32_t suseconds_t;

/* BSD types provided only to support porting to TinyAra. */

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

/* SYSV types provided only to support porting to TinyAra.  */

typedef unsigned char unchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef signed char s_char;
typedef FAR char *caddr_t;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

/* Task entry point */

typedef CODE int (*main_t)(int argc, char *argv[]);

/* pre-init application task entry point */

typedef CODE int (*preapp_main_t)(int argc, char *argv[]);

#endif

/****************************************************************************
 * Global Function Prototypes
 ****************************************************************************/

#endif							/* __INCLUDE_SYS_TYPES_H */
