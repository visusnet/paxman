#ifndef _shell_h
#define _shell_h

#ifdef __unix__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#elif __WIN32__ || _MS_DOS_
#include <dir.h>
#else
//#include <direct.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#endif
