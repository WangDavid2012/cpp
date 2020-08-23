/*
2020-03-10	完成该文件相关函数的调用和编写，完成调试。
				修改该文件的协议内容采用新结构体方式。
*/
#include "SDF.h"
#include "SDF_EX.h"
#include "Interface.h"
#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"
#include "../base/SDFLog.h"
#include "debug.h"



//void PrintBuf(u8 * buf, u32 buflen);

u32 SDF_OpenDevice_Path(HANDLE* phDeviceHandle, u8 *iniPath)
{
	u32 ret = 0;
	return ret;
}


u32 SDF_OpenDeviceByID(HANDLE* phDeviceHandle, u8 *id, u32 lenth)
{
	sis_session session = { 0 };
	u32 idlenth = lenth;
	u32 rst = 0;
	u32 params[1] = { 0 };
	u64 deviceAddr = 0;


	memset(&(session), 0, sizeof(sis_session));
	session.mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ENV_MANAGE;
	session.mcu_task_info.send_head.sub_cmd = CMD_SUB_OPEN_DEVICE_BY_ID;
	session.mcu_task_info.send_head.data_length = lenth;

	session.mcu_task_info.send_param_count = 1;
	session.mcu_task_info.send_param[0].ptr_param_len = &idlenth;
	session.mcu_task_info.send_param[0].ptr_param = id;

	rst = vsm_process(&session);
	if (rst == SDR_OK)
	{
		memcpy(&deviceAddr, session.mcu_task_info.resp_head.user_parm, 8);
		rst = LIB_CreateDevice(deviceAddr, phDeviceHandle);
		//debug_printf("The LIB_CreateDevice ret:%d,addr:0x%02x\n", rst, deviceAddr);
	}

	return rst;
}

/* 打开设备 */
DLL u32 SDF_OpenDevice(HANDLE* phDeviceHandle)
{
// 	u8 id[32] = { 0 };
// 	for (int i = 0; i < 32; i++)
// 	{
// 		id[i] = i + 0x30;
// 	}
// 	return SDF_OpenDeviceByID(phDeviceHandle, id, 32);

	return C_OpenDevice(phDeviceHandle);


}



/* 关闭设备 */
DLL u32 SDF_CloseDevice(HANDLE hDeviceHandle)
{

	sis_session session;
	u32 rst = 0;
	u32 params[1] = { 0 };
	u64 deviceAddr = 0;

	sis_device* dev;

	memset(&(session), 0, sizeof(sis_session));
	session.mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ENV_MANAGE;
	session.mcu_task_info.send_head.sub_cmd = CMD_SUB_CLOSE_DEVICE;
	session.mcu_task_info.send_head.data_length = 0;
	
	//vsm将devicehandle的值存档到user_parm 中
	//session.mcu_task_info.resp_head.user_parm = (u8*)deviceAddr;

	rst = LIB_GetDevice(hDeviceHandle, &dev);
	memcpy(&(session.mcu_task_info.send_head.user_parm), &(dev->device_address), 8);
	rst = vsm_process(&session);
	
	rst = LIB_ReleaseDevice(dev, 0);
	return rst;
}

/* 关闭设备 */
//需要调整代码位置到 C_API_DEV
u32 SDF_CloseDeviceByID(HANDLE hDeviceHandle, u8 *id, u32 lenth)
{
	sis_session session;
	u32 idlenth = lenth;
	
	u32 rst = 0;
	u32 params[1] = { 0 };
	u64 deviceAddr = 0;

	memset(&(session), 0, sizeof(sis_session));
	session.mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ENV_MANAGE;
	session.mcu_task_info.send_head.sub_cmd = CMD_SUB_CLOSE_DEVICE_BY_ID;
	session.mcu_task_info.send_head.data_length = 32;
	//vsm将devicehandle的值存档到user_parm 中
	//session.mcu_task_info.resp_head.user_parm = (u8*)deviceAddr;
	memcpy(&(session.mcu_task_info.resp_head.user_parm), &deviceAddr, sizeof(deviceAddr));

	session.mcu_task_info.send_param_count = 1;
	session.mcu_task_info.send_param[0].ptr_param_len = &idlenth;
	session.mcu_task_info.send_param[0].ptr_param = id;
	rst = vsm_process(&session);

	rst = LIB_ReleaseALLDevice(0);
	return GET_FULL_ERR_CODE(rst);
}


/* 打开会话 */
DLL u32 SDF_OpenSession(HANDLE hDeviceHandle, HANDLE* phSessionHandle)
{
	sis_session session = { 0 };
	
	u32 rst = 0;
	u32 params[1] = { 0 };
	u64 deviceAddr = 0;
	u64 sessionAddr = 0;
	sis_device* device = NULL;

	rst = LIB_GetDevice(hDeviceHandle, &device);
	deviceAddr = device->device_address;

	memset(&(session), 0, sizeof(sis_session));
	session.mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ENV_MANAGE;
	session.mcu_task_info.send_head.sub_cmd = CMD_SUB_OPEN_SESSION;
	session.mcu_task_info.send_head.hard_parm = 0x0;
	memcpy(&session.mcu_task_info.send_head.user_parm, &deviceAddr, 8);

	rst = vsm_process(&session);
	if (rst == SDR_OK)
	{
		//返回值，将sesssion的地址放到session.mcu_task_info.resp_head.user_parm
		memcpy(&sessionAddr, &(session.mcu_task_info.resp_head.user_parm), 8);
		rst = LIB_CreateSession(device, sessionAddr, phSessionHandle);
        if(rst != 0){
            debug_printf("LIB_CreateSession error\n");
            while(1);
        }
		debug_printf("The sessionAddr is 0x%llx\n", sessionAddr);
	}
	return rst;
}


DLL u32 SDF_CloseSession(HANDLE hSessionHandle)
{
	u32 ret = 0;
	sis_session session = { 0 };
	u8 devaddr[8];
	u32 rst = 0;
	u32 params[1] = { 0 };
	u64 sessionAddr = 0;
	sis_session* releasesession = NULL;

	rst = LIB_GetSession(hSessionHandle, &releasesession);
	if (rst != SDR_OK) {
		return rst;
	}
	sessionAddr = releasesession->session_address;

	//debug_printf("the release session addr is 0x%x\n", sessionAddr);

	memset(&(session), 0, sizeof(sis_session));
	session.mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ENV_MANAGE;
	session.mcu_task_info.send_head.sub_cmd = CMD_SUB_CLOSE_SESSION;
	session.mcu_task_info.send_head.hard_parm = 0;
	memcpy(&(session.mcu_task_info.send_head.user_parm), &sessionAddr, 8);
	session.mcu_task_info.send_head.data_length = 0;
	rst = vsm_process(&session);
	if (rst == SDR_OK) {
		rst = LIB_ReleaseSession(releasesession, 1);
        if(rst != 0){
            debug_printf("LIB_CreateSession error\n");
            while(1);
        }
	}
	debug_printf("SDF_CloseSession success\n");
	return rst;
}

/* 获取设备信息 */
DLL u32 SDF_GetDeviceInfo(HANDLE hSessionHandle, DEVICEINFO *pstDeviceInfo)
{

	u32 ret = 0;
	sis_session* session = NULL;
	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK) {
		ret = C_GetDeviceInfo(session, pstDeviceInfo);
		if (ret == SDR_OK) {
			// _SDF_Log(SDF_INFO,"SDF_GetDeviceInfo complete......\n");
		}
	}
	return ret;
}

/* 产生随机数 */
DLL u32 SDF_GenerateRandom(HANDLE hSessionHandle, u32  uiLength, u8 *pucRandom)
{
	u32 offset = 0, left, one_size;

	u32 ret = 0;
	sis_session* session = NULL;
	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK) {
		left = uiLength;
		while (left > 0) {
			one_size = (left > 512) ? 512 : left;
			ret = C_GetRandom(session, one_size, pucRandom + offset);
			if (ret != SDR_OK) {
				// _SDF_Log(SDF_ERR, "------>C_GetRandom，uiLength=%d", uiLength);
				return ret;
			}
			offset += one_size;
			left -= one_size;
		}
	}
	return ret;
}

/* 获取私钥使用权限 */
DLL u32 SDF_GetPrivateKeyAccessRight(HANDLE hSessionHandle, u32  uiKeyIndex, u8 *pucPassword, u32  uiPwdLength)
{
	u32 ret = 0;
	sis_session *session = NULL;

	// _SDF_Log(SDF_INFO, "SDF_GetPrivateKeyAccessRight starting......");

	if (uiKeyIndex >= MAX_ASYM_KEY_COUNT || uiKeyIndex <= 0) {
		return SDR_KEYERR;
	}

	if ((pucPassword == NULL) || (uiPwdLength < 8)) {
		return SDR_INARGERR;
	}
	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK) {
		ret = C_PrikeyLogin(session, uiKeyIndex, pucPassword, uiPwdLength);
		if (ret == SDR_OK) {
			// _SDF_Log(SDF_INFO, "SDF_GetPrivateKeyAccessRight complete......\n");
		}
	}
	return ret;
}

/* 释放私钥使用权限 */
DLL u32 SDF_ReleasePrivateKeyAccessRight(HANDLE hSessionHandle, u32  uiKeyIndex)
{

	u32 ret = 0;
	sis_session  *session = NULL;
	// _SDF_Log(SDF_INFO, "SDF_ReleasePrivateKeyAccessRight starting......");
	if (uiKeyIndex >= MAX_ASYM_KEY_COUNT || uiKeyIndex <= 0) {
		return SDR_KEYERR;
	}
	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK) {
		ret = C_PrikeyLogin(session, uiKeyIndex, NULL, 0);
		if (ret == SDR_OK) {
			// _SDF_Log(SDF_INFO, "SDF_ReleasePrivateKeyAccessRight complete......\n");
		}
		else {
			// _SDF_Log(SDF_ERR, "------>C_PrikeyLogin For Logout");
		}
	}
	return ret;
}
