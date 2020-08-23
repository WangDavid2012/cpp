#include "SDF.h"
#include "SDF_EX.h"
#include "../base/SDFLog.h"
#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"

#define MAXBUFFERSIZE	1024*48


/*
描述：			在密码设备内部创建用于存储用户数据的文件
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucFileName[in]	    缓冲区指针，用于存放输入的文件名，最大长度128字节
				uiNameLen[in]	    文件名长度
				uiFileSize[in]	    文件所占存储空间的长度
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL u32 SDF_CreateFile(HANDLE hSessionHandle,
	u8 *pucFileName,
	u32 uiNameLen,
	u32 uiFileSize)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if ((pucFileName == NULL) || (uiNameLen == 0)) {
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_CreateFile(session, pucFileName, uiFileSize);
		if (ret != 0) {
			// _SDF_Log(SDF_ERR, "------>C_CreateFile,ret=%d", ret);
		}
	}
	return ret;
}

/*
描述：		读取在密码设备内部存储用户数据的文件的内容
参数：		hSessionHandle[in]	    与设备建立的会话句柄
			pucFileName[in]	        缓冲区指针，用于存放输入的文件名，最大长度128字节
			uiNameLen[in]	        文件名长度
			uiOffset[in]	        指定读取文件时的偏移值
			puiFileLength[in|out]	入参时指定读取文件内容的长度；出参时返回实际读取文件内容的长度
			pucBuffer[out]	        缓冲区指针，用于存放读取的文件数据
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL u32 SDF_ReadFile(HANDLE hSessionHandle,
	u8 *pucFileName,
	u32 uiNameLen,
	u32 uiOffset,
	u32  *puiFileLength,
	u8 *pucBuffer)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if ((pucFileName == NULL) || (uiNameLen == 0)) {
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_ReadFile(session, pucFileName, uiNameLen, uiOffset, puiFileLength, pucBuffer);
		if (ret != 0) {
			// _SDF_Log(SDF_ERR, "------>C_ReadFile,ret=%d", ret);
		}
	}
	return ret;
}

/*
描述：			向密码设备内部存储用户数据的文件中写入内容
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucFileName[in]	    缓冲区指针，用于存放输入的文件名，最大长度128字节
				uiNameLen[in]	    文件名长度
				uiOffset[in]	    指定写入文件时的偏移值
				uiFileLength[in]	指定写入文件内容的长度
				pucBuffer[in]	    缓冲区指针，用于存放输入的写文件数据
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL u32 SDF_WriteFile(HANDLE hSessionHandle,
	u8 *pucFileName,
	u32 uiNameLen,
	u32 uiOffset,
	u32  uiFileLength,
	u8 *pucBuffer)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;


	if ((pucFileName == NULL) || (uiNameLen == 0)) {
		return SDR_INARGERR;
	}

	if (uiFileLength > (MAXBUFFERSIZE - 64)) {
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_WriteFile(session, pucFileName, uiNameLen, uiOffset, uiFileLength, pucBuffer);
		if (ret != 0) {
			// _SDF_Log(SDF_ERR, "------>C_WriteFile,ret=%d", ret);
		}
	}
	return ret;
}

/* 删除文件*/
DLL u32 SDF_DeleteFile(HANDLE hSessionHandle, u8 *pucFileName, u32 uiNameLen)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if ((pucFileName == NULL) || (uiNameLen == 0)) {
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_DeleteFile(session, pucFileName, uiNameLen);
		if (ret != 0) {
			// _SDF_Log(SDF_ERR, "------>C_CreateFile,ret=%d", ret);
		}
	}
	return ret;
}
