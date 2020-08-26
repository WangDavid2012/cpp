#ifndef C_API_H_INCLUDED
#define C_API_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../base/Context.h"





#define SDG_ALG_TYPE_SM1 1
#define SDG_ALG_TYPE_SM4 4

#define SDG_ALG_PATTERN_ECB 1
#define SDG_ALG_PATTERN_CBC 2
#define SDG_ALG_PATTERN_CFB 4
#define SDG_ALG_PATTERN_OFB 8
#define SDG_ALG_PATTERN_MAC 0x10             //王占备修改，与代码不匹配


u32 C_GetDeviceInfo(sis_session *session, DEVICEINFO *pstDeviceInfo);

u32 C_PrikeyLogin(sis_session *session, u32 KeyId, u8 *pPassword, u32 uiPasswdLen);
u32 C_GetRandom(sis_session *session, u32 uiLen, u8 *pRandom);



u32 C_GetPubSignKey_RSA(sis_session *session,
	u32 keyId,
	RSArefPublicKey *pPublicKey,
	u32 *pPublicKeyLen);

u32 C_GetPubEncKey_RSA(sis_session *session,
	u32 keyId,
	RSArefPublicKey *pPublicKey,
	u32 *pPublicKeyLen);

u32 C_GenKeyPair_RSA(sis_session *session,
	u32 uiKeySize,
	RSArefPublicKey *pPublicKey,
	RSArefPrivateKey *pPrivateKey);

u32 C_GenKeyWithIPK_RSA(sis_session *session,
	u32 keyId,
	u32 genKeyBits,
	u32 algIdentify,
	u8 *pRSACipher,
	u32 *pRSACipherLen,
	HANDLE *symKeyHandle);

u32 C_GenKeyWithEPK_RSA(sis_session *session,
	u32 genKeyBits,
	u32 algIdentify,
	RSArefPublicKey *pucPublicKey,
	u8 *pRSACipher,
	u32 *pRSACipherLen,
	HANDLE *symKeyHandle);

u32 C_ImportKeyWithISK_RSA(sis_session *session,
	u32 keyID,
	u8 *pSessionKeyCipher,
	u32 sessionKeyCipherLen,
	HANDLE *symKeyHandle);

u32 C_ExchangeEnvelope_RSA(sis_session *session,
	u32 keyId,
	RSArefPublicKey pucPublicKey, //做值拷贝
	u8 *pucEncDataIn,
	u32 pucEncDataInLen,
	u8 *pucEncDataOut,
	u32 *pucEncDataOutLen);

u32 C_GetPubSignKey_ECC(sis_session *session,
	u32 keyId,
	ECCrefPublicKey *pPublicKey,
	u32 *pPublicKeyLen);

u32 C_GetPubEncKey_ECC(sis_session *session,
	u32 keyId,
	ECCrefPublicKey *pPublicKey,
	u32 *pPublicKeyLen);

u32 C_GenKeyPair_ECC(sis_session *session,
	u32 algIdentify,
	u32 uiKeySize,
	ECCrefPublicKey *pPublicKey,
	ECCrefPrivateKey *pPrivateKey);

u32 C_GenKeyWithIPK_ECC(sis_session *session,
	u32 keyId,
	u32 genKeyBits,
	u32 algIdentify,
	ECCCipher *pEccCipher,
	HANDLE *symKeyHandle);

u32 C_GenKeyWithEPK_ECC(sis_session *session,
	u32 genKeyBits,
	u32 algIdentify,
	ECCrefPublicKey pucPublicKey,
	ECCCipher *pEccCipher,
	HANDLE *symKeyHandle);

u32 C_ImportKeyWithISK_ECC(sis_session *session,
	u32 keyID,
	ECCCipher pSessionKeyCipher,
	HANDLE *symKeyHandle);

u32 C_GenerateAgreementDataWithECC(sis_session *session,
	u32 keyId,
	u32 agreementkeyBits,
	u8 *sponsorID,
	u32 sponsorIDLength,
	ECCrefPublicKey *pucPublicKey,
	ECCrefPublicKey *pucTmpPublicKey,
	HANDLE *phAgreementHandle);

u32 C_GenerateKeyWithECC(sis_session *session,
	u8 *pucResponseID,
	u32 pucResponseIDLength,
	ECCrefPublicKey pucResponsePublicKey,    //做值拷贝
	ECCrefPublicKey pucResponseTmpPublicKey, //做值拷贝
	HANDLE phAgreementHandle,
	HANDLE *phKeyHandle);

u32 C_GenerateAgreementDataAndKeyWithECC(sis_session *session,
	u32 keyId,
	u32 uiKeyBits,
	u8 *responseID,
	u32 responseIDLength,
	u8 *sponsorID,
	u32 sponsorIDLength,
	ECCrefPublicKey sponsorPublicKey,
	ECCrefPublicKey sponsorTmpPublicKey,
	ECCrefPublicKey *responsePublicKey,
	ECCrefPublicKey *responseTmpPublicKey,
	HANDLE *phKeyHandle);

u32 C_ExchangeEnvelope_ECC(sis_session *session,
	u32 algIdentify,
	u32 keyId,
	ECCrefPublicKey pucPublicKey,
	ECCCipher pucEncDataIn,
	ECCCipher *pucEncDataOut);

u32 C_GenKeyWithKEK(sis_session *session,
	u32 keyId,
	u32 algIdentify,
	u32 uiKeyBits,
	u8 *pKeyCipher,
	u32 *pKeyCipherLen,
	HANDLE *symKeyHandle);

u32 C_ImportKeyWithKEK(sis_session *session,
	u32 keyId,
	u32 algIdentify,
	u8 *pKeyCipher,
	u32 pKeyCipherLen,
	HANDLE *symKeyHandle);

u32 C_DestorySymKey(sis_session *session, sis_work_key *key);

u32 C_ExternPublicKeyOperationEnc_RSA(sis_session *session,
	RSArefPublicKey pPublicKey,
	u8 *pDataInput,
	u32 uiDataInputLen,
	u8 *pDataOut,
	u32 *puiDataOutLen);

u32 C_InterPublicKeyOperation_RSA(sis_session *session,
	u32 keyId,
	u8 *pDataInput,
	u32 uiDataInputLen,
	u8 *pDataOut,
	u32 *puiDataOutLen);

u32 C_InterPrivateKeyOperation_RSA(sis_session *session,
	u32 keyId,
	u8 *pDataInput,
	u32 uiDataInputLen,
	u8 *pDataOut,
	u32 *puiDataOutLen);

u32 C_InterSign_ECC(sis_session *session,
	u32 keyId,
	u8 *pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature);


u32 C_InterVerify_ECC(sis_session *session,
	u32 keyId,
	u8 *pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature);

u32 C_ExternVerify_ECC(sis_session *session,
	u32 algIdentify,
	ECCrefPublicKey pucPublicKey,
	u8 *pucData,
	u32 uiDataInputLen,
	ECCSignature *pucSignature);

u32 C_ExternalEncrypt_ECC(sis_session *session,
	u32 algIdentify,
	ECCrefPublicKey pucPublicKey,
	u8 *pucData,
	u32 uiDataLength,
	ECCCipher *pucEncData);

u32 C_Encrypt_MCU(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pData,
	u32 uiDataLen,
	u8 *pEncryptData,
	u32 *puiEncryptDataLen);


u32 C_Decrypt_MCU(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pEncryptData,
	u32 uiEncryptDataLen,
	u8 *pData,
	u32 *puiDataLen);

/**支持分包运算，包大小为SYM_BLOCK_SIZE*/
u32 C_Encrypt(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pData,
	u32 uiDataLen,
	u8 *pEncryptData,
	u32 *puiEncryptDataLen);

u32 C_Decrypt(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pEncryptData,
	u32 uiEncryptDataLen,
	u8 *pData,
	u32 *puiDataLen);

u32 C_CalculateMAC(sis_session *session,
	u32 Mechanism,
	sis_work_key *key,
	u8 *pIV,
	u8 *pData,
	u32 uiDataLen,
	u8 *pMacData,
	u32 *puiMacDataLen);

u32 C_CreateFile(sis_session *session, u8 *pFileName, u32 uiFileSize);

u32 C_WriteFile(sis_session *session, u8 *pFileName, u32 uiNameLen, u32 uiOffset, u32 uiDataLen, u8 *pData);


u32 C_ReadFile(sis_session *session, u8 *pFileName, u32 uiNameLen, u32 uiOffset, u32 *puiDataLen, u8 *pData);

u32 C_DeleteFile(sis_session *session, u8 *pFileName, u32 uiNameLen);

u32 C_HashInit_SM3(sis_session *session, u8 *pID, u32 uiIdLen, u8 *pPubkey, u32 uiPubkeyLen);
u32 C_Hash_SM3(sis_session *session, u8 *pData, u32 uiDataLen);
u32 C_HashFinal_SM3(sis_session *session, u8 *pHash, u32 *uiHashLen);

u32 C_HashInit(sis_session *session, u32 Mechanism, u8 *pID, u32 uiIdLen, u8 *pPubkey, u32 uiPubkeyLen);
u32 C_Hash(sis_session *session, u8 *pData, u32 uiDataLen);
u32 C_HashFinal(sis_session *session, u8 *pHash, u32 *uiHashLen);

u32 C_HMAC_Init(sis_session *session, sis_work_key *key, u32 Mechanism);
u32 C_HMAC_Update(sis_session *session, u8 *pData, u32 uiDataLen);
u32 C_HMAC_Final(sis_session *session, u8 *pHash, u32 *uiHashLen);


#define SPEC_ELEMENT_MAX 50
extern const u32 spec_len[SPEC_ELEMENT_MAX];
extern const u32 *const ptr_len_2;
extern const u32 *const ptr_len_4;
extern const u32 *const ptr_len_8;
extern const u32 *const ptr_len_16;
extern const u32 *const ptr_len_32;
extern const u32 *const ptr_len_64;
extern const u32 *const ptr_len_128;
extern const u32 *const ptr_len_256;
extern const u32 *const ptr_len_dev_info;
extern const u32 *const ptr_len_ecc_pub;
extern const u32 *const ptr_len_rsa_pub;
extern const u32 *const ptr_len_ecc_cipher;
extern const u32 *const ptr_len_ecc_cipher_no_LC;
extern const u32 *const ptr_len_ecc_cipher_no_C;
extern const u32 *const ptr_len_ecc_pri;
extern const u32 *const ptr_len_rsa_pri;
extern const u32 *const ptr_len_ecc_sign_data;
extern const u32 *const ptr_len_1;
extern const u32 *const ptr_len_15;
extern const u32 *const ptr_len_ecc_cipher_C;

#endif