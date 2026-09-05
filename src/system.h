/* system.h: system-dependent declarations; include this first.

   Copyright 1996-2026 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#ifndef HELLO_SYSTEM_H
# define HELLO_SYSTEM_H

/* Assume ANSI C89 headers are available.  */
# include <limits.h>
# include <locale.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* Use POSIX headers.  If they are not available, we use the substitute
   provided by gnulib.  */
# include <getopt.h>
# include <unistd.h>

/* Unicode. */
#include <wchar.h>
#include <wctype.h>

/* Take care of NLS matters.  */

#include "gettext.h"
#if ! ENABLE_NLS
# undef textdomain
# define textdomain(Domainname) /* empty */
# undef bindtextdomain
# define bindtextdomain(Domainname, Dirname) /* empty */
#endif

#define _(msgid) gettext (msgid)
#define N_(msgid) msgid

/* Check for errors on write.  */
# include "closeout.h"

/* Use unlocked FILE stream functions.  */
#include "unlocked-io.h"

/* Use a macro rather than an inline function, as this references
   the global program_name, which causes dynamic linking issues
   in libstdbuf.so on some systems where unused functions
   are not removed by the linker.  */
#define emit_try_help() \
  do \
    { \
      fprintf (stderr, _("Try '%s --help' for more information.\n"), \
               program_name); \
    } \
  while (0)

#endif /* HELLO_SYSTEM_H */
