#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED


#include "../sdf/SDF_EX.h"
#include "../base/Common.h"
#include "../base/LinkList.h"
#include "../base/VSM.h"
#include <string>


extern LinkList *g_deviceList;



#define CONFIG_FILE_NAME "/etc/config/device.cfg"


typedef struct SIS_SESSION sis_session;
typedef struct SIS_DEVICE sis_device;
typedef struct SIS_WORK_KEY sis_work_key;
typedef struct SIS_AGREMENT_CONTEXT sis_agreement_context;
typedef struct SIS_HASH_CONTEXT sis_hash_ctx_t;
typedef struct SIS_SYM_CONTEXT sis_sym_ctx_t;


typedef struct SIS_AGREMENT_CONTEXT
{
	LinkNode *node;
	u8	sponsorid[128];
	u32 sponsorid_size;
	u32 selfKeyIndex;               ///自己预制公私钥索引号
	u32 keyBitSize;                 ///密钥长度

	u64 agreePubkeyHandleAddr;
	u64 agreePrikeyHandleAddr;
	sis_agreement_context* next;    ///密钥的链表
} sis_agreement_context;


#define STEP_HASH_INIT      0x00
#define STEP_HASH_UPDATE	0x01
#define STEP_HASH_FINAL     0x02


typedef struct SIS_HASH_CONTEXT
{
	u32 handle;                             ///ARM运算所需要的对象
	u32 alg_id;
	u32 step;                               ///是否首块标志 0首块 1后续块
	u32 padded_size;                        ///填充后真实长度，有可能是1包，也有可能是2包
	u32 padding_size;                       ///待填充数据长度(输入数据分块后剩余的长度)
	u32 chunk_count;                        ///记录待hash数据总的块数，分块大小64字节
	u8 padding_buffer[SM3_CHUNK_SIZE * 2];    ///记录待填充的数据，即不够64字节的数据，第一块
	u8 unsent_buffer[SM3_CHUNK_SIZE];
	u32 unsent_size;
	u8 iv[SM3_IV_LEN];
} sis_hash_ctx_t;

#define STEP_MAC_INIT	    0x00
#define STEP_MAC_UPDATE	    0x01
#define STEP_MAC_FINAL	    0x02
typedef struct SIS_SYM_CONTEXT
{
 	u8 iv[SM14_IV_LEN];
	u8 cfb_ctx[SM14_CHUNK_SIZE];
} sis_sym_ctx_t;


/**设备结构*/
typedef struct SIS_DEVICE
{
	LinkNode *node;
	LinkList *sessionlist;
	LinkList *worklist;
	std::string ip;

	sis_device *next;
	// pthread_mutex_t device_locker;  ///设备使用的锁
	u8* key_right;                  ///会话中是否获取私钥权限
	u64 device_address;
} sis_device;

/**会话结构*/
typedef struct SIS_SESSION
{
	LinkNode *node;
	LinkList* agree_contextlist;
	sis_session *next;
	sis_fpga_task_info	fpga_task_info;			///交给虚拟密码机执行的任务信息
	sis_mcu_task_info   mcu_task_info;			///交给虚拟密码机执行的任务信息

	u8* key_right;                              ///会话中是否获取私钥权限
	u32 key_count;
	sis_device* device;                         ///会话所对应的设备句柄              
	sis_agreement_context* agreement_context_front; ///协商上下文
	sis_agreement_context* agreement_context_rear; ///协商上下文
	sis_hash_ctx_t hash_context;
	sis_hash_ctx_t hmac_context;
	sis_sym_ctx_t cmac_context;
	sis_sym_ctx_t sym_context;
	u64 session_address;
} sis_session;

typedef struct SIS_WORK_KEY
{
	LinkNode *node;
	sis_work_key* next;
	sis_device* device;
	u64 key_handle_addr;
} sis_work_key;




// #ifdef __cplusplus
// extern "C" {
// #endif










void LIB_HandleInit();
u32 LIB_CreateDevice(u64 deviceHandleAddr, HANDLE* deviceHandle, std::string ip);
u32 LIB_GetDevice(HANDLE deviceHandle, sis_device** device);
u32 LIB_ReleaseDevice(sis_device* device, u8 isLocked);
u32 LIB_ReleaseALLDevice(u8 isLocked);
u32 LIB_CreateSession(sis_device* device, u64 sessionHandleAddr, HANDLE* sessionHandle);
u32 LIB_GetSession(HANDLE sessionHandle, sis_session** session);
u32 LIB_ReleaseSession(sis_session* session, u8 isLocked);
u32 LIB_CreateWorkKey(sis_session* session, HANDLE* keyHandle, u64 keyHandleAddr, u8 isLocked);
u32 LIB_GetWorkKey(sis_session* session, HANDLE keyHandle, sis_work_key** key);
u32 LIB_ReleaseWorkKey(sis_session* session, sis_work_key* key, u8 isLocked);

u32 LIB_CreateAgreementContext(sis_session* session, HANDLE* agreementHandle, u8 isLocked);

u32 LIB_GetAgreementContext(sis_session* session, HANDLE agreementHandle, sis_agreement_context** context);

u32 LIB_ReleaseAgreementContext(sis_session* session, sis_agreement_context* context, u8 isLocked);
u32 LIB_SetPrvKeyChecked(sis_session* session, u32 keyIndex);

u32 LIB_SetPrvKeyUnchecked(sis_session* session, u32 keyIndex);



u32 LIB_ReleaseAllWorkKey(sis_device *device, u8 isLock);
u32 LIB_ReleaseAllSession(sis_device *device, u8 isLock);

u32 LIB_ReleaseALLAgreementContext(sis_session *session, u8 isLock);
void HandleTest();
void WorkkeyNodePrintf(LinkNode *data);
void SessionNodePrintf(LinkNode *data);







#endif /// CONTEXT_H_INCLUDED

