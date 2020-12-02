#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"
#include "../base/Common.h"
#include "../base/SDFLog.h"
#include "../base/Util.h"

#include "interface.h"
#include <string.h>

/*客户端库全局上下文对象*/
// extern sis_sdf_lib_ctx *context;

/*描述：公钥运算函数，使用rsa公钥运算,用RSA公钥对数据进行加密操作*/
u32 C_ExternPublicKeyOperationEnc_RSA(sis_session* session,
	RSArefPublicKey pPublicKey,  //做值拷贝
	u8* pDataInput,
	u32 uiDataInputLen,
	u8* pDataOut,
	u32* puiDataOutLen)
{
	u32 rst = 0;
	u32 params[1] = { 0 };

	params[0] = htonl(uiDataInputLen);
	pPublicKey.bits = htonl(pPublicKey.bits);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_EXTERNAL_PUBLICKEY_RSA;
	//printf("&&&&&&&&&&&&&&&&&&&&[%d][%d].\n",(*ptr_len_rsa_pub),uiDataInputLen);
	session->mcu_task_info.send_head.data_length = (*ptr_len_rsa_pub) + 4 + uiDataInputLen;

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_rsa_pub;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&pPublicKey;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[2].ptr_param_len = &uiDataInputLen;
	session->mcu_task_info.send_param[2].ptr_param = pDataInput;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)puiDataOutLen;
	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = puiDataOutLen;
	session->mcu_task_info.resp_param[1].ptr_param = pDataOut;

	rst = vsm_process(session,nullptr);
	return GET_FULL_ERR_CODE(rst);
}

/*描述:使用内部索引位置的RSA公钥对数据进行计算*/
u32 C_InterPublicKeyOperation_RSA(sis_session* session,
	u32 keyId,
	u8* pDataInput,
	u32 uiDataInputLen,
	u8* pDataOut,
	u32* puiDataOutLen)
{
	u32 rst = 0;
	u32 params[2] = { 0 };

	params[0] = htonl(keyId);
	params[1] = htonl(uiDataInputLen);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_INTERNAL_PUBLICKEY_RSA;
	session->mcu_task_info.send_head.data_length = 4 + 4 + uiDataInputLen;

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&params[1];
	session->mcu_task_info.send_param[2].ptr_param_len = &uiDataInputLen;
	session->mcu_task_info.send_param[2].ptr_param = pDataInput;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)puiDataOutLen;
	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = puiDataOutLen;
	session->mcu_task_info.resp_param[1].ptr_param = pDataOut;

	rst = vsm_process(session,nullptr);
	return GET_FULL_ERR_CODE(rst);
}

/*描述:使用内部索引位置的RSA私钥对数据进行计算*/
u32 C_InterPrivateKeyOperation_RSA(sis_session* session,
	u32 keyId,
	u8* pDataInput,
	u32 uiDataInputLen,
	u8* pDataOut,
	u32* puiDataOutLen)
{
	u32 rst = 0;
	u32 params[2] = { 0 };

	params[0] = htonl(keyId);
	params[1] = htonl(uiDataInputLen);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_INTERNAL_PRIVATEKEY_RSA;
	session->mcu_task_info.send_head.data_length = 4 + 4 + uiDataInputLen;

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&params[1];
	session->mcu_task_info.send_param[2].ptr_param_len = &uiDataInputLen;
	session->mcu_task_info.send_param[2].ptr_param = pDataInput;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)puiDataOutLen;
	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = puiDataOutLen;
	session->mcu_task_info.resp_param[1].ptr_param = pDataOut;

	rst = vsm_process(session,nullptr);
	return GET_FULL_ERR_CODE(rst);
}

/*描述:使用内部ECC私钥对数据进行签名*/
u32 C_InterSign_ECC_MCU(sis_session* session,
	u32 keyId,
	u8*pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature)
{
	u32 rst = 0;
	u32 params[2] = { 0 };

	params[0] = htonl(keyId);
	params[1] = htonl(uiDataInputLen);

	session->mcu_task_info.send_head.cmd = MCU_CMD_INTERNAL_SIGN_ECC;
	session->mcu_task_info.send_head.data_length = 4 + 4 + uiDataInputLen;

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&params[1];
	session->mcu_task_info.send_param[2].ptr_param_len = &uiDataInputLen;
	session->mcu_task_info.send_param[2].ptr_param = pucData;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_ecc_sign_data;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pucSignature;

	rst = vsm_process(session,nullptr);

	return GET_FULL_ERR_CODE(rst);
}

/*描述:使用内部ECC公钥对ECC签名值进行验证运算*/
u32 C_InterVerify_ECC_MCU(sis_session* session,
	u32 keyId,
	u8*pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature)
{
	u32 rst = 0;
	u32 params[3] = { 0 };

	params[0] = htonl(keyId);
	params[1] = htonl(uiDataInputLen);
	params[2] = (*ptr_len_ecc_sign_data) / 2;//(2 * 2);

	session->mcu_task_info.send_head.cmd = MCU_CMD_INTERNAL_VERIFY_ECC;
	session->mcu_task_info.send_head.data_length = 4 + 4 + uiDataInputLen + 2 * params[2];

	session->mcu_task_info.send_param_count = 4;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_ecc_sign_data;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)pucSignature;
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)&params[1];
	session->mcu_task_info.send_param[3].ptr_param_len = &uiDataInputLen;
	session->mcu_task_info.send_param[3].ptr_param = pucData;
	rst = vsm_process(session,nullptr);
	return GET_FULL_ERR_CODE(rst);
}

/*描述:使用外部ECC公钥对ECC签名值进行验证计算*/
u32 C_ExternVerify_ECC_MCU(sis_session* session,
	u32 algIdentify,
	ECCrefPublicKey pucPublicKey,
	u8*pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature)
{
	u32 rst = 0;
	u32 params[2] = { 0 };

	params[0] = htonl(algIdentify);
	params[1] = htonl(uiDataInputLen);
	pucPublicKey.bits = htonl(pucPublicKey.bits);

	// memset(&(session->mcu_task_info),0,sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_EXTERNAL_VERIFY_ECC;
	session->mcu_task_info.send_head.data_length = 4 + 4 + uiDataInputLen + (*ptr_len_ecc_pub) + (*ptr_len_ecc_sign_data);

	session->mcu_task_info.send_param_count = 5;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&pucPublicKey;
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_ecc_sign_data;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)pucSignature;
	session->mcu_task_info.send_param[3].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[3].ptr_param = (u8*)&params[1];
	session->mcu_task_info.send_param[4].ptr_param_len = &uiDataInputLen;
	session->mcu_task_info.send_param[4].ptr_param = pucData;
	rst = vsm_process(session,nullptr);
	debug_printf("C_ExternVerify_ECC_MCU status:0x%02x\n", session->mcu_task_info.resp_head.status);
	return GET_FULL_ERR_CODE(rst);
}

/*描述:使用外部ECC公钥对数据进行加密运算*/
u32 C_ExternalEncrypt_ECC_MCU(sis_session *session,
	u32 algIdentify,
	ECCrefPublicKey pucPublicKey, //做值拷贝
	u8*pucData,
	u32 uiDataLength,
	ECCCipher *pucEncData)
{
	u32 rst = 0;
	u32 params[2] = { 0 };

	params[0] = htonl(algIdentify);
	params[1] = htonl(uiDataLength);
	pucPublicKey.bits = htonl(pucPublicKey.bits);

	session->mcu_task_info.send_head.cmd = MCU_CMD_EXTERNAL_ENCRYPT_ECC;
	session->mcu_task_info.send_head.data_length = 4 + 4 + uiDataLength + (*ptr_len_ecc_pub);

	session->mcu_task_info.send_param_count = 4;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)params;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_ecc_pub;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&pucPublicKey;
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)&params[1];
	session->mcu_task_info.send_param[3].ptr_param_len = &uiDataLength;
	session->mcu_task_info.send_param[3].ptr_param = pucData;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_ecc_cipher_no_C;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)pucEncData;
	session->mcu_task_info.resp_param[1].reply_prev_property = RELAY_PREV_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = &(pucEncData->L);
	session->mcu_task_info.resp_param[1].ptr_param = pucEncData->C;
	rst = vsm_process(session,nullptr);
	debug_printf("C_ExternalEncrypt_ECC_MCU status:0x%02x\n", session->mcu_task_info.resp_head.status);
	return GET_FULL_ERR_CODE(rst);
}

/**
 *  \brief 使用内部私钥进行签名
 *
 *  \param [in] session 会话句柄
 *  \param [in] keyId 内部密钥索引
 *  \param [in] pucData 输入数据
 *  \param [in] uiDataInputLen 输入数据长度
 *  \param [out] pucSignature 得到的签名值
 *  \return 0成功
 *
 *  \details FPGA使用密钥索引还是密钥地址，暂时没有确定
 */
u32 C_InterSign_ECC(sis_session* session,
	u32 keyId,
	u8* pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature)
{
	u32 rst = 0;

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_PROCESS;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM2_INTERNAL_SIGN_ECC;
	session->mcu_task_info.send_head.hard_parm = keyId;
	session->mcu_task_info.send_head.data_length = uiDataInputLen;

	session->mcu_task_info.send_param_count = 1;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)&uiDataInputLen;
	session->mcu_task_info.send_param[0].ptr_param = pucData;

	// session->mcu_task_info.resp_param_count = 1;
	// session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_ecc_sign_data;
	// session->mcu_task_info.resp_param[0].ptr_param = (u8*)pucSignature;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_32;
	session->mcu_task_info.resp_param[0].ptr_param = &(pucSignature->r[32]);

	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32*)ptr_len_32;
	session->mcu_task_info.resp_param[1].ptr_param = &(pucSignature->s[32]);

	rst = vsm_process(session,nullptr);

	//debug_printf("C_InterSign_ECC status:0x%02x\n",session->mcu_task_info.resp_head.status );
	return GET_FULL_ERR_CODE(rst);
}

/**
 *  \brief 使用内部公钥验证签名
 *
 *  \param [in] session 会话句柄
 *  \param [in] keyId 使用keyid
 *  \param [in] pucData 输入数据，实际是hash结果值
 *  \param [in] uiDataInputLen 长度
 *  \param [in] pucSignature 待验签数据
 *  \return 验签结果0,表示成功
 *
 *  \details wangzhanbei
 *      状态返回值有问题，需要调试
 */
u32 C_InterVerify_ECC(sis_session* session,
	u32 keyId,
	u8* pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature)
{
	u32 rst = 0, verify_len = 0;
	u8 tmpdata[32] = { 0 };

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_PROCESS;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM2_INTERNAL_VERIFY_ECC;
	session->mcu_task_info.send_head.hard_parm = keyId;

	session->mcu_task_info.send_head.data_length = uiDataInputLen + 64;

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)&uiDataInputLen;
	session->mcu_task_info.send_param[0].ptr_param = pucData;

	session->mcu_task_info.send_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32 *)ptr_len_32;
	session->mcu_task_info.send_param[1].ptr_param = &(pucSignature->r[32]);

	session->mcu_task_info.send_param[2].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.send_param[2].ptr_param_len = (u32 *)ptr_len_32;
	session->mcu_task_info.send_param[2].ptr_param = &(pucSignature->s[32]);

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = tmpdata;

	rst = vsm_process(session,nullptr);
	if (rst != SDR_OK) {
		debug_printf("C_InterVerify_ECC ErrorCode:0x%02x\n", rst);
	}
	rst = session->mcu_task_info.resp_head.status;

	return GET_FULL_ERR_CODE(rst);
}

/*描述:使用外部ECC公钥对ECC签名值进行验证计算*/
u32 C_ExternVerify_ECC(sis_session* session,
	u32 algIdentify,
	ECCrefPublicKey pucPublicKey,
	u8*pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature)
{
	u32 ret = SDR_OK, verify_len = 0;
	sis_work_key* workkey = NULL;
	u32 keyadr = 0;
	HANDLE phKeyHandle = NULL;

	u8 tmpdata[32] = { 0 };

	ret = C_ImportPublicKey_ECC(session, pucPublicKey, &phKeyHandle);
	if (ret != SDR_OK) {
		return ret;
	}
	ret = LIB_GetWorkKey(session, phKeyHandle, &workkey);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_PROCESS;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM2_EXTERNAL_VERIFY_ECC;
	session->mcu_task_info.send_head.data_length = uiDataInputLen + 64 + 8;

	session->mcu_task_info.send_param_count = 4;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_8;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&(workkey->key_handle_addr);

	session->mcu_task_info.send_param[1].ptr_param_len = &uiDataInputLen;
	session->mcu_task_info.send_param[1].ptr_param = pucData;

	//    if(ECCref_MAX_LEN == 32)
	//    {
	//        session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_ecc_sign_data;
	//        session->mcu_task_info.send_param[2].ptr_param = (u8*)pucSignature;
	//    }
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_32;
	session->mcu_task_info.send_param[2].ptr_param = &(pucSignature->r[32]);

	session->mcu_task_info.send_param[3].ptr_param_len = (u32*)ptr_len_32;
	session->mcu_task_info.send_param[3].ptr_param = &(pucSignature->s[32]);

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = tmpdata;

	ret = vsm_process(session,nullptr);
	if (session->mcu_task_info.resp_head.status == 0) {
	}
	else {
		debug_printf("C_ExternVerify_ECC errorCode:0x%02x\n", session->mcu_task_info.resp_head.status);
		while (1);
	}

	ret = C_DestorySymKey(session, workkey);
	if (ret != SDR_OK) {
		debug_printf("C_DestorySymKey errorCode:0x%02x\n", ret);
	}
	return ret;
}

/*描述:使用外部ECC公钥对数据进行加密运算,SM2加密运算过于复杂，暂时留给MCU操作*/
u32 C_ExternalEncrypt_ECC(sis_session *session,
	u32 algIdentify,
	ECCrefPublicKey pucPublicKey,      //做值拷贝
	u8* pucData,
	u32 uiDataLength,
	ECCCipher *pucEncData)
{
	u32 rst = SDR_OK;
	sis_work_key* workkey;
	HANDLE pkeyHandle = NULL;

	u8 fpgadata[128] = { 0 };
	u32 fpgaDataSize = 0x80;

	rst = C_ImportPublicKey_ECC(session, pucPublicKey, &pkeyHandle);
	if (rst != SDR_OK) {
		return rst;
	}
	rst = LIB_GetWorkKey(session, pkeyHandle, &workkey);
	if (rst != SDR_OK) {
		return rst;
	}
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ECC_PROCESS;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM2_EXTERNAL_ENCRYPT_ECC;

	session->mcu_task_info.send_head.data_length = uiDataLength + 8;

	//如果需要随机数，则需要三个参数
	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&(workkey->key_handle_addr);
	session->mcu_task_info.send_param[1].ptr_param_len = &uiDataLength;
	session->mcu_task_info.send_param[1].ptr_param = pucData;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)&fpgaDataSize;
	session->mcu_task_info.resp_param[0].ptr_param = (u8 *)(fpgadata);

	//    session->mcu_task_info.resp_param_count = 1;
	//    session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	//    session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_ecc_cipher;
	//    session->mcu_task_info.resp_param[0].ptr_param = (u8 *)(pucEncData);

	if (SDR_OK == (rst = vsm_process(session,nullptr))) {
	
	}


	rst = sm2_compute_cipher(session,pucData,uiDataLength,fpgadata,fpgaDataSize,pucEncData);


	rst = C_DestorySymKey(session, workkey);
	if (rst != SDR_OK) {
		debug_printf("C_DestorySymKey errorCode:0x%02x\n", rst);
	}
	return GET_FULL_ERR_CODE(rst);

	// session->fpga_task_info.send_key_index = keyadr;
	// session->fpga_task_info.send_data_length = 32;
	// session->fpga_task_info.send_data = randate;
	// session->fpga_task_info.resp_data = fpgadata;
	//从虚拟密码机资源池中获得一个虚拟密码机
	// VSM_PopDevice(context->vsm_pool,&vsmInfo);
	// //让虚拟密码机执行任务
	// VSM_ExecuteFPGATask(vsmInfo,&session->fpga_task_info);
	// //将虚拟密码机重新放回到资源池中
	// VSM_PushDevice(context->vsm_pool,vsmInfo);
	// fpgaDataSize = session->fpga_task_info.resp_data_length;
	// VSM_ClearFPGATask(&session->fpga_task_info);
	





}