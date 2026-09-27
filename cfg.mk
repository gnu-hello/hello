# Configuration for maintainer-makefile
#
# Copyright (c) 2012-2026 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

GNULIB_SRCDIR ?= $(srcdir)/gnulib
gnulib_dir = $(GNULIB_SRCDIR)
manual_title = GNU Hello

# This causes tests/init.sh to emit the commands being executed in logs,
# which is useful for investigating failures.
export VERBOSE = yes

# Larger values for the compression level don't seem to help GNU Hello.
# Tested with:
# for e in '' '-e'; do
#   for l in $(seq 0 9); do
#     echo == $e -$l ==;
#     env time -f 'elapsed=%E CPU=%Us Mem=%MKB' \
#       xz -c $e -$l < hello-2.12.3.tar | wc -c;
#   done;
# done
export XZ_OPT = -6e

# Write cksum supported checksums into the announcement.
# I.e., base64 to reduce space, and possibly tagged to ease usage.
announce_gen_args = --cksum-checksums

# Tests not to run as part of "make distcheck".
local-checks-to-skip = \
  sc_indent

# Set format of NEWS
old_NEWS_hash := b6e2880ab51e94270167a5cdaf96441a

update-copyright-env = \
  UPDATE_COPYRIGHT_FORCE=1 \
  UPDATE_COPYRIGHT_USE_INTERVALS=2

# Some words/syntax that 'codespell' doesn't understand.
codespell_ignore_words_list = debbugs,UE

# We don't run 'codespell' on these files.
exclude_file_name_regexp--sc_codespell =  ^THANKS$$
