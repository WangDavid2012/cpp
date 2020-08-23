#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "../sdf/SDF.h"

u32 sm2_z(u8*userid, u32 userid_len, ECCrefPublicKey * pub, u8*z);

u32 sm3_padding(sis_hash_ctx_t *sm3_ctx);

u32 sm2_kdf(sis_session *session, u8* in, u32 in_len, u8* out, u32 * out_len);

u32 sm2_compute_cipher(sis_session *session, u8* m, u32 mLen, u8* fpgaData, u32 dataLen, ECCCipher* cipher);

u32 sm2_compute_plain(sis_session *session, ECCCipher* cipher, u8*fpgaData, u32 dataLen, u8*plain, u32 *plainLen);
#endif // UTIL_H_INCLUDED
