#ifndef HEADER_SM3_H
#define HEADER_SM3_H

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef unsigned long u32m3;
typedef unsigned char u8m3;

#define SM3_DIGEST_LENGTH 32
#define SM3_CBLOCK	64

//SM3 Flag值
#define SM3_FLAG_NEED_CALC_ZVALUE 0x1

typedef struct _SM3_CTX
{
	u8m3	m_pbLastGroup[SM3_CBLOCK];
	u32m3	m_dwLastLen;
	u32m3	m_dwGroupNum; //已经计算过的分组数目
	u32m3	m_AA;
	u32m3   m_BB;
	u32m3	m_CC;
	u32m3   m_DD;
	u32m3	m_EE;
	u32m3   m_FF;
	u32m3	m_GG;
	u32m3   m_HH;

	u8m3	m_ucFlag;
}SM3_CTX;

int SM3_HASH_INIT(SM3_CTX* pSm3Ctx);

int SM3_HASH_UPDATE(SM3_CTX* pSm3Ctx, 
					 u8m3* pbData, 
					 u32m3 dwDataLen);

int SM3_HASH_FINAL(u8m3* pbHashValue, 
					SM3_CTX* pSm3Ctx);

int SM3_HASH_GETSTATE(SM3_CTX*	pSm3Ctx, u8m3* iv, u8m3* lastData, int* lastDataLen, int64_t *bitsHashProcessed);

#ifdef  __cplusplus
}
#endif

#endif