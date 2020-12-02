#include "interface.h"
#include "SSF.h"
#include "./api/C_API.h"
#include "./api/C_API_EX.h"
#include "./base/Context.h"
#include "./base/Common.h"
#include "./base/SDFLog.h"
#include "./mcu/MCU.h"
#include "mmj_client.h"
#include "Tcpclient.hpp"
#include <mutex>

std::mutex netmutex;



u32 C_OpenDevice(void **phDeviceHandle)
{
    MmjClient *pClient = MmjClient::getInstance();
    TcpClient *client = pClient->createClientConnect();
    if (client == nullptr) {
        mydebug << "Creat connect failed!" << std::endl;
        return -1;
    }
    sis_session session = { 0 };
    u32 idlenth = 32;
    u32 rst = 0;
    u32 params[1] = { 0 };
    u64 deviceAddr = 0;
    u8 id[32] = {0};


    memset(&(session), 0, sizeof(sis_session));
    session.mcu_task_info.send_head.cmd = CMD_MAIN_SDF_ENV_MANAGE;
    session.mcu_task_info.send_head.sub_cmd = CMD_SUB_OPEN_DEVICE_BY_ID;
    session.mcu_task_info.send_head.data_length = idlenth;

    session.mcu_task_info.send_param_count = 1;
    session.mcu_task_info.send_param[0].ptr_param_len = &idlenth;
    session.mcu_task_info.send_param[0].ptr_param = id;
    rst = vsm_process(&session, client);
    if (rst == SDR_OK) {
        memcpy(&deviceAddr, session.mcu_task_info.resp_head.user_parm, 8);
        rst = LIB_CreateDevice(deviceAddr, phDeviceHandle, client->gettcpip());
		debug_printf("The deviceAddr is 0x%llx\n", deviceAddr);
    }
    return rst;
}

u32 vsm_process(sis_session *session, TcpClient *clientsocket)
{
    // 需要加容错处理
    u32 ret = SDR_OK;
    u32 respLength = 0;
    u32 sendLength = 0;
    u32 i = 0, read_len = 0;
    static u32 count = 0;
    ++count;	

    sis_mcu_task_info *taskInfo = &session->mcu_task_info;
    //涉及到FPGA高低位转码和MCU头网络字节序转码，所以需要首先计算真实长度
    sendLength = taskInfo->send_head.data_length + MCU_SEND_HEAD_LENGTH;
    taskInfo->send_head.data_length = htons(taskInfo->send_head.data_length);
    taskInfo->send_head.hard_parm = htonl(taskInfo->send_head.hard_parm);

	int sendfd = 0;
	MmjClient *pClient = MmjClient::getInstance();
	TcpClient *sock = nullptr;
	if (clientsocket == nullptr) {
// 		sock = pClient->getConnectionClient("172.16.81.101");
		sock = pClient->getConnectionClient(session->device->ip);
		while (!sock) {
			std::cout << "*********  waiting **********" << std::endl;
			sock = pClient->getConnectionClient(session->device->ip);

		}
	}
	else {
		sock = clientsocket;
	}
	sendfd = sock->getfd();


	mydebug << "The socket is " << sendfd << std::endl;
    sock->Write((const char *)&taskInfo->send_head, MCU_SEND_HEAD_LENGTH);
    if (0 > ret) {
        return -1;
    }

    //2、然后发送参数
    for (i = 0; i < taskInfo->send_param_count; i++) {
        debug_printf("The socket %d The param %d lenth is %d\n",sendfd, i, *(taskInfo->send_param[i].ptr_param_len));
        ret = sock->Write((const char *)taskInfo->send_param[i].ptr_param, *(taskInfo->send_param[i].ptr_param_len));
        if (0 > ret) {
            return -1;				  
        }
    }
    //3、读取返回数据
    debug_printf("The socket %d send success!\n",sendfd);

    //0、读取数据，首先读取网络包头 16个字节
    u8 rechead[32] = { 0 };
	ret = sock->Read((char *)&taskInfo->resp_head, MCU_RESP_HEAD_LENGTH);
    if (ret == -1) {
        printf("time out\n");
        return 0;
	}

	memcpy(rechead,(char *)&taskInfo->resp_head,16);
// 	printf("************rechead %d***********\n",sendfd);
// 	for (int i = 0; i < 16; i++)
// 	{
// 		printf("0x%02x,",rechead[i]);
// 	}
// 	printf("\n");



    taskInfo->resp_head.data_length = ntohs(taskInfo->resp_head.data_length);
    debug_printf("The socketid is %d,The Status is 0x%02x,the lenth is 0x%02x\n", sendfd,taskInfo->resp_head.status, taskInfo->resp_head.data_length);


    if (taskInfo->resp_head.status == 0) {
        u32 user_read_len = 0;
        for (i = 0; i < taskInfo->resp_param_count; i++) {
            switch (taskInfo->resp_param[i].reply_prev_property) {
            //依赖于上一包数据
            case RELAY_PREV_PROPERTY:
                *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
                read_len = *(taskInfo->resp_param[i].ptr_param_len);
                break;
            case RELAY_TOTAL_PROPERTY:
                *(taskInfo->resp_param[i].ptr_param_len) = taskInfo->resp_head.data_length;
                // read_len = *(taskInfo->resp_param[i].ptr_param_len)	- taskInfo->resp_param[i].ptr_param[0];
                read_len = taskInfo->resp_head.data_length;
                break;

            case RELAY_PREV_PROPERTY_4:
                *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
                read_len = *(taskInfo->resp_param[i].ptr_param_len) * 4;
                break;
            case RELAY_PREV_PROPERTY_8:
                *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
                read_len = *(taskInfo->resp_param[i].ptr_param_len) * 8;
                break;
            case RELAY_PREV_PROPERTY_12:
                *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len)) * 12;
                read_len = *(taskInfo->resp_param[i].ptr_param_len) * 12;
                break;
            case RELAY_PREV_PROPERTY_72:
                *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
                *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len)) * 72;
                read_len = *(taskInfo->resp_param[i].ptr_param_len) * 72;
                break;
            default:
                read_len = *(taskInfo->resp_param[i].ptr_param_len);
                break;
            }

            if (read_len > 0) {
                ret = sock->Read((char *)taskInfo->resp_param[i].ptr_param, read_len);
				debug_printf("The socketfd %d,read param %d,lenth:%d\n",sendfd,i,read_len);
                if (0 > ret) {
                    return -1;
                }
            }
        }
	}else{
		printf("\n**************** error socket %d   ******************\n",sendfd);
 		while (1);
	}
	pClient->putConnectionClient(sock);
    return SDR_OK;

}






u32 nettest(unsigned char *senddata, unsigned int sendlenth, unsigned char *recdata)
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














