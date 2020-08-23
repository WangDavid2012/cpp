#include "SDF.h"
#include "SDF_EX.h"
#include "debug.h"
#include "../base/SDFLog.h"
#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"
#include "../base/Common.h"

//#include "debug.h"         //有问题，待查

/*杂凑运算初始化*/
DLL u32 SDF_HashInit(HANDLE hSessionHandle, u32 uiAlgID, ECCrefPublicKey *pucPublicKey, u8 *pucID, u32 uiIDLength)
{
	u32 ret = 0;
	sis_session* session = NULL;

	if ((uiAlgID != SGD_SM3) && (uiAlgID != SGD_SHA1) && (uiAlgID != SGD_SHA256)) {
		return SDR_ALGNOTSUPPORT;
	}
	if (uiIDLength > 64) {
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK) {
 		memset(&(session->hash_context),0,sizeof(sis_hash_ctx_t));
		if (uiAlgID == SGD_SM3) {
			ret = C_HashInit_SM3(session, pucID, uiIDLength, (u8*)pucPublicKey, sizeof(ECCrefPublicKey));
		}
		else {
			ret = C_HashInit(session, uiAlgID, pucID, uiIDLength, (u8*)pucPublicKey, sizeof(ECCrefPublicKey));
		}
		if (ret == SDR_OK) {
			// _SDF_Log(SDF_INFO,"C_Hashinit complete......\n");
		}
		else {
			// _SDF_Log(SDF_ERR, "------>C_Hashinit,uiIDLength=%d", uiIDLength);
		}
	}
    else{
        Print_LinkList(session->device->sessionlist, SessionNodePrintf);
        std::cout << "LIB_GetSession error" << endl;
        while(1);
    }
	return ret;
}

/*多包杂凑*/
DLL u32 SDF_HashUpdate(HANDLE hSessionHandle, u8 *pucData, u32  uiDataLength)
{
	u32 ret = 0;
	sis_session* session = NULL;
	u32 offset = 0;
	u32 needSendSize = 0;

	// _SDF_Log(SDF_INFO,"SDF_HashUpdate starting......");

	if (uiDataLength == 0)
	{
		return SDR_INARGERR;
	}

	if (pucData == NULL)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK)
	{
		while (offset < uiDataLength)
		{
			needSendSize = MIN(MAX_SM3_SEND_PACKAGE_SIZE, uiDataLength - offset);
			if (session->hash_context.alg_id == SGD_SM3)
			{
				debug_printf("****** offset=%d,needSendSize=%d ****** \n", offset, needSendSize);
				ret = C_Hash_SM3(session, pucData + offset, needSendSize);
			}
			else
			{
				ret = C_Hash(session, pucData + offset, needSendSize);
			}
			if (ret != SDR_OK)
			{
				// _SDF_Log(SDF_ERR, "------>SDF_HashUpdate,uiDataLength=%d", uiDataLength);
				return ret;
			}
			offset += needSendSize;
		}
		if (ret == SDR_OK)
		{
			// _SDF_Log(SDF_INFO,"SDF_HashUpdate complete......\n");
		}
	}
	return ret;
}


/*杂凑运算结束*/
DLL u32 SDF_HashFinal(HANDLE hSessionHandle, u8 *pucHash, u32* puiHashLength)
{
	u32 ret = 0;
	sis_session* session = NULL;

	// _SDF_Log(SDF_INFO,"SDF_HashFinal starting......");
	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK)
	{
		if (session->hash_context.alg_id == SGD_SM3)
		{
			ret = C_HashFinal_SM3(session, pucHash, puiHashLength);
		}
		else
		{
			ret = C_HashFinal(session, pucHash, puiHashLength);
		}
		if (ret == SDR_OK)
		{
			// _SDF_Log(SDF_INFO,"SDF_HashFinal complete......\n");
		}
		else
		{
			// _SDF_Log(SDF_ERR, "------>C_HashFinal,puiHashLength=%d", *puiHashLength);
		}
	}
	else
	{
		debug_printf("LIB_GetSession(hSessionHandle,&session) error\n");
	}

	return ret;
}


/********************************************非标准函数***************************************************/
/*
描述：			三步式HMAC运算第一步
参数：			hSessionHandle[in]	与设备建立的会话句柄
				hKeyHandle[in]	    秘钥句柄
				uiAlgID[in]			算法ID
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL u32 SDF_MacInit(HANDLE hSessionHandle, HANDLE hKeyHandle, u32 uiAlgID)
{
	u32 ret = 0;
	sis_session* session = NULL;
	sis_work_key *key = NULL;

	if (uiAlgID != SGD_SM3)
	{
		return SDR_ALGNOTSUPPORT;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	ret = LIB_GetWorkKey(session, hKeyHandle, &key);
	if (ret == SDR_OK)
	{
		ret = C_HMAC_Init(session, key, uiAlgID);
		if (ret == SDR_OK)
		{
			// _SDF_Log(SDF_INFO, "SDF_MacInit complete......\n");
		}
		else
		{
			// _SDF_Log(SDF_ERR, "------>SDF_MacInit,KeyHandle=%p", hKeyHandle);
		}
	}
	return ret;
}
/*
描述：			三步式HMAC运算第二步
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucData[in]			缓冲区指针，用于存放输入的数据明文
				uiDataLength[in]	输入的数据明文长度（每次update的缓冲区数据小于3K+128byte）
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL u32 SDF_MacUpdate(HANDLE hSessionHandle, u8 *pucData, u32 uiDataLength)
{
	u32 ret = 0;
	sis_session* session = NULL;
	u32 offset = 0;
	u32 needSendSize = 0;

	// _SDF_Log(SDF_INFO, "SDF_MacUpdate starting......");

	if (uiDataLength == 0)
	{
		return SDR_INARGERR;
	}

	if (pucData == NULL)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK)
	{
		// while (offset < uiDataLength)
		// {
		//     needSendSize = min(MAX_SM3_SEND_PACKAGE_SIZE, uiDataLength - offset);
		//     ret = C_HMAC_Update(session, pucData + offset, needSendSize);
		//     if (ret != SDR_OK)
		//     {
		//          _SDF_Log(SDF_ERR, "------>SDF_MacUpdate,uiDataLength=%d", uiDataLength);
		//         return ret;
		//     }
		//     offset += needSendSize;
		// }
		ret = C_HMAC_Update(session, pucData, uiDataLength);
		if (ret == SDR_OK)
		{
			// _SDF_Log(SDF_INFO, "SDF_MacUpdate complete......\n");
		}
	}
	return ret;
}

/*
描述：			三步式HMAC运算第三步
参数：			hSessionHandle[in]		与设备建立的会话句柄
				pucHash[out]			输出计算的HMAC
				puiHashLength[out]		计算出的HMAC长度
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL u32 SDF_MacFinal(HANDLE hSessionHandle, u8 *pucHash, u32 *puiHashLength)
{
	u32 ret = 0;
	sis_session* session = NULL;

	// _SDF_Log(SDF_INFO,"SDF_MacFinal starting......");

	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK)
	{
		ret = C_HMAC_Final(session, pucHash, puiHashLength);
		if (ret == SDR_OK)
		{
			// _SDF_Log(SDF_INFO, "SDF_MacFinal complete......\n");
		}
		else
		{
			// _SDF_Log(SDF_ERR, "------>SDF_MacFinal,puiHashLength=%d", *puiHashLength);
		}
	}
	return ret;
}

