#include "../api/C_API.h"
#include "../api/C_API_EX.h"
// #include "../base/VSM.h"
#include "../base/Context.h"
#include "../base/Common.h"
#include "Interface.h"

u32 C_CreateFile(sis_session *session,
	u8* pucFileName,
	u32 uiFileSize)
{
	u32 rst = 0, i = 0;
	u32 params[3] = { 0 };
	u32 uiNameLen = (u32)strlen((char *)pucFileName);

	params[0] = htonl(uiFileSize);
	params[1] = htonl(uiNameLen);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_CREATE_FILE;
	session->mcu_task_info.send_head.data_length = 4 + 4 + uiNameLen;

	session->mcu_task_info.send_param_count = 3;
	for (i = 0; i < 2; i++)
	{
		session->mcu_task_info.send_param[i].ptr_param_len = (u32*)ptr_len_4;
		session->mcu_task_info.send_param[i].ptr_param = (u8*)&params[i];
	}
	session->mcu_task_info.send_param[i].ptr_param_len = &uiNameLen;
	session->mcu_task_info.send_param[i].ptr_param = pucFileName;

	rst = vsm_process(session);
	return GET_FULL_ERR_CODE(rst);

	return 0;
}

u32 C_ReadFile(sis_session *session,
	u8* pucFileName,
	u32 uiNameLen,
	u32 uiOffset,
	u32* puiFileLength,
	u8* pucBuffer)
{
	u32 rst = 0, i = 0;
	u32 params[3] = { 0 };

	params[0] = htonl(uiNameLen);
	params[1] = htonl(uiOffset);
	params[2] = htonl(*puiFileLength);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_READ_FILE;
	session->mcu_task_info.send_head.data_length = 12 + uiNameLen;

	session->mcu_task_info.send_param_count = 4;
	for (i = 0; i < 3; i++)
	{
		session->mcu_task_info.send_param[i].ptr_param_len = (u32*)ptr_len_4;
		session->mcu_task_info.send_param[i].ptr_param = (u8*)&params[i];
	}
	session->mcu_task_info.send_param[i].ptr_param_len = &uiNameLen;
	session->mcu_task_info.send_param[i].ptr_param = pucFileName;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)puiFileLength;

	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	//    session->mcu_task_info.resp_param[1].ptr_param_len = (u8*)puiFileLength;  wangzhanbei
	session->mcu_task_info.resp_param[1].ptr_param = pucBuffer;

	rst = vsm_process(session);
	return GET_FULL_ERR_CODE(rst);
	return 0;
}

u32 C_WriteFile(sis_session *session,
	u8* pucFileName,
	u32 uiNameLen,
	u32 uiOffset,
	u32 uiFileLength,
	u8* pucBuffer)
{
	u32 rst = 0, i = 0;
	u32 params[3] = { 0 };

	params[0] = htonl(uiNameLen);
	params[1] = htonl(uiOffset);
	params[2] = htonl(uiFileLength);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_WRITE_FILE;
	session->mcu_task_info.send_head.data_length = 12 + uiNameLen + uiFileLength;

	session->mcu_task_info.send_param_count = 5;
	for (i = 0; i < 3; i++)
	{
		// session->mcu_task_info.send_param[i].ptr_param_len = ptr_len_4;
		session->mcu_task_info.send_param[i].ptr_param = (u8*)&params[i];
	}
	session->mcu_task_info.send_param[i].ptr_param_len = &uiNameLen;
	session->mcu_task_info.send_param[i].ptr_param = pucFileName;
	session->mcu_task_info.send_param[i + 1].ptr_param_len = &uiFileLength;
	session->mcu_task_info.send_param[i + 1].ptr_param = pucBuffer;

	// rst = vsm_process(session);
	// return GET_FULL_ERR_CODE(rst);
	return 0;
}

u32 C_DeleteFile(sis_session *session,
	u8* pucFileName,
	u32 uiNameLen)
{
	u32 rst = 0, i = 0;
	u32 params[3] = { 0 };

	params[0] = htonl(uiNameLen);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_DELETE_FILE;
	session->mcu_task_info.send_head.data_length = 4 + uiNameLen;

	session->mcu_task_info.send_param_count = 2;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = &uiNameLen;
	session->mcu_task_info.send_param[1].ptr_param = pucFileName;

	// rst = vsm_process(session);
	// return GET_FULL_ERR_CODE(rst);
	return 0;
}