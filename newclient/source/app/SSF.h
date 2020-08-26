#ifndef _SSF_H_
#define _SSF_H_



typedef void* pHANDLE;

#ifdef  __cplusplus
extern "C" {
#endif






#define SEND_HEAD_INFO_LENGTH 16
	typedef struct SIS_SEND_HEAD_INFO
	{
		unsigned char 	cmd;
		unsigned char 	sub_cmd;
		unsigned short	data_length;
		unsigned int	hard_parm;
		unsigned long long user_parm;
	}sis_send_head_info;



#define RESP_HEAD_INFO_LENGTH 16
	typedef struct SIS_RESP_HEAD_INFO
	{
		unsigned char 	status;         //应答状态
		unsigned char 	reserved1;      //保留字段
		unsigned short	data_length;    //应答数据部分的长度
		unsigned int	hard_parm;      //硬件参数
		unsigned long long	user_parm;
	}sis_resp_head_info;



	typedef struct SIS_NET_DATA_HEAD
	{
		unsigned char logo[8];
		unsigned int lenth;
		unsigned int reserve;
		unsigned char  headinfo[16];
		unsigned char *data;
		unsigned char  checkdata[16];
	}sis_net_data_head;








	/**
	*  \brief 将数组中的元素提取成word
	*  \param [out] n unsigned long 存放返回结果
	*  \param [in] b 输入数组指针
	*  \param [in] i index位置
	*  \return
	*
	*  \details 举例说明：b[8] = {0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF}
	*  GET_ULONG_BE(n,b,4)
	*  n = 0x90ABCDEF
	*/
#ifndef GET_ULONG_BE
#define GET_ULONG_BE(n,b,i)                             \
{                                                       \
    (n) = ( (unsigned long) (b)[(i)    ] << 24 )        \
        | ( (unsigned long) (b)[(i) + 1] << 16 )        \
        | ( (unsigned long) (b)[(i) + 2] <<  8 )        \
        | ( (unsigned long) (b)[(i) + 3]       );       \
}
#endif


// #ifndef GET_ULONG_BE
// #define GET_ULONG_BE(n,b,i)                             \
// {                                                       \
//     (n) = ( (unsigned long) ((b)[(i)    ] & 0xFF) << 24 )        \
//         | ( (unsigned long) ((b)[(i) + 1] & 0xFF) << 16 )        \
//         | ( (unsigned long) ((b)[(i) + 2] & 0xFF) <<  8 )        \
//         | ( (unsigned long) ((b)[(i) + 3] & 0xFF)       );       \
// }
// #endif




#ifndef GET_SHORT_BE
#define GET_SHORT_BE(n,b,i)                             \
{                                                       \
    (n) = ( (unsigned long) (b)[(i)    ] << 8 )        \
        | ( (unsigned long) (b)[(i) + 1]      );       \
}
#endif



	/**
	*  \brief GET_ULONG_BE(n,b,i)的逆过程
	*
	*  \param [in] n 32bit输入
	*  \param [out] b
	*  \param [in] b数组位置
	*  \return
	*
	*  \details
	*/
#ifndef PUT_ULONG_BE
#define PUT_ULONG_BE(n,b,i)                             \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif

#ifndef PUT_SHORT_BE
#define PUT_SHORT_BE(n,b,i)                             \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 8 );       \
    (b)[(i) + 1] = (unsigned char) ( (n)  );            \
}
#endif





	unsigned int SSF_ExecutetLocalCmd(sis_send_head_info* hSendHead, unsigned char* sendData, unsigned int dataLength, sis_resp_head_info* hRespHead);

	unsigned int SSF_SendCmdInit(sis_send_head_info* hSendHead, pHANDLE* phSessionHandle, pHANDLE* phVsmHandle);
	unsigned int SSF_SendCmdUpdate(pHANDLE hSessionHandle, pHANDLE hVsmHandle, unsigned char* sendData, unsigned int dataLength);
	unsigned int SSF_SendCmdFinal(pHANDLE hSessionHandle, pHANDLE hVsmHandle);

	unsigned int SSF_RespCmdInit(pHANDLE hSessionHandle, pHANDLE hVsmHandle, sis_resp_head_info* hRespHead);
	unsigned int SSF_RespCmdUpdate(pHANDLE hSessionHandle, pHANDLE hVsmHandle, unsigned char* sendData, unsigned int dataLength);
	unsigned int SSF_RespCmdFinal(pHANDLE hSessionHandle, pHANDLE hVsmHandle);




#ifdef  __cplusplus
}
#endif


#endif












