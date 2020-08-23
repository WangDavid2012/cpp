#include "SDF.h"
#include "SDF_EX.h"
#include "../base/Context.h"
#include "../base/SDFLog.h"
#include "../api/C_API_EX.h"



/**导入临时公钥**/
DLL u32 SDF_ImportPublicKey_ECC(HANDLE hSessionHandle, ECCrefPublicKey pucPublicKey, HANDLE* phKeyHandle)
{
	u32 ret = 0;
	sis_session *session = NULL;

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_ImportPublicKey_ECC(session, pucPublicKey, phKeyHandle);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "C_ImportWorkKey,ret(0x%x)",ret);
		}
	}
	return ret;
}

/**导入临时对称密钥**/
DLL u32 SDF_ImportKey(HANDLE hSessionHandle, u8* pucKey, u32 uiKeyLength, HANDLE* phKeyHandle)
{
	u32 ret = 0;
	sis_session *session = NULL;

	if ((pucKey == NULL) || (uiKeyLength != 16))
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_ImportKey(session, pucKey, uiKeyLength, phKeyHandle);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>SDF_ImportKey,ret(0x%x)",ret);
		}
	}
	return ret;

}

/**产生临时对称密钥**/
DLL u32 SDF_GenerateKeyHandle(HANDLE hSessionHandle, HANDLE* phKeyHandle)
{
	u32 ret = 0;
	sis_session* session = NULL;

	// ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_GenerateKeyHandle(session, phKeyHandle);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>SDF_GenerateKeyHandle,ret(0x%x)",ret);
		}
	}
	return ret;

}

/**产生临时非对称密钥**/
DLL u32 SDF_GenerateKeyHandle_ECC(HANDLE hSessionHandle, HANDLE* phPkHandle, HANDLE* phSkHandle)
{
	u32 ret = 0;
	sis_session* session = NULL;

	// ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_GenerateKeyHandle_ECC(session, phPkHandle, phSkHandle);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>SDF_GenerateKeyHandle_ECC,ret(0x%x)",ret);
		}
	}
	return ret;

}

/**使用临时对称密钥导出工作密钥**/
DLL u32 SDF_ExportKeyWithKey(HANDLE hSessionHandle, HANDLE hKeyHandle, HANDLE hWorkKeyHandle, u8* pucEncKey, u32* puiKeyLength)
{
	u32 ret = 0;

	sis_session* session = NULL;
	sis_work_key *key = NULL;
	sis_work_key *workkey = NULL;


	// ret = LIB_GetSession(hSessionHandle,&session);
	// ret = LIB_GetWorkKey(hKeyHandle,&key);
	// ret = LIB_GetWorkKey(hWorkKeyHandle,&workkey);
	if (SDR_OK == ret)
	{
		ret = C_ExportKeyWithKey(session, key, workkey, pucEncKey, puiKeyLength);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>SDF_ExportKeyWithKey,ret(0x%x)",ret);
		}
	}
	return ret;


}

/**使用临时公钥导出工作密钥**/
DLL u32 SDF_ExportKeyWithKey_ECC(HANDLE hSessionHandle, HANDLE hKeyHandle, HANDLE hWorkKeyHandle, ECCCipher *pEccCipher)
{
	u32 ret = 0;

	sis_session* session = NULL;
	sis_work_key *key = NULL;
	sis_work_key *workkey = NULL;


	// ret = LIB_GetSession(hSessionHandle,&session);
	// ret = LIB_GetWorkKey(hKeyHandle,&key);
	// ret = LIB_GetWorkKey(hWorkKeyHandle,&workkey);
	if (SDR_OK == ret)
	{
		ret = C_ExportKeyWithKey_ECC(session, key, workkey, pEccCipher);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>SDF_ExportKeyWithKey,ret(0x%x)",ret);
		}
	}
	return ret;
}



