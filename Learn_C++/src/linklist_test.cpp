<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LinkList.h"
#include "common.h"

#define TRUE				1
#define FALSE				0
typedef void*				HANDLE;
typedef unsigned char		BYTE;
typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long  u64;

typedef struct _PERSON {
	LinkNode *node;
	char name[64];
	int age;
}Person;

void MyPrintf(LinkNode *data)
{
	Person *p = (Person *)data;
	printf("Name:%s£¬Age:%d\n", p->name, p->age);
}

int MyCompare(LinkNode *a, LinkNode *b)
{
	Person* pa = (Person*)a;
	Person* pb = (Person*)b;
	if (pa->age == pb->age)
		return 0;
	else
		return 1;
}




void linklist_test()
{
	LinkList *list = Init_LinkList();
	Free_LinkList(list);



	// 	Person p1, p2, p3, p4, p0, p5;
	// 
	// 	strcpy(p0.name, "0000");
	// 	strcpy(p1.name, "aaa");
	// 	strcpy(p2.name, "bbb");
	// 	strcpy(p3.name, "ccc");
	// 	strcpy(p4.name, "ddd");
	// 	strcpy(p5.name, "kkk");
	// 	p0.age = 0;
	// 	p1.age = 1;
	// 	p2.age = 2;
	// 	p3.age = 3;
	// 	p4.age = 4;
	// 	p5.age = 5;

	// 	Insert_LinkList(list, 0, (LinkNode*)&p4);
	// 	Insert_LinkList(list, 0, (LinkNode*)&p3);
	// 	Insert_LinkList(list, 0, (LinkNode*)&p2);
	// 	Insert_LinkList(list, 0, (LinkNode*)&p1);
	// 	Insert_LinkList(list, 0, (LinkNode*)&p0);
	// 
	// 	Print_LinkList(list, MyPrintf);
	// 
	// 	printf("\n------------------------------\n");
		// 	Remove_LinkList(list, 5);
		// 	Print_LinkList(list, MyPrintf);

	// 	int ret = Find_LinkList(list, (LinkNode *)&p3, MyCompare);
	// 	printf("The ret value is ret:%d\n", ret);
	// 	ret = Find_LinkList(list, (LinkNode *)&p0, MyCompare);
	// 	printf("The ret value is ret:%d\n", ret);

	//Free_LinkList(list);

}

typedef struct SIS_SESSION sis_session;
typedef struct SIS_DEVICE sis_device;
typedef struct SIS_WORK_KEY sis_work_key;


typedef struct SIS_AGREMENT_CONTEXT sis_agreement_context;
typedef struct SIS_AGREMENT_CONTEXT
{
	LinkNode *node;
	u8	sponsorid[128];
	u32 sponsorid_size;
	u32 selfKeyIndex;					///×Ô¼ºÔ¤ÖÆ¹«Ë½Ô¿Ë÷ÒýºÅ
	u32 keyBitSize;						///ÃÜÔ¿³¤¶È
	sis_work_key* tempPubKey;			///×Ô¼ºÁÙÊ±¹«Ô¿
	sis_work_key* tempPrvKey;			///×Ô¼ºÁÙÊ±Ë½Ô¿
} sis_agreement_context;


typedef struct SIS_DEVICE {
	LinkNode *node;
	LinkList *sessionlist;
	LinkList *worklist;
	u64 device_address;
}sis_device;

typedef struct SIS_SESSION {
	LinkNode *node;
	LinkList* agree_contextlist;
	sis_device *device;
	u64 session_address;
}sis_session;

typedef struct SIS_WORK_KEY {
	LinkNode *node;
	sis_device *device;
	u64 key_handle_addr;
}sis_work_key;


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
	int pos = Find_LinkList(g_deviceList, (LinkNode*)device, DeviceCompareFun);
	if (pos != -1)
	{
		ret = Remove_LinkList(g_deviceList, pos);
		if (ret != -1)
		{
			//ÐèÒªÏÈÊÍ·ÅËùÓÐµÄsessionºÍworkkey
			//È»ºóÊÍ·Åfree
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

u32 LIB_ReleaseALLDevice(unsigned char lock)
{
	return 0;
}
u32 LIB_CreateSession(sis_device* device, u64 sessionHandleAddr, HANDLE* sessionHandle)
{
	int ret = 0;
	if (device == nullptr)
		return -1;
	sis_session *session = (sis_session *)malloc(sizeof(sis_session));
	if (session == nullptr)
		return -1;
	session->agree_contextlist = Init_LinkList();
	// 	memcpy(&(session->mcu_task_info.send_head.user_parm),&sessionHandleAddr,8);
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
	sis_session *tmpsession = (sis_session *)sessionHandle;

	ret = Find_LinkList(tmpsession->device->sessionlist, (LinkNode*)tmpsession, SessionCompareFun);
	if (ret == -1) {
		return -1;
	}
	else {
		*session = (sis_session *)sessionHandle;
		return ret;
	}
}
u32 LIB_ReleaseSession(sis_session* session, u8 isLocked)
{
	if (session == nullptr)
		return -1;
	int ret = 0;
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
	//¶ÔÓ¦µÄÖ¸Õë¿Õ¼äÐèÒª¿ª±Ù
	if (agree_contex == nullptr)
		return -1;

	ret = Insert_LinkList(session->agree_contextlist, 0, (LinkNode*)agree_contex);
	if (ret != 0) {
		free(agree_contex);
		return ret;
	}

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
		ret = Remove_LinkList(session->device->worklist, pos);
		if (ret == 0) {
			//×¢Òâ£¬ÊÍ·ÅÊ±£¬agree_context ÀïÃæ»¹ÓÐÖ¸Õë£¬Ó¦¸ÃÏÈÊÍ·ÅÖ¸ÕëÖ¸ÏòµÄÄÚÈÝ£»
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
		//ÊÍ·Åsis_agreement_contextÄÚµÄÖ¸Õë
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
=======
ï»¿#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LinkList.h"
#include "common.h"

#define TRUE				1
#define FALSE				0
typedef void*				HANDLE;
typedef unsigned char		BYTE;
typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long  u64;

typedef struct _PERSON {
	LinkNode *node;
	char name[64];
	int age;
}Person;

void MyPrintf(LinkNode *data)
{
	Person *p = (Person *)data;
	printf("Name:%sï¼ŒAge:%d\n", p->name, p->age);
}

int MyCompare(LinkNode *a, LinkNode *b)
{
	Person* pa = (Person*)a;
	Person* pb = (Person*)b;
	if (pa->age == pb->age)
		return 0;
	else
		return 1;
}

void linklist_test()
{
	LinkList *list = Init_LinkList();
	Free_LinkList(list);

	// 	Person p1, p2, p3, p4, p0, p5;
	//
	// 	strcpy(p0.name, "0000");
	// 	strcpy(p1.name, "aaa");
	// 	strcpy(p2.name, "bbb");
	// 	strcpy(p3.name, "ccc");
	// 	strcpy(p4.name, "ddd");
	// 	strcpy(p5.name, "kkk");
	// 	p0.age = 0;
	// 	p1.age = 1;
	// 	p2.age = 2;
	// 	p3.age = 3;
	// 	p4.age = 4;
	// 	p5.age = 5;

	// 	Insert_LinkList(list, 0, (LinkNode*)&p4);
	// 	Insert_LinkList(list, 0, (LinkNode*)&p3);
	// 	Insert_LinkList(list, 0, (LinkNode*)&p2);
	// 	Insert_LinkList(list, 0, (LinkNode*)&p1);
	// 	Insert_LinkList(list, 0, (LinkNode*)&p0);
	//
	// 	Print_LinkList(list, MyPrintf);
	//
	// 	printf("\n------------------------------\n");
		// 	Remove_LinkList(list, 5);
		// 	Print_LinkList(list, MyPrintf);

	// 	int ret = Find_LinkList(list, (LinkNode *)&p3, MyCompare);
	// 	printf("The ret value is ret:%d\n", ret);
	// 	ret = Find_LinkList(list, (LinkNode *)&p0, MyCompare);
	// 	printf("The ret value is ret:%d\n", ret);

	//Free_LinkList(list);
}

typedef struct SIS_SESSION sis_session;
typedef struct SIS_DEVICE sis_device;
typedef struct SIS_WORK_KEY sis_work_key;

typedef struct SIS_AGREMENT_CONTEXT sis_agreement_context;
typedef struct SIS_AGREMENT_CONTEXT
{
	LinkNode *node;
	u8	sponsorid[128];
	u32 sponsorid_size;
	u32 selfKeyIndex;					///è‡ªå·±é¢„åˆ¶å…¬ç§é’¥ç´¢å¼•å·
	u32 keyBitSize;						///å¯†é’¥é•¿åº¦
	sis_work_key* tempPubKey;			///è‡ªå·±ä¸´æ—¶å…¬é’¥
	sis_work_key* tempPrvKey;			///è‡ªå·±ä¸´æ—¶ç§é’¥
} sis_agreement_context;

typedef struct SIS_DEVICE {
	LinkNode *node;
	LinkList *sessionlist;
	LinkList *worklist;
	u64 device_address;
}sis_device;

typedef struct SIS_SESSION {
	LinkNode *node;
	LinkList* agree_contextlist;
	sis_device *device;
	u64 session_address;
}sis_session;

typedef struct SIS_WORK_KEY {
	LinkNode *node;
	sis_device *device;
	u64 key_handle_addr;
}sis_work_key;

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
	int pos = Find_LinkList(g_deviceList, (LinkNode*)device, DeviceCompareFun);
	if (pos != -1)
	{
		ret = Remove_LinkList(g_deviceList, pos);
		if (ret != -1)
		{
			//éœ€è¦å…ˆé‡Šæ”¾æ‰€æœ‰çš„sessionå’Œworkkey
			//ç„¶åŽé‡Šæ”¾free
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

u32 LIB_ReleaseALLDevice(unsigned char lock)
{
	return 0;
}
u32 LIB_CreateSession(sis_device* device, u64 sessionHandleAddr, HANDLE* sessionHandle)
{
	int ret = 0;
	if (device == nullptr)
		return -1;
	sis_session *session = (sis_session *)malloc(sizeof(sis_session));
	if (session == nullptr)
		return -1;
	session->agree_contextlist = Init_LinkList();
	// 	memcpy(&(session->mcu_task_info.send_head.user_parm),&sessionHandleAddr,8);
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
	sis_session *tmpsession = (sis_session *)sessionHandle;

	ret = Find_LinkList(tmpsession->device->sessionlist, (LinkNode*)tmpsession, SessionCompareFun);
	if (ret == -1) {
		return -1;
	}
	else {
		*session = (sis_session *)sessionHandle;
		return ret;
	}
}
u32 LIB_ReleaseSession(sis_session* session, u8 isLocked)
{
	if (session == nullptr)
		return -1;
	int ret = 0;
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
	//å¯¹åº”çš„æŒ‡é’ˆç©ºé—´éœ€è¦å¼€è¾Ÿ
	if (agree_contex == nullptr)
		return -1;

	ret = Insert_LinkList(session->agree_contextlist, 0, (LinkNode*)agree_contex);
	if (ret != 0) {
		free(agree_contex);
		return ret;
	}
	*agreementHandle = (HANDLE)agree_contex;   //åŽæ¥æ·»åŠ  20200702
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
			//æ³¨æ„ï¼Œé‡Šæ”¾æ—¶ï¼Œagree_context é‡Œé¢è¿˜æœ‰æŒ‡é’ˆï¼Œåº”è¯¥å…ˆé‡Šæ”¾æŒ‡é’ˆæŒ‡å‘çš„å†…å®¹ï¼›
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
		//Remove_LinkList(session->agree_contextlist, 0);
		//é‡Šæ”¾sis_agreement_contextå†…çš„æŒ‡é’ˆ
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
sis_work_key *workkey1 = nullptr;
sis_work_key *workkey2 = nullptr;
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
	LIB_GetWorkKey(session, keyhandle2, &workkey2);
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
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
