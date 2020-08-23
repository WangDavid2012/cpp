#ifndef C_API_EX_H_INCLUDED
#define C_API_EX_H_INCLUDED

#include "../sdf/SDF.h"


u32 C_ImportPublicKey_ECC(sis_session* session, ECCrefPublicKey pucPublicKey, HANDLE* phKeyHandle);
u32 C_ImportKey(sis_session* session, u8* pucKey, u32 uiKeyLength, HANDLE* phKeyHandle);
u32 C_GenerateKeyHandle(sis_session* session, HANDLE* phKeyHandle);
u32 C_GenerateKeyHandle_ECC(sis_session* session, HANDLE* phPkHandle, HANDLE* phSkHandle);
u32 C_ExportKeyWithKey(sis_session* session, sis_work_key *key, sis_work_key *workkey, u8* pucEncKey, u32* puiKeyLength);
u32 C_ExportKeyWithKey_ECC(sis_session* session, sis_work_key *key, sis_work_key *workkey, ECCCipher *pEccCipher);

#endif 
