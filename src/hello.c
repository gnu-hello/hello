/* hello.c -- print a greeting message and exit.

   Copyright 1992-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

#include <errno.h>
#include <error.h>
#include <getopt.h>
#include <wchar.h>

#include "system.h"

#include "closeout.h"
#include "configmake.h"
#include "dirname.h"
#include "gettext.h"
#include "progname.h"
#include "propername.h"
#include "quote.h"
#include "version-etc.h"

/* The official name of this program (e.g., no 'g' prefix).  */
#define PROGRAM_NAME "hello"

#define AUTHORS \
  proper_name ("Karl Berry"), \
  proper_name ("Sami Kerola"), \
  proper_name ("Jim Meyering"), \
  proper_name ("Reuben Thomas")

/* Print help info.  This long message is split into
   several pieces to help translators be able to align different
   blocks and identify the various pieces.  */
static _Noreturn void
print_help (FILE *restrict out)
{
  /* TRANSLATORS: --help output 1 (synopsis)
     no-wrap */
  fprintf (out, _("Usage: %s [OPTION]...\n"), program_name);
  /* TRANSLATORS: --help output 2 (brief description)
     no-wrap */
  fputs (_("Print a friendly, customizable greeting.\n"), out);
  fputs ("\n", out);
  /* TRANSLATORS: --help output 3: options
     no-wrap */
  fputs (_("  -t, --traditional       use traditional greeting\n"), out);
  fputs (_("  -g, --greeting=TEXT     use TEXT as the greeting message\n"),
         out);
  fputs ("\n", out);
  fputs (_("      --help     display this help and exit\n"), out);
  fputs (_("      --version  output version information and exit\n"), out);
  emit_bug_reporting_address ();
  exit (out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

static void
parse_options (int argc, char *argv[], const char **greeting_msg)
{
  int lose = 0;
  enum { OPT_HELP = CHAR_MAX + 1, OPT_VERSION };
  static const struct option longopts[] = {
    {"greeting", required_argument, NULL, 'g'},
    {"traditional", no_argument, NULL, 't'},
    {"help", no_argument, NULL, OPT_HELP},
    {"version", no_argument, NULL, OPT_VERSION},
    {NULL, 0, NULL, 0}
  };

  for (int c; (c = getopt_long (argc, argv, "g:t", longopts, NULL)) != -1;)
    switch (c)
      {
        /* --help and --version exit immediately, per GNU coding standards.  */
      case OPT_VERSION:
        version_etc (stdout, PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION,
                     AUTHORS, (char *) NULL);
        exit (EXIT_SUCCESS);
      case 'g':
        *greeting_msg = optarg;
        break;
      case OPT_HELP:
        print_help (stdout);
      case 't':
        *greeting_msg = _("hello, world");
        break;
      default:
        lose = 1;
        break;
      }

  if (lose || optind < argc)
    {
      /* Print error message and exit.  */
      if (argv[optind])
        error (0, 0, "%s: %s", _("extra operand"), quote (argv[optind]));
      emit_try_help ();
      exit (EXIT_FAILURE);
    }
}

int
main (int argc, char *argv[])
{
  set_program_name (argv[0]);

  /* Set locale via LC_ALL.  */
  setlocale (LC_ALL, "");

  /* Set the text message domain.  */
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  /* Having initialized gettext, get the default message. */
  const char *greeting_msg = _("Hello, world!");

  /* Even exiting has subtleties.  On exit, if any writes failed, change
     the exit status.  The /dev/full device on GNU/Linux can be used for
     testing; for instance, hello >/dev/full should exit unsuccessfully.
     This is implemented in the Gnulib module "closeout".  */
  atexit (close_stdout);

  parse_options (argc, argv, &greeting_msg);

  mbstate_t mbstate; mbszero (&mbstate);
  size_t len = mbsrtowcs (NULL, &greeting_msg, strlen (greeting_msg) + 1,
                          &mbstate);
  if (len == (size_t) -1)
    error (EXIT_FAILURE, errno, _("conversion to a multibyte string failed"));

  /* Print greeting message and exit.  */
  puts (greeting_msg);

  exit (EXIT_SUCCESS);
}
