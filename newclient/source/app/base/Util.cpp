#include "../sdf/SDF.h"
#include "../base/Context.h"
#include "../base/SDFLog.h"
#include "../base/Util.h"
#include "../api/C_API.h"

/* Za = H( ENTL || ID || a || b || xG || yG || xa || ya ) */
u32 sm2_z(u8* userid, u32 userid_len, ECCrefPublicKey* pub, u8*z)
{
	u8 a[] = "\xFF\xFF\xFF\xFE\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00\x00\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFC";
	u8 b[] = "\x28\xE9\xFA\x9E\x9D\x9F\x5E\x34\x4D\x5A\x9E\x4B\xCF\x65\x09\xA7\xF3\x97\x89\xF5\x15\xAB\x8F\x92\xDD\xBC\xBD\x41\x4D\x94\x0E\x93";
	u8 xG[] = "\x32\xC4\xAE\x2C\x1F\x19\x81\x19\x5F\x99\x04\x46\x6A\x39\xC9\x94\x8F\xE3\x0B\xBF\xF2\x66\x0B\xE1\x71\x5A\x45\x89\x33\x4C\x74\xC7";
	u8 yG[] = "\xBC\x37\x36\xA2\xF4\xF6\x77\x9C\x59\xBD\xCE\xE3\x6B\x69\x21\x53\xD0\xA9\x87\x7C\xC6\x2A\x47\x40\x02\xDF\x32\xE5\x21\x39\xF0\xA0";
	//u8 abxGyG[] = "\xFF\xFF\xFF\xFE\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00\x00\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFC\x28\xE9\xFA\x9E\x9D\x9F\x5E\x34\x4D\x5A\x9E\x4B\xCF\x65\x09\xA7\xF3\x97\x89\xF5\x15\xAB\x8F\x92\xDD\xBC\xBD\x41\x4D\x94\x0E\x93\x32\xC4\xAE\x2C\x1F\x19\x81\x19\x5F\x99\x04\x46\x6A\x39\xC9\x94\x8F\xE3\x0B\xBF\xF2\x66\x0B\xE1\x71\x5A\x45\x89\x33\x4C\x74\xC7\xBC\x37\x36\xA2\xF4\xF6\x77\x9C\x59\xBD\xCE\xE3\x6B\x69\x21\x53\xD0\xA9\x87\x7C\xC6\x2A\x47\x40\x02\xDF\x32\xE5\x21\x39\xF0\xA0";
	/* u8 a[] = "\x78\x79\x68\xB4\xFA\x32\xC3\xFD\x24\x17\x84\x2E\x73\xBB\xFE\xFF\x2F\x3C\x84\x8B\x68\x31\xD7\xE0\xEC\x65\x22\x8B\x39\x37\xE4\x98";
	 u8 b[] = "\x63\xE4\xC6\xD3\xB2\x3B\x0C\x84\x9C\xF8\x42\x41\x48\x4B\xFE\x48\xF6\x1D\x59\xA5\xB1\x6B\xA0\x6E\x6E\x12\xD1\xDA\x27\xC5\x24\x9A";
	 u8 xG[] = "\x42\x1D\xEB\xD6\x1B\x62\xEA\xB6\x74\x64\x34\xEB\xC3\xCC\x31\x5E\x32\x22\x0B\x3B\xAD\xD5\x0B\xDC\x4C\x4E\x6C\x14\x7F\xED\xD4\x3D";
	 u8 yG[] = "\x06\x80\x51\x2B\xCB\xB4\x2C\x07\xD4\x73\x49\xD2\x15\x3B\x70\xC4\xE5\xD7\xFD\xFC\xBF\xA3\x6E\xA1\xA8\x58\x41\xB9\xE4\x6E\x09\xA2";
	 */
	u32 offset = 0;
	u8  idbits[2];

	idbits[0] = (u8)(((userid_len * 8) >> 8) % 256);
	idbits[1] = (u8)((userid_len * 8) % 256);

	memcpy(z, idbits, 2);
	offset += 2;
	memcpy(z + offset, userid, userid_len);
	offset += userid_len;
	//data = a || b || xG || yG || xa || ya */
	memcpy(z + offset, a, 32);
	offset += 32;
	memcpy(z + offset, b, 32);
	offset += 32;
	memcpy(z + offset, xG, 32);
	offset += 32;
	memcpy(z + offset, yG, 32);
	offset += 32;
	memcpy(z + offset, pub->x + 32, 32);
	offset += 32;
	memcpy(z + offset, pub->y + 32, 32);
	offset += 32;

	return offset;
}


/*对hash填充数据进行补齐*/
u32 sm3_padding(sis_hash_ctx_t *sm3_ctx)
{
	//待补齐数据的长度
	u32 dlen = sm3_ctx->padding_size;
	u32* count_pos = NULL;

	count_pos = (u32*)(sm3_ctx->padding_buffer + SM3_CHUNK_SIZE - 8);

	sm3_ctx->padding_buffer[dlen] = 0x80;

	if (dlen + 9 <= SM3_CHUNK_SIZE)
	{
		memset(sm3_ctx->padding_buffer + dlen + 1, 0, SM3_CHUNK_SIZE - dlen - 9);
		sm3_ctx->padded_size = SM3_CHUNK_SIZE;
	}
	else
	{
		memset(sm3_ctx->padding_buffer + dlen + 1, 0, SM3_CHUNK_SIZE - dlen - 1);
		memset(sm3_ctx->padding_buffer + SM3_CHUNK_SIZE, 0, SM3_CHUNK_SIZE - 8);
		count_pos = (u32*)(sm3_ctx->padding_buffer + SM3_CHUNK_SIZE + SM3_CHUNK_SIZE - 8);
		sm3_ctx->padded_size = 2 * SM3_CHUNK_SIZE;
	}

	//填充长度
	count_pos[0] = cpu_to_be32((sm3_ctx->chunk_count) >> 23);
	count_pos[1] = cpu_to_be32((sm3_ctx->chunk_count << 9) + (dlen << 3));

	return 0;
}

u32 sm2_kdf(sis_session *session, u8* in, u32 in_len, u8* out, u32 * out_len)
{
	u32	counter = 1;
	u32 counter_be;
	u8 dgst[32];
	u32 dgstlen = 0;
	u8*pout = out;
	u32 rlen = *out_len;
	u32 len;
	u32 hashhandle;

	memset(&(session->hash_context),0,sizeof(sis_hash_ctx_t));
	while (rlen > 0)
	{
		counter_be = cpu_to_be32(counter);
		counter++;

 		C_HashInit_SM3(session, NULL, 0, NULL, 0);
 		C_Hash_SM3(session, in, in_len);
 		C_Hash_SM3(session, (u8*)&counter_be, sizeof(counter_be));
 		C_HashFinal_SM3(session, dgst, &dgstlen);

		len = (dgstlen <= rlen) ? dgstlen : rlen;
		memcpy(pout, dgst, len);
		rlen -= len;
		pout += len;
	}

	return 0;
}

u32 sm2_compute_cipher(sis_session *session, u8* m, u32 mLen, u8* fpgaData, u32 dataLen, ECCCipher* cipher)
{
	u8 t[MAX_ECC_CIPHERLEN], c2[MAX_ECC_CIPHERLEN], c3[32], *ptr = NULL;
	u32 tLen, i, hashhandle, c3Len = 0;

	ptr = m;
	tLen = mLen;
	//1. 计算t=KDF（x2||y2，klen）
	sm2_kdf(session, fpgaData + 64, 64, t, &tLen);

	//2. 计算C2 = m^t
	for (i = 0; i < mLen; i++)
	{
		c2[i] = *ptr ^ t[i];
		ptr++;
	}

	//3. 计算C3=Hash(x2 || M || y2)

   memset(&(session->hash_context),0,sizeof(sis_hash_ctx_t));

   C_HashInit_SM3(session,NULL, 0, NULL, 0);
   C_Hash_SM3(session, fpgaData + 64, 32);
   C_Hash_SM3(session, m, mLen);
   C_Hash_SM3(session, fpgaData + 96, 32);
   C_HashFinal_SM3(session, c3, &c3Len);
	//4. 计算 C=C1||C3||C2, fpgaData结构 x1||y1||x2||y2 总共128B
	memcpy(cipher->x + 32, fpgaData, 32);
	memcpy(cipher->y + 32, fpgaData + 32, 32);
	memcpy(cipher->M, c3, c3Len);
	cipher->L = mLen;
	memcpy(cipher->C, c2, mLen);

	return 0;
}

u32 sm2_compute_plain(sis_session *session, ECCCipher* cipher, u8*fpgaData, u32 dataLen, u8*plain, u32 *plainLen)
{
	u8 t[MAX_ECC_CIPHERLEN], m[MAX_ECC_CIPHERLEN], c2[MAX_ECC_CIPHERLEN], u[32], c3[32];
	u32 i, uLen = 0;

	memcpy(c3, cipher->M, 32);
	memcpy(c2, cipher->C, cipher->L);
	//t=KDF(x2 || y2, klen)
	sm2_kdf(session, fpgaData, dataLen, t, &(cipher->L));

	//m' = c2 ^ t
	for (i = 0; i < cipher->L; i++)
	{
		m[i] = c2[i] ^ t[i];
	}

	//u=Hash(x2||m'||y2)
	 C_HashInit_SM3(session, NULL, 0, NULL, 0);
	 C_Hash_SM3(session, fpgaData, 32);
	 C_Hash_SM3(session, m, cipher->L);
	 C_Hash_SM3(session, fpgaData + 32, 32);
	 C_HashFinal_SM3(session, u, &uLen);

	//u == c3
	if (memcmp(u, c3, uLen) == 0)
	{
		memcpy(plain, m, cipher->L);
		*plainLen = cipher->L;
	}
	else
	{
		return -1;
	}

	return 0;
}


