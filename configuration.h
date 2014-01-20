#ifndef _configuration_h
#define _configuration_h

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#define MAX_LINE_LENGTH 1024
#define MAX_DIR_LENGTH 265

#ifdef __unix__
#define CONFIG_FILE "/etc/paxman/config.xml"
#elif __WIN32__ || _MS_DOS_
#define CONFIG_FILE "%ProgramFiles%\\paxman\\config.xml"
#else
#define CONFIG_FILE "config.xml"
#endif

#endif
