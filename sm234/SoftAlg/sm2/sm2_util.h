#ifndef HEADER_SM2_UTIL_H
#define HEADER_SM2_UTIL_H

#include "polarssl/ecp.h"

#ifdef  __cplusplus
extern "C" {
#endif

//#define _SM2_OLD_VERSION

//Assertion
#define SM2_ASSERT_EQ(_rtn,_val) \
	do\
	{\
		if((_rtn)!=(_val))\
		{\
			goto END;\
		}\
	} while(0)

#define SM2_ASSERT_EQ_EX(_rtn,_val,_err_num) \
	do\
	{\
		if((_rtn)!=(_val))\
		{\
			iRtn=(_err_num);\
			goto END;\
		}\
	} while(0)

#define SM2_ASSERT_NEQ(_rtn,_val) \
	do\
	{\
		if((_rtn)==(_val))\
		{\
			goto END;\
		}\
	} while(0)

#define SM2_ASSERT_NEQ_EX(_rtn,_val,_err_num) \
	do\
	{\
		if((_rtn)==(_val))\
		{\
			iRtn=(_err_num);\
			goto END;\
		}\
	} while(0)

typedef unsigned int sm2u32;

typedef struct _sm2_keypair
{
	ecp_group grp;      /*!<  elliptic curve used           */
	mpi d;              /*!<  secret signature key          */
	ecp_point Q;        /*!<  public signature key          */
} sm2_keypair;

#define ECPARAMS    POLARSSL_SM2_256

int LittleEndianCheck(void);// is little endian
void reverseData(unsigned char* pbData, unsigned int uiDataLen);
void xorData(unsigned char *out, const unsigned char * const input1, const unsigned char * const input2, const long length);
void andData(unsigned char *out, const unsigned char * const input1, const unsigned char * const input2, const long length);
void orData(unsigned char *out, const unsigned char * const input1, const unsigned char * const input2, const long length);
int SM2_KDF(const unsigned char *pbZValue, unsigned int uiZLen, unsigned char *pbK, unsigned int uiKLen, sm2u32 uiCTInit);
int SM2_initKeyPair(sm2_keypair *pSM2KeyPair);
int SM2_freeKeyPair(sm2_keypair *pSM2KeyPair);
int SM2_genKeyPair(sm2_keypair *pSM2KeyPair);

#ifdef __cplusplus
}
#endif

#endif