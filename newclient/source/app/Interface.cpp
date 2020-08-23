#include "Interface.h"
#include "SSF.h"
#include "./api/C_API.h"
#include "./api/C_API_EX.h"
#include "./base/Context.h"
#include "./base/Common.h"
#include "mmj_client.h"
#include <mutex>





u32 C_OpenDevice(void **pDeviceHandle)
{
	MmjClient *pClient = MmjClient::getInstance();	
	TcpClient* client = pClient->createClientConnect();
	if (client == nullptr) {
		mydebug << "Creat connect failed!" << std::endl;
		return -1;
	}


	
		



// 	sis_session session = { 0 };
// 	u32 idlenth = lenth;
// 	u32 rst = 0;
// 	u32 params[1] = { 0 };
// 	u64 deviceAddr = 0;


// 	memset(&(session), 0, sizeof(sis_session));
// 	session.mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ENV_MANAGE;
// 	session.mcu_task_info.send_head.sub_cmd = CMD_SUB_OPEN_DEVICE_BY_ID;
// 	session.mcu_task_info.send_head.data_length = lenth;

// 	session.mcu_task_info.send_param_count = 1;
// 	session.mcu_task_info.send_param[0].ptr_param_len = &idlenth;
// 	session.mcu_task_info.send_param[0].ptr_param = id;

// 	rst = vsm_process(&session);
// 	if (rst == SDR_OK)
// 	{
// 		memcpy(&deviceAddr, session.mcu_task_info.resp_head.user_parm, 8);
// 		rst = LIB_CreateDevice(deviceAddr, phDeviceHandle);
// 		//debug_printf("The LIB_CreateDevice ret:%d,addr:0x%02x\n", rst, deviceAddr);
// 	}
// 
// 	return rst;













	//创建socket连接，然后还要创建一个的devicehandle

	for (int i = 0; i < 64; i++)
	{
		//TcpClient *ptmp = new TcpClient(m_conf.getConfigMap()[IP], atoi(m_conf.getConfigMap()[PORT].c_str()));
		// m_pClientlist.push_back(ptmp);
	}
	return 0;

}






// #define __TCP_DEBUG


u32 vsm_process(sis_session* session)
{
// 	// 需要加容错处理
// 	u32 ret = 0;
// 	u32 respLength = 0;
// 	u32 sendLength = 0;
// 	u32 i = 0, read_len = 0;
// 	static u32 count = 0;
// 	++count; //发送的网络包序号
// 
// 	sis_mcu_task_info* taskInfo = &session->mcu_task_info;
// 
// 	//涉及到FPGA高低位转码和MCU头网络字节序转码，所以需要首先计算真实长度
// 	sendLength = taskInfo->send_head.data_length + MCU_SEND_HEAD_LENGTH;
// 	taskInfo->send_head.data_length = htons(taskInfo->send_head.data_length);
// 	taskInfo->send_head.hard_parm = htonl(taskInfo->send_head.hard_parm);
// 
// 	debug_printf("the mcu_task_info lenth:0x%02x,hard_parm:0x%02x\n", taskInfo->send_head.data_length, taskInfo->send_head.hard_parm);
// 
// 	MmjClient *pClient = MmjClient::getInstance();
// 	TcpClient *sock = pClient->getSocket();
// 	// mydebug << "****The send socket fd :" << sock->getfd() << endl;
// 
// 	while (!sock){
// 		mydebug << "error " << endl;
// 		sock = pClient->getSocket();
// 	}
// 
// 	//0、发送网络包头 @siscom\n + lenth  发送16个字节的网络头
// 	//u8 headnet[16] = { '@','s','i','s','c','o','m','\n',0,0,0,0,0,0,0,0 };
// 	//u32 allLenth = sendLength;
// 	//PUT_ULONG_BE(allLenth, headnet, 8);
// 	//PUT_ULONG_BE(count, headnet, 12);
// 	//ret = sock->Write((const char *)headnet, 16);
// 
// #ifdef __TCP_DEBUG
// 	mydebug << "send head net data " << endl;
// 	for (int i = 0; i < 16; i++)
// 	{
// 		my_printf("0x%02x ", headnet[i]);
// 	}
// 	my_printf("\n");
// #endif
// 	//1、先发送包头
// 	sock->Write((const char *)&taskInfo->send_head, MCU_SEND_HEAD_LENGTH);
// 	if (0 > ret) {
// 		return -1;
// 	}
// #ifdef __TCP_DEBUG
// 	u8 data[MCU_RESP_HEAD_LENGTH] = { 0 };
// 	mydebug << "send session head data " << endl;
// 	memcpy(data, (char*)&taskInfo->send_head, MCU_RESP_HEAD_LENGTH);
// 	for (int i = 0; i < MCU_RESP_HEAD_LENGTH; i++)
// 	{
// 		my_printf("0x%02x ", data[i]);
// 	}
// 	my_printf("\n");
// #endif
// 
// 	//2、然后发送参数
// 	for (i = 0; i < taskInfo->send_param_count; i++) {
// 		debug_printf("The netsend -------> param %d lenth is %d\n", i, *(taskInfo->send_param[i].ptr_param_len));
// 		// ret = sock.Write((char *)taskInfo->send_param[i].ptr_param, *(taskInfo->send_param[i].ptr_param_len));
// 		ret = sock->Write((const char *)taskInfo->send_param[i].ptr_param, *(taskInfo->send_param[i].ptr_param_len));
// 		 #ifdef __TCP_DEBUG
// 		     u8 data2[512] = {0};
// 		     debug_printf("\n------------taskInfo->send_param[%d].ptr_param----------------\n",i);
// 		     memcpy(data2,(char*)&taskInfo->send_param[i].ptr_param,*(taskInfo->send_param[i].ptr_param_len));
// 		     for(int i=0;i<*(taskInfo->send_param[i].ptr_param_len);i++)
// 		     {
// 		         my_printf("0x%02x ", data2[i]);
// 		     }
// 		     my_printf("\n");
// 		 #endif
// 		if (0 > ret) {
// 			return -1;
// 		}
// 	}
// 	//3、读取返回数据
// 	debug_printf("sock.Write success!\n");
// 
// 	//0、读取数据，首先读取网络包头 16个字节
// 	u8 rechead[32] = { 0 };
// // 	mydebug << "****The read socket fd :" << sock->getfd() << endl;
// // 	ret = sock->Read((char *)rechead, 16);
// // #ifdef __TCP_DEBUG
// // 	mydebug << "rec tcpip head data " << endl;
// // 	for (int i = 0; i < 16; i++)
// // 	{
// // 		my_printf("0x%02x ", rechead[i]);
// // 	}
// // 	my_printf("\n----------------------------------\n");
// // #endif
// 
// 	ret = sock->Read((char *)&taskInfo->resp_head, MCU_RESP_HEAD_LENGTH);
// 	if (ret == -1) {
// 		debug_printf("time out\n");
// 		return 0;
// 	}
// #ifdef __TCP_DEBUG
// 	u8 rsphead[MCU_RESP_HEAD_LENGTH] = { 0 };
// 	mydebug << "rec resp head data " << endl;
// 	memcpy(rsphead, (char*)&taskInfo->resp_head, MCU_RESP_HEAD_LENGTH);
// 	for (int i = 0; i < MCU_RESP_HEAD_LENGTH; i++) {
// 		my_printf("0x%02x ", rsphead[i]);
// 	}
// 	my_printf("\n----------------------------------------\n");
// #endif
// 	mydebug << "taskInfo->resp_param info" << endl;
// 
// 	taskInfo->resp_head.data_length = ntohs(taskInfo->resp_head.data_length);
// 	debug_printf("######## The Status is 0x%02x,the lenth is 0x%02x\n", taskInfo->resp_head.status, taskInfo->resp_head.data_length);
// 
// 	if (taskInfo->resp_head.status == 0) {
// 		u32 user_read_len = 0;
// 		for (i = 0; i < taskInfo->resp_param_count; i++) {
// 			switch (taskInfo->resp_param[i].reply_prev_property) {
// 				//依赖于上一包数据
// 			case RELAY_PREV_PROPERTY:
// 				*(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
// 				read_len = *(taskInfo->resp_param[i].ptr_param_len);
// 				break;
// 			case RELAY_TOTAL_PROPERTY:
// 				*(taskInfo->resp_param[i].ptr_param_len) = taskInfo->resp_head.data_length;
// 				// read_len = *(taskInfo->resp_param[i].ptr_param_len)	- taskInfo->resp_param[i].ptr_param[0];
// 				read_len = taskInfo->resp_head.data_length;
// 				break;
// 
// 			case RELAY_PREV_PROPERTY_4:
// 				*(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
// 				read_len = *(taskInfo->resp_param[i].ptr_param_len) * 4;
// 				break;
// 			case RELAY_PREV_PROPERTY_8:
// 				*(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
// 				read_len = *(taskInfo->resp_param[i].ptr_param_len) * 8;
// 				break;
// 			case RELAY_PREV_PROPERTY_12:
// 				*(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len)) * 12;
// 				read_len = *(taskInfo->resp_param[i].ptr_param_len) * 12;
// 				break;
// 			case RELAY_PREV_PROPERTY_72:
// 				*(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
// 				*(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len)) * 72;
// 				read_len = *(taskInfo->resp_param[i].ptr_param_len) * 72;
// 				break;
// 			default:
// 				read_len = *(taskInfo->resp_param[i].ptr_param_len);
// 				break;
// 			}
// 
// 			debug_printf("The net read <------ read_len is 0x%02x\n", read_len);
// 			if (read_len > 0) {
// 				ret = sock->Read((char *)taskInfo->resp_param[i].ptr_param, read_len);
// #ifdef __TCP_DEBUG
// 				mydebug << "recive ptr_param data " << endl;
// 				for (unsigned int j = 0; j < read_len; j++)
// 				{
// 					my_printf("0x%02x ", *(taskInfo->resp_param[i].ptr_param + j));
// 				}
// 				my_printf("\n------------------------------------------------\n");
// #endif
// 				if (0 > ret) {
// 					return -1;
// 				}
// 			}
// 		}
// 	}
// 	else {
// 		//debug_printf("resp_head get res status err!!!!!!",(u8*)(&taskInfo->resp_head), 0);
// 	}
// 	pClient->putSocket(sock);
// 	return SDR_OK;
	return 0;
}






u32 nettest(unsigned char *senddata,unsigned int sendlenth,unsigned char *recdata)
{
// 	// 需要加容错处理
// 	u32 ret = 0;
// 	u32 respLength = 0;
// 	u32 sendLength = 1024;
// 	u32 i = 0, read_len = 0;
// 	static u32 count = 0;
// 	++count;       //发送的网络包序号
// 
// 	MmjClient *pClient = MmjClient::getInstance();
// 	TcpClient *sock = pClient->getSocket();
// 
// 	while (!sock)
// 	{
// 		mydebug << "error " << endl;
// 		sock = pClient->getSocket();
// 	}
// 
// 	SOCKET fd = sock->getfd();
// 
// 	PUT_ULONG_BE(fd, senddata, 0);
// 	PUT_ULONG_BE(count, senddata, 4);
// 	PUT_ULONG_BE(sendlenth, senddata, 8);
// 
// 	ret = sock->Write((const char *)senddata, 16);
// 	if (0 > ret) {
// 		mydebug << "send error" << endl;
// 		return -1;
// 	}
// 
// 	sock->Write((const char *)(senddata), 1024);
// 	if (0 > ret) {
// 		mydebug << "send error" << endl;
// 		return -1;
// 	}
// 
// 	ret = sock->Read((char *)recdata, 16);
// 	ret = sock->Read((char *)(recdata+16), (1024-16));
// 
// 
// 	pClient->putSocket(sock);
// 	return SDR_OK;
	return 0;
}














