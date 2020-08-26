#include "../sdf/SDF.h"
#include "../sdf/SDF_EX.h"
#include "../base/Context.h"
#include "../base/SDFLog.h"
#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "Interface.h"


/**导入临时公钥**/
u32 C_ImportPublicKey_ECC(sis_session* session, ECCrefPublicKey pucPublicKey, HANDLE* phKeyHandle)
{
	u32 rst = 0;
	u64 rspkeyaddr = 0;
	u32 sendKeyLength = 0;
	u32 keyBitLength = 0;
	u8* keyDataHandle = (u8 *)&pucPublicKey;
	keyDataHandle += 4;

	sendKeyLength = ECCref_PublicKey_SIZE - 4;
	keyBitLength = htonl(ECCref_BITS_SIZE);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_EXT_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_IMPORT_PUBLICKEY_ECC;

	session->mcu_task_info.send_head.data_length = ECCref_PublicKey_SIZE;

	session->mcu_task_info.send_param_count = 2;

	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&keyBitLength;
	session->mcu_task_info.send_param[1].ptr_param_len = &sendKeyLength;
	session->mcu_task_info.send_param[1].ptr_param = keyDataHandle;

	u32 len = 0;
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&rspkeyaddr;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		rst = LIB_CreateWorkKey(session, phKeyHandle, rspkeyaddr, 1);
	}
	return GET_FULL_ERR_CODE(rst);
}

/**导入临时对称密钥**/
u32 C_ImportKey(sis_session* session, u8* pucKey, u32 uiKeyLength, HANDLE* phKeyHandle)
{
	u32 rst = 0;
	u32 sendKeyLength = 8;
	sendKeyLength = SM14_CHUNK_SIZE;

	u64 keyhandleaddr = 0;

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_EXT_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_IMPORT_KEY;
	session->mcu_task_info.send_head.data_length = sendKeyLength;

	session->mcu_task_info.send_param_count = 1;
	session->mcu_task_info.send_param[0].ptr_param_len = &sendKeyLength;
	session->mcu_task_info.send_param[0].ptr_param = pucKey;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&keyhandleaddr;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		rst = LIB_CreateWorkKey(session, phKeyHandle, keyhandleaddr, 1);
	}
	debug_printf("The importkey keyhandleaddr is 0x%llx\n",keyhandleaddr);
	return GET_FULL_ERR_CODE(rst);
}

/**产生临时对称密钥**/
u32 C_GenerateKeyHandle(sis_session* session, HANDLE* phKeyHandle)
{
	u32 rst = 0;
	u64 respKeyAddress = 0;

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_EXT_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_KEY_HANDLE;
	session->mcu_task_info.send_head.data_length = 0;
	session->mcu_task_info.send_param_count = 0;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respKeyAddress;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		LIB_CreateWorkKey(session, phKeyHandle, respKeyAddress, 1);
	}
	return GET_FULL_ERR_CODE(rst);
}

/**产生临时非对称密钥**/
u32 C_GenerateKeyHandle_ECC(sis_session* session, HANDLE* phPkHandle, HANDLE* phSkHandle)
{
	u32 rst = 0;
	u32 respPubKeyHandle, respPrvKeyHandle, respPubKeyAddress, respPrvKeyAddress = 0;

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_EXT_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_KEY_HANDLE;
	session->mcu_task_info.send_head.data_length = 0;
	session->mcu_task_info.send_param_count = 0;

	session->mcu_task_info.resp_param_count = 4;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respPubKeyHandle;
	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)&respPubKeyAddress;
	session->mcu_task_info.resp_param[2].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.resp_param[2].ptr_param = (u8*)&respPrvKeyHandle;

	session->mcu_task_info.resp_param[3].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[3].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.resp_param[3].ptr_param = (u8*)&respPrvKeyAddress;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		respPubKeyHandle = ntohl(respPubKeyHandle);
		respPubKeyAddress = ntohl(respPubKeyAddress);
		//         LIB_CreateWorkKey(session, phPkHandle, respPubKeyHandle,respPubKeyAddress,WORK_KEY_TYPT_ECC_PK,FALSE);
		respPrvKeyHandle = ntohl(respPrvKeyHandle);
		respPrvKeyAddress = ntohl(respPrvKeyAddress);
		//         LIB_CreateWorkKey(session, phSkHandle, respPrvKeyHandle,respPrvKeyAddress,WORK_KEY_TYPT_ECC_SK,FALSE);
	}

	return GET_FULL_ERR_CODE(rst);
}

/**使用临时对称密钥导出工作密钥**/
u32 C_ExportKeyWithKey(sis_session* session, sis_work_key *key, sis_work_key *workkey, u8* pucEncKey, u32* puiKeyLength)
{
	// u32 rst = 0;
	// u32 keyAddress = LIB_GetMcuWorkKeyAddress(key);
	// keyAddress = htonl(keyAddress);
	// u32 workkeyAddress = LIB_GetMcuWorkKeyAddress(workkey);
	// workkeyAddress = htonl(workkeyAddress);

	u32 rst = 0;
	u32 keyAddress = 0;
	keyAddress = htonl(keyAddress);
	u32 workkeyAddress = 0;
	workkeyAddress = htonl(workkeyAddress);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_EXT_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_EXPORT_KEY_WITH_KEY;
	session->mcu_task_info.send_head.data_length = 4;
	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&keyAddress;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&workkeyAddress;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)puiKeyLength;
	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = puiKeyLength;
	session->mcu_task_info.resp_param[1].ptr_param = pucEncKey;

	rst = vsm_process(session);

	return GET_FULL_ERR_CODE(rst);
}

/**使用临时公钥导出工作密钥**/
u32 C_ExportKeyWithKey_ECC(sis_session* session, sis_work_key *key, sis_work_key *workkey, ECCCipher *pEccCipher)
{
	// u32 rst = 0;
	// u32 keyAddress = LIB_GetMcuWorkKeyAddress(key);
	// keyAddress = htonl(keyAddress);
	// u32 workkeyAddress = LIB_GetMcuWorkKeyAddress(workkey);
	// workkeyAddress = htonl(workkeyAddress);

	u32 rst = 0;
	u32 keyAddress = 0;
	keyAddress = htonl(keyAddress);
	u32 workkeyAddress = 0;
	workkeyAddress = htonl(workkeyAddress);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_EXT_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_EXPORT_KEY_WITH_KEY_ECC;
	session->mcu_task_info.send_head.data_length = 4;
	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&keyAddress;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&workkeyAddress;

	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_ecc_cipher_no_LC;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pEccCipher;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)&(pEccCipher->L);
	session->mcu_task_info.resp_param[2].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = &(pEccCipher->L);
	session->mcu_task_info.resp_param[2].ptr_param = (u8*)(pEccCipher->C);

	rst = vsm_process(session);
	return GET_FULL_ERR_CODE(rst);
}