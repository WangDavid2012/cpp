#include "../sdf/SDF.h"
#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"
#include "../base/Common.h"
#include "../base/SDFLog.h"
#include "interface.h"
#include "config.h"



/**数据异或方法**/
static u8 *memxor(u8 *dst, const u8 *src, size_t n)
{
	u32 i;
	for (i = 0; i < n; i++)
	{
		*(dst + i) ^= *(src + i);
	}
	/*
	u64* a,b;
	u32 i, j, raduis, dwlen,dwords;

	dwlen = 8;
	dwords = n / dwlen;
	raduis = n % dwlen;

	for (i = 0; i < dwords; i++)
	{
		a = (u64*)(dst + i * dwlen);
		b = (u64*)(src + i * dwlen);
		*a = (*a) ^ (* b);
	}

	for(j = 0; j < raduis; j++)
	{
		int idx = i * dwlen + j;
		a[idx] = a[idx] ^ b[idx];
	}*/

	return dst;
}

/**************************4 对称算法运算函数*****************************/
u32 C_Crypt_MCU(sis_session *session,
	u32 cypType,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pData,
	u32 uiDataLen,
	u8 *pEncryptData,
	u32 *puiEncryptDataLen)
{
	u32 rst = 0;
	u32 params[4] = { 0 };
	u8 rever[16] = { 0 };
	// u32 key_id = LIB_GetMcuWorkKeyAddress(key);

	u32 key_id = 1;

	memset(&(session->mcu_task_info), 0, sizeof(sis_mcu_task_info));
	session->mcu_task_info.send_head.cmd = MCU_CMD_SM4;

	if (cypType == DATA_ENCRYPT)
	{
		if (Mechanism == SGD_SM4_ECB)
			session->mcu_task_info.send_head.sub_cmd = SUB_CMD_ECB_ENC;
		else if (Mechanism == SGD_SM4_CBC)
			session->mcu_task_info.send_head.sub_cmd = SUB_CMD_CBC_ENC;
	}
	else if (cypType == DATA_DECRYPT)
	{
		if (Mechanism == SGD_SM4_ECB)
			session->mcu_task_info.send_head.sub_cmd = SUB_CMD_ECB_DEC;
		else if (Mechanism == SGD_SM4_CBC)
			session->mcu_task_info.send_head.sub_cmd = SUB_CMD_CBC_DEC;
	}
	session->mcu_task_info.send_head.data_length = 16 + 16 + uiDataLen;
	session->mcu_task_info.send_head.hard_parm = key_id;
	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.send_param[0].ptr_param = rever;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.send_param[1].ptr_param = pIV;
	session->mcu_task_info.send_param[2].ptr_param_len = &uiDataLen;
	session->mcu_task_info.send_param[2].ptr_param = pData;

	session->mcu_task_info.resp_param_count = 3;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.resp_param[0].ptr_param = rever;
	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.resp_param[1].ptr_param = pIV;

	session->mcu_task_info.resp_param[2].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = (u32 *)ptr_len_ecc_pub;
	session->mcu_task_info.resp_param[2].ptr_param = pEncryptData;

	if (SDR_OK == (rst = vsm_process(session,nullptr)))
	{
		*puiEncryptDataLen = uiDataLen;
	}
	return GET_FULL_ERR_CODE(rst);
}

/*描述：对称Mac运算函数，支持SM1、SM4算法*/
u32 C_MAC_MCU(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pData,
	u32 uiDataLen,
	u8 *pMacData,
	u32 *puiMacDataLen)
{
	u32 rst = 0;
	u8 reverse[16] = { 0 };

	memset(&(session->mcu_task_info), 0, sizeof(sis_mcu_task_info));

	// u32 key_id = LIB_GetMcuWorkKeyAddress(key);
	u32 key_id = 0;
	session->mcu_task_info.send_head.cmd = MCU_CMD_SM4_MAC;
	session->mcu_task_info.send_head.sub_cmd = htonl(0);
	session->mcu_task_info.send_head.data_length = htonl((short)(16 + 16 + uiDataLen));
	session->mcu_task_info.send_head.hard_parm = htonl(key_id);

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.send_param[0].ptr_param = reverse;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.send_param[1].ptr_param = pIV;
	session->mcu_task_info.send_param[2].ptr_param_len = &uiDataLen;
	session->mcu_task_info.send_param[2].ptr_param = pData;

	session->mcu_task_info.resp_param_count = 3;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.resp_param[0].ptr_param = reverse;

	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.resp_param[1].ptr_param = pIV;

	session->mcu_task_info.resp_param[2].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[2].ptr_param_len = &uiDataLen;
	session->mcu_task_info.resp_param[2].ptr_param = pMacData;

	if (SDR_OK == (rst = vsm_process(session,nullptr)))
	{
		*puiMacDataLen = 16;
	}

	return GET_FULL_ERR_CODE(rst);
}

/*描述：对称算法运算函数，支持SM4算法*/
u32 C_Encrypt_MCU(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pData,
	u32 uiDataLen,
	u8 *pEncryptData,
	u32 *puiEncryptDataLen)
{
	return C_Crypt_MCU(session, DATA_ENCRYPT, Mechanism, key, pIV, pData, uiDataLen, pEncryptData, puiEncryptDataLen);
}

/*描述：对称算法运算函数，支持SM4算法*/
u32 C_Decrypt_MCU(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pEncryptData,
	u32 uiEncryptDataLen,
	u8 *pData,
	u32 *puiDataLen)
{
	return C_Crypt_MCU(session, DATA_DECRYPT, Mechanism, key, pIV, pEncryptData, uiEncryptDataLen, pData, puiDataLen);
}

/*描述：对称算法扩展运算函数，支持FPGASM1、SM4算法*/
u32 C_Crypt_FPGA_ECB(sis_session *session,
	u32 CryptType,
	u32 Mechanism,
	u64 SymKeyAddr,
	u8 *pInData,
	u32 uiInDataLen,
	u8 *pOutData,
	u32 *puiOutDataLen)
{
	u32 rst = SDR_OK;

	/*根据算法确定给FPGA发送的指令*/
	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_SYM_PROCESS;
	switch (Mechanism) {
	case SGD_SM4_ECB:
		if (CryptType == DATA_ENCRYPT) {
			session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM4_ECB_ENC;
		}
		else {
			session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM4_ECB_DEC;
		}
		break;
	case SGD_SM1_ECB:
		if (CryptType == DATA_ENCRYPT) {
			session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM1_ECB_ENC;
		}
		else {
			session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM1_ECB_DEC;
		}
		break;
	default:
		break;
	}
	debug_printf("The workkey addr is 0x%llx\n", SymKeyAddr);

	session->mcu_task_info.send_head.data_length = 8 + uiInDataLen;
	session->mcu_task_info.send_head.hard_parm = 0;

	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&SymKeyAddr;

	session->mcu_task_info.send_param[1].ptr_param_len = &uiInDataLen;
	session->mcu_task_info.send_param[1].ptr_param = pInData;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = RELAY_TOTAL_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = puiOutDataLen;
	session->mcu_task_info.resp_param[0].ptr_param = pOutData;

	if (SDR_OK == (rst = vsm_process(session,nullptr))) {
	}
	return GET_FULL_ERR_CODE(rst);

	///从虚拟密码机资源池中获得一个虚拟密码机
	// VSM_PopDevice(context->vsm_pool,&vsmInfo);
	// ///定位从DMA起始位置写数据
	// lseek(vsmInfo->fd, 0, SEEK_SET);
	// ///往内核态写入数据，由驱动提交给DMA
	// write(vsmInfo->fd, pInData, uiInDataLen);
	// _SDF_PrintBuf("C_Crypt_FPGA_ECB Send Data ",pInData,uiInDataLen);
	///写长度寄存器
	// sendLength = uiInDataLen;
	// ///长度转码
	// sendLength = sendLength % 32 ? (sendLength << 16 | ((sendLength / 32 + 1) * 32)) : (sendLength << 16 | sendLength);
	// ioctl(vsmInfo->fd,CMD_SET_SEND_LEN,sendLength);
	// ///写密钥寄存器
	// ioctl(vsmInfo->fd,CMD_SET_KEY_INDEX,keyIndex);
	// ///写指令寄存器
	// ioctl(vsmInfo->fd,CMD_SET_SEND_CMD,cmd);
	// debug_printf("C_Crypt_FPGA_ECB keyIndex:0x%02x sendLength:%d cmd:%x\n",htonl(keyIndex),uiInDataLen,cmd);
	// ///读返回数据长度，驱动内部异步转同步

	// ///wangzhanbei添加
	// ioctl(vsmInfo->fd,CMD_GET_STATUS,&ret);
	// if(ret != SDR_OK)
	// {
	//     debug_printf("C_InterVerify_ECC_FPGA error,errorCode:0x%08X\n",ret);
	//     VSM_PushDevice(context->vsm_pool,vsmInfo);
	//     return ret;
	// }
	// ioctl(vsmInfo->fd,CMD_GET_RESP_LEN,&respLength);
	// U32_SPLIT(respLength, dlen_h, dlen_l);
	// readLength = ((dlen_h == 0) ? dlen_l : dlen_h);
	// ///重定位从DMA起始位置读数据
	// lseek(vsmInfo->fd, 0, SEEK_SET);
	// ///读取数据，从内核态读回直接写到用户指针
	// read(vsmInfo->fd, pOutData,readLength);
	// _SDF_PrintBuf("C_Crypt_FPGA_ECB Recv Data ",pOutData,readLength);
	// *puiOutDataLen = readLength;
	// ///将虚拟密码机重新放回到资源池中
	// VSM_PushDevice(context->vsm_pool,vsmInfo);
}

/*描述：对称算法扩展运算函数，支持FPGASM1、SM4算法*/
u32 C_Crypt_FPGA_CBC(sis_session *session,
	u32 CryptType,
	u32 Mechanism,
	u64 SymKeyAddr,
	u8 *pInData,
	u32 uiInDataLen,
	u8 *pOutData,
	u32 *puiOutDataLen)
{
	u32 rst = SDR_OK;
	sis_sym_ctx_t *symContext = NULL;
	symContext = &session->sym_context;

	/*根据算法确定给FPGA发送的指令*/

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_SYM_PROCESS;
	switch (Mechanism) {
	case SGD_SM4_CBC:
		if (CryptType == DATA_ENCRYPT) {
			session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM4_CBC_ENC;
		}
		else {
			session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM4_CBC_DEC;
		}
		break;
	case SGD_SM1_CBC:
		if (CryptType == DATA_ENCRYPT) {
			session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM1_CBC_ENC;
		}
		else {
			session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM1_CBC_DEC;
		}
		break;
	default:
		break;
	}
	session->mcu_task_info.send_head.data_length = 8 + uiInDataLen + SM14_IV_LEN;  //8+32+16 = 56 
	session->mcu_task_info.send_head.hard_parm = 0;

	session->mcu_task_info.send_param_count = 3;

	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&SymKeyAddr;

	session->mcu_task_info.send_param[1].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.send_param[1].ptr_param = symContext->iv;
	session->mcu_task_info.send_param[2].ptr_param_len = &uiInDataLen;
	session->mcu_task_info.send_param[2].ptr_param = pInData;

	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = &uiInDataLen;
	*puiOutDataLen = uiInDataLen;
	// session->mcu_task_info.resp_param[0].ptr_param_len = puiOutDataLen;
	session->mcu_task_info.resp_param[0].ptr_param = pOutData;

	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.resp_param[1].ptr_param = symContext->iv;

	if (SDR_OK == (rst = vsm_process(session,nullptr))) {

		memcpy(symContext->iv, pOutData + uiInDataLen - 16, 16);


// 		session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
// 		session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)ptr_len_16;
// 		session->mcu_task_info.resp_param[1].ptr_param = symContext->iv;
	}
	return GET_FULL_ERR_CODE(rst);
}

/*描述：对称算法扩展运算函数，支持FPGASM1、SM4算法*/
u32 C_Crypt_FPGA_OFB(sis_session *session,
	u32 Mechanism,
	u32 SymKeyId,
	u8 *pInData,
	u32 uiInDataLen,
	u8 *pOutData,
	u32 *puiOutDataLen)
{
	u32 ret = SDR_OK;
	u8 defaultData[SM14_CHUNK_SIZE] = { 0 };
	//sis_vsm_info *vsmInfo = NULL;
	sis_sym_ctx_t *symContext = NULL;
	sis_work_key *key = NULL;
	u32 cmd, keyIndex;
	u32 readLength, writeLength;

	u32 respLength = 0;
	u32 sendLength = 0;
	u32 dlen_l, dlen_h;

	symContext = &session->sym_context;

	/*根据算法确定给FPGA发送的指令*/
	switch (Mechanism)
	{
	case SGD_SM4_OFB:
		cmd = SM4_CBC_FIRST_BLOCK_ENC_CMD;
		break;
	case SGD_SM1_OFB:
		cmd = SM1_CBC_FIRST_BLOCK_ENC_CMD;
		break;
	default:
		break;
	}

	///通过密钥索引转换得到密钥偏移地址
	keyIndex = SymKeyId;
	readLength = 0;

	///从虚拟密码机资源池中获得一个虚拟密码机
	// VSM_PopDevice(context->vsm_pool,&vsmInfo);

	// /*根据算法模式，第一包和后续包处理发送数据的参数信息*/

	// /*OFB模式*/
	// ///定位从DMA起始位置写数据
	// lseek(vsmInfo->fd, 0, SEEK_SET);
	// ///往内核态写入数据，由驱动提交给DMA，分次写，先写IV
	// write(vsmInfo->fd, symContext->iv, SM14_IV_LEN);
	// _SDF_PrintBuf("C_Crypt_FPGA_OFB Send IV ",symContext->iv,SM14_IV_LEN);
	// ///往内核态写入数据，由驱动提交给DMA
	// ///OFB写入数据为全零
	// writeLength=0;
	// while(writeLength<uiInDataLen)
	// {
	//     write(vsmInfo->fd, defaultData, 8);
	//     writeLength+=8;
	// }
	// _SDF_Print("C_Crypt_FPGA_OFB write data zero length:%d \n",writeLength);
	// ///写长度寄存器，会根据数据长度得到返回的长度（？？这个长度应该和FPGA生成长度相关）
	// sendLength = SM14_IV_LEN+uiInDataLen;
	// _SDF_Print("C_Crypt_FPGA_OFB keyIndex:%x sendLength:%d cmd:%x\n",keyIndex,sendLength,cmd);
	// sendLength = sendLength % 32 ? (sendLength << 16 | ((sendLength / 32 + 1) * 32)) : (sendLength << 16 | sendLength);
	// ioctl(vsmInfo->fd,CMD_SET_SEND_LEN,sendLength);
	// ///写密钥寄存器
	// ioctl(vsmInfo->fd,CMD_SET_KEY_INDEX,keyIndex);
	// ///写指令寄存器
	// ioctl(vsmInfo->fd,CMD_SET_SEND_CMD,cmd);
	// ///读返回数据长度，驱动内部异步转同步
	// ioctl(vsmInfo->fd,CMD_GET_RESP_LEN,&respLength);
	// U32_SPLIT(respLength, dlen_h, dlen_l);
	// readLength = ((dlen_h == 0) ? dlen_l : dlen_h);
	// if(uiInDataLen!=readLength)
	// {
	//     _SDF_Print("C_Crypt_FPGA_OFB is error. input:%d output:%d",uiInDataLen,readLength);
	// }
	// readLength = uiInDataLen;
	// *puiOutDataLen = readLength;
	// ///重定位从DMA起始位置读数据
	// lseek(vsmInfo->fd, 0, SEEK_SET);
	// ///读取掩码数据，从内核态读回直接写到用户指针
	// read(vsmInfo->fd, pOutData,readLength);
	// _SDF_PrintBuf("C_Crypt_FPGA_OFB Recv Data ",pOutData,readLength);
	// ///使用最后一包作为后续的IV
	// memcpy(symContext->iv, pOutData + readLength - SM14_IV_LEN, SM14_IV_LEN);
	// _SDF_PrintBuf("C_Crypt_FPGA_OFB Recv New IV Data ",symContext->iv,SM14_IV_LEN);
	// ///使用掩码对数据异或
	// memxor(pOutData, pInData, readLength);
	// _SDF_PrintBuf("C_Crypt_FPGA_OFB XOR Data ",pOutData,readLength);
	// ///将虚拟密码机重新放回到资源池中
	// VSM_PushDevice(context->vsm_pool,vsmInfo);
	return ret;
}

u32 C_Encrypt_FPGA_CFB(sis_session *session,
	u32 Mechanism,
	u32 SymKeyId,
	u8 *pInData,
	u32 uiInDataLen,
	u8 *pOutData,
	u32 *puiOutDataLen)
{
	u32 ret = SDR_OK;
	//sis_vsm_info *vsmInfo = NULL;
	sis_sym_ctx_t *symContext = NULL;
	u32 cmd, keyIndex;
	u32 readLength;

	u32 respLength = 0;
	u32 sendLength = 0;
	u32 dlen_l, dlen_h;

	symContext = &session->sym_context;

	/*根据算法确定给FPGA发送的指令*/
	switch (Mechanism)
	{
	case SGD_SM4_CFB:
		cmd = SM4_CBC_FIRST_BLOCK_ENC_CMD;
		break;
	case SGD_SM1_CFB:
		cmd = SM1_CBC_FIRST_BLOCK_ENC_CMD;
		break;
	default:
		break;
	}

	///通过密钥索引转换得到密钥偏移地址
	keyIndex = SymKeyId;
	readLength = 0;

	///从虚拟密码机资源池中获得一个虚拟密码机
	// VSM_PopDevice(context->vsm_pool,&vsmInfo);

	// /*CFB模式*/
	// ///定位从DMA起始位置写数据
	// lseek(vsmInfo->fd, 0, SEEK_SET);
	// ///往内核态写入数据，由驱动提交给DMA，分次写，先写IV
	// write(vsmInfo->fd, symContext->iv, SM14_IV_LEN);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB Send IV ",symContext->iv,SM14_IV_LEN);
	// ///CFB 初始上下文用全零
	// ///往内核态写入数据，由驱动提交给DMA，分次写，再写初始量
	// write(vsmInfo->fd, symContext->cfb_ctx, SM14_CHUNK_SIZE);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB Send InitData ",symContext->cfb_ctx,SM14_CHUNK_SIZE);
	// ///不用往DMA搬移数据，因为CFB计算仅需要初始值
	// ///往内核态写入数据，由驱动提交给DMA
	// write(vsmInfo->fd, pInData, uiInDataLen-SM14_CHUNK_SIZE);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB Send Data ",pInData,uiInDataLen-SM14_CHUNK_SIZE);
	// ///写长度寄存器，会根据数据长度得到返回的长度（？？这个长度应该和FPGA生成长度相关）
	// sendLength = SM14_IV_LEN+uiInDataLen;
	// _SDF_Print("C_SymCrypt_FPGA keyIndex:%x sendLength:%d cmd:%x\n",keyIndex,sendLength,cmd);
	// sendLength = sendLength % 32 ? (sendLength << 16 | ((sendLength / 32 + 1) * 32)) : (sendLength << 16 | sendLength);
	// ioctl(vsmInfo->fd,CMD_SET_SEND_LEN,sendLength);
	// ///写密钥寄存器
	// ioctl(vsmInfo->fd,CMD_SET_KEY_INDEX,keyIndex);
	// ///写指令寄存器
	// ioctl(vsmInfo->fd,CMD_SET_SEND_CMD,cmd);
	// ///读返回数据长度，驱动内部异步转同步
	// ioctl(vsmInfo->fd,CMD_GET_RESP_LEN,&respLength);
	// U32_SPLIT(respLength, dlen_h, dlen_l);
	// readLength = ((dlen_h == 0) ? dlen_l : dlen_h);
	// if(uiInDataLen!=readLength)
	// {
	//     _SDF_Print("C_Crypt_FPGA_CFB is error. input:%d output:%d",uiInDataLen,readLength);
	// }
	// readLength = uiInDataLen;
	// *puiOutDataLen = readLength;
	// ///重定位从DMA起始位置读数据
	// lseek(vsmInfo->fd, 0, SEEK_SET);
	// ///读取掩码数据，从内核态读回直接写到用户指针
	// read(vsmInfo->fd, pOutData,readLength);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB Recv Data ",pOutData,readLength);
	// ///使用最后一包作为后续的IV
	// memcpy(symContext->iv, pOutData + readLength - SM14_IV_LEN, SM14_IV_LEN);
	// ///使用掩码对数据异或
	// memxor(pOutData, pInData, readLength);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB XOR Data ",pOutData,readLength);
	// ///CFB模式使用上一包最后的明文作为下一包的上下文
	// memcpy(symContext->cfb_ctx, pInData + uiInDataLen - SM14_CHUNK_SIZE, SM14_CHUNK_SIZE);
	// ///将虚拟密码机重新放回到资源池中
	// VSM_PushDevice(context->vsm_pool,vsmInfo);

	return ret;
}

u32 C_Decrypt_FPGA_CFB(sis_session *session,
	u32 Mechanism,
	u32 SymKeyId,
	u8 *pInData,
	u32 uiInDataLen,
	u8 *pOutData,
	u32 *puiOutDataLen)
{
	u32 ret = SDR_OK;
	//sis_vsm_info *vsmInfo = NULL;
	sis_sym_ctx_t *symContext = NULL;
	u32 cmd, keyIndex;
	u32 readLength;

	u32 respLength = 0;
	u32 sendLength = 0;
	u32 dlen_l, dlen_h;

	symContext = &session->sym_context;

	/*根据算法确定给FPGA发送的指令*/
	switch (Mechanism)
	{
	case SGD_SM4_CFB:
		cmd = SM4_ECB_ENC_CMD;
		break;
	case SGD_SM1_CFB:
		cmd = SM1_ECB_ENC_CMD;
		break;
	default:
		break;
	}

	///通过密钥索引转换得到密钥偏移地址
	keyIndex = SymKeyId;
	readLength = 0;

	///从虚拟密码机资源池中获得一个虚拟密码机
	// VSM_PopDevice(context->vsm_pool,&vsmInfo);

	// /*CFB模式*/
	// ///定位从DMA起始位置写数据
	// lseek(vsmInfo->fd, 0, SEEK_SET);
	// ///往内核态写入数据，由驱动提交给DMA，分次写，先写IV
	// write(vsmInfo->fd, symContext->iv, SM14_IV_LEN);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB Send IV ",symContext->iv,SM14_IV_LEN);
	// ///不用往DMA搬移数据，因为CFB计算仅需要初始值
	// ///往内核态写入数据，由驱动提交给DMA
	// write(vsmInfo->fd, pInData, uiInDataLen-SM14_CHUNK_SIZE);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB Send Data ",pInData,uiInDataLen-SM14_CHUNK_SIZE);
	// ///写长度寄存器，会根据数据长度得到返回的长度（？？这个长度应该和FPGA生成长度相关）
	// sendLength = uiInDataLen;
	// _SDF_Print("C_SymCrypt_FPGA keyIndex:%x sendLength:%d cmd:%x\n",keyIndex,sendLength,cmd);
	// sendLength = sendLength % 32 ? (sendLength << 16 | ((sendLength / 32 + 1) * 32)) : (sendLength << 16 | sendLength);
	// ioctl(vsmInfo->fd,CMD_SET_SEND_LEN,sendLength);
	// ///写密钥寄存器
	// ioctl(vsmInfo->fd,CMD_SET_KEY_INDEX,keyIndex);
	// ///写指令寄存器
	// ioctl(vsmInfo->fd,CMD_SET_SEND_CMD,cmd);
	// ///读返回数据长度，驱动内部异步转同步
	// ioctl(vsmInfo->fd,CMD_GET_RESP_LEN,&respLength);
	// U32_SPLIT(respLength, dlen_h, dlen_l);
	// readLength = ((dlen_h == 0) ? dlen_l : dlen_h);
	// if(uiInDataLen!=readLength)
	// {
	//     _SDF_Print("C_Crypt_FPGA_CFB is error. input:%d output:%d",uiInDataLen,readLength);
	// }
	// readLength = uiInDataLen;
	// *puiOutDataLen = readLength;
	// ///重定位从DMA起始位置读数据
	// lseek(vsmInfo->fd, 0, SEEK_SET);
	// ///读取掩码数据，从内核态读回直接写到用户指针
	// read(vsmInfo->fd, pOutData,readLength);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB Recv Data ",pOutData,readLength);
	// ///使用最后一包作为后续的IV
	// memcpy(symContext->iv, pOutData + readLength - SM14_IV_LEN, SM14_IV_LEN);
	// ///使用掩码对数据异或
	// memxor(pOutData, pInData, readLength);
	// _SDF_PrintBuf("C_Crypt_FPGA_CFB XOR Data ",pOutData,readLength);
	// ///将虚拟密码机重新放回到资源池中
	// VSM_PushDevice(context->vsm_pool,vsmInfo);

	return ret;
}

/*描述：对称算法扩展运算函数，支持FPGASM1、SM4算法*/
u32 C_Crypt_FPGA_CFB(sis_session *session,
	u32 CryptType,
	u32 Mechanism,
	u32 SymKeyId,
	u8 *pInData,
	u32 uiInDataLen,
	u8 *pOutData,
	u32 *puiOutDataLen)
{
	if (CryptType == DATA_ENCRYPT)
	{
		return C_Encrypt_FPGA_CFB(session, Mechanism, SymKeyId,
			pInData, uiInDataLen, pOutData, puiOutDataLen);
	}
	else
	{
		return C_Decrypt_FPGA_CFB(session, Mechanism, SymKeyId,
			pInData, uiInDataLen, pOutData, puiOutDataLen);
	}
}

/*描述：对称算法扩展运算函数，支持FPGASM1、SM4算法*/
u32 C_Crypt_FPGA_MAC(sis_session *session,
	u32 Mechanism,
	u64 SymKeyAddr,
	u8 *pInData,
	u32 uiInDataLen)
{
	u32 rst = SDR_OK;
	sis_sym_ctx_t *symContext = NULL;
	symContext = &session->sym_context;


	//引入两个垃圾变量，是因为底层卡上传的数据比较多，此处只需要16个数据，但是底层
	//上传数据时	uiInDataLen ，只有前16个有效，所以这么处理
	//20200713 wangzhanbei
	u8 tmpdata[1024*5] = {0};
	u32 tmplen = uiInDataLen - 16;

	/*根据算法确定给FPGA发送的指令*/

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_SYM_PROCESS;
	//不知道那个命令
	switch (Mechanism) {
	case SGD_SM4_MAC:
		session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM4_CBC_ENC;
		break;
	case SGD_SM1_MAC:
		session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM1_CBC_ENC;
		break;
	default:
		break;
	}								   

	session->mcu_task_info.send_head.data_length = 8 + uiInDataLen + SM14_IV_LEN;
	session->mcu_task_info.send_head.hard_parm = 0;

	session->mcu_task_info.send_param_count = 3;


	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&SymKeyAddr;
	session->mcu_task_info.send_param[1].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&(symContext->iv);
	session->mcu_task_info.send_param[2].ptr_param_len = &uiInDataLen;
	session->mcu_task_info.send_param[2].ptr_param = pInData;
// 	session->mcu_task_info.send_param[2].ptr_param_len = (u32 *)ptr_len_8;
// 	session->mcu_task_info.send_param[2].ptr_param = (u8*)&SymKeyAddr;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_16;
	session->mcu_task_info.resp_param[0].ptr_param = (u8 *)&(symContext->iv);

	//此处无用数据时根据卡做的修改，卡中返回值是输入值的长度，需要全部读取完成
	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)&tmplen;
	session->mcu_task_info.resp_param[1].ptr_param = (u8 *)&(tmpdata);

	if (SDR_OK == (rst = vsm_process(session,nullptr))) {
	}
	return GET_FULL_ERR_CODE(rst);
}

/*支持分包运算，包大小为SYM_BLOCK_SIZE*/
u32 C_Part_Crypt_FPGA(sis_session *session,
	u32 CryptType,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pInData,
	u32 uiInDataLen,
	u8 *pOutData,
	u32 *puiOutDataLen)
{
	u32 ret = SDR_OK;
	u32 index = 0, partlen = 0;
	u32 packageSize = 0;
	u32 algPattern, algType = 0;
	

	u64 keyRealAddr = key->key_handle_addr;
	if (keyRealAddr == 0){
		debug_printf("****************error****************\n");
		return SDR_OK;
	}

	*puiOutDataLen = 0;
	memset(&(session->sym_context), 0, sizeof(sis_sym_ctx_t));

	algType = Mechanism / (0x100);
	algPattern = Mechanism % (0x100);

	if (algPattern == SDG_ALG_PATTERN_ECB) {
		memset(session->sym_context.iv, 0, SM14_IV_LEN);
	}
	else {
		memcpy(session->sym_context.iv, pIV, SM14_IV_LEN);
	}
	memset(session->sym_context.cfb_ctx, 0, SM14_CHUNK_SIZE);
	if (algType == SDG_ALG_TYPE_SM1) {
		packageSize = MAX_SM1_SEND_PACKAGE_SIZE;
	}
	else {
		packageSize = MAX_SM4_SEND_PACKAGE_SIZE;
	}

	while (uiInDataLen >= packageSize) {
		switch (algPattern) {
		case SDG_ALG_PATTERN_ECB:
			ret = C_Crypt_FPGA_ECB(session, CryptType, Mechanism, keyRealAddr,
				pInData + index, packageSize, pOutData + index, &partlen);
			break;
		case SDG_ALG_PATTERN_CBC:
			ret = C_Crypt_FPGA_CBC(session, CryptType, Mechanism, keyRealAddr,
				pInData + index, packageSize, pOutData + index, &partlen);
			break;
		case SDG_ALG_PATTERN_CFB:
			ret = C_Crypt_FPGA_CFB(session, CryptType, Mechanism, keyRealAddr, pInData + index,
				packageSize, pOutData + index, &partlen);
			break;
		case SDG_ALG_PATTERN_OFB:
			ret = C_Crypt_FPGA_OFB(session, Mechanism, keyRealAddr, pInData + index,
				packageSize, pOutData + index, &partlen);
			break;
		case SDG_ALG_PATTERN_MAC:
			ret = C_Crypt_FPGA_MAC(session, Mechanism, keyRealAddr, pInData + index, packageSize);
			break;
		default:
			break;
		}
		if (ret != SDR_OK) {
			return ret;
		}
		uiInDataLen -= packageSize;
		index += packageSize;
		*puiOutDataLen += partlen;
	}

	if (uiInDataLen)
	{
		switch (algPattern)
		{
		case SDG_ALG_PATTERN_ECB:
			ret = C_Crypt_FPGA_ECB(session, CryptType, Mechanism, keyRealAddr,
				pInData + index, uiInDataLen, pOutData + index, &partlen);
			break;
		case SDG_ALG_PATTERN_CBC:
			ret = C_Crypt_FPGA_CBC(session, CryptType, Mechanism, keyRealAddr,
				pInData + index, uiInDataLen, pOutData + index, &partlen);
			break;
		case SDG_ALG_PATTERN_CFB:
			ret = C_Crypt_FPGA_CFB(session, CryptType, Mechanism, keyRealAddr, pInData + index,
				uiInDataLen, pOutData + index, &partlen);
			break;
		case SDG_ALG_PATTERN_OFB:
			ret = C_Crypt_FPGA_OFB(session, Mechanism, keyRealAddr, pInData + index,
				uiInDataLen, pOutData + index, &partlen);
			break;
		case SDG_ALG_PATTERN_MAC:
			ret = C_Crypt_FPGA_MAC(session, Mechanism, keyRealAddr, pInData + index, uiInDataLen);
			break;
		default:
			break;
		}
		if (ret != SDR_OK)
		{
			return ret;
		}
		*puiOutDataLen += partlen;
	}
	return ret;
}

/*支持分包运算，包大小为SYM_BLOCK_SIZE*/
u32 C_Encrypt(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pData,
	u32 uiDataLen,
	u8 *pEncryptData,
	u32 *puiEncryptDataLen)
{						 
	return C_Part_Crypt_FPGA(session, DATA_ENCRYPT, Mechanism, key,
		pIV, pData, uiDataLen, pEncryptData, puiEncryptDataLen);
}

u32 C_Decrypt(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pEncryptData,
	u32 uiEncryptDataLen,
	u8 *pData,
	u32 *puiDataLen)
{
	return C_Part_Crypt_FPGA(session, DATA_DECRYPT, Mechanism, key, \
		pIV, pEncryptData, uiEncryptDataLen, pData, puiDataLen);
}

/*描述：对称Mac运算函数，支持SM1、SM4算法*/
u32 C_CalculateMAC(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pData,
	u32 uiDataLen,
	u8 *pMacData,
	u32 *puiMacDataLen)
{
	u32 ret = 0;
	ret = C_Part_Crypt_FPGA(session, DATA_ENCRYPT_DECRYPT, Mechanism, key,
		pIV, pData, uiDataLen, pMacData, puiMacDataLen);
	if (ret == SDR_OK)
	{
		*puiMacDataLen = SM14_IV_LEN;
		memcpy(pMacData, session->sym_context.iv, SM14_IV_LEN);
	}
	return ret;
}

/**********************************************************************/