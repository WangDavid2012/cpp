#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "./api/C_API.h"
#include "./api/C_API_EX.h"
#include "./base/Context.h"
#include "./base/Common.h"
#include "debug.h"
#include "config.h"

#ifdef  __cplusplus
extern "C" {
#endif


u32 C_OpenDevice(void ** pDeviceHandle);

u32 vsm_process(sis_session* session);
u32 nettest(unsigned char *senddata, unsigned int sendlenth, unsigned char *recdata);



#ifdef  __cplusplus
}
#endif

#endif
