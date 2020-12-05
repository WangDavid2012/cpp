#ifndef HEADER_SM2_H
#define HEADER_SM2_H

#include "sm2_util.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SM2_BITS_LEN	256
#define SM2_BYTES_LEN	(SM2_BITS_LEN / 8)

typedef enum
{
	SM2_VER_1,
	SM2_VER_2
} sm2_version;

typedef enum
{
	SM2_SIG_TYPE_NORM,
	SM2_SIG_TYPE_CERT
} sm2_sig_type;

int SM2_check_version(sm2_version sm2ver);

int SM2_check_sig_type(sm2_sig_type sm2sigtype);

int SM2_sign_size(sm2_keypair *eckey);

int SM2_encrypt_size(sm2_keypair *eckey, const unsigned int uiPlainLen);

int SM2_decrypt_size(sm2_keypair *eckey, const unsigned int uiCipherLen);

int SM2_encrypt(const unsigned char *pbPlain, unsigned int uiPlainLen,
	unsigned char *pbCipher, unsigned int *puiCipherLen, sm2_keypair *eckey, sm2_version sm2ver);

int SM2_decrypt(const unsigned char *pbCipher, unsigned int uiCipherLen,
	unsigned char *pbPlain, unsigned int *puiPlainLen, sm2_keypair *eckey, sm2_version sm2ver);


//m is hash value of sm3, m_length must be 32
int SM2_sign_core(const unsigned char *m, unsigned int m_length,
	unsigned char *sigret, unsigned int *siglen, sm2_keypair *eckey);

//m is hash value of sm3, m_length must be 32
int SM2_verify_core(const unsigned char *m, unsigned int m_length,
	const unsigned char *sigbuf, unsigned int siglen, sm2_keypair *eckey);

int SM2_getZ(const unsigned char *pbIDValue, unsigned int IDLen, 
	unsigned char *pbZValue, unsigned int *puiZLen, sm2_keypair *eckey);

int SM2_sign(const unsigned char *m, unsigned int m_length,
	unsigned char *sigret, unsigned int *siglen, sm2_keypair *eckey);

int SM2_verify(const unsigned char *m, unsigned int m_length,
	const unsigned char *sigbuf, unsigned int siglen, sm2_keypair *eckey);

int SM2_sign_ex(const unsigned char *pbIDValue, unsigned int IDLen, 
				const unsigned char *m, unsigned int m_length,
				unsigned char *sigret, unsigned int *siglen, sm2_keypair *eckey);

int SM2_verify_ex(const unsigned char *pbIDValue, unsigned int IDLen, 
				  const unsigned char *m, unsigned int m_length,
				  const unsigned char *sigbuf, unsigned int siglen, sm2_keypair *eckey);

int SM2_genAgreementData(const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
						 const sm2_keypair *eckey_sponsor, const unsigned int uiSessKeyLen, \
						 ecp_point **pubkey_sponsor_tmp, sm2_keypair **eckey_sponsor_tmp);

int SM2_genAgreementDataAndKey(const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
							   const unsigned char *pbReceiverID, const unsigned int uiReceiverIDLen, \
							   const ecp_point *pubkey_sponsor, const ecp_point *pubkey_sponsor_tmp, \
							   const sm2_keypair *eckey_receiver, const unsigned int uiSessKeyLen, \
							   ecp_point **pubkey_receiver_tmp, sm2_keypair **eckey_receiver_tmp, \
							   unsigned char *pbSessKey, unsigned char *pbSB, unsigned char *pbS2);

int SM2_genKey(const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
			   const unsigned char *pbReceiverID, const unsigned int uiReceiverIDLen, \
			   const ecp_point *pubkey_receiver, const ecp_point *pubkey_receiver_tmp, \
			   const sm2_keypair *eckey_sponsor, const sm2_keypair *eckey_tmp_sponsor, \
			   const unsigned int uiSessKeyLen, unsigned char *pbSessKey, \
			   const unsigned char *pbSB, unsigned char *pbSA);
			   
// int SM2_genKey_Symm(const unsigned char *pbReceiverID, const unsigned int uiReceiverIDLen, \
// 			   const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
// 			   const EC_POINT *pubkey_sponsor, const EC_POINT *pubkey_sponsor_tmp, \
// 			   const EC_KEY *eckey_receiver, const EC_KEY *eckey_tmp_receiver, \
// 			   const unsigned int uiSessKeyLen, unsigned char *pbSessKey, \
// 			   const unsigned char *pbSB, unsigned char *pbSA);

#ifdef  __cplusplus
}
#endif
#endif