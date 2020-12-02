#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"
#include "../base/Common.h"
#include "../base/SDFLog.h"
#include "interface.h"
#include <stdlib.h>
#include <string.h>



u32 C_API_Opendevice(sis_session* session)
{
	return SDR_OK;
}

/**************************1 设备管理函数*****************************/
/*描述：获取设备信息函数*/
u32 C_GetDeviceInfo(sis_session* session, DEVICEINFO *pstDeviceInfo)
{

	int rst = 0;
	// sis_vsm_info *vsmInfo = NULL;
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_DEV_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GET_DEVICE_INFO;
	session->mcu_task_info.send_head.data_length = 0;
	session->mcu_task_info.send_param_count = 0;

	//将返回数据结果放到resp_data中，所以返回参数长度为0，返回参数默认值为0，所以可以不赋值
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_dev_info;
	//将输出结果指针执行传入的结构体，直接将内核态结果返回，减少一次内存拷贝
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pstDeviceInfo;

	if (SDR_OK == (rst = vsm_process(session,nullptr)))
	{
		rst = session->mcu_task_info.resp_head.status;
	}
	return GET_FULL_ERR_CODE(rst);
}
/*描述：校验私钥使用授权码*/
u32 C_PrikeyLogin(sis_session* session, u32 KeyId, u8 *pPassword, u32 uiPasswdLen)
{

	int rst = 0;

	u32 sendKeyId = htonl(KeyId);
	u32 sendPwdLen = htonl(uiPasswdLen);
	u8 tmpdata[32] = { 0 };

	if (uiPasswdLen == 0)
	{
		session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_DEV_MANAGE;
		session->mcu_task_info.send_head.sub_cmd = CMD_SUB_RELEASE_PRIVATEKEY_ACCESSRIGHT;
		session->mcu_task_info.send_head.data_length = 4;

		session->mcu_task_info.send_param_count = 1;
		session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
		session->mcu_task_info.send_param[0].ptr_param = (u8*)&sendKeyId;
		session->mcu_task_info.resp_param_count = 1;
		session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
		session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_16;
		session->mcu_task_info.resp_param[0].ptr_param = tmpdata;
	}
	else
	{
		session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_DEV_MANAGE;
		session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GET_PRIVATEKEY_ACCESSRIGHT;
		session->mcu_task_info.send_head.data_length = 4 + 4 + uiPasswdLen;

		session->mcu_task_info.send_param_count = 3;

		session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
		session->mcu_task_info.send_param[0].ptr_param = (u8*)&sendKeyId;
		session->mcu_task_info.send_param[1].reply_prev_property = DEFAULT_PROPERTY;
		session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
		session->mcu_task_info.send_param[1].ptr_param = (u8*)&sendPwdLen;
		session->mcu_task_info.send_param[2].reply_prev_property = DEFAULT_PROPERTY;
		session->mcu_task_info.send_param[2].ptr_param_len = &uiPasswdLen;
		session->mcu_task_info.send_param[2].ptr_param = pPassword;
		session->mcu_task_info.resp_param_count = 0;
	}
	rst = vsm_process(session,nullptr);
	if (rst != SDR_OK)
	{
		debug_printf("The return value is 0x%02x\n", rst);
		return GET_FULL_ERR_CODE(rst);
	}
	return rst;
}

u32 C_GetRandom(sis_session* session, u32 uiLen, u8 *pRandom)
{

	u32 rst = 0;

	u32 randomOutLen = 0;
	u32 sendGetRandomLen = htonl(uiLen);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_DEV_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_RANDOM;
	session->mcu_task_info.send_head.data_length = 4;

	session->mcu_task_info.send_param_count = 1;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&sendGetRandomLen;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&randomOutLen;
	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = &randomOutLen;
	session->mcu_task_info.resp_param[1].ptr_param = pRandom;

	if (SDR_OK == (rst = vsm_process(session,nullptr))) {
		rst = session->mcu_task_info.resp_head.status;
	}
	if (uiLen != randomOutLen) {
		return SDR_UNKNOWERR;
	}
	return GET_FULL_ERR_CODE(rst);
}
