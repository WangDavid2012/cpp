#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::string;


// #define __DEBUG

#ifdef __DEBUG
#define mydebug std::cout << "debug:["<< __FILE__ <<":"<< __LINE__ << "]"

#ifdef _WIN32
#define debug_printf( format, ...)  \
					printf("debug:[%s:%d]" format ,__FUNCTION__,__LINE__,__VA_ARGS__)
// #define debug_printf( format, ...)  \
// 					printf("debug:[%s:%s:%d]" format ,__FILE__,__FUNCTION__,__LINE__,__VA_ARGS__)
#define my_printf( format, ... )    \
							   printf(format,__VA_ARGS__)
#else

#define debug_printf( format, arg...)              \
						   printf("debug:[%s:%s:%d]" format ,__FILE__,__FUNCTION__,__LINE__,## arg)
#define my_printf( format, arg...)              \
						   printf(format,## arg)
#endif

#else


#ifdef _WIN32


#define mydebug 0 && std::cout
#define debug_printf(format,...) do {  } while (0)
#define my_printf(format,...)   do {  } while (0)

#else


#define debug_printf(format, arg...) do {  } while (0)
#define my_printf(format, arg...)   do {  } while (0)
#define mydebug 0 && std::cout



#endif


#endif

#endif
