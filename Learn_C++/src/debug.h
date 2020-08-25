#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>

#define DEBUG        0
#ifdef DEBUG
	//日志显示(文件名：行号}+日期
//#define pr_debug(fmt,args...) printf(fmt, ##args)
#define LOG(s) printf("[%s:%d] %s\n", __FILE__, __LINE__, s)
//错误信息位置（级别+文件名+函数名+行号+错误信息)
#define ERROR(s)                                                                      \
	do{																					  \
	fprintf(stderr, "[ERROR  at:]%s %s(Line %d): %s\n",__FILE__,__FUNCTION__,__LINE__,s); \
	}while(0)
//二维float数组打印显示
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
	//日志不显示
#define LOG(s)
//二维float数组打印不显示
#define PrintArray2D(arr,m,n)
//错误信息不显示
#define ERROR(s)
//#define pr_debug(fmt,args...)
#endif

#ifdef __cplusplus
}
#endif