#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED




#define CHANNEL_RESET_CMD					((1 << 15) | (1 << 14))
#define MCU_CMD								((1 << 16) | (1 << 14))


#define DATA_ENCRYPT						0
#define DATA_DECRYPT						1
#define DATA_ENCRYPT_DECRYPT				2


#define WORK_KEY_TYPT_ECC_PK 0x01
#define WORK_KEY_TYPT_ECC_SK 0x02
#define WORK_KEY_TYPT_RSA_PK 0x03
#define WORK_KEY_TYPT_RSA_SK 0x04
#define WORK_KEY_TYPT_SYM_KEY 0x05

#define SM1_ECB_ENC_CMD						((1 << 19) | (1 << 18) | (1 << 14))
#define SM1_ECB_DEC_CMD						((1 << 20) | (1 << 18) | (1 << 14))
#define SM1_CBC_FIRST_BLOCK_ENC_CMD			((1 << 21) | (1 << 18) | (1 << 14))
#define SM1_CBC_OTHER_BLOCK_ENC_CMD			((1 << 21) | (1 << 14))
#define SM1_CBC_FIRST_BLOCK_DEC_CMD			((1 << 22) | (1 << 18) | (1 << 14))
#define SM1_CBC_OTHER_BLOCK_DEC_CMD			((1 << 22) | (1 << 14))
#define SM1_OFB_CMD							((1 << 23) | (1 << 14))
#define SM1_CBC_MAC_FIRST_BLOCK_CMD			((1 << 24) | (1 << 18) | (1 << 14))
#define SM1_CBC_MAC_OTHER_BLOCK_CMD			((1 << 24) | (1 << 14))

#define SM4_ECB_ENC_CMD						((1 << 19) | (1 << 18) | (1 << 17) | (1 << 14))
#define SM4_ECB_DEC_CMD						((1 << 20) | (1 << 18) | (1 << 17) | (1 << 14))
#define SM4_CBC_FIRST_BLOCK_ENC_CMD			((1 << 21) | (1 << 18) | (1 << 17) | (1 << 14))
#define SM4_CBC_OTHER_BLOCK_ENC_CMD			((1 << 21) | (1 << 17) | (1 << 14))
#define SM4_CBC_FIRST_BLOCK_DEC_CMD			((1 << 22) | (1 << 18) | (1 << 17) | (1 << 14))
#define SM4_CBC_OTHER_BLOCK_DEC_CMD			((1 << 22) | (1 << 17) | (1 << 14))
#define SM4_CTR_CMD							0
#define SM4_OFB_CMD							((1 << 23) | (1 << 17) | (1 << 14))
#define SM4_CBC_MAC_FIRST_BLOCK_CMD			((1 << 24) | (1 << 18) | (1 << 17) | (1 << 14))
#define SM4_CBC_MAC_OTHER_BLOCK_CMD			((1 << 24) | (1 << 17) | (1 << 14))

#define SM2_KEY_PARI_GEN_CMD				((1 << 26) | (1 << 14))
#define SM2_SIGN_CMD						((1 << 27) | (1 << 14))
#define SM2_VERIFY_CMD						((1 << 28) | (1 << 14))
#define SM2_PUB_ENC_CMD						((1 << 29) | (1 << 14))
#define SM2_PRI_DEC_CMD						((1 << 30) | (1 << 14))
#define SM2_KEY_AGREEMENT_CMD				((1 << 31) | (1 << 14))

#define SM3_CMD								((1 << 25) | (1 << 14))


#define GM_DEFAULT_USERID		"1234567812345678"
#define SM14_CHUNK_SIZE			16
#define SM14_IV_LEN				16

#define SM3_CHUNK_SIZE			64
#define SM3_INIT_IV				"\x73\x80\x16\x6f\x49\x14\xb2\xb9\x17\x24\x42\xd7\xda\x8a\x06\x00\xa9\x6f\x30\xbc\x16\x31\x38\xaa\xe3\x8d\xee\x4d\xb0\xfb\x0e\x4e"
#define SM3_IV_LEN				32
#define SM3_Z_BUFFER_LEN		256

#define HSM2_SIGN_LEN			64
#define HSM2_VERIFY_LEN			4
#define HSM2_ENC_LEN			128
#define HSM2_DEC_LEN			64
#define SM2_Z_LEN				256


#define CHANNEL_BUF_SIZE		    4096
#define MAX_SM1_SEND_PACKAGE_SIZE   3936    
// #define MAX_SM1_SEND_PACKAGE_SIZE   (1024*32)    
//#define MAX_SM3_SEND_PACKAGE_SIZE   2032    //(2048-SM3_CHUNK_SIZE)
#define MAX_SM3_SEND_PACKAGE_SIZE   1984      //注意此处必须是64的倍数

#define MAX_SM4_SEND_PACKAGE_SIZE   3936 
// #define MAX_SM4_SEND_PACKAGE_SIZE   (1024*32) 

#define MAX_SYM_KEY_COUNT		1024    //对称密钥，需与服务端对应
#define MAX_ASYM_KEY_COUNT		1024    //非对称密钥，需与服务端对应
#define MAX_CHANNEL_SUM			64//256
#define MAX_DATA_SIZE			4096

#define CHAN_BUF_SIZE		32*1024
#define CHAN_SIZE			256

#define SM3_HASH_SIZE       32






#ifdef CPU_BIGENDIAN
#define cpu_to_be32(v) (v)
#else
#define cpu_to_be32(v)	(((v)>>24) | (((v)>>8)&0xff00) | (((v)<<8)&0xff0000) | ((v)<<24))
#endif

#define MIN(a,b)            (((a) < (b)) ? (a) : (b))

#define U32_SPLIT(v32, h16, l16)\
	do{\
	u64 mask = 0xFFFF; \
	(l16) = v32 & mask; \
	(h16) = (v32 >> 16) & mask; \
	}while(0)
#endif // COMMON_H_INCLUDED


