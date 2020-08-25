#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>

#define DEBUG        0
#ifdef DEBUG
	//��־��ʾ(�ļ������к�}+����
//#define pr_debug(fmt,args...) printf(fmt, ##args)
#define LOG(s) printf("[%s:%d] %s\n", __FILE__, __LINE__, s)
//������Ϣλ�ã�����+�ļ���+������+�к�+������Ϣ)
#define ERROR(s)                                                                      \
	do{																					  \
	fprintf(stderr, "[ERROR  at:]%s %s(Line %d): %s\n",__FILE__,__FUNCTION__,__LINE__,s); \
	}while(0)
//��άfloat�����ӡ��ʾ
#define PrintArray2D(arr,m,n)       \
	do                                  \
	{                                   \
		int  i = 0;                     \
		int  j = 0;                     \
		for(i=0;i<m;i++)                \
		{                               \
		  for(j=0;j<n;j++)              \
		  {                             \
		   printf("%f  ",arr[i][j]);    \
		  }                             \
		   printf("\n");                \
		}                               \
	}while(0)

#else
	//��־����ʾ
#define LOG(s)
//��άfloat�����ӡ����ʾ
#define PrintArray2D(arr,m,n)
//������Ϣ����ʾ
#define ERROR(s)
//#define pr_debug(fmt,args...)
#endif

#ifdef __cplusplus
}
#endif