// -*- C++ -*-
/* Copyright (C) 1989, 1990, 1991, 1992, 2000 Free Software Foundation, Inc.
     Written by James Clark (jjc@jclark.com)

This file is part of groff.

groff is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

groff is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with groff; see the file COPYING.  If not, write to the Free Software
Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "lib.h"
#include "searchpath.h"
#include "nonposix.h"

search_path::search_path(const char *envvar, const char *standard,
			 int add_home, int add_current)
{
  char *home = 0;
  if (add_home)
    home = getenv("HOME");
  char *e = 0;
  if (envvar)
    e = getenv(envvar);
  dirs = new char[((e && *e) ? strlen(e) + 1 : 0)
		  + (add_current ? 1 + 1 : 0)
		  + ((home && *home) ? strlen(home) + 1 : 0)
		  + ((standard && *standard) ? strlen(standard) : 0)
		  + 1];
  *dirs = '\0';
  if (e && *e) {
    strcat(dirs, e);
    strcat(dirs, PATH_SEP);
  }
  if (add_current) {
    strcat(dirs, ".");
    strcat(dirs, PATH_SEP);
  }
  if (home && *home) {
    strcat(dirs, home);
    strcat(dirs, PATH_SEP);
  }
  if (standard && *standard)
    strcat(dirs, standard);
  init_len = strlen(dirs);
}

search_path::~search_path()
{
  // dirs is always allocated
  a_delete dirs;
}

void search_path::command_line_dir(const char *s)
{
  char *old = dirs;
  unsigned old_len = strlen(old);
  unsigned slen = strlen(s);
  dirs = new char[old_len + 1 + slen + 1];
  memcpy(dirs, old, old_len - init_len);
  char *p = dirs;
  p += old_len - init_len;
  if (init_len == 0)
    *p++ = PATH_SEP[0];
  memcpy(p, s, slen);
  p += slen;
  if (init_len > 0) {
    *p++ = PATH_SEP[0];
    memcpy(p, old + old_len - init_len, init_len);
    p += init_len;
  }
  *p++ = '\0';
  a_delete old;
}

FILE *search_path::open_file(const char *name, char **pathp)
{
  assert(name != 0);
  if (IS_ABSOLUTE(name) || *dirs == '\0') {
    FILE *fp = fopen(name, "r");
    if (fp) {
      if (pathp)
	*pathp = strsave(name);
      return fp;
    }
    else
      return 0;
  }
  unsigned namelen = strlen(name);
  char *p = dirs;
  for (;;) {
    char *end = strchr(p, PATH_SEP[0]);
    if (!end)
      end = strchr(p, '\0');
    int need_slash = end > p && strchr(DIR_SEPS, end[-1]) == 0;
    char *path = new char[(end - p) + need_slash + namelen + 1];
    memcpy(path, p, end - p);
    if (need_slash)
      path[end - p] = '/';
    strcpy(path + (end - p) + need_slash, name);
#if 0
    fprintf(stderr, "trying `%s'\n", path);
#endif
    FILE *fp = fopen(path, "r");
    if (fp) {
      if (pathp)
	*pathp = path;
      else
	a_delete path;
      return fp;
    }
    a_delete path;
    if (*end == '\0')
      break;
    p = end + 1;
  }
  return 0;
}
