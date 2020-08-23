#ifndef SDF_EX_H_INCLUDED
#define SDF_EX_H_INCLUDED


#include "SDF.h"


#ifdef __cplusplus
extern "C" {
#endif



DLL u32 SDF_ImportPublicKey_ECC(HANDLE hSessionHandle, ECCrefPublicKey pucPublicKey, HANDLE* phKeyHandle);

DLL u32 SDF_ImportKey(HANDLE hSessionHandle, u8* pucKey, u32 uiKeyLength, HANDLE* phKeyHandle);

DLL u32 SDF_GenerateKeyHandle(HANDLE hSessionHandle, HANDLE* phKeyHandle);

DLL u32 SDF_GenerateKeyHandle_ECC(HANDLE hSessionHandle, HANDLE* phPkHandle, HANDLE* phSkHandle);

DLL u32 SDF_ExportKeyWithKey(HANDLE hSessionHandle, HANDLE hKeyHandle, HANDLE hWorkKeyHandle, u8 *pucEncKey, u32 *puiKeyLength);

DLL u32 SDF_ExportKeyWithKey_ECC(HANDLE hSessionHandle, HANDLE hKeyHandle, HANDLE hWorkKeyHandle, ECCCipher *pEccCipher);




//u32 SDF_HMacInit(HANDLE hSessionHandle, HANDLE hKeyHandle, u32 uiAlgID);
//u32 SDF_HMacUpdate(HANDLE hSessionHandle, u8 *pucData, u32 uiDataLength);
//u32 SDF_HMacFinal(HANDLE hSessionHandle, u8 *pucMac, u32 *puiMacLength);

//u32 SDF_CMacInit(HANDLE hSessionHandle, HANDLE hKeyHandle, u8 *pucIV, u32 uiAlgID);
//u32 SDF_CMacUpdate(HANDLE hSessionHandle, u8 *pucData, u32 uiDataLength);
//u32 SDF_CMacFinal(HANDLE hSessionHandle, u8 *pucMac, u32 *puiMacLength);


u32 SDF_EncryptInit(HANDLE hSessionHandle, HANDLE hKeyHandle, u8 *pucIV, u32 uiAlgID);
u32 SDF_EncryptUpdate(HANDLE hSessionHandle, u8 *pucData, u32 uiDataLength, u8 *pucEncData, u32 *puiEncDataLength);
u32 SDF_EncryptFinal(HANDLE hSessionHandle, u8 *pucData, u32 uiDataLength, u8 *pucEncData, u32 *puiEncDataLength);

u32 SDF_DecryptInit(HANDLE hSessionHandle, HANDLE hKeyHandle, u8 *pucIV, u32 uiAlgID);
u32 SDF_DecryptUpdate(HANDLE hSessionHandle, u8 *pucEncData, u32 uiEncDataLength, u8 *pucData, u32 *puiDataLength);
u32 SDF_DecryptFinal(HANDLE hSessionHandle, u8 *pucEncData, u32 uiEncDataLength, u8 *pucData, u32 *puiDataLength);



DLL u32 SDF_ImportAtomKey(HANDLE hSessionHandle,
	u8 *SourceID,
	u8 *DestID,
	u32 ParaDataLen,
	u8 *ParaData,
	u32 SessionKeyLen,//密钥生成会话密钥长度
	u32 SessionAlg,//密钥生成会话密钥加密算法标识
	u32 SignAlg,//签名算法标识
	u32 uiKEKIndex,//密管密码机内部存储密钥加密密钥的索引值
	ECCSignature *DataSign,//用密钥加密密钥加密输出的原子密钥
	u32 *AtomKeyLen,//原子密钥的长度
	u8  *AtomKey,//密钥生成会话密钥加密的原子密钥
	ECCCipher *CipheredSKey,
	ECCSignature *AtomKeySign,
	u8 *pucKeyOut);


DLL u32 SDF_ExchangeDigitEnvelopeBaseOnKEK(HANDLE hSessionHandle,
	HANDLE hKeyHandle,//外部指定的密钥句柄
	u32 uiAlgID,//算法标识，指定对称加密算法
	u32 uiKEKIndex,//密码设备内部存储密钥加密密钥的索引值
	u32 puiKeyLength,//输入的会话密钥密文长度
	u8 *pucKeyIn,//缓冲区指针，用于存放输入的会话密钥密文
	u8 *pucKeyOut);//缓冲区指针，用于存放输出的会话密钥密文

DLL u32 SDF_GenerateRandomWithSDM(HANDLE hSessionHandle,//与设备建立的会话句柄
	u32 uiAlgID,//算法标识，指定使用的ECC算法
	u32 uiRandomBits,//需要产生的随机数长度
	u32 uiISKIndex,//密码设备内部存储私钥的索引值，该私钥用于管理代理对随机数签名
	ECCrefPublicKey *pucPublicKey,//外部输入的管理中心ECC公钥结构
	ECCSignature *AgentSign,//管理代理对随机数的ECC签名
	ECCCipher *CipheredRandom,//管理代理产生并用管理中心ECC公钥加密输出的随机数密文
	HANDLE *phAgreementHandle);//返回的协商句柄，用于计算安全通道会话密钥


DLL u32 SDF_GenerateRandomAndKeyWithSDM(HANDLE hSessionHandle,  //与设备建立的会话句柄
	u32 uiAlgID,            //算法标识，指定使用的ECC算法
	u32 uiRandomBits,//需要产生的随机数长度
	u32 uiISKIndexSign,//密码设备内部存储签名私钥的索引值，该私钥用于管理中心对随机数签名
	u32 uiISKIndexEnc,//密码设备内部存储加密私钥的索引值，该私钥用于解密用管理中心ECC公钥加密的随机数
	ECCrefPublicKey *pucPublicKeySign,//外部输入的管理代理ECC签名公钥结构，用于验证管理代理对随机数的ECC签名
	ECCrefPublicKey *pucPublicKeyEnc,//外部输入的管理代理ECC加密公钥结构，用于加密管理中心产生的随机数
	ECCSignature *AgentSign,//管理代理对随机数的ECC签名
	ECCCipher *CipheredRandomAgent,//管理中心ECC公钥加密的随机数密文
	ECCSignature *SDMSign,//管理中心对随机数的ECC签名
	ECCCipher *CipheredRandomSDM,//管理中心产生并用管理代理ECC公钥加密输出的随机数密文
	HANDLE *phKeyHandle);//返回的会话密钥句柄


DLL u32 SDF_GenerateKeyWithSDM(HANDLE hSessionHandle,//与设备建立的会话句柄
	u32 uiAlgID,//算法标识，指定使用的ECC算法
	u32 uiISKIndexEnc,//密码设备内部存储加密私钥的索引值，该私钥用于解密用管理代理ECC公钥加密的随机数
	ECCrefPublicKey  *pucPublicKey,//外部输入的管理中心ECC公钥结构, 用于验证管理中心对随机数的ECC签名
	ECCSignature *SDMSign,//管理中心对随机数的ECC签名
	ECCCipher *CipheredRandomSDM,
	HANDLE hAgreementHandle,//协商句柄，用于计算会话密钥
	HANDLE *phKeyHandle);//返回的会话密钥句柄


#ifdef __cplusplus
    }
#endif


#endif // SDF_EX_H_INCLUDED
