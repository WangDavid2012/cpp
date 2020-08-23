#ifndef VSM_H_INCLUDED
#define VSM_H_INCLUDED

#include "../mcu/MCU.h"
#include "../sdf/SDF.h"

// #include <sys/types.h>

// #include <sys/ioctl.h>
// #include <pthread.h>
// #include <unistd.h>

#define CMD_DRV_REST        0x00    //重置驱动
#define CMD_HSM_REST        0x01    //重置密码卡
#define CMD_VSM_REST        0x02    //重置通道

#define CMD_SET_SEND_LEN    0x10    //设置发送数据长度
#define CMD_SET_KEY_INDEX   0x11    //设置使用密钥索引号
#define CMD_SET_SEND_CMD    0x12    //设置发送的指令
#define CMD_GET_RESP_LEN    0x13    //获得应答数据长度
#define CMD_GET_STATUS      0x14    //获得执行状态

#define SIS_VSM_NAME           "sis_vsm"
#define SIS_HSM_SESSION_COUNT   64



#define MCU_SEND_HEAD_LENGTH 16

typedef struct SIS_MCU_SEND_HEAD_INFO
{
	u8 	cmd;                //主命令
	u8 	sub_cmd;            //扩展命令
	u16	data_length;        //数据部分的长度
	u32	hard_parm;          //硬件参数
	u8 	user_parm[8];       //应用参数

}sis_mcu_send_head_info;


#define MCU_RESP_HEAD_LENGTH 16
typedef struct SIS_MCU_RESP_HEAD_INFO
{
	u8 	status;         //应答状态
	u8 	reserved1;      //保留字段
	u16	data_length;    //应答数据部分的长度
	u32	hard_parm;      //硬件参数
	u8 	user_parm[8];   //应用参数
}sis_mcu_resp_head_info;

enum {
	DEFAULT_PROPERTY = 0,
	RELAY_PREV_PROPERTY,	//依赖前一个长度
	RELAY_TOTAL_PROPERTY,	//依赖开始的总长度,要解决的是管理工具的用户id，协议没有长度问题,该属性会将传出的参数当传入用，赋值为要获取协议节点当前位置之前的长度总和,最大值0xff
	RELAY_PREV_PROPERTY_4,	//依赖长度的倍数为4
	RELAY_PREV_PROPERTY_8,	//渚濊禆闀垮害鐨勫€嶆暟涓?
	RELAY_PREV_PROPERTY_12,	//依赖长度的倍数为12
	RELAY_PREV_PROPERTY_72,
};

typedef struct proto_param_info {
	//note:长度是否依赖上一个长度，
	//主要解决长度的字节序转换问题	并且将长度转为主机字节序
	u8	reply_prev_property;
	u32* ptr_param_len;		//数据的长度指针
	u8 *ptr_param;			//数据指针
}proto_param_t;

#define PARAM_MAX (16)
#define PARAM_RECV_MAX (5+128+128*4)	//为了解决管理接口协议中查询密钥结果的不确定性扩充了该变量

typedef struct SIS_MCU_TASK_INFO
{
	sis_mcu_send_head_info	send_head;      //发送给MCU的命令头
	u32 send_param_count;	                //发送参数数量
	proto_param_t send_param[PARAM_MAX];	//发送参数的内容
	sis_mcu_resp_head_info  resp_head;      //MCU应答的数据头
	u32 resp_param_count;	                //应答参数的数量
	proto_param_t resp_param[PARAM_RECV_MAX]; //如何回避查询密钥的大数组问题
}sis_mcu_task_info;

typedef struct SIS_FPGA_TASK_INFO
{
	u32				send_cmd;               //命令字
	u32				send_key_index;         //密钥索引号s
	u32				send_param_length;      //发送的参数部分的长度
	u8*				send_param;             //参数数据，包括IV、随机数等，可在内存重新组包
	u32				send_undelivered_length;//上次不满足分组要求未发送部分的长度
	u8*				send_undelivered;       //上次不满足分组要求未发送部分的数据，主要用于HASH和分组算法
	u32				send_data_length;       //发送的数据部分的长度
	u8*				send_data;              //发送计算数据，不含参数，使用调用者的内存地址，不重新封装，减少内存拷贝，提高效率
	u32				send_padding_length;    //发送的数据填充的部分长度
	u8*				send_padding;           //发送填充的数据，主要用于HASH和分组算法
	u32				resp_param_length;      //应答的参数部分长度，发送前指定，接收时按此长度截取数据
	u8*				resp_param;             //参数部分的数据，接收时自动截取
	u32				resp_data_length;       //应答的数据部分长度，等于应答总长度减去参数部分的长度
	u8*				resp_data;              //数据体部分的数据，接收时自动截取
	u32				resp_status;            //执行状态信息
}sis_fpga_task_info;


//定义队列（保存队首和队尾指针）
typedef struct SIS_VSM_POOL {
}sis_vsm_pool;




#endif // VSM_H_INCLUDED
