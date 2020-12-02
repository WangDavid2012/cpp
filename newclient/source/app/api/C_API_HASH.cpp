#include "../api/C_API.h"
#include "../api/C_API_EX.h"
// #include "../base/VSM.h"
#include "../base/Context.h"
#include "../base/Common.h"
#include "../base/SDFLog.h"
#include "../base/Util.h"
#include "interface.h"

/**
 *  \brief SM3杂凑算法初始化
 *
 *  \param [in] session 会话句柄
 *  \param [in] pID 身份ID
 *  \param [in] uiIdLen id长度
 *  \param [in] pPubkey 公钥
 *  \param [in] uiPubkeyLen 公钥长度
 *  \return 0成功
 *
 *  \details 主要完成功能给hash_ctx 的初始IV赋值
 */
u32 blocksize = 0;
u32 padsize = 0;
u32 C_HashInit_SM3(sis_session* session, u8* pID, u32 uiIdLen, u8* pPubkey, u32 uiPubkeyLen)
{
	int rst = SDR_OK;

	sis_hash_ctx_t *hashContext = nullptr;
	u8 zBuffer[SM3_Z_BUFFER_LEN] = { 0 };     //z函数的返回值是固定的，大小应可以优化
	u32 zlen = 0;
	u32 chunkCount = 0;
	u32 padding = 0;

	hashContext = &session->hash_context;
	memcpy(hashContext->iv, SM3_INIT_IV, SM3_IV_LEN);
	hashContext->alg_id = SGD_SM3;
	hashContext->step = STEP_HASH_INIT;

	//处理待发送数据
	if (uiIdLen != 0 && uiPubkeyLen != 0) {
		//如果有公钥，需要拼接起来
		zlen = sm2_z(pID, uiIdLen, (ECCrefPublicKey*)pPubkey, zBuffer);
	}
	if (zlen) {
		session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_HASH_PROCESS;
		session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM3_HASH;
		// session->mcu_task_info.send_head.data_length = zlen;
		//处理流程如下：
		//1、发送IV向量
		session->mcu_task_info.send_param_count = 3;
		session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_32;
		session->mcu_task_info.send_param[0].ptr_param = hashContext->iv;

		//2、对数据进行填充---将 zBuffer[]中不足64字节数据放到填充区，然后进行填充 补足成64byte或者128byte
		chunkCount = zlen / SM3_CHUNK_SIZE;
		padding = zlen % SM3_CHUNK_SIZE;
		hashContext->padding_size = padding;
		memcpy(hashContext->padding_buffer, zBuffer + chunkCount * SM3_CHUNK_SIZE, padding);
		hashContext->chunk_count = chunkCount;
		sm3_padding(hashContext);

		blocksize = zlen - hashContext->padding_size;

		session->mcu_task_info.send_param[1].ptr_param_len = &blocksize;
		session->mcu_task_info.send_param[1].ptr_param = zBuffer;

		//3、发送填充 ZBuffer中不满64byte的数据，填充后的数据，长度应该是64byte或者128byte
		padsize = hashContext->padded_size;
		session->mcu_task_info.send_param[2].ptr_param_len = &padsize;
		session->mcu_task_info.send_param[2].ptr_param = hashContext->padding_buffer;

		session->mcu_task_info.send_head.data_length = 32 + blocksize + padsize;

		//4、将返回结果放到hashContext->unsent_buffer中
		session->mcu_task_info.resp_param_count = 1;
		session->mcu_task_info.resp_param[0].reply_prev_property = RELAY_TOTAL_PROPERTY;
		session->mcu_task_info.resp_param[0].ptr_param_len = &(hashContext->unsent_size);
		session->mcu_task_info.resp_param[0].ptr_param = hashContext->unsent_buffer;

		rst = vsm_process(session,nullptr);
		if ((rst == SDR_OK) && (session->mcu_task_info.resp_head.status == 0)) {
			hashContext->chunk_count = 0;
			hashContext->padded_size = 0;
			hashContext->padding_size = 0;
			hashContext->unsent_size = session->mcu_task_info.resp_head.data_length;
		}
	}
	return rst;
}
//疑问：关于IV向量的维护问题，是否需要此端维护------
u32 C_Hash_SM3(sis_session* session, u8* pData, u32 uiDataLen)
{
	int rst = SDR_OK;
	sis_hash_ctx_t *hashContext = nullptr;

	u32 chunkCount = 0;
	u32 unsentLength = 0;
	u32 sendLength = 0;

	hashContext = &session->hash_context;

	if (hashContext->alg_id != SGD_SM3) {
		return SDR_ALGNOTSUPPORT;
	}

	if (hashContext->step != STEP_HASH_INIT && hashContext->step != STEP_HASH_UPDATE) {
		return SDR_STEPERR;
	}
	hashContext->step = STEP_HASH_UPDATE;

	unsentLength = hashContext->unsent_size + uiDataLen;
	chunkCount = unsentLength / SM3_CHUNK_SIZE;
	sendLength = chunkCount * SM3_CHUNK_SIZE;
	hashContext->chunk_count += chunkCount;

// 	mydebug << "the hashContext->unsent_size: " << hashContext->unsent_size << endl;
// 	mydebug << "the unsentLength: " << unsentLength << " the sendLength:" << sendLength << endl;




	//增加缓存反而影响速度，所以直接交给FPGA计算
	//如果要发送的数据小于一包，则缓存
	if (chunkCount == 0) {
		memcpy(hashContext->unsent_buffer + hashContext->unsent_size, pData, uiDataLen);
		hashContext->unsent_size += uiDataLen;
		return rst;
	}

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_HASH_PROCESS;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM3_HASH;
	// session->mcu_task_info.send_head.data_length = zlen;
	//处理流程如下：
	//1、发送IV向量
	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_32;
	session->mcu_task_info.send_param[0].ptr_param = hashContext->iv;

	//2、发送上次遗留的数据
	session->mcu_task_info.send_param[1].ptr_param_len = &(hashContext->unsent_size);
	session->mcu_task_info.send_param[1].ptr_param = hashContext->unsent_buffer;

	//3、发送可以拼接成整包的数据
	u32 blocklenth = sendLength - hashContext->unsent_size;
	session->mcu_task_info.send_param[2].ptr_param_len = &blocklenth;
	session->mcu_task_info.send_param[2].ptr_param = pData;

	session->mcu_task_info.send_head.data_length = 32 + hashContext->unsent_size + blocklenth;

	//4、将返回结果放到hashContext->unsent_buffer中

	u32 IVlenth = 32;
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = &(IVlenth);
	session->mcu_task_info.resp_param[0].ptr_param = hashContext->iv;

	rst = vsm_process(session,nullptr);
	if ((rst == SDR_OK) && (session->mcu_task_info.resp_head.status == 0)) {
		//hashContext->unsent_size = ntohs(session->mcu_task_info.resp_head.data_length);
	}
	else {
		debug_printf("hash_updata errorCode:0x%02x\n", session->mcu_task_info.resp_head.status);
		return rst;
	}
	hashContext->unsent_size = unsentLength - sendLength;
	if (hashContext->unsent_size > 0)
	{
		memcpy(hashContext->unsent_buffer, pData + sendLength, hashContext->unsent_size);
		//std::cout << "*****************" << endl;
	}
	return rst;
}

u32 C_HashFinal_SM3(sis_session* session, u8* pHash, u32* uiHashLen)
{
	int rst = SDR_OK;
	sis_hash_ctx_t *hashContext = NULL;

	hashContext = &session->hash_context;

	if (hashContext->alg_id != SGD_SM3) {
		return SDR_ALGNOTSUPPORT;
	}

	if (hashContext->step != STEP_HASH_UPDATE) {
		return SDR_STEPERR;
	}
	mydebug << "hashContext->padding_size/the hashContext->unsent_size:" << hashContext->unsent_size << endl;
	hashContext->padding_size = hashContext->unsent_size;
	memcpy(hashContext->padding_buffer, hashContext->unsent_buffer, hashContext->unsent_size);
	sm3_padding(hashContext);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_HASH_PROCESS;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM3_HASH;

	//处理流程如下：
	//1、发送IV向量
	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_32;
	session->mcu_task_info.send_param[0].ptr_param = hashContext->iv;
	session->mcu_task_info.send_param[1].ptr_param_len = &(hashContext->padded_size);
	session->mcu_task_info.send_param[1].ptr_param = hashContext->padding_buffer;

	session->mcu_task_info.send_head.data_length = 32 + hashContext->padded_size;

	u32 phashlenth = 32;
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;  //wangzhanbei添加
	session->mcu_task_info.resp_param[0].ptr_param_len = &(phashlenth);
	session->mcu_task_info.resp_param[0].ptr_param = pHash;

	rst = vsm_process(session,nullptr);
	if ((rst == SDR_OK) && (session->mcu_task_info.resp_head.status == 0)) {
		*uiHashLen = (session->mcu_task_info.resp_head.data_length);
		debug_printf("hash_final success,the rsplenth is 0x%02x\n", *uiHashLen);
	}
	else {
		debug_printf("hash_final errorCode:0x%02x\n", session->mcu_task_info.resp_head.status);
		return rst;
	}
	memset(hashContext, 0, sizeof(sis_hash_ctx_t));
	//运行完成此函数后，session的返回值数组被修改，
	//memset(session->sis_mcu_task_info, 0, sizeof(sis_mcu_task_info));
	return rst;
}

u32 C_HashInit(sis_session* session, u32 uiAlgId, u8* pID, u32 uiIdLen, u8* pPubkey, u32 uiPubkeyLen)
{
	u32 rst = SDR_OK;

	memset(&(session->hash_context), 0, sizeof(sis_hash_ctx_t));
	// sis_hash_ctx_t *hashContext = &(session->hash_context);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_HASH_PROCESS;
	session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM3_HASH;        //不确定子命令对不对

	if (uiIdLen != 0 && uiPubkeyLen != 0) {
		session->mcu_task_info.send_head.data_length = 4 + ECCref_PublicKey_SIZE + 4 + uiIdLen;
	}
	else {
		session->mcu_task_info.send_head.data_length = 4 + ECCref_PublicKey_SIZE + 4;
	}

	session->mcu_task_info.send_param_count = 4;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)&ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&uiAlgId;	//算法标识
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)&ptr_len_ecc_pub;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)(pPubkey);
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)&ptr_len_4;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)(&uiIdLen);
	session->mcu_task_info.send_param[3].ptr_param_len = &uiIdLen;
	session->mcu_task_info.send_param[3].ptr_param = (u8*)pID;

	//将输出结果指针执行传入的结构体，直接将内核态结果返回，减少一次内存拷贝
	session->mcu_task_info.resp_param_count = 1;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)&ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)(&session->hash_context);

	if (SDR_OK == (rst = vsm_process(session,nullptr))) {
	}
	return GET_FULL_ERR_CODE(rst);
}

u32 C_Hash(sis_session* session, u8* pData, u32 uiDataLen)
{
	u32 rst = SDR_OK;
	//sis_vsm_info *vsmInfo = NULL;

	//感觉这块有问题，抄的老的SDF
	session->mcu_task_info.send_head.cmd = MCU_CMD_HASH_UPDATE;
	session->mcu_task_info.send_head.data_length = 4 + 4 + uiDataLen;

	session->mcu_task_info.send_param_count = 3;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)(&session->hash_context);
	// session->mcu_task_info.send_param[1].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)(&uiDataLen);
	session->mcu_task_info.send_param[2].ptr_param_len = &uiDataLen;
	session->mcu_task_info.send_param[2].ptr_param = (u8*)pData;

	//从虚拟密码机资源池中获得一个虚拟密码机
	// VSM_PopDevice(context->vsm_pool,&vsmInfo);
	// //让虚拟密码机执行任务
	// VSM_ExecuteMCUTask(vsmInfo,&session->mcu_task_info);
	// //将虚拟密码机重新放回到资源池中
	// VSM_PushDevice(context->vsm_pool,vsmInfo);
	// //获得任务执行结果
	// rst = session->mcu_task_info.resp_head.status;
	// //清楚任务缓存，核心是清除指向接口库分配资源的指针，避免内存泄漏
	// VSM_ClearMCUTask(&session->mcu_task_info);

	// return GET_FULL_ERR_CODE(rst);

	return 0;
}

u32 C_HashFinal(sis_session* session, u8* pHash, u32* uiHashLen)
{
	u32 rst = SDR_OK;
	//sis_vsm_info *vsmInfo = NULL;

	//感觉这块有问题，抄的老的SDF
	session->mcu_task_info.send_head.cmd = MCU_CMD_HASH_FINAL;
	session->mcu_task_info.send_head.data_length = 4 + 4;

	//todo@share 王总写的和协议没对上，暂时按王总写的，后续测试的时候再调整
	session->mcu_task_info.send_param_count = 2;
	// session->mcu_task_info.send_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)(&session->hash_context);
	// session->mcu_task_info.send_param[1].ptr_param_len = ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)(&uiHashLen);

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	// session->mcu_task_info.resp_param[0].ptr_param_len = ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)(&uiHashLen);
	// session->mcu_task_info.resp_param[1].ptr_param_len = &uiHashLen;   wangzhanbei
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)pHash;

	//从虚拟密码机资源池中获得一个虚拟密码机
	// VSM_PopDevice(context->vsm_pool,&vsmInfo);
	// //让虚拟密码机执行任务
	// VSM_ExecuteMCUTask(vsmInfo,&session->mcu_task_info);
	// //将虚拟密码机重新放回到资源池中
	// VSM_PushDevice(context->vsm_pool,vsmInfo);
	// //获得任务执行结果
	// rst = session->mcu_task_info.resp_head.status;
	// //清楚任务缓存，核心是清除指向接口库分配资源的指针，避免内存泄漏
	// VSM_ClearMCUTask(&session->mcu_task_info);

	// return GET_FULL_ERR_CODE(rst);

	return 0;
}

u32 C_HMAC_Init(sis_session* session, sis_work_key *key, u32 Mechanism)
{
	u32 rst = SDR_OK;

	u64 keyRealAddr = key->key_handle_addr;
	u32 uiAlgID = htonl(Mechanism);
	memset(&(session->hash_context), 0, sizeof(sis_hash_ctx_t));
	debug_printf("The uiAlgID is 0x%02x\n", uiAlgID);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_HASH_PROCESS;
	//session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM3_HMAC_INIT;
	session->mcu_task_info.send_head.sub_cmd = MCU_CMD_HMAC_INIT;

	session->mcu_task_info.send_head.data_length = 12;

	session->mcu_task_info.send_param_count = 2;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)(&uiAlgID);	//算法标识

	session->mcu_task_info.send_param[1].ptr_param_len = (u32 *)ptr_len_8;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)(&keyRealAddr);

	//将输出结果指针执行传入的结构体，直接将内核态结果返回，减少一次内存拷贝
	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32 *)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)(&session->hmac_context.handle);

	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32 *)ptr_len_32;
	session->mcu_task_info.resp_param[1].ptr_param = session->hash_context.iv;


	rst = vsm_process(session,nullptr);
	rst = session->mcu_task_info.resp_head.status;
	if (rst == SDR_OK) {
		session->hmac_context.handle = ntohl(session->hmac_context.handle);
		session->hash_context.alg_id = SGD_SM3;
		session->hash_context.step = STEP_HASH_INIT;
		session->hash_context.unsent_size = 0;
		session->hash_context.chunk_count = 1;
		session->hash_context.padded_size = 0;
		session->hash_context.padding_size = 0;
	}
	else {
		debug_printf("The Return Status is 0x%02x\n", rst);
	}

	return GET_FULL_ERR_CODE(rst);;

	// //从虚拟密码机资源池中获得一个虚拟密码机
	// VSM_PopDevice(context->vsm_pool,&vsmInfo);
	// //让虚拟密码机执行任务
	// VSM_ExecuteMCUTask(vsmInfo,&session->mcu_task_info);
	// //将虚拟密码机重新放回到资源池中
	// VSM_PushDevice(context->vsm_pool,vsmInfo);
	// //获得任务执行结果
	// rst = session->mcu_task_info.resp_head.status;
	// //清楚任务缓存，核心是清除指向接口库分配资源的指针，避免内存泄漏
	// VSM_ClearMCUTask(&session->mcu_task_info);

	// return GET_FULL_ERR_CODE(rst);
}

u32 C_HMAC_Update(sis_session* session, u8* pData, u32 uiDataLen)
{


#define min(a,b)            (((a) < (b)) ? (a) : (b))

	u32 ret = SDR_OK;
	u32 uiHashLen = 0;
	u32 offset = 0;
	u32 needSendSize = 0;

	u32 param[10] = { 0 };

	while (offset < uiDataLen)
	{
		needSendSize = min(MAX_SM3_SEND_PACKAGE_SIZE, uiDataLen - offset);
		//对数据做hash
		ret = C_Hash_SM3(session, pData, uiDataLen);
		if (ret != SDR_OK)	break;
		offset += needSendSize;
	}

	return GET_FULL_ERR_CODE(ret);
}

u32 C_HMAC_Final(sis_session* session, u8* pHash, u32* uiHashLen)
{
	u32 ret = SDR_OK;
	u32 param[10] = { 0 };
	u8 mac[32] = { 0 };
	u32 mac_len = 0;
	u32 recLen = 0;

	ret = C_HashFinal_SM3(session, mac, &mac_len);
	param[0] = htonl(session->hmac_context.handle);
	param[1] = htonl(mac_len);

	session->mcu_task_info.send_head.cmd = CMD_MAIN_SDF_HASH_PROCESS;
	// session->mcu_task_info.send_head.sub_cmd = CMD_SUB_SM3_HMAC_FINAL;
	session->mcu_task_info.send_head.sub_cmd = MCU_CMD_HMAC_FINAL;

	session->mcu_task_info.send_head.data_length = 4 + 4 + 32;

	session->mcu_task_info.send_param_count = 3;
	session->mcu_task_info.send_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[0].ptr_param = (u8*)&(param[0]);
	session->mcu_task_info.send_param[1].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.send_param[1].ptr_param = (u8*)&(param[1]);
	session->mcu_task_info.send_param[2].ptr_param_len = (u32*)ptr_len_32;
	session->mcu_task_info.send_param[2].ptr_param = mac;

	session->mcu_task_info.resp_param_count = 2;
	session->mcu_task_info.resp_param[0].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[0].ptr_param_len = (u32*)ptr_len_4;
	session->mcu_task_info.resp_param[0].ptr_param = (u8*)(&recLen);

	//session->mcu_task_info.resp_param[0].ptr_param = (u8*)(uiHashLen);
	session->mcu_task_info.resp_param[1].reply_prev_property = DEFAULT_PROPERTY;
	session->mcu_task_info.resp_param[1].ptr_param_len = (u32*)ptr_len_32;
	//session->mcu_task_info.resp_param[1].ptr_param_len = uiHashLen;   //注意原来是 &uiHashLen
	session->mcu_task_info.resp_param[1].ptr_param = (u8*)pHash;

	ret = vsm_process(session,nullptr);
	ret = session->mcu_task_info.resp_head.status;
	if (ret == SDR_OK)
	{
		*uiHashLen = ntohl(recLen);
	}
	else
	{
		*uiHashLen = 0;
	}




	return GET_FULL_ERR_CODE(ret);;


}

/**********************************************************************/