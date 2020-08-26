#define _CRT_SECURE_NO_WARNINGS
#include "SDFLog.h"

char   szFilename[256];
int	   nLineNum;
FILE   *fp;
LogConf g_logConf;

int parseLogConf()
{
	FILE *fp = NULL;
	char buf[MAX_LOG_LEN] = { 0 };
	char *p = NULL;

	fp = fopen(LOG_CONF, "r");

	if (fp == NULL) {
		return -1;
	}

	while (fgets(buf, MAX_LOG_LEN, fp) != NULL) {
		if (strncmp(buf, "#", 1) == 0) {
			continue;
		}

		p = strtok(buf, "=");

		if (p == NULL) {
			continue;
		}

		if (strcmp(p, "logfile") == 0) {
			p = strtok(NULL, "=");

			if (p != NULL) {
				strcpy(g_logConf.logPath, p);
				g_logConf.logPath[strlen(p) - 2] = '\0';
			}
		}
		else if (strcmp(p, "loglevel") == 0) {
			p = strtok(NULL, "=");

			if (p != NULL) {
				g_logConf.loglevel = atoi(p);
			}
		}
	}

	fclose(fp);

	return 0;
}

void  _SDF_LogInit()
{
#if 1 //_DEBUG_VERSION
	parseLogConf();
	fp = fopen(g_logConf.logPath, "w+");
	//printf("_SDF_LogInit fp=%d\n",*fp);    //王占�?    //fp = fopen(NAME_OF_LOG,"w+");
#endif
	return;
}

void  _SDF_Log(LogType ilogtype, char const *pszFormat, ...)
{
#if 1// _DEBUG_VERSION

	if (g_logConf.loglevel != SDF_ALL && g_logConf.loglevel != ilogtype) {
		return;
	}

	char data[1024];
	char *ptr;
	char type[15] = { 0 };
	time_t timep;
	struct tm  *p;
#ifdef _WIN32
	_tzset();
#else
	tzset();
#endif
	time(&timep);
	p = localtime(&timep);

	ptr = data + sprintf(data, "%4d/%2d/%2d  %2d:%2d:%2d   ", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday, \
		p->tm_hour, p->tm_min, p->tm_sec);

	switch (ilogtype) {
	case SDF_INFO:
		strcpy((char *)type, "");
		break;

	case SDF_ERR:
		strcpy((char *)type, "**SDF_ERR**");
		break;

	case SDF_WARNING:
		strcpy((char *)type, "SDF_WARNING");
		break;

	default:
		strcpy((char *)type, "SDF_UNDEFINED");

	}

	strncpy(ptr, type, sizeof(type));
	ptr += sizeof(type);

	*ptr = ' ';
	ptr++;
	*ptr = ' ';
	ptr++;
	*ptr = ' ';
	ptr++;

	va_list         Args;
	va_start(Args, pszFormat);
	vsprintf(ptr, pszFormat, Args);
	va_end(Args);

	data[sizeof(data) - 1] = '\0';
	ptr += strlen(ptr);
	*ptr = '\n';

	fwrite(data, ptr - data + 1, 1, fp);
	fflush(fp);
#endif
	return;

}

void  _SDF_LogEnd()
{
#if 1 //_DEBUG_VERSION

	//printf("_SDF_LogEnd fp=%d\n",fp);
	if (fp != NULL) {
		fclose(fp);
	}

#endif
	return;
}

void  _SDF_PrintBuf(char* header, unsigned char* buf, unsigned int buflen)
{
#if 1
	int i, j;
	printf("%s len = %d\n", header, buflen);
	if (buflen > 128)
	{
		j = buflen / 32 - 1;
		for (i = 0; i < 96; i++) {
			if (i % 32 == 0)
			{
				printf("%02d-%02d: ", i, i + 31);
			}
			if (i % 32 != 31)
				printf("%02x,", (unsigned char)buf[i]);
			else
				printf("%02x,\n", (unsigned char)buf[i]);
		}
		for (i = j * 32; i < buflen; i++) {
			if (i % 32 == 0)
			{
				printf("%02d-%02d: ", i, i + 31);
			}
			if (i % 32 != 31)
				printf("%02x,", (unsigned char)buf[i]);
			else
				printf("%02x,\n", (unsigned char)buf[i]);
		}
	}
	else
	{
		for (i = 0; i < buflen; i++) {
			if (i % 32 == 0)
			{
				printf("%02d-%02d: ", i, i + 31);
			}
			if (i % 32 != 31)
				printf("%02x,", (unsigned char)buf[i]);
			else
				printf("%02x,\n", (unsigned char)buf[i]);
		}
	}
	printf("\n");
#endif
	return;
}
/*
void _SDF_Print(char const *fmt, ...)
{
	printf(fmt, ##__VA_ARGS__)
}*/
