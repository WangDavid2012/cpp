//#include "VSM.h"
//#include "Common.h"
//#include "SDFLog.h"
//#include "Context.h"
//
//#include <fcntl.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <arpa/inet.h>
//
//    /**客户端库全局上下文对象*/
//    extern sis_sdf_lib_ctx *context;
//
//    /*初始化虚拟密码机资源池*/
//    u32 VSM_InitPool(sis_vsm_pool **phPool)
//    {
//        sis_vsm_pool *pool = malloc(sizeof(sis_vsm_pool));
//        if(pool == NULL)                                        //内存分配失败
//            return -1;
//        pool->front = NULL;
//        pool->rear = NULL;
//        pthread_mutex_init(&(pool->queue_lock),NULL);           //初始化互斥量
//        pthread_mutex_init(&(pool->queue_ready_lock),NULL);     //初始化条件变量用的互斥量
//        pthread_cond_init(&(pool->queue_ready),NULL);           //初始化条件变量
//        *phPool = pool;
//        return SDR_OK;
//    }
//
//    /*在虚拟密码机*/
//    u32 VSM_AddDevice(sis_vsm_pool *pool,u32 pipe)
//    {
//        char deviceName[16]= {};
//        char *pDeviceName;
//        sis_vsm_info * vsm = (sis_vsm_info *)malloc(sizeof(sis_vsm_info));
//        if(vsm == NULL) { //内存分配失败
//            free(vsm);
//            return -1;
//        }
//        sprintf(deviceName,"/dev/%s%d",SIS_VSM_NAME,pipe);
//        pDeviceName = malloc(strlen(deviceName));
//        memcpy(pDeviceName,deviceName,strlen(deviceName));
//        vsm->fd = open(pDeviceName, O_RDWR | O_NONBLOCK );
//        if(0 > vsm->fd ) {
//            free(vsm);
//            free(pDeviceName);
//            return -1;
//        }
//        //vsm->device_name = (u8*)malloc(strlen(deviceName));
//        //strcpy(vsm->device_name,deviceName);
//        free(pDeviceName);
//        vsm->pipe_no = pipe;
//        VSM_PushDevice(pool,vsm);
//        return SDR_OK;
//    }
//
//    /*从密码机池里面获得一个可用虚拟密码机*/
//    u32 VSM_PopDevice(sis_vsm_pool *pool,sis_vsm_info **phVsmInfo)
//    {
//        /*从资源池里面获取虚拟密码机时需要使用两个锁，否则会造成死锁*/
//        sis_vsm_info *vsmInfo;
//        /*读取密码机的锁是保证只有一个线程可以读取密码机*/
//        pthread_mutex_lock(&(pool->queue_ready_lock));
//        /*如果资源池中没有可用的密码机*/
//        while(pool->front == NULL) {
//            //等待资源池虚拟密码机数量发生变化
//            pthread_cond_wait(&(pool->queue_ready), &(pool->queue_ready_lock));
//        }
//        /*写锁是保证在获取密码机时，无法让其线程修改资源池*/
//        pthread_mutex_lock(&(pool->queue_lock));
//        vsmInfo = pool->front;
//        if(pool->rear == pool->front) {
//            pool->rear = NULL;
//            pool->front = NULL;
//        } else {
//            //在队列头指针进行操作
//            pool->front = pool->front->next;
//        }
//        /*解除资源池锁定，允许其他线程将虚拟密码机放入资源池*/
//        pthread_mutex_unlock(&(pool->queue_lock));
//        /*解除读取密码机的锁，允许其他线程获取虚拟密码机*/
//        pthread_mutex_unlock(&(pool->queue_ready_lock));
//        *phVsmInfo = vsmInfo;
//        return SDR_OK;
//    }
//
//    /*将虚拟密码机使用完毕后放回池中*/
//    u32 VSM_PushDevice(sis_vsm_pool *pool,sis_vsm_info *vsmInfo)
//    {
//        /*锁定资源池，无法让其线程修改资源池*/
//        pthread_mutex_lock(&(pool->queue_lock)); //互斥量上锁
//        if(pool->front == NULL) {
//            pool->front = vsmInfo;
//        }
//        if(pool->rear == NULL) {
//            pool->rear = vsmInfo;
//        } else {
//            pool->rear->next = vsmInfo;
//            pool->rear = vsmInfo;
//        }
//        /*解除资源池锁定，允许其他线程修改资源池*/
//        pthread_mutex_unlock(&(pool->queue_lock)); //互斥量解锁
//        /*通知资源池有可用的虚拟密码机*/
//        pthread_cond_signal(&(pool->queue_ready)); //给条件变量发信号
//        return SDR_OK;
//    }
//
//    /*清空虚拟密码机资源池*/
//    u32 VSM_ClearPool(sis_vsm_pool *pool)
//    {
//        sis_vsm_info *vsmInfo = NULL;
//        while(pool->front != NULL) {
//            VSM_PopDevice(pool,&vsmInfo);
//            if(vsmInfo!=NULL) {
//                free(vsmInfo);
//                vsmInfo = NULL;
//            }
//        }
//        /*
//        pthread_mutex_lock(&(pool->queue_lock));//互斥量加锁
//        while(pool->front != pool->rear)
//        {
//            vsmInfo = pool->front->next;
//            pool->front->next = vsmInfo->next;
//            if (pool->front->next == NULL)
//                pool->rear = pool->front;
//            vsmInfo->next = NULL;
//            close(vsmInfo->fd);
//            //free(vsmInfo->device_name);
//            free(vsmInfo);
//        }
//        if(pool->front!=NULL)
//        {
//            free(pool->front);
//        }
//        pthread_mutex_unlock(&(pool->queue_lock)); //互斥量解锁
//        */
//        free(pool);
//        return SDR_OK;
//    }
//
//    ///**传入session句柄完成数据收发处理*/
//    //u32 vsm_process(sis_session* session)
//    //{
//    //    u32 rst = 0;
//    //    sis_vsm_info *vsmInfo = NULL;
//    //    //从虚拟密码机资源池中获得一个虚拟密码机
//    //    VSM_PopDevice(context->vsm_pool,&vsmInfo);
//    //    //让虚拟密码机执行任务
//    //    VSM_ExecuteMCUTask(vsmInfo,&session->mcu_task_info);
//    //    //将虚拟密码机重新放回到资源池中
//    //    VSM_PushDevice(context->vsm_pool,vsmInfo);
//    //    //获得任务执行结果
//    //    rst = session->mcu_task_info.resp_head.status;
//    //    //清楚任务缓存，核心是清除指向接口库分配资源的指针，避免内存泄漏
//    //    VSM_ClearMCUTask(&session->mcu_task_info);
//    //    return rst;
//    //}
//
//    /*清除FPGA任务的残留数据*/
//    u32 VSM_ClearFPGATask(sis_fpga_task_info* taskInfo)
//    {
//        taskInfo->send_cmd=0;                   //命令字
//        taskInfo->send_key_index=0;             //密钥索引号
//        taskInfo->send_param_length=0;          //发送的参数部分的长度
//        taskInfo->send_param=NULL;              //参数数据，包括IV、随机数等，可在内存重新组包
//        taskInfo->send_undelivered_length=0;    //上次不满足分组要求未发送部分的长度
//        taskInfo->send_undelivered=NULL;        //上次不满足分组要求未发送部分的数据，主要用于HASH和分组算法
//        taskInfo->send_data_length=0;           //发送的数据部分的长度
//        taskInfo->send_data=NULL;               //发送计算数据，不含参数，使用调用者的内存地址，不重新封装，减少内存拷贝，提高效率
//        taskInfo->send_padding_length=0;        //发送的数据填充的部分长度
//        taskInfo->send_padding=NULL;            //发送填充的数据，主要用于HASH和分组算法
//        taskInfo->resp_param_length=0;          //应答的参数部分长度，发送前指定，接收时按此长度截取数据
//        taskInfo->resp_param=NULL;              //参数部分的数据，接收时自动截取
//        taskInfo->resp_data_length=0;           //应答的数据部分长度，等于应答总长度减去参数部分的长度
//        taskInfo->resp_data=NULL;               //数据体部分的数据，接收时自动截取
//        taskInfo->resp_status=0;                //执行状态信息
//        return SDR_OK;
//    }
//
//    /*清除MCU任务的残留数据*/
//    u32 VSM_ClearMCUTask(sis_mcu_task_info* taskInfo)
//    {
//        u8 i = 0;
//        //发送给MCU的命令头
//        memset(&taskInfo->send_head,0,MCU_SEND_HEAD_LENGTH);//应用参数
//        //发送给MCU的数据体
//        taskInfo->send_param_count = 0;
//        for(i = 0; i < PARAM_MAX; i++) {
//            taskInfo->send_param[i].ptr_param_len = NULL;
//            taskInfo->send_param[i].ptr_param = NULL;
//        }
//        //taskInfo->send_param_length=0;//发送的参数部分的长度
//        //taskInfo->send_param=NULL;//参数数据，包括IV、随机数等，可在内存重新组包
//        //taskInfo->send_data_length=0;//发送的数据部分的长度
//        //taskInfo->send_data=NULL;//发送计算数据，不含参数，使用调用者的内存地址，不重新封装，减少内存拷贝，提高效率
//        //MCU应答的数据头
//        memset(&taskInfo->resp_head,0,MCU_RESP_HEAD_LENGTH);//应用参数
//        //MCU应答的数据体
//        taskInfo->resp_param_count = 0;
//        for(i = 0; i < PARAM_MAX; i++) {
//            taskInfo->resp_param[i].ptr_param = NULL;
//            taskInfo->resp_param[i].ptr_param_len = NULL;
//        }
//        //taskInfo->resp_param_length=0;//应答的参数部分长度，发送前指定，接收时按此长度截取数据
//        //taskInfo->resp_param=NULL;//参数部分的数据，接收时自动截取
//        //taskInfo->resp_data_length=0;//应答的数据部分长度，等于应答总长度减去参数部分的长度
//        //taskInfo->resp_data=NULL; //数据体部分的数据，接收时自动截取
//
//        return SDR_OK;
//    }
//
//
//    /*向虚拟密码机发送执令并获得返回结果*/
//    u32 VSM_ExecuteFPGATask(sis_vsm_info *vsmInfo,sis_fpga_task_info* taskInfo)
//    {
//        u32 ret = 0;
//        ret = VSM_SendFPGATask(vsmInfo, taskInfo);
//        if(ret!=SDR_OK) {
//            return ret;
//        }
//        return VSM_ReceFPGATask(vsmInfo, taskInfo);
//    }
//
//    /*向虚拟密码机发送执令*/
//    u32 VSM_SendFPGATask(sis_vsm_info *vsmInfo,sis_fpga_task_info* taskInfo)
//    {
//        // 需要加容错处理
//        u32 ret = 0;
//        u32 sendLength=0;
//        ret = lseek(vsmInfo->fd, 0, SEEK_SET);
//        if(0 > ret) {
//            return -1;
//        }
//        if(taskInfo->send_param_length>0) {
//            ret = write(vsmInfo->fd, taskInfo->send_param, taskInfo->send_param_length);
//            _SDF_PrintBuf("send_param",taskInfo->send_param,taskInfo->send_param_length);
//            if(0 > ret) {
//                return -1;
//            }
//        }
//        if(taskInfo->send_undelivered_length>0) {
//            ret = write(vsmInfo->fd, taskInfo->send_undelivered, taskInfo->send_undelivered_length);
//            _SDF_PrintBuf("send_undelivered",taskInfo->send_undelivered,taskInfo->send_undelivered_length);
//            if(0 > ret) {
//                return -1;
//            }
//        }
//        if(taskInfo->send_data_length>0) {
//            ret = write(vsmInfo->fd, taskInfo->send_data, taskInfo->send_data_length);
//            _SDF_PrintBuf("send_data",taskInfo->send_data,taskInfo->send_data_length);
//            if(0 > ret) {
//                return -1;
//            }
//        }
//        if(taskInfo->send_padding_length>0) {
//            ret = write(vsmInfo->fd, taskInfo->send_padding, taskInfo->send_padding_length);
//            _SDF_PrintBuf("send_padding",taskInfo->send_padding,taskInfo->send_padding_length);
//            if(0 > ret) {
//                return -1;
//            }
//        }
//        ret = ioctl(vsmInfo->fd,CMD_SET_KEY_INDEX,taskInfo->send_key_index);
//        if(0 > ret) {
//            return -1;
//        }
//        sendLength = taskInfo->send_data_length+taskInfo->send_param_length+taskInfo->send_padding_length+taskInfo->send_undelivered_length;
//        _SDF_Print("VSM_SendFPGATask vsm:%d chan_no:%d sendLength:%x\n",vsmInfo->fd,vsmInfo->pipe_no,sendLength);
//        sendLength = sendLength % 32 ? (sendLength << 16 | ((sendLength / 32 + 1) * 32)) : (sendLength << 16 | sendLength);
//        ret = ioctl(vsmInfo->fd,CMD_SET_SEND_LEN,sendLength);
//        if(0 > ret) {
//            return -1;
//        }
//        ret = ioctl(vsmInfo->fd,CMD_SET_SEND_CMD,taskInfo->send_cmd);
//        if(0 > ret) {
//            return -1;
//        }
//        return SDR_OK;
//    }
//
//    /*获得虚拟密码机返回结果*/
//    u32 VSM_ReceFPGATask(sis_vsm_info *vsmInfo,sis_fpga_task_info* taskInfo)
//    {
//        // 需要加容错处理
//        u32 ret = 0;
//        u32 respLength=0;
//        u32 respStatus=0;
//        u32 dlen_l, dlen_h;
//        ret = ioctl(vsmInfo->fd,CMD_GET_RESP_LEN,&respLength);
//        U32_SPLIT(respLength, dlen_h, dlen_l);
//        respLength = ((dlen_h == 0) ? dlen_l : dlen_h);
//        _SDF_Print("VSM_ExecuteMCUTask vsm:%d chan_no:%d respLength:%x\n",vsmInfo->fd,vsmInfo->pipe_no,respLength);
//
//
//        ret = ioctl(vsmInfo->fd,CMD_GET_STATUS,&respStatus);
//        U32_SPLIT(respStatus, dlen_h, dlen_l);
//        taskInfo->resp_status = ((dlen_h == 0) ? dlen_l : dlen_h);
//        _SDF_Print("VSM_ExecuteMCUTask vsm:%d chan_no:%d respStatus:%x\n",vsmInfo->fd,vsmInfo->pipe_no,respStatus);
//
//        taskInfo->resp_data_length = respLength - taskInfo->resp_param_length;
//        if(0 > ret) {
//            return -1;
//        }
//        ret = lseek(vsmInfo->fd, 0, SEEK_SET);
//        if(0 > ret) {
//            return -1;
//        }
//        if(taskInfo->resp_param_length>0) {
//            ret = read(vsmInfo->fd, taskInfo->resp_param, taskInfo->resp_param_length);
//            _SDF_PrintBuf("resp_param",taskInfo->resp_param,taskInfo->resp_param_length);
//            if(0 > ret) {
//                return -1;
//            }
//        }
//        if(taskInfo->resp_data_length>0) {
//            ret = read(vsmInfo->fd, taskInfo->resp_data, taskInfo->resp_data_length);
//            _SDF_PrintBuf("resp_data",taskInfo->resp_data,taskInfo->resp_data_length);
//            if(0 > ret) {
//                return -1;
//            }
//        }
//        return SDR_OK;
//
//    }
//
//    /*向虚拟密码机发送执令并获得返回结果*/
//    u32 VSM_ExecuteMCUTask(sis_vsm_info *vsmInfo,sis_mcu_task_info* taskInfo)
//    {
//        // 需要加容错处理
//        u32 ret = 0;
//        u32 respLength=0;
//        u32 sendLength=0;
//        u32 dlen_l, dlen_h;
//        u32 i = 0, read_len = 0;;
//
//        //涉及到FPGA高低位转码和MCU头网络字节序转码，所以需要首先计算真实长度
//        sendLength = taskInfo->send_head.data_length + MCU_SEND_HEAD_LENGTH;
//
//        ret = lseek(vsmInfo->fd, 0, SEEK_SET);
//        if(0 > ret) {
//            return -1;
//        }
//        _SDF_Print("VSM_ExecuteMCUTask vsm:%d chan_no:%d\n",vsmInfo->fd,vsmInfo->pipe_no);
//        //taskInfo->send_head.channel_no = (u8)(vsmInfo->pipe_no % SIS_HSM_SESSION_COUNT);
//        //taskInfo->send_head.mcu_cmd = MCU_CMD;
//        //发送给MCU数据的长度需要做网络字节序的转码
//        taskInfo->send_head.data_length = htons(taskInfo->send_head.data_length);
//        //硬件参数不检测可以关闭
//        //taskInfo->send_head.hard_parm = htonl(taskInfo->send_head.hard_parm);
//        //通道号不检测可以关闭
//        //taskInfo->send_head.channel_no = (CK_CHAR)(vsmInfo->pipe_no % SIS_HSM_SESSION_COUNT);
//        _SDF_PrintBuf("send_head",(u8*)(&taskInfo->send_head), MCU_SEND_HEAD_LENGTH);
//
//        ret = write(vsmInfo->fd, &taskInfo->send_head, MCU_SEND_HEAD_LENGTH);
//        if(0 > ret) {
//            return -1;
//        }
//
//        for(i = 0; i < taskInfo->send_param_count; i++) {
//            ret = write(vsmInfo->fd, taskInfo->send_param[i].ptr_param, *(taskInfo->send_param[i].ptr_param_len));
//            _SDF_PrintBuf("send_param",taskInfo->send_param[i].ptr_param, *(taskInfo->send_param[i].ptr_param_len));
//            if(0 > ret) {
//                return -1;
//            }
//        }
//
//        _SDF_Print("VSM_ExecuteMCUTask vsm:%d chan_no:%d sendLength:%d\n",vsmInfo->fd,vsmInfo->pipe_no,sendLength);
//        //发送给FPGA的数据长度需要做高低位转码
//        sendLength = sendLength % 32 ? (sendLength << 16 | ((sendLength / 32 + 1) * 32)) : (sendLength << 16 | sendLength);;
//        ret = ioctl(vsmInfo->fd,CMD_SET_SEND_LEN,sendLength);
//        if(0 > ret) {
//            return -1;
//        }
//        ret = ioctl(vsmInfo->fd,CMD_SET_SEND_CMD,MCU_CMD);
//        if(0 > ret) {
//            return -1;
//        }
//        ret = ioctl(vsmInfo->fd,CMD_GET_RESP_LEN,&respLength);
//
//        U32_SPLIT(respLength, dlen_h, dlen_l);
//        respLength = ((dlen_h == 0) ? dlen_l : dlen_h);
//        _SDF_Print("VSM_ExecuteMCUTask vsm:%d chan_no:%d respLength:%d\n",vsmInfo->fd,vsmInfo->pipe_no,respLength);
//        if(0 > ret) {
//            return -1;
//        }
//        ret = lseek(vsmInfo->fd, 0, SEEK_SET);
//        if(0 > ret) {
//            return -1;
//        }
//
//        ret = read(vsmInfo->fd, &taskInfo->resp_head, MCU_RESP_HEAD_LENGTH);
//        _SDF_Print("VSM_ExecuteMCUTask respheadDataLength:%x \n",taskInfo->resp_head.data_length);
//        //MCU返回数据的长度需要做网络字节序的转码
//        taskInfo->resp_head.data_length = ntohs(taskInfo->resp_head.data_length);
//        _SDF_Print("VSM_ExecuteMCUTask respheadDataLength:%x \n",taskInfo->resp_head.data_length);
//        _SDF_PrintBuf("resp_head",(u8*)(&taskInfo->resp_head), MCU_RESP_HEAD_LENGTH);
//
//        if(taskInfo->resp_head.status == 0) {
//            u32 user_read_len = 0;
//            for(i = 0; i < taskInfo->resp_param_count; i++) {
//                switch (taskInfo->resp_param[i].reply_prev_property) {
//                case RELAY_PREV_PROPERTY:
//                    *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
//    				read_len = *(taskInfo->resp_param[i].ptr_param_len);			
//                    break;
//                case RELAY_TOTAL_PROPERTY:
//                    *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
//                    read_len = *(taskInfo->resp_param[i].ptr_param_len)	- taskInfo->resp_param[i].ptr_param[0];
//                    break;
//
//                case RELAY_PREV_PROPERTY_4:
//                    *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
//    				read_len = *(taskInfo->resp_param[i].ptr_param_len) * 4;
//                    break;
//    			case RELAY_PREV_PROPERTY_8:
//    				*(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
//    				read_len = *(taskInfo->resp_param[i].ptr_param_len) * 8;
//    				break;
//                case RELAY_PREV_PROPERTY_12:
//                    *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len)) * 12;
//    				read_len = *(taskInfo->resp_param[i].ptr_param_len) * 12;
//                    break;
//                case RELAY_PREV_PROPERTY_72:
//                    *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len));
//                    *(taskInfo->resp_param[i].ptr_param_len) = ntohl(*(taskInfo->resp_param[i].ptr_param_len)) * 72;
//    				read_len = *(taskInfo->resp_param[i].ptr_param_len) * 72;                
//    				break;
//    			default:
//    				read_len = *(taskInfo->resp_param[i].ptr_param_len);
//    				break;
//                }
//
//                if(read_len > 0) {
//                    ret = read(vsmInfo->fd, (u8*)taskInfo->resp_param[i].ptr_param, read_len);
//                    _SDF_PrintBuf("resp_param",taskInfo->resp_param[i].ptr_param, read_len);
//                    if(0 > ret) {
//                        return -1;
//                    }
//                    //user_read_len += (*(taskInfo->resp_param[i].ptr_param_len));
//                }
//            }
//        } 
//    	else {
//            _SDF_PrintBuf("resp_head get res status err!!!!!!",(u8*)(&taskInfo->resp_head), 0);
//        }
//        return SDR_OK;
//    }
//
//    /*向虚拟密码机发送数据，可分包多次执行*/
//    u32 VSM_SetSendData(sis_vsm_info *vsmInfo,HANDLE data,u32 dataLength,u32 pos)
//    {
//        // 需要加容错处理
//        u32 ret = 0;
//        ret = lseek(vsmInfo->fd, pos, SEEK_SET);
//        if(0 > ret) {
//            return -1;
//        }
//        ret = write(vsmInfo->fd, data, dataLength);
//        if(0 > ret) {
//            return -1;
//        }
//        return SDR_OK;
//    }
//    /*向虚拟密码发送指令，执行任务*/
//    u32 VSM_SetExcuting(sis_vsm_info *vsmInfo,u32 keyIndex,u32 dataFullLength,u32 cmd)
//    {
//        // 需要加容错处理
//        u32 ret = 0;
//        ret = ioctl(vsmInfo->fd,CMD_SET_KEY_INDEX,keyIndex);
//        if(0 > ret) {
//            return -1;
//        }
//        ret = ioctl(vsmInfo->fd,CMD_SET_SEND_LEN,dataFullLength);
//        if(0 > ret) {
//            return -1;
//        }
//        ret = ioctl(vsmInfo->fd,CMD_SET_SEND_CMD,cmd);
//        if(0 > ret) {
//            return -1;
//        }
//        return SDR_OK;
//    }
//    /*获得密码机的执行结果、应答数据长度*/
//    u32 VSM_GetRespLength(sis_vsm_info *vsmInfo,u32* respLength)
//    {
//        //需要加容错处理
//        u32 ret = 0;
//        ret = ioctl(vsmInfo->fd,CMD_GET_RESP_LEN,&respLength);
//        if(0 > ret) {
//            return -1;
//        }
//        return SDR_OK;
//    }
//    /*获得密码机的应答数据，可分包多次执行*/
//    u32 VSM_GetRespData(sis_vsm_info *vsmInfo,HANDLE data,u32 dataLength,u32 pos)
//    {
//        // 需要加容错处理
//        u32 ret = 0;
//        ret = lseek(vsmInfo->fd, pos, SEEK_SET);
//        if(0 > ret) {
//            return -1;
//        }
//        ret = read(vsmInfo->fd, data, dataLength);
//        if(0 > ret) {
//            return -1;
//        }
//        return SDR_OK;
//    }
//    /*释放虚拟密码机访问控制权，分解任务执行的最后一步*/
//    //CK_INT32 VSM_UnLockDevice(sis_vsm_info *vsmInfo);
//
