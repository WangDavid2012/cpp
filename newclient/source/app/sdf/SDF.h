#ifndef _SDF_H_
#define _SDF_H_

#if _UNIX
#define DLL
#elif _WIN32_EXP
#define DLL _declspec (dllexport)
#elif _WIN32_IMP 
#define DLL _declspec (dllimport)
#else
#define DLL
#endif

#define TRUE 1
#define FALSE 0

typedef void* HANDLE;
typedef unsigned char  BYTE;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long long  u64;




typedef struct DeviceInfo_st
{
	u8 IssuerName[40];
	u8 DeviceName[16];
	u8 DeviceSerial[16];
	u32 DeviceVersion;
	u32 StandardVersion;
	u32 AsymAlgAbility[2];
	u32 SymAlgAbility;
	u32 HashAlgAbility;
	u32 BufferSize;
} DEVICEINFO;

#define RSAref_MAX_BITS  2048
#define RSAref_MAX_LEN   256 
#define RSAref_MAX_PBITS 1024 
#define RSAref_MAX_PLEN  128 
#define RSAref_PublicKey_SIZE	519
#define RSAref_PrivateKey_SIZE	1412


typedef struct RSArefPublicKey_st
{
	u32 bits;
	u8 m[RSAref_MAX_LEN];
	u8 e[RSAref_MAX_LEN];
} RSArefPublicKey;


typedef struct RSArefPrivateKey_st
{
	u32 bits;
	u8 m[RSAref_MAX_LEN];
	u8 e[RSAref_MAX_LEN];
	u8 d[RSAref_MAX_LEN];
	u8 prime[2][RSAref_MAX_PLEN];
	u8 pexp[2][RSAref_MAX_PLEN];
	u8 coef[RSAref_MAX_PLEN];
} RSArefPrivateKey;


#define ECCref_BITS_SIZE		 256
#define ECCref_MAX_BITS			 512
#define ECCref_MAX_LEN			  64 ///((ECCref_MAX_BITS+7) / 8)
#define MAX_ECC_CIPHERLEN		 136 ///最大SM2密文长度
#define ECCref_PublicKey_SIZE    132 ///ECCref_MAX_LEN*2+4
#define ECCref_PrivateKey_SIZE    68 ///ECCref_MAX_LEN+4
#define ECCref_CIPHER_SIZE	     300 ///(ECCref_MAX_LEN + ECCref_MAX_LEN + 32 + 4 + MAX_ECC_CIPHERLEN)
#define ECCref_SIGN_SIZE		 128 ///(ECCref_MAX_LEN+ECCref_MAX_LEN)
#define ECC_ENCRYPT_LEN 		 128
#define ECC_DECRYPE_LEN			  64


typedef struct ECCrefPublicKey_st
{
	u32 bits;
	u8 x[ECCref_MAX_LEN];
	u8 y[ECCref_MAX_LEN];
} ECCrefPublicKey;

typedef struct ECCrefPrivateKey_st
{
	u32 bits;
	u8 D[ECCref_MAX_LEN];
} ECCrefPrivateKey;


typedef struct ECCCipher_st
{
	u8 x[ECCref_MAX_LEN];
	u8 y[ECCref_MAX_LEN];
	u8 M[32];
	u32 L;
	u8 C[MAX_ECC_CIPHERLEN];
} ECCCipher;


typedef struct ECCSignature_st
{
	u8 r[ECCref_MAX_LEN];
	u8 s[ECCref_MAX_LEN];
} ECCSignature;





#define OSCCA_NEWFP_256   7      


#define SGD_RSA         0x00010000 
#define SGD_SM2		    0x00020100
#define SGD_SM2_1	    0x00020200 
#define SGD_SM2_2	    0x00020400 
#define SGD_SM2_3	    0x00020800 


#define SGD_SM1_ECB	    0x00000101
#define SGD_SM1_CBC	    0x00000102
#define SGD_SM1_CFB	    0x00000104
#define SGD_SM1_OFB	    0x00000108
#define SGD_SM1_MAC	    0x00000110

#define SGD_SSF33_ECB	  0x00000201
#define SGD_SSF33_CBC	  0x00000202
#define SGD_SSF33_CFB	  0x00000204
#define SGD_SSF33_OFB	  0x00000208
#define SGD_SSF33_MAC	  0x00000210

#define SGD_SM4_ECB	    0x00000401
#define SGD_SM4_CBC	    0x00000402
#define SGD_SM4_CFB	    0x00000404
#define SGD_SM4_OFB	    0x00000408
#define SGD_SM4_MAC	    0x00000410


#define SGD_SHA1	    0x00000002 
#define SGD_SHA256	    0x00000004
#define SGD_SM3		    0x00000001



#ifdef __cplusplus
extern "C" {
#endif



DLL u32 SDF_OpenDevice(HANDLE* phDeviceHandle);

DLL u32 SDF_CloseDevice(HANDLE hDeviceHandle);

DLL u32 SDF_OpenSession(HANDLE hDeviceHandle, HANDLE* phSessionHandle);

DLL u32 SDF_CloseSession(HANDLE hSessionHandle);

DLL u32 SDF_GetDeviceInfo(HANDLE hSessionHandle, DEVICEINFO *pstDeviceInfo);

DLL u32 SDF_GenerateRandom(HANDLE hSessionHandle, u32 uiLength, u8* pucRandom);

DLL u32 SDF_GetPrivateKeyAccessRight(HANDLE hSessionHandle, u32 uiKeyIndex, u8* pucPassword, u32 uiPwdLength);

DLL u32 SDF_ReleasePrivateKeyAccessRight(HANDLE hSessionHandle, u32 uiKeyIndex);





u32 SDF_ExportSignPublicKey_RSA(HANDLE hSessionHandle, u32 uiKeyIndex, RSArefPublicKey *pucPublicKey);
u32 SDF_ExportEncPublicKey_RSA(HANDLE hSessionHandle, u32 uiKeyIndex, RSArefPublicKey *pucPublicKey);
u32 SDF_GenerateKeyPair_RSA(HANDLE hSessionHandle,
	u32 uiKeyBits, RSArefPublicKey *pucPublicKey, RSArefPrivateKey *pucPrivateKey);

u32 SDF_GenerateKeyWithIPK_RSA(HANDLE hSessionHandle,
	u32 uiIPKIndex,
	u32 uiKeyBits,
	u8* pucKey,
	u32* puiKeyLength,
	HANDLE* phKeyHandle);

u32 SDF_GenerateKeyWithEPK_RSA(HANDLE hSessionHandle,
	u32 uiKeyBits,
	RSArefPublicKey *pucPublicKey,
	u8* pucKey,
	u32* puiKeyLength,
	HANDLE* phKeyHandle);

u32 SDF_ImportKeyWithISK_RSA(HANDLE hSessionHandle,
	u32 uiISKIndex,
	u8* pucKey,
	u32 uiKeyLength,
	HANDLE* phKeyHandle);

u32 SDF_ExchangeDigitEnvelopeBaseOnRSA(HANDLE hSessionHandle,
	u32 uiKeyIndex,
	RSArefPublicKey *pucPublicKey,
	u8* pucDEInput,
	u32 uiDELength,
	u8* pucDEOutput,
	u32 *puiDELength);


DLL u32 SDF_ExportSignPublicKey_ECC(HANDLE hSessionHandle,
	u32 uiKeyIndex,
	ECCrefPublicKey *pucPublicKey);

DLL u32 SDF_ExportEncPublicKey_ECC(HANDLE hSessionHandle,
	u32 uiKeyId,
	ECCrefPublicKey *pucPublicKey);

DLL u32 SDF_GenerateKeyPair_ECC(HANDLE hSessionHandle,
	u32 uiAlgID, u32 uiKeyBits,
	ECCrefPublicKey *pucPublicKey,
	ECCrefPrivateKey *pucPrivateKey);

DLL u32 SDF_GenerateKeyWithIPK_ECC(HANDLE hSessionHandle,
	u32 uiIPKIndex, u32 uiKeyBits,
	ECCCipher *pucKey, HANDLE* phKeyHandle);

DLL u32 SDF_GenerateKeyWithEPK_ECC(HANDLE hSessionHandle,
	u32 uiKeyBits, u32 uiAlgID,
	ECCrefPublicKey *pucPublicKey, ECCCipher *pucKey, HANDLE* phKeyHandle);

DLL u32 SDF_ImportKeyWithISK_ECC(HANDLE hSessionHandle,
	u32 uiISKIndex,
	ECCCipher *pucKey,
	HANDLE* phKeyHandle);

DLL u32 SDF_GenerateAgreementDataWithECC(HANDLE hSessionHandle, u32 uiISKIndex,
	u32 uiKeyBits, u8* pucSponsorID,
	u32 uiSponsorIDLength,
	ECCrefPublicKey *pucSponsorPublicKey,
	ECCrefPublicKey *pucSponsorTmpPublicKey,
	HANDLE* phAgreementHandle);


DLL u32 SDF_GenerateKeyWithECC(HANDLE hSessionHandle, u8* pucResponseID,
	u32 uiResponseIDLength,
	ECCrefPublicKey *pucResponsePublicKey,
	ECCrefPublicKey *pucResponseTmpPublicKey,
	HANDLE phAgreementHandle,
	HANDLE* phKeyHandle);


DLL u32 SDF_GenerateAgreementDataAndKeyWithECC(HANDLE hSessionHandle,
	u32 uiISKIndex,
	u32 uiKeyBits,
	u8* pucResponseID,
	u32 uiResponseIDLength,
	u8* pucSponsorID,
	u32 uiSponsorIDLength,
	ECCrefPublicKey *pucSponsorPublicKey,
	ECCrefPublicKey *pucSponsorTmpPublicKey,
	ECCrefPublicKey *pucResponsePublicKey,
	ECCrefPublicKey *pucResponseTmpPublicKey,
	HANDLE* phKeyHandle);


DLL u32 SDF_ExchangeDigitEnvelopeBaseOnECC(HANDLE hSessionHandle,
	u32 uiKeyIndex,
	u32 uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	ECCCipher *pucEncDataIn,
	ECCCipher *pucEncDataOut);

DLL u32 SDF_GenerateKeyWithKEK(HANDLE hSessionHandle,
	u32 uiKeyBits,
	u32 uiAlgID,
	u32 uiKEKIndex,
	u8* pucKey,
	u32* puiKeyLength,
	HANDLE* phKeyHandle);

DLL u32 SDF_ImportKeyWithKEK(HANDLE hSessionHandle,
	u32 uiAlgID,
	u32 uiKEKIndex,
	u8* pucKey,
	u32 uiKeyLength,
	HANDLE* phKeyHandle);

DLL u32 SDF_DestroyKey(HANDLE hSessionHandle,
	HANDLE hKeyHandle);

DLL u32 SDF_ExternalPublicKeyOperation_RSA(HANDLE hSessionHandle,
	RSArefPublicKey *pucPublicKey,
	u8* pucDataInput,
	u32 uiInputLength,
	u8* pucDataOutput,
	u32 *puiOutputLength);

DLL u32 SDF_InternalPublicKeyOperation_RSA(HANDLE hSessionHandle,
	u32 uiKeyIndex,
	u8* pucDataInput,
	u32 uiInputLength,
	u8* pucDataOutput,
	u32 *puiOutputLength);

DLL u32 SDF_InternalPrivateKeyOperation_RSA(HANDLE hSessionHandle,
	u32 uiKeyIndex,
	u8* pucDataInput,
	u32 uiInputLength,
	u8* pucDataOutput,
	u32 *puiOutputLength);

DLL u32 SDF_InternalSign_ECC(HANDLE hSessionHandle,
	u32 uiISKIndex,
	u8* pucData,
	u32 uiDataLength,
	ECCSignature *pucSignature);

DLL u32 SDF_InternalVerify_ECC(HANDLE hSessionHandle,
	u32 uiISKIndex,
	u8* pucData,
	u32 uiDataLength,
	ECCSignature *pucSignature);

DLL u32 SDF_ExternalVerify_ECC(HANDLE hSessionHandle,
	u32 uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	u8* pucDataInput,
	u32 uiInputLength,
	ECCSignature *pucSignature);

DLL u32 SDF_ExternalEncrypt_ECC(HANDLE hSessionHandle,
	u32 uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	u8* pucData,
	u32 uiDataLength,
	ECCCipher *pucEncData);

DLL u32 SDF_Encrypt(HANDLE hSessionHandle,
	HANDLE hKeyHandle,
	u32 uiAlgID,
	u8* pucIV,
	u8* pucData,
	u32 uiDataLength,
	u8* pucEncData,
	u32 *puiEncDataLength);

DLL u32 SDF_Decrypt(HANDLE hSessionHandle,
	HANDLE hKeyHandle,
	u32 uiAlgID,
	u8* pucIV,
	u8* pucEncData,
	u32 uiEncDataLength,
	u8* pucData,
	u32 *puiDataLength);

DLL u32 SDF_CalculateMAC(HANDLE hSessionHandle,
	HANDLE hKeyHandle,
	u32 uiAlgID,
	u8* pucIV,
	u8* pucData,
	u32 uiDataLength,
	u8* pucMAC,
	u32 *puiMACLength);

DLL u32 SDF_HashInit(HANDLE hSessionHandle,
	u32 uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	u8* pucID,
	u32 uiIDLength);

DLL u32 SDF_HashUpdate(HANDLE hSessionHandle,
	u8* pucData,
	u32 uiDataLength);

DLL u32 SDF_HashFinal(HANDLE hSessionHandle,
	u8* pucHash,
	u32 *puiHashLength);

DLL u32 SDF_MacInit(HANDLE hSessionHandle, HANDLE hKeyHandle, u32 uiAlgID);
DLL u32 SDF_MacUpdate(HANDLE hSessionHandle, u8 *pucData, u32 uiDataLength);
DLL u32 SDF_MacFinal(HANDLE hSessionHandle, u8 *pucHash, u32 *puiHashLength);

DLL u32 SDF_CreateFile(HANDLE hSessionHandle,
	u8* pucFileName,
	u32 uiNameLen,
	u32 uiFileSize);

DLL u32 SDF_ReadFile(HANDLE hSessionHandle,
	u8* pucFileName,
	u32 uiNameLen,
	u32 uiOffset,
	u32 *puiFileLength,
	u8* pucBuffer);

DLL u32 SDF_WriteFile(HANDLE hSessionHandle,
	u8* pucFileName,
	u32 uiNameLen,
	u32 uiOffset,
	u32 uiFileLength,
	u8* pucBuffer);

DLL u32 SDF_DeleteFile(HANDLE hSessionHandle,
	u8* pucFileName,
	u32 uiNameLen);

#ifdef __cplusplus
    }
#endif


#define SDR_OK						0x0
#define SDR_BASE					0x01000000
#define SDR_UNKNOWERR				SDR_BASE+0x00000001
#define SDR_NOTSUPPORT				SDR_BASE+0x00000002
#define SDR_COMMFAIL				SDR_BASE+0x00000003	//与设备通信失败
#define SDR_HARDFAIL				SDR_BASE+0x00000004	//运算模块无响应
#define SDR_OPENDEVICE				SDR_BASE+0x00000005	//打开设备失败
#define SDR_OPOENSESSION			SDR_BASE+0x00000006	//创建会话失败
#define SDR_PARDENY					SDR_BASE+0x00000007	//无私钥使用权限
#define SDR_KEYNOTEXIST				SDR_BASE+0x00000008	//不存在的密钥调用
#define SDR_ALGNOTSUPPORT			SDR_BASE+0x00000009	//不支持的算法调用
#define SDR_ALGMODNOTSUPPORT		SDR_BASE+0x0000000A	//不支持的算法模式调用
#define SDR_PKOPERR					SDR_BASE+0x0000000B	//公钥运算失败
#define SDR_SKOPERR					SDR_BASE+0x0000000C	//私钥运算失败
#define SDR_SIGNERR					SDR_BASE+0x0000000D	//签名运算失败
#define SDR_VERIFYERR				SDR_BASE+0x0000000E	//验证签名失败
#define SDR_SYMOPERR				SDR_BASE+0x0000000F	//对称算法运算失败
#define SDR_STEPERR					SDR_BASE+0x00000010	//多步运算步骤错误
#define SDR_FILESIZEERR				SDR_BASE+0x00000011	//文件长度超出限制
#define SDR_FILENOTEXIST			SDR_BASE+0x00000012	//指定的文件不存在
#define SDR_FILEOFSERR				SDR_BASE+0x00000013	//文件起始位置错误
#define SDR_KEYTYPEERR				SDR_BASE+0x00000014	//密钥类型错误
#define SDR_KEYERR					SDR_BASE+0x00000015	//密钥错误
#define SDR_ENCDATAERR				SDR_BASE+0x00000016	//ECC加密数据错误
#define SDR_RANDERR					SDR_BASE+0x00000017	//随机数产生失败
#define SDR_PRKRERR					SDR_BASE+0x00000018	//私钥使用权限获取失败
#define SDR_MACERR					SDR_BASE+0x00000019	//MAC运算失败
#define SDR_FILEEXISTS				SDR_BASE+0x0000001A	//指定文件已存在
#define SDR_FILEWERR				SDR_BASE+0x0000001B	//文件写入失败
#define SDR_NOBUFFER				SDR_BASE+0x0000001C	//存储空间不足
#define SDR_INARGERR				SDR_BASE+0x0000001D	//输入参数错误
#define SDR_OUTARGERR				SDR_BASE+0x0000001E	//输出参数错误

#define GET_FULL_ERR_CODE(code)		((code == SDR_OK) ? code : (code + SDR_BASE))


#define SDR_ALLOC_MEM_ERR		    -1
#define SDR_CARD_RECV_ERR		    -2 
#define SDR_CARD_SENDPACKLEN_RANGE	-3 


#endif



/***************************************
与原来相比，不支持的接口：

   SDF_ExternalSign_ECC




******************************************/