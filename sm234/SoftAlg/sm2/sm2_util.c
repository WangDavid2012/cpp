#include <string.h>
#include <time.h>

#include "..\sm3\sm3.h"
#include "sm2_util.h"

#include "sm2.h"//just to execute

#if defined(POLARSSL_PLATFORM_C)
#include "polarssl/platform.h"
#else
#include <stdlib.h>
#define polarssl_malloc     malloc
#define polarssl_free       free
#endif

#include "polarssl/hmac_drbg.h"

int LittleEndianCheck(void)// is little endian
{
	unsigned int i = 0x12;

	if (*((unsigned char*)(&i)) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void reverseData(unsigned char* pbData, unsigned int uiDataLen)
{
	unsigned int i = 0;

	if (!pbData)
	{
		return;
	}

	for (i=0; i<uiDataLen/2; i++)
	{
		pbData[i] = pbData[i] ^ pbData[uiDataLen-i-1];
		pbData[uiDataLen-i-1] = pbData[i] ^ pbData[uiDataLen-i-1];
		pbData[i] = pbData[i] ^ pbData[uiDataLen-i-1];
	}
}

void xorData(unsigned char *out, const unsigned char * const input1, const unsigned char * const input2, const long length)
{
	long i = 0;

	for (i=0; i<length; i++)
	{
		out[i] = input1[i] ^ input2[i];
	}
}

void andData(unsigned char *out, const unsigned char * const input1, const unsigned char * const input2, const long length)
{
	long i = 0;

	for (i=0; i<length; i++)
	{
		out[i] = input1[i] & input2[i];
	}
}

void orData(unsigned char *out, const unsigned char * const input1, const unsigned char * const input2, const long length)
{
	long i = 0;

	for (i=0; i<length; i++)
	{
		out[i] = input1[i] | input2[i];
	}
}


int SM2_KDF(const unsigned char *pbZValue, unsigned int uiZLen, unsigned char *pbK, unsigned int uiKLen, sm2u32 uiCTInit)
{
	int iRtn = 0;

	int	iLE = 0;
	SM3_CTX	sm3ctx;
	sm2u32	uiCT = 0;
	unsigned char	*pbMsg = NULL;
	unsigned int	uiMsgLen = 0;
	unsigned char	pbFinalHash[SM3_DIGEST_LENGTH] = {0};

	unsigned int	uiLoopCount = 0, uiFinalCount = 0, i = 0;

	SM2_ASSERT_NEQ_EX(pbK, 0, 0);
	SM2_ASSERT_EQ_EX(sizeof(sm2u32), 4, 0);

	if (!pbZValue)
	{
		uiZLen = 0;
	}
	uiMsgLen = uiZLen + 4;// Z || xx xx xx xx
	pbMsg = (unsigned char*)polarssl_malloc(uiMsgLen);
	SM2_ASSERT_NEQ_EX(pbMsg, 0, 0);
	memcpy(pbMsg, pbZValue, uiZLen);

	uiLoopCount = uiKLen / SM3_DIGEST_LENGTH;
	uiFinalCount = uiKLen % SM3_DIGEST_LENGTH;
	iLE = LittleEndianCheck();
	uiCT=uiCTInit;
	if (iLE)
	{
		for (i=0; i<uiLoopCount; i++)
		{
			memcpy(pbMsg+uiZLen, (unsigned char*)(&uiCT), 4);
			reverseData(pbMsg+uiZLen, 4);

			SM3_HASH_INIT(&sm3ctx);
			SM3_HASH_UPDATE(&sm3ctx, pbMsg, uiMsgLen);
			SM3_HASH_FINAL(pbK, &sm3ctx);
			pbK += SM3_DIGEST_LENGTH;
			uiCT++;
		}
		if (uiFinalCount)
		{
			memcpy(pbMsg+uiZLen, (unsigned char*)(&uiCT), 4);
			reverseData(pbMsg+uiZLen, 4);

			SM3_HASH_INIT(&sm3ctx);
			SM3_HASH_UPDATE(&sm3ctx, pbMsg, uiMsgLen);
			SM3_HASH_FINAL(pbFinalHash, &sm3ctx);
			memcpy(pbK, pbFinalHash, uiFinalCount);
		}
	}
	else
	{
		for (i=0; i<uiLoopCount; i++)
		{
			memcpy(pbMsg+uiZLen, ((unsigned char*)(&uiCT) + sizeof(uiCT) -4), 4);

			SM3_HASH_INIT(&sm3ctx);
			SM3_HASH_UPDATE(&sm3ctx, pbMsg, uiMsgLen);
			SM3_HASH_FINAL(pbK, &sm3ctx);
			pbK += SM3_DIGEST_LENGTH;
			uiCT++;
		}
		if (uiFinalCount)
		{
			memcpy(pbMsg+uiZLen, ((unsigned char*)(&uiCT) + sizeof(uiCT) -4), 4);

			SM3_HASH_INIT(&sm3ctx);
			SM3_HASH_UPDATE(&sm3ctx, pbMsg, uiMsgLen);
			SM3_HASH_FINAL(pbFinalHash, &sm3ctx);
			memcpy(pbK, pbFinalHash, uiFinalCount);
		}
	}

	iRtn = 1;
END:
	if (pbMsg)
	{
		polarssl_free(pbMsg);
		pbMsg = NULL;
	}

	return iRtn;
}

static int sm2_rand(void *rng_state, unsigned char *output, size_t len )
{
	size_t use_len;
	int rnd;

	if( rng_state != NULL )
	{ 
		rng_state = NULL;
	}

	srand((int)time(0));

	while( len > 0 )
	{
		use_len = len;
		if (use_len > sizeof(int))
		{
			use_len = sizeof(int);
		}
			
		rnd = rand();
		memcpy(output, &rnd, use_len);
		output += use_len;
		len -= use_len;
	}

	return 0;
}

int SM2_initKeyPair(sm2_keypair *pSM2KeyPair)
{
	int iRtn = -1;

	SM2_ASSERT_NEQ_EX(pSM2KeyPair, 0, 0);

	ecp_group_init(&pSM2KeyPair->grp);
	mpi_init(&pSM2KeyPair->d);
	ecp_point_init(&pSM2KeyPair->Q);

	iRtn = 1;
END:
	return iRtn;
}

int SM2_freeKeyPair(sm2_keypair *pSM2KeyPair)
{
	int iRtn = -1;

	SM2_ASSERT_NEQ_EX(pSM2KeyPair, 0, 0);

	ecp_group_free(&pSM2KeyPair->grp);
	mpi_free(&pSM2KeyPair->d);
	ecp_point_free(&pSM2KeyPair->Q);

	iRtn = 1;
END:
	return iRtn;
}

int SM2_genKeyPair(sm2_keypair *pSM2KeyPair)
{
	int iRtn = -1;

	hmac_drbg_context *rng_ctx = 0;
	const md_info_t *md_info = 0;

	SM2_ASSERT_NEQ_EX(pSM2KeyPair, 0, 0);

	iRtn = ecp_use_known_dp(&pSM2KeyPair->grp, ECPARAMS);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	md_info = md_info_from_type(POLARSSL_MD_SHA256);
	SM2_ASSERT_NEQ_EX(md_info, 0, 0);
	rng_ctx = (hmac_drbg_context*)polarssl_malloc(sizeof(hmac_drbg_context));
	SM2_ASSERT_NEQ_EX(rng_ctx, 0, 0);
	iRtn = hmac_drbg_init(rng_ctx, md_info, sm2_rand, 0, 0, 0);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	iRtn = ecp_gen_keypair(&pSM2KeyPair->grp, &pSM2KeyPair->d, &pSM2KeyPair->Q, hmac_drbg_random, rng_ctx);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	iRtn = 1;
END:
	if (rng_ctx)
	{
		hmac_drbg_free(rng_ctx);
		free(rng_ctx);
		rng_ctx = 0;
	}
	
	return iRtn;
}
