#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mutex>
#include "../base/Context.h"
#include "SDFLog.h"
#include "../mcu/MCU.h"
#include "debug.h"

std::mutex devicemutex;
std::mutex sessionmutex;
std::mutex workkeymutex;


LinkList *g_deviceList = nullptr;

u32 LIB_ReleaseALLAgreementContext(sis_session* session, u8 isLock);
u32 LIB_ReleaseAllSession(sis_device *device, u8 isLock);
u32 LIB_ReleaseAllWorkKey(sis_device *device, u8 isLock);

int DeviceCompareFun(LinkNode *a, LinkNode *b)
{
	sis_device *deviceA = (sis_device *)a;
	sis_device *deviceB = (sis_device*)b;
	if (deviceA->device_address == deviceB->device_address)
		return 0;
	else
		return 1;
}

int SessionCompareFun(LinkNode *a, LinkNode *b)
{
	sis_session *sessionA = (sis_session *)a;
	sis_session *sessionB = (sis_session*)b;
	if (sessionA->session_address == sessionB->session_address)
		return 0;
	else
		return 1;
}
int WorkKeyCompareFun(LinkNode *a, LinkNode *b)
{
	sis_work_key *keyA = (sis_work_key *)a;
	sis_work_key *keyB = (sis_work_key *)b;
	if (keyA->key_handle_addr == keyB->key_handle_addr)
		return 0;
	else
		return 1;
}

int AgreeContextCompareFun(LinkNode *a, LinkNode *b)
{
	return 0;
}

void LibConfigInit()
{
	g_deviceList = Init_LinkList();
}
void LIB_HandleInit()
{
	g_deviceList = Init_LinkList();
}

u32 LIB_CreateDevice(u64 deviceHandleAddr, HANDLE* deviceHandle)
{
	int ret = 0;
	
	std::lock_guard<std::mutex> lock(devicemutex);

	sis_device *device = (sis_device *)malloc(sizeof(sis_device));
	memset(device, 0, sizeof(sis_device));
	if (device == nullptr)
		return -1;
	device->device_address = deviceHandleAddr;
	*deviceHandle = (void *)device;
	device->sessionlist = Init_LinkList();
	device->worklist = Init_LinkList();
	device->node = nullptr;

	ret = Insert_LinkList(g_deviceList, 0, (LinkNode*)device);
	if (ret != 0) {
		Free_LinkList(device->sessionlist);
		device->sessionlist = nullptr;
		Free_LinkList(device->worklist);
		device->worklist = nullptr;
		free(device);
		device = nullptr;
		return ret;
	}
	return 0;
}

u32 LIB_GetDevice(HANDLE deviceHandle, sis_device** device)
{
	int ret = 0;
	sis_device *tmpdevice = (sis_device*)deviceHandle;
	ret = Find_LinkList(g_deviceList, (LinkNode*)(tmpdevice), DeviceCompareFun);
	if (ret != -1) {
		*device = (sis_device*)(deviceHandle);
		return ret;
	}
	else {
		return -1;
	}
}

u32 LIB_ReleaseDevice(sis_device* device, u8 isLocked)
{
	int ret = 0;
	if (device == nullptr)
		return -1;

	std::lock_guard<std::mutex> lock(devicemutex);

	int pos = Find_LinkList(g_deviceList, (LinkNode*)device, DeviceCompareFun);
	if (pos != -1)
	{
		ret = Remove_LinkList(g_deviceList, pos);

		if (ret != -1)
		{
			//需要先释放所有的session和workkey
			//然后释放free
			if (device->sessionlist->size != 0) {
				LIB_ReleaseAllSession(device, 1);
			}
			if (device->worklist->size != 0) {
				LIB_ReleaseAllWorkKey(device, 1);
			}
			free(device);
			device = nullptr;
		}
	}
	return ret;
}
//需要添加一个回调函数，回调函数中有文件读写，还有有SDF_CloseDevice相关函数
u32 LIB_ReleaseALLDevice(unsigned char lock)
{
	//存在bug，指示从RAM中读取 device信息，实质是没有的
	//需要从一个文件中读取，也需要有一个配置文件？？？？
	int deviceCount = g_deviceList->size;
	LinkNode *pDel = nullptr;
	LinkNode *pCur = &(g_deviceList->head);


	if (deviceCount > 0)
	{
		for (int i = 0; i < deviceCount; i++) {
			pDel = pCur->next;
			pCur->next = pDel->next;
			LIB_ReleaseDevice((sis_device*)pDel, 1);
		}
		Free_LinkList(g_deviceList);
	}
	return 0;
}

u32 LIB_CreateSession(sis_device* device, u64 sessionHandleAddr, HANDLE* sessionHandle)
{
	int ret = 0;
	if (device == nullptr)
		return -1;
	std::lock_guard<std::mutex> lock(sessionmutex);
	sis_session *session = (sis_session *)malloc(sizeof(sis_session));
	if (session == nullptr)
		return -1;

	session->agree_contextlist = Init_LinkList();
	memcpy(&(session->mcu_task_info.send_head.user_parm), &sessionHandleAddr, 8);
	session->device = device;
	session->session_address = sessionHandleAddr;
	*sessionHandle = (HANDLE *)session;
	session->node = nullptr;

	ret = Insert_LinkList(device->sessionlist, 0, (LinkNode*)session);
	if (ret == -1) {
		Free_LinkList(session->agree_contextlist);
		free(session);
		session = nullptr;
		return -1;
	}
	return 0;
}

u32 LIB_GetSession(HANDLE sessionHandle, sis_session** session)
{
	int ret = 0;
	int index = 0;
	sis_session *tmpsession = (sis_session *)sessionHandle;

	index = Find_LinkList(tmpsession->device->sessionlist, (LinkNode*)tmpsession, SessionCompareFun);
	if (index == -1) {
		return -1;
	}
	else {
		*session = (sis_session *)sessionHandle;
	}
	return ret;
}
u32 LIB_ReleaseSession(sis_session* session, u8 isLocked)
{
	if (session == nullptr)
		return -1;
	int ret = 0;
	std::lock_guard<std::mutex> lock(sessionmutex);
	mydebug << "LIB_ReleaseSession start" <<endl;
	int pos = Find_LinkList(session->device->sessionlist, (LinkNode*)session, SessionCompareFun);
	if (pos >= 0) {
		ret = Remove_LinkList(session->device->sessionlist, pos);
		if (ret != -1) {
			LIB_ReleaseALLAgreementContext(session, 1);
			free(session);
			session = nullptr;
		}
	}
	else
	{
		ret = -1;
	}

	mydebug << "LIB_ReleaseSession finish" <<endl;
	return ret;
}

u32 LIB_ReleaseAllSession(sis_device *device, u8 isLock)
{
	if (device == nullptr)
		return -1;

	int SessionCount = device->sessionlist->size;
	LinkNode *pDel = nullptr;
	LinkNode *pCur = &(device->sessionlist->head);
	for (int i = 0; i < SessionCount; i++) {
		pDel = pCur->next;
		pCur->next = pDel->next;
		device->sessionlist->size--;
		// 		Remove_LinkList(device->sessionlist, 0);
		LIB_ReleaseALLAgreementContext((sis_session*)pDel, 1);
		free((sis_session*)pDel);
	}
	Free_LinkList(device->sessionlist);
	return 0;
}
u32 LIB_ReleaseAllWorkKey(sis_device *device, u8 isLock)
{
	if (device == nullptr)
		return -1;

	int WorkKeyCount = device->worklist->size;
	LinkNode *pCur = &(device->worklist->head);
	LinkNode *pDel = nullptr;
	for (int i = 0; i < WorkKeyCount; i++) {
		pDel = pCur->next;
		pCur->next = pDel->next;
		device->worklist->size--;
		// 		Remove_LinkList(device->worklist, 0);
		free((sis_work_key*)pDel);
	}
	Free_LinkList(device->worklist);
	return 0;
}

u32 LIB_CreateWorkKey(sis_session* session, HANDLE* keyHandle, u64 keyHandleAddr, u8 isLocked)
{
	if (session == nullptr)
		return -1;
	std::lock_guard<std::mutex> lock(workkeymutex);
	sis_work_key* key = (sis_work_key*)malloc(sizeof(sis_work_key));
	memset(key, 0, sizeof(sis_work_key));
	key->key_handle_addr = keyHandleAddr;
	key->device = session->device;
	key->node = nullptr;

	int ret = Insert_LinkList(session->device->worklist, 0, (LinkNode*)key);
	if (ret != 0) {
		free(key);
		*keyHandle = nullptr;
		return -1;
	}
	*keyHandle = (HANDLE)key;
	return 0;
}
u32 LIB_GetWorkKey(sis_session* session, HANDLE keyHandle, sis_work_key** key)
{
	sis_work_key *pkey = (sis_work_key *)keyHandle;
	if (pkey == nullptr || session->device == nullptr) {
		*key = nullptr;
		return 0x0100001d;
	}
	int ret = 0;
	ret = Find_LinkList(session->device->worklist, (LinkNode*)pkey, WorkKeyCompareFun);
	if (ret == -1)
	{
		*key = nullptr;
		return ret;
	}
	*key = (sis_work_key *)keyHandle;
	return 0;
}
u32 LIB_ReleaseWorkKey(sis_session* session, sis_work_key* key, u8 isLocked)
{
	if (session == nullptr || key == nullptr)
		return 0x0100001d;
	int pos = 0;
	int ret = 0;
	std::lock_guard<std::mutex> lock(workkeymutex);
	pos = Find_LinkList(session->device->worklist, (LinkNode*)key, WorkKeyCompareFun);
	if (pos >= 0)
	{
		ret = Remove_LinkList(session->device->worklist, pos);
		if (ret == 0) {
			free(key);
		}
	}
	else
	{
		ret = -1;
	}
	return ret;
}

u32 LIB_CreateAgreementContext(sis_session* session, HANDLE* agreementHandle, u8 isLocked)
{
	int ret = 0;
	sis_agreement_context *agree_contex = (sis_agreement_context *)malloc(sizeof(sis_agreement_context));
	memset(agree_contex, 0, sizeof(sis_agreement_context));
	agree_contex->node = nullptr;
	//对应的指针空间需要开辟
	if (agree_contex == nullptr)
		return -1;

	ret = Insert_LinkList(session->agree_contextlist, 0, (LinkNode*)agree_contex);
	if (ret != 0) {
		free(agree_contex);
		return ret;
	}
	*agreementHandle = (HANDLE)agree_contex;
	return 0;
}
u32 LIB_GetAgreementContext(sis_session* session, HANDLE agreementHandle, sis_agreement_context** context)
{
	sis_agreement_context *pcontex = (sis_agreement_context *)agreementHandle;

	if (agreementHandle == nullptr || session == nullptr) {
		*context = nullptr;
		return 0x0100001d;
	}
	int ret = 0;
	ret = Find_LinkList(session->agree_contextlist, (LinkNode*)pcontex, AgreeContextCompareFun);
	if (ret == -1)
	{
		*context = nullptr;
		return ret;
	}
	*context = (sis_agreement_context *)agreementHandle;

	return 0;
}
u32 LIB_ReleaseAgreementContext(sis_session* session, sis_agreement_context* agreement_context, u8 isLocked)
{
	if (session == nullptr || agreement_context == nullptr)
		return 0x0100001d;
	int pos = 0;
	int ret = 0;
	pos = Find_LinkList(session->agree_contextlist, (LinkNode*)agreement_context, AgreeContextCompareFun);
	if (pos >= 0)
	{
		ret = Remove_LinkList(session->agree_contextlist, pos);
		if (ret == 0) {
			//注意，释放时，agree_context 里面还有指针，应该先释放指针指向的内容;
			//free(agreement_context->tempPrvKey);
			//free(agreement_context->tempPubKey)
			free(agreement_context);
		}
	}
	else
	{
		ret = -1;
	}
	return ret;
}
u32 LIB_ReleaseALLAgreementContext(sis_session* session, u8 isLock)
{
	if (session == nullptr)
		return -1;
	int Count = session->agree_contextlist->size;

	LinkNode *pCur = &(session->agree_contextlist->head);
	for (int i = 0; i < Count; i++) {
		LinkNode *pDel = pCur->next;
		pCur->next = pDel->next;
		session->agree_contextlist->size--;
		// 		Remove_LinkList(session->agree_contextlist, 0);
				//释放sis_agreement_context内的指针
				//free(((sis_agreement_context*)pDel)->tempPrvKey);
				//free(((sis_agreement_context*)pDel)->tempPubKey);
		free((sis_agreement_context*)pDel);
	}
	Free_LinkList(session->agree_contextlist);
	return 0;
}

HANDLE devhandle1;
HANDLE devhandle2;
HANDLE devhandle3;
sis_device *dev = nullptr;
sis_session *session = nullptr;
sis_work_key *workkey = nullptr;
HANDLE sessionHandle0;
HANDLE sessionHandle1;
HANDLE sessionHandle2;

HANDLE keyhandle0;
HANDLE keyhandle1;
HANDLE keyhandle2;
HANDLE keyhandle3;

void DeviceNodePrintf(LinkNode *data)
{
	sis_device *pCur = (sis_device  *)data;
	printf("\n*****************DeviceNodePrintf***********************\n");
	printf("the deviceaddr is 0x%llx\n", pCur->device_address);
	printf("the device sessionhandle count is %d\n", pCur->sessionlist->size);
	printf("the device keyhandle count is %d\n", pCur->worklist->size);
}

void SessionNodePrintf(LinkNode *data)
{
	printf("\n*****************SessionNodePrintf***********************\n");
	sis_session *pCur = (sis_session  *)data;
	printf("the father DeviceAddr:0x%llx, sisDeviceAddr:0x%llx\n", pCur->device->device_address, pCur->session_address);
}
void WorkkeyNodePrintf(LinkNode *data)
{
	printf("\n*****************WorkkeyNodePrintf***********************\n");
	sis_work_key *pCur = (sis_work_key  *)data;
	printf("the father DeviceAddr:0x%llx, workKeyAddr:0x%llx\n", pCur->device->device_address, pCur->key_handle_addr);
}

void HandleTest()
{
	LIB_HandleInit();
	LIB_CreateDevice(0x1111111111111111, &devhandle1);
	LIB_CreateDevice(0x2222222222222222, &devhandle2);
	LIB_CreateDevice(0x3333333333333333, &devhandle3);
	Print_LinkList(g_deviceList, DeviceNodePrintf);

	LIB_GetDevice(devhandle2, &dev);
	LIB_CreateSession(dev, 0xAAAAAAAAAAAAAAAA, &sessionHandle0);
	LIB_CreateSession(dev, 0xBBBBBBBBBBBBBBBB, &sessionHandle1);
	LIB_CreateSession(dev, 0xCCCCCCCCCCCCCCCC, &sessionHandle2);

	Print_LinkList(dev->sessionlist, SessionNodePrintf);
	Print_LinkList(g_deviceList, DeviceNodePrintf);
	LIB_GetSession(sessionHandle0, &session);

	LIB_ReleaseSession(session, 1);
	session = nullptr;

	Print_LinkList(dev->sessionlist, SessionNodePrintf);
	Print_LinkList(g_deviceList, DeviceNodePrintf);

	LIB_GetSession(sessionHandle2, &session);
	LIB_CreateWorkKey(session, &keyhandle0, 0x123456790123456, 1);
	LIB_CreateWorkKey(session, &keyhandle1, 0x444444444444444, 1);
	LIB_CreateWorkKey(session, &keyhandle2, 0x987456123456687, 1);

	Print_LinkList(session->device->worklist, WorkkeyNodePrintf);

	printf("LIB_GetWorkKey start!\n");
	LIB_GetWorkKey(session, keyhandle0, &workkey);

	LIB_ReleaseWorkKey(session, workkey, 1);
	Print_LinkList(g_deviceList, DeviceNodePrintf);
	LIB_ReleaseDevice(dev, 1);
	Print_LinkList(g_deviceList, DeviceNodePrintf);

	// printfDeviceHandleInfo();
	// LIB_GetSession(sessionHandle2,&session);
	// LIB_ReleaseSession(session,1);
	// printfSessionList(dev);
	// printfDeviceHandleInfo();
}