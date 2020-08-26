
#ifndef SDF_LOG_H
#define SDF_LOG_H

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>











#define _DEBUG_VERSION  1
#define MAX_LOG_LEN  256
#define NAME_OF_LOG "./SDFLog.log"
#define LOG_CONF	"./sisconf.ini"

typedef enum {
	SDF_UNDEFINED,
	SDF_INFO,
	SDF_ERR,
	SDF_WARNING,
	SDF_ALL,
} LogType;


typedef struct {
	char logPath[MAX_LOG_LEN];
	int loglevel;
} LogConf;

extern char   szFilename[256];
extern int	   nLineNum;
extern FILE   *fp;

#define _SDF_Print(fmt, ...)    printf(fmt, ##__VA_ARGS__)

void  _SDF_LogInit();
void  _SDF_Log(LogType ilogtype, char const *pszFormat, ...);
void  _SDF_LogEnd();
void  _SDF_PrintBuf(char* header, unsigned char*  buf, unsigned int buflen);


#endif

