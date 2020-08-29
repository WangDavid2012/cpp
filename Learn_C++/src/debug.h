<<<<<<< HEAD
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>

#define DEBUG        0
#ifdef DEBUG
	//ÈÕÖ¾ÏÔÊ¾(ÎÄ¼şÃû£ºĞĞºÅ}+ÈÕÆÚ
//#define pr_debug(fmt,args...) printf(fmt, ##args)
#define LOG(s) printf("[%s:%d] %s\n", __FILE__, __LINE__, s)
//´íÎóĞÅÏ¢Î»ÖÃ£¨¼¶±ğ+ÎÄ¼şÃû+º¯ÊıÃû+ĞĞºÅ+´íÎóĞÅÏ¢)
#define ERROR(s)                                                                      \
	do{																					  \
	fprintf(stderr, "[ERROR  at:]%s %s(Line %d): %s\n",__FILE__,__FUNCTION__,__LINE__,s); \
	}while(0)
//¶şÎ¬floatÊı×é´òÓ¡ÏÔÊ¾
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
	//ÈÕÖ¾²»ÏÔÊ¾
#define LOG(s)
//¶şÎ¬floatÊı×é´òÓ¡²»ÏÔÊ¾
#define PrintArray2D(arr,m,n)
//´íÎóĞÅÏ¢²»ÏÔÊ¾
#define ERROR(s)
//#define pr_debug(fmt,args...)
#endif

#ifdef __cplusplus
}
#endif
=======
ï»¿#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#define __DEBUG

#ifdef __DEBUG
#define mydebug std::cout << "Debuginfo:["<< __FILE__ <<":"<< __LINE__ << "]"

#ifdef _WIN32

#define debug_printf( format, ...)  \
					printf("DebugInfo:[%s:%s:%d]" format ,__FILE__,__FUNCTION__,__LINE__,__VA_ARGS__)
#define my_printf( format, ... )    \
							   printf(format,__VA_ARGS__)
#else
#define debug_printf( format, arg...)              \
						   printf("DebugInfo:[%s:%s:%d]" format ,__FILE__,__FUNCTION__,__LINE__,## arg)
#define my_printf( format, arg...)              \
						   printf(format,## arg)
#endif

#else
#define mydebug 0 && std::cout
#define debug_printf(format,...) do {  } while (0)
#define my_printf(format,...)   do {  } while (0)

// #define debug_printf(format, arg...) do {  } while (0)
// #define my_printf(format, arg...)   do {  } while (0)
#endif

#endif
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
