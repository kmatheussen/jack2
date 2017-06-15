/*
 Copyright (C) 2004-2008 Grame

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

 */


#ifndef __JackCompilerDeps_WIN32__
#define __JackCompilerDeps_WIN32__

#define	LIB_EXPORT __declspec(dllexport)

#ifdef SERVER_SIDE
    #define	SERVER_EXPORT __declspec(dllexport)
#else
    #define	SERVER_EXPORT
#endif

#if __GNUC__

    #define MEM_ALIGN(x,y) x __attribute__((aligned(y)))
    
#else

    #define MEM_ALIGN(x,y) x
 
#endif

#if defined(_MSC_VER) /* Added by JE - 31-01-2012 */
#define vsnprintf _vsnprintf
#define snprintf _snprintf
#define strdup _strdup
#endif

#if defined(__MINGW32__)

// Simple implementations of setenv and unsetenv using _putenv.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static inline int setenv(const char *name, const char *value, int overwrite)
{

  if (overwrite==0 && getenv(name)!=NULL)
    return 0;

  int size = strlen(name)+strlen(value)+2;

  char *command = (char*)malloc(size);

  snprintf(command, size, "%s=%s", name, value);

  int ret = _putenv(command);

  free(command);

  return ret;
}

static inline int unsetenv(const char *name)
{

  int size = strlen(name)+2;

  char *command = (char*)malloc(size);

  snprintf(command, size, "%s=", name);

  int ret = _putenv(command);

  free(command);

  return ret;
}

#endif

#endif
