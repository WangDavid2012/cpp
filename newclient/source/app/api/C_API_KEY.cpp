#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"
#include "../base/Common.h"
#include "Interface.h"
#include "debug.h"



/**定义常量长度数据,方便协议组帧的操作*/
const u32 spec_len[SPEC_ELEMENT_MAX] =
{
	2,4,8,16,
	32,64,128,256,
	sizeof(DEVICEINFO),
	sizeof(ECCrefPublicKey),sizeof(RSArefPublicKey),
	sizeof(ECCCipher),(ECCref_MAX_LEN * 2 + 32),(ECCref_MAX_LEN * 2 + 32 + 4),
	sizeof(ECCrefPrivateKey),sizeof(RSArefPrivateKey),
	sizeof(ECCSignature),1,15,MAX_ECC_CIPHERLEN,
};
const u32 *const ptr_len_2 = &(spec_len[0]);
const u32 *const ptr_len_4 = &(spec_len[1]);
const u32 *const ptr_len_8 = &(spec_len[2]);
const u32 *const ptr_len_16 = &(spec_len[3]);
const u32 *const ptr_len_32 = &(spec_len[4]);
const u32 *const ptr_len_64 = &(spec_len[5]);
const u32 *const ptr_len_128 = &(spec_len[6]);
const u32 *const ptr_len_256 = &(spec_len[7]);
const u32 *const ptr_len_dev_info = &(spec_len[8]);
const u32 *const ptr_len_ecc_pub = &(spec_len[9]);
const u32 *const ptr_len_rsa_pub = &(spec_len[10]);
const u32 *const ptr_len_ecc_cipher = &(spec_len[11]);
const u32 *const ptr_len_ecc_cipher_no_LC = &(spec_len[12]);
const u32 *const ptr_len_ecc_cipher_no_C = &(spec_len[13]);
const u32 *const ptr_len_ecc_pri = &(spec_len[14]);
const u32 *const ptr_len_rsa_pri = &(spec_len[15]);
const u32 *const ptr_len_ecc_sign_data = &(spec_len[16]);
const u32 *const ptr_len_1 = &(spec_len[17]);
const u32 *const ptr_len_15 = &(spec_len[18]);
const u32 *const ptr_len_ecc_cipher_C = &(spec_len[19]);

/**描述：获取签名公钥，包括rsa签名公钥以及Ecc签名公钥*/
u32 C_GetPubSignKey_RSA(sis_session* session,
	u32 keyId,
	RSArefPublicKey *pPublicKey,
	u32* pPublicKeyLen)
{
	u32 rst = 0;
	keyId = htonl(keyId);

	session->mcu_task_info.send_head.cmd = MCU_CMD_EXPORT_SIGNPUBLICKEY_RSA; //导出RSA签名公钥
	session->mcu_task_info.send_head.data_length = 4;

	session->mcu_task_info.send_param_count = 1;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)(&keyId);

	//接收数据组帧
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = ptr_len_rsa_pub;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)(pPublicKey);
	// if(SDR_OK == (rst = vsm_process(session)))
	// {
	//     pPublicKey->bits = ntohl(pPublicKey->bits);
	// }
	// return GET_FULL_ERR_CODE(rst);
	return 0;
}

/**描述：获取加密公钥，包括rsa加密公钥以及Ecc加密公钥*/
u32 C_GetPubEncKey_RSA(sis_session* session,
	u32 keyId,
	RSArefPublicKey *pPublicKey,
	u32* pPublicKeyLen)
{
	u32 rst = 0;
	keyId = htonl(keyId);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_EXPORT_ENCPUBLICKEY_RSA;
	session->mcu_task_info.send_head.data_length = 4;

	session->mcu_task_info.send_param_count = 1;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)(&keyId);

	//接收数据组帧
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = ptr_len_rsa_pub;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pPublicKey;
	// if(SDR_OK == (rst = vsm_process(session)))
	// {
	//     pPublicKey->bits = ntohl(pPublicKey->bits);
	// }
	// return GET_FULL_ERR_CODE(rst);

	return 0;
}

/**描述：产生RSA非对密钥对并输出*/
u32 C_GenKeyPair_RSA(sis_session* session,
	u32 	uiKeySize,
	RSArefPublicKey *pPublicKey,
	RSArefPrivateKey *pPrivateKey)
{
	u32 rst = 0;
	u32 params[1] = { 0 };

	params[0] = htonl(uiKeySize);
	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_GENERATE_KEYPAIR_RSA;
	session->mcu_task_info.send_head.data_length = 4;
	session->mcu_task_info.send_param_count = 1;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = ptr_len_rsa_pub;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pPublicKey;
	// session->mcu_task_info.resp_param[1].ptr_param_len = ptr_len_rsa_pri;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)pPrivateKey;

	// if(SDR_OK == (rst = vsm_process(session)))
	// {
	//     pPublicKey->bits = ntohl(pPublicKey->bits);
	//     pPrivateKey->bits = ntohl(pPrivateKey->bits);
	// }

	// return GET_FULL_ERR_CODE(rst);
	return 0;
}

u32 C_GenKeyWithIPK_RSA(sis_session* session,
	u32 keyId,
	u32 genKeyBits,
	u32 algIdentify,
	u8* pRSACipher,
	u32* pRSACipherLen,
	HANDLE* symKeyHandle)
{
	u32 rst = 0;
	u32 params[2] = { 0 };

	params[0] = htonl(keyId);
	params[1] = htonl(genKeyBits);

	session->mcu_task_info.send_head.cmd = MCU_CMD_GENERATE_KEYWITHIPK_RSA;
	session->mcu_task_info.send_head.data_length = 4 + 4;//4+4

	session->mcu_task_info.send_param_count = 2;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	// session->mcu_task_info.send_param[1].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&params[1];

	session->mcu_task_info.resp_param_count = 3;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)symKeyHandle;
	// session->mcu_task_info.resp_param[1].ptr_param_len = ptr_len_4;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)pRSACipherLen;
	session->mcu_task_info.resp_param[2].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = pRSACipherLen;
	session->mcu_task_info.resp_param[2].ptr_param = (u8*)pRSACipher;

	// if(SDR_OK == (rst = vsm_process(session)))
	// {
	//     *symKeyHandle = ntohl(*(u32*)symKeyHandle);
	//     //LIB_CreateWorkKey(session, symKeyHandle, *(u32*)(symKeyHandle), FALSE);
	// }
	// return GET_FULL_ERR_CODE(rst);
	return 0;
}

u32 C_GenKeyWithEPK_RSA(sis_session* session,
	u32 genKeyBits,
	u32 algIdentify,
	RSArefPublicKey* pucPublicKey,
	u8* pRSACipher,
	u32* pRSACipherLen,
	HANDLE* symKeyHandle)
{
	u32 rst = 0;
	u32 params[1] = { 0 };

	params[0] = htonl(genKeyBits);
	pucPublicKey->bits = htonl(pucPublicKey->bits);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_GENERATE_KEYWITHEPK_RSA;
	session->mcu_task_info.send_head.data_length = 4 + (*ptr_len_rsa_pub);

	session->mcu_task_info.send_param_count = 2;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	// session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	// session->mcu_task_info.send_param[1].ptr_param_len = ptr_len_rsa_pub;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&pucPublicKey;

	session->mcu_task_info.resp_param_count = 3;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)symKeyHandle;
	// session->mcu_task_info.resp_param[1].ptr_param_len = ptr_len_4;
	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)pRSACipherLen;
	session->mcu_task_info.resp_param[2].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = pRSACipherLen;
	session->mcu_task_info.resp_param[2].ptr_param = (u8*)pRSACipher;

	// if(SDR_OK == (rst = vsm_process(session)))
	// {
	//     *symKeyHandle = ntohl(*(u32*)symKeyHandle);
	//     //LIB_CreateWorkKey(session, symKeyHandle, *(u32*)(symKeyHandle), FALSE);
	// }

	// pucPublicKey->bits = ntohl(pucPublicKey->bits);

	// return GET_FULL_ERR_CODE(rst);

	return 0;
}

/**描述：导入会话密钥并用内部RSA私钥解密*/
u32 C_ImportKeyWithISK_RSA(sis_session* session,
	u32 keyID,
	u8* pSessionKeyCipher,
	u32 sessionKeyCipherLen,
	HANDLE* symKeyHandle)
{
	u32 rst = 0;
	u32 param[2] = { 0 };

	param[0] = htonl(keyID);
	param[1] = htonl(sessionKeyCipherLen);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_IMPORT_KEYWITHISK_RSA; //
	session->mcu_task_info.send_head.data_length = 8 + sessionKeyCipherLen;

	session->mcu_task_info.send_param_count = 3;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)param;
	// session->mcu_task_info.send_param[1].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&param[1];
	session->mcu_task_info.send_param[2].ptr_param_len = &sessionKeyCipherLen;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)pSessionKeyCipher;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)symKeyHandle;

	// if(SDR_OK == (rst = vsm_process(session)))
	// {
	//     *symKeyHandle = ntohl(*(u32*)symKeyHandle);
	//     //**symKeyHandle = ntohl(*(u32*)symKeyHandle);
	//     //LIB_CreateWorkKey(session, symKeyHandle, *(u32*)(symKeyHandle), FALSE);
	// }

	// return GET_FULL_ERR_CODE(rst);

	return 0;
}

u32 C_ExchangeEnvelope_RSA(sis_session* session,
	u32 keyId,
	RSArefPublicKey pucPublicKey,
	u8* pucEncDataIn,
	u32 pucEncDataInLen,
	u8* pucEncDataOut,
	u32* pucEncDataOutLen)
{
	u32 rst = 0;
	u32 params[2] = { 0 };

	params[0] = htonl(keyId);
	params[1] = htonl(pucEncDataInLen);
	pucPublicKey.bits = htonl(pucPublicKey.bits);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_EXCHANGE_DIGITENVELOPE_RSA;
	session->mcu_task_info.send_head.data_length = 4 + (*ptr_len_rsa_pub) + 4 + pucEncDataInLen;//4+公钥结构+4+密文长度

	session->mcu_task_info.send_param_count = 4;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	// session->mcu_task_info.send_param[1].ptr_param_len = ptr_len_rsa_pub; wangzhanbei
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&pucPublicKey;
	// session->mcu_task_info.send_param[2].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)&params[1];
	session->mcu_task_info.send_param[3].ptr_param_len = &pucEncDataInLen;
	session->mcu_task_info.send_param[3].ptr_param = pucEncDataIn;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pucEncDataOutLen;
	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = pucEncDataOutLen;
	session->mcu_task_info.resp_param[1].ptr_param = pucEncDataOut;

	// rst = vsm_process(session);
	// return GET_FULL_ERR_CODE(rst);

	return 0;
}

/**描述:获取ecc索引下的加密公钥结构*/
u32 C_GetPubEncKey_ECC(sis_session* session,
	u32 keyId,
	ECCrefPublicKey *pPublicKey,
	u32* pPublicKeyLen)
{
	u32 rst = 0;
	keyId = htonl(keyId);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_EXPORT_ENCPUBLICKEY_ECC;//导出ECC加密公钥

	session->mcu_task_info.send_head.data_length = 4;

	session->mcu_task_info.send_param_count = 1;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)(&keyId);

	//接收数据组帧
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pPublicKey;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		pPublicKey->bits = ntohl(pPublicKey->bits);
	}
	return GET_FULL_ERR_CODE(rst);
}

/**描述：获取签名公钥，包括rsa签名公钥以及Ecc签名公钥*/
u32 C_GetPubSignKey_ECC(sis_session* session,
	u32 keyId,
	ECCrefPublicKey *pPublicKey,
	u32* pPublicKeyLen)
{
	u32 rst = 0;
	keyId = htonl(keyId);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_EXPORT_SIGNPUBLICKEY_ECC;//导出ECC签名公钥
	session->mcu_task_info.send_head.data_length = 4;

	session->mcu_task_info.send_param_count = 1;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)(&keyId);

	//接收数据组帧
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pPublicKey;
	if (SDR_OK == (rst = vsm_process(session)))
	{
		pPublicKey->bits = ntohl(pPublicKey->bits);
	}
	return GET_FULL_ERR_CODE(rst);
}

/**描述：产生ECC非对称密钥对并输出*/
u32 C_GenKeyPair_ECC(sis_session* session,
	u32	algIdentify,
	u32 	uiKeySize,
	ECCrefPublicKey *pPublicKey,
	ECCrefPrivateKey *pPrivateKey)
{
	u32 rst = 0;
	u32 params[2] = { 0 };

	params[0] = htonl(algIdentify);
	params[1] = htonl(uiKeySize);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_KEYPAIR_ECC; //生成ecc临时密钥对
	
	session->mcu_task_info.send_head.data_length = 8;

	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&(params[1]);

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pPublicKey;
	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32*)ptr_len_ecc_pri;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)pPrivateKey;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		pPublicKey->bits = ntohl(pPublicKey->bits);
		pPrivateKey->bits = ntohl(pPrivateKey->bits);
	}

	return GET_FULL_ERR_CODE(rst);
}

/**描述：生成会话密钥并用内部ECC公钥加密输出，同时返回密钥句柄*/
u32 C_GenKeyWithIPK_ECC(sis_session* session,
	u32 keyId,
	u32 genKeyBits,
	u32 algIdentify,
	ECCCipher *pEccCipher,
	HANDLE* symKeyHandle)
{
	u32 rst = 0;
	u32 params[2] = { 0 };
	u32 respKeyHandle, respKeyAddress = 0;

	params[0] = htonl(keyId);
	params[1] = htonl(genKeyBits);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_KEYWITHIPK_ECC;//生成会话密钥并用内部ECC公钥加密输出
	session->mcu_task_info.send_head.data_length = 8;

	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&params[1];

	//接收数据设置组帧
	//返回值前四个字节为临时密钥指针
	session->mcu_task_info.resp_param_count = 5;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respKeyHandle;
	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)&respKeyAddress;
	session->mcu_task_info.resp_param[2].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = (u32*)ptr_len_ecc_cipher_no_LC;
	session->mcu_task_info.resp_param[2].ptr_param = (u8*)pEccCipher;
	session->mcu_task_info.resp_param[3].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[3].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[3].ptr_param = (u8*)&(pEccCipher->L);
	session->mcu_task_info.resp_param[4].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[4].ptr_param_len = (u32*)&(pEccCipher->L);
	session->mcu_task_info.resp_param[4].ptr_param = (u8*)(pEccCipher->C);

	if (SDR_OK == (rst = vsm_process(session)))
	{
		respKeyHandle = ntohl(respKeyHandle);
		respKeyAddress = ntohl(respKeyAddress);
		// LIB_CreateWorkKey(session, symKeyHandle, respKeyHandle,respKeyAddress,WORK_KEY_TYPT_SYM_KEY,FALSE);
	}

	return GET_FULL_ERR_CODE(rst);
}

/**描述：生成会话密钥并用外部ECC公钥加密输出,同时返回密文和密钥句柄*/
u32 C_GenKeyWithEPK_ECC(sis_session* session,
	u32 genKeyBits,
	u32 algIdentify,
	ECCrefPublicKey pucPublicKey,
	ECCCipher *pEccCipher,
	HANDLE* symKeyHandle)
{
	u32 rst = 0;
	u32 param[2] = { 0 };
	u32 respKeyHandle, respKeyAddress = 0;

	u64 keyHandleAddr = 0;

	param[0] = htonl(algIdentify);
	param[1] = htonl(genKeyBits);
	pucPublicKey.bits = htonl(pucPublicKey.bits);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_KEYWITHEPK_ECC; //生成会话密钥并用外部ECC公钥加密输出
	session->mcu_task_info.send_head.data_length = 4 + 4 + (*ptr_len_ecc_pub);//4+4+ecc公钥长度

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)param;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&param[1];
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)&pucPublicKey;

	session->mcu_task_info.resp_param_count = 4;
	//  session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	// session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respKeyHandle;
	//  session->mcu_task_info.resp_param[1].ptr_param_len = (u32*)ptr_len_4;
	// session->mcu_task_info.resp_param[1].ptr_param = (u8*)&respKeyAddress;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&keyHandleAddr;

	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)ptr_len_ecc_cipher_no_LC;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)pEccCipher;

	session->mcu_task_info.resp_param[2].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[2].ptr_param = (u8*)&(pEccCipher->L);

	session->mcu_task_info.resp_param[3].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[3].ptr_param_len = &(pEccCipher->L);
	session->mcu_task_info.resp_param[3].ptr_param = (u8*)(pEccCipher->C);

	if (SDR_OK == (rst = vsm_process(session)))
	{
		rst = LIB_CreateWorkKey(session, symKeyHandle, keyHandleAddr, 1);
		debug_printf("The LIB_CreateWorkKey return 0x%02x\n", rst);
	}

	return GET_FULL_ERR_CODE(rst);
}

/**描述：导入会话密钥并用内部ECC私钥解密*/
//note:记得拆分ECC密文结构体，因为L需要转序
u32 C_ImportKeyWithISK_ECC(sis_session* session,
	u32 keyID,
	ECCCipher pSessionKeyCipher,
	HANDLE* symKeyHandle)
{
	u32 rst = 0;
	u32 params[2] = { 0 };
	u32 respKeyHandle, respKeyAddress = 0;
	u64 keyHandleAddr = 0;

	params[0] = htonl(keyID);
	params[1] = (*ptr_len_ecc_cipher_no_LC) + 4 + pSessionKeyCipher.L;
	pSessionKeyCipher.L = htonl(pSessionKeyCipher.L);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_IMPORT_KEYWITHISK_ECC;
	session->mcu_task_info.send_head.data_length = 4 + params[1];

	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	//ECC密文内容
	session->mcu_task_info.send_param[1].ptr_param_len = &params[1];
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&pSessionKeyCipher;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&keyHandleAddr;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		rst = LIB_CreateWorkKey(session, symKeyHandle, keyHandleAddr, 1);
		debug_printf("LIB_CreateWorkKey rst=0x%02x\n", rst);
	}
	return GET_FULL_ERR_CODE(rst);
}



u32 C_GenerateAgreementDataWithECC(sis_session* session,
	u32 keyId,
	u32 agreementkeyBits,
	u8* sponsorID,
	u32 sponsorIDLength,
	ECCrefPublicKey *pucPublicKey,
	ECCrefPublicKey *pucTmpPublicKey,
	HANDLE* phAgreementHandle)
{
	u32 rst = 0;
	sis_agreement_context* handle = NULL;

	HANDLE agreeHandle = NULL;
	u32 publicKeySize = 0, sendKeyId = 0;
	u64 respPubKeyAddress = 0, respPrvKeyAddress = 0;

	rst = LIB_CreateAgreementContext(session, &agreeHandle, 1);
	rst = LIB_GetAgreementContext(session, agreeHandle, &handle);

	memcpy(handle->sponsorid, sponsorID, sponsorIDLength);
	handle->sponsorid_size = sponsorIDLength;
	handle->selfKeyIndex = keyId;
	handle->keyBitSize = agreementkeyBits;

	int i = 0;

	sendKeyId = htonl(keyId);
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_AGREEMENTDATA_ECC;
	session->mcu_task_info.send_head.data_length = 4;

	session->mcu_task_info.send_param_count = 1;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&sendKeyId;

	session->mcu_task_info.resp_param_count = 4;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respPubKeyAddress;

	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)&respPrvKeyAddress;

	session->mcu_task_info.resp_param[2].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.resp_param[2].ptr_param = (u8*)pucTmpPublicKey;

	session->mcu_task_info.resp_param[3].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[3].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.resp_param[3].ptr_param = (u8*)pucPublicKey;

	if (SDR_OK == (rst = vsm_process(session))) {
		// LIB_CreateWorkKey(session, (void **)&(handle->tempPubKey) ,respPubKeyAddress,1);
		// LIB_CreateWorkKey(session, (void **)&(handle->tempPrvKey),respPrvKeyAddress,1);
		// handle->agreePubkey.key_handle_addr = respPubKeyAddress;
		// handle->agreePrikey.key_handle_addr = respPrvKeyAddress;

		handle->agreePubkeyHandleAddr = respPubKeyAddress;
		handle->agreePrikeyHandleAddr = respPrvKeyAddress;

		pucPublicKey->bits = ntohl(pucPublicKey->bits);
		pucTmpPublicKey->bits = ntohl(pucTmpPublicKey->bits);

		*phAgreementHandle = handle;
		//debug_printf("----------return handle 0x%02x\n", handle);
		//debug_printf("----------The respPubKeyAddress:0x%llx , respPrvKeyAddress:0x%llx \n", respPubKeyAddress, respPrvKeyAddress);
	}
	else {
		LIB_ReleaseAgreementContext(session, handle, 1);
	}
	return GET_FULL_ERR_CODE(rst);

}

/**描述：计算会话密钥*/
u32 C_GenerateKeyWithECC(sis_session* session,
	u8* pucResponseID,
	u32 pucResponseIDLength,
	ECCrefPublicKey pucResponsePublicKey,
	ECCrefPublicKey pucResponseTmpPublicKey,
	HANDLE phAgreementHandle,
	HANDLE* phKeyHandle)
{
	u32 rst = 0;
	sis_agreement_context* handle = NULL;
	u64 respKeyAddress = 0;
	rst = LIB_GetAgreementContext(session, phAgreementHandle, &handle);



	u64 aTmpPKAddr = handle->agreePubkeyHandleAddr;
	u64 aTmpSKAddr = handle->agreePrikeyHandleAddr;

	u32 aKeyIndex = htonl(handle->selfKeyIndex);
	pucResponsePublicKey.bits = htonl(pucResponsePublicKey.bits);
	pucResponseTmpPublicKey.bits = htonl(pucResponseTmpPublicKey.bits);
	u32 aIdSize = htonl(handle->sponsorid_size);
	u32 bIdSize = htonl(pucResponseIDLength);
	u32 keySize = htonl(handle->keyBitSize);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_SESSIONKEY_ECC;
	session->mcu_task_info.send_head.data_length = 8 + 8 + 4 + \
		ECCref_PublicKey_SIZE + \
		ECCref_PublicKey_SIZE + \
		4 + \
		handle->sponsorid_size + \
		4 + \
		pucResponseIDLength + \
		4;

	session->mcu_task_info.send_param_count = 10;

	//此处地址长度需要核实一下
	session->mcu_task_info.send_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&aTmpPKAddr;

	session->mcu_task_info.send_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&aTmpSKAddr;

	session->mcu_task_info.send_param[2].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)&aKeyIndex;
	session->mcu_task_info.send_param[3].ptr_param_len = (u32 *)ptr_len_ecc_pub;
	session->mcu_task_info.send_param[3].ptr_param = (u8*)&pucResponsePublicKey;
	session->mcu_task_info.send_param[4].ptr_param_len = (u32 *)ptr_len_ecc_pub;
	session->mcu_task_info.send_param[4].ptr_param = (u8*)&pucResponseTmpPublicKey;
	session->mcu_task_info.send_param[5].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[5].ptr_param = (u8*)&aIdSize;
	session->mcu_task_info.send_param[6].ptr_param_len = &(handle->sponsorid_size);
	session->mcu_task_info.send_param[6].ptr_param = handle->sponsorid;
	session->mcu_task_info.send_param[7].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[7].ptr_param = (u8*)&bIdSize;
	session->mcu_task_info.send_param[8].ptr_param_len = &pucResponseIDLength;
	session->mcu_task_info.send_param[8].ptr_param = pucResponseID;
	session->mcu_task_info.send_param[9].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.send_param[9].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[9].ptr_param = (u8*)&keySize;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respKeyAddress;


	if (SDR_OK == (rst = vsm_process(session)))
	{
		debug_printf("----------The respKeyAddress is 0x%llx\n", respKeyAddress);
		LIB_CreateWorkKey(session, phKeyHandle, respKeyAddress, 1);
		//Print_LinkList(session->device->worklist, WorkkeyNodePrintf);
		debug_printf("-----------the size is %d\n", session->device->worklist->size);
		LIB_ReleaseAgreementContext(session, handle, 1);
		debug_printf("-----------the size is %d\n", session->device->worklist->size);
	}

	return GET_FULL_ERR_CODE(rst);
}

/**描述：产生协商数据并计算会话密钥*/
u32 C_GenerateAgreementDataAndKeyWithECC(sis_session* session,
	u32 keyId,
	u32 uiKeyBits,
	u8* responseID,
	u32 responseIDLength,
	u8* sponsorID,
	u32 sponsorIDLength,
	ECCrefPublicKey sponsorPublicKey,
	ECCrefPublicKey sponsorTmpPublicKey,
	ECCrefPublicKey *responsePublicKey,
	ECCrefPublicKey *responseTmpPublicKey,
	HANDLE* phKeyHandle)
{
	u32 rst = 0;
	u64 respKeyAddress = 0;


	u32 bKeyIndex = htonl(keyId);
	sponsorPublicKey.bits = htonl(sponsorPublicKey.bits);
	sponsorTmpPublicKey.bits = htonl(sponsorTmpPublicKey.bits);
	u32 aIdSize = htonl(sponsorIDLength);
	u32 bIdSize = htonl(responseIDLength);
	u32 keySize = htonl(uiKeyBits);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_AGREEMENTDATAKEY_ECC;
	session->mcu_task_info.send_head.data_length = 4 * 4 + ECCref_PublicKey_SIZE * 2 + sponsorIDLength + responseIDLength;

	session->mcu_task_info.send_param_count = 8;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&bKeyIndex;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32 *)ptr_len_ecc_pub;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&sponsorPublicKey;
	session->mcu_task_info.send_param[2].ptr_param_len = (u32 *)ptr_len_ecc_pub;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)&sponsorTmpPublicKey;
	session->mcu_task_info.send_param[3].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[3].ptr_param = (u8*)&aIdSize;
	session->mcu_task_info.send_param[4].ptr_param_len = &sponsorIDLength;
	session->mcu_task_info.send_param[4].ptr_param = sponsorID;
	session->mcu_task_info.send_param[5].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[5].ptr_param = (u8*)&bIdSize;
	session->mcu_task_info.send_param[6].ptr_param_len = &responseIDLength;
	session->mcu_task_info.send_param[6].ptr_param = responseID;
	session->mcu_task_info.send_param[7].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[7].ptr_param = (u8*)&keySize;

	session->mcu_task_info.resp_param_count = 3;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respKeyAddress;
	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)ptr_len_ecc_pub;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)responsePublicKey;
	session->mcu_task_info.resp_param[2].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = (u32 *)ptr_len_ecc_pub;
	session->mcu_task_info.resp_param[2].ptr_param = (u8*)responseTmpPublicKey;



	if (SDR_OK == (rst = vsm_process(session)))
	{
		debug_printf("-----------The respKeyAddress is 0x%llx,sessionAddress is 0x%llx\n", respKeyAddress, session->session_address);
		LIB_CreateWorkKey(session, phKeyHandle, respKeyAddress, 1);

		//Print_LinkList(session->device->worklist, WorkkeyNodePrintf);
		debug_printf("-----------the size is %d\n", session->device->worklist->size);
		responsePublicKey->bits = ntohl(responsePublicKey->bits);
		responseTmpPublicKey->bits = ntohl(responseTmpPublicKey->bits);
	}

	return GET_FULL_ERR_CODE(rst);
}

/** 描述：数字信封转换，使用ECC算法*/
u32 C_ExchangeEnvelope_ECC(sis_session* session,
	u32 algIdentify,
	u32 keyId,
	ECCrefPublicKey pucPublicKey,
	ECCCipher pucEncDataIn,
	ECCCipher *pucEncDataOut)
{
	u32 rst = 0;
	u32 params[4] = { 0 };
	int i = 0;

	params[0] = htonl(keyId);
	params[1] = htonl(algIdentify);
	params[2] = (*ptr_len_ecc_cipher_no_LC) + 4 + pucEncDataIn.L;
	params[3] = htonl(pucEncDataIn.L);

	pucPublicKey.bits = htonl(pucPublicKey.bits);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_EXCHANGE_DIGITENVELOPE_ECC;
	session->mcu_task_info.send_head.data_length = 4 + 4 + (*ptr_len_ecc_pub) + params[2];

	session->mcu_task_info.send_param_count = 6;
	for (i = 0; i < 2; i++)
	{
		session->mcu_task_info.send_param[i].ptr_param_len = (u32*)ptr_len_4;
		session->mcu_task_info.send_param[i].ptr_param = (u8*)&(params[i]);
	}
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)&pucPublicKey;
	session->mcu_task_info.send_param[3].ptr_param_len = (u32*)ptr_len_ecc_cipher_no_LC;
	session->mcu_task_info.send_param[3].ptr_param = (u8*)&pucEncDataIn;
	session->mcu_task_info.send_param[4].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[4].ptr_param = (u8*)&params[3];
	session->mcu_task_info.send_param[5].ptr_param_len = &(pucEncDataIn.L);
	session->mcu_task_info.send_param[5].ptr_param = (u8*)&(pucEncDataIn.C);

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_ecc_cipher_no_C;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pucEncDataOut;
	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = &(pucEncDataOut->L);
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)(pucEncDataOut->C);

	rst = vsm_process(session);
	return GET_FULL_ERR_CODE(rst);
}

/**描述：生成会话密钥并用内部密钥加密密钥加密输出*/
u32 C_GenKeyWithKEK(sis_session* session,
	u32 keyId,
	u32 algIdentify,
	u32 uiKeyBits,
	u8* pKeyCipher,
	u32* pKeyCipherLen,
	HANDLE* symKeyHandle)
{
	u32 rst = 0;
	u32 params[3] = { 0 };
	u64 respKeyAddress = 0;

	params[0] = htonl(keyId);
	params[1] = htonl(algIdentify);
	params[2] = htonl(uiKeyBits);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_KEK_MANAGE; //生成会话密钥并用密钥加密密钥加密输出
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_GENERATE_KEY_KEK;

	session->mcu_task_info.send_head.data_length = 12;              //4+4+4

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&params[0];
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&params[1];
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)&params[2];

	session->mcu_task_info.resp_param_count = 3;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respKeyAddress;

	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)pKeyCipherLen;
	session->mcu_task_info.resp_param[2].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = pKeyCipherLen;
	session->mcu_task_info.resp_param[2].ptr_param = pKeyCipher;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		LIB_CreateWorkKey(session, symKeyHandle, respKeyAddress, 1);
	}

	return GET_FULL_ERR_CODE(rst);
}

/**描述：导入会话密钥并用内部密钥加密密钥解密,同时返回密钥句柄*/
u32 C_ImportKeyWithKEK(sis_session* session,
	u32 keyId,
	u32 algIdentify,
	u8* pKeyCipher,
	u32 pKeyCipherLen,
	HANDLE* symKeyHandle)
{
	u32 rst = 0;
	u32 params[3] = { 0 };
	int i = 0;
	u64 respKeyAddress = 0;

	params[0] = htonl(keyId);
	params[1] = htonl(algIdentify);
	params[2] = htonl(pKeyCipherLen);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_KEK_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_IMPORT_KEY_KEK;
	session->mcu_task_info.send_head.data_length = 4 + 4 + 4 + pKeyCipherLen;//4+4+4+密文长度s

	session->mcu_task_info.send_param_count = 4;
	for (i = 0; i < 3; i++)
	{
		session->mcu_task_info.send_param[i].ptr_param_len = (u32*)ptr_len_4;
		session->mcu_task_info.send_param[i].ptr_param = (u8*)&params[i];
	}
	session->mcu_task_info.send_param[i].ptr_param_len = &pKeyCipherLen;
	session->mcu_task_info.send_param[i].ptr_param = pKeyCipher;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)&respKeyAddress;

	if (SDR_OK == (rst = vsm_process(session)))
	{
		LIB_CreateWorkKey(session, symKeyHandle, respKeyAddress, 1);
	}

	return GET_FULL_ERR_CODE(rst);
}


u32 C_DestorySymKey(sis_session* session, sis_work_key *key)
{
	u32 rst = 0;
	u64 keyaddr = key->key_handle_addr;

	debug_printf("The keyaddr is 0x%llx\n", keyaddr);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_KEY_MANAGE;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_DESTROY_KEY;
	session->mcu_task_info.send_head.data_length = 8;

	session->mcu_task_info.send_param_count = 1;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&keyaddr;

	session->mcu_task_info.resp_param_count = 0;

	rst = vsm_process(session);
	if (rst == SDR_OK) {
		rst = LIB_ReleaseWorkKey(session, key, 1);
	}
	return GET_FULL_ERR_CODE(rst);
}