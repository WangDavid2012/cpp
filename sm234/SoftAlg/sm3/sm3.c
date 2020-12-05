#include "sm3.h"
#include <string.h>
#include <stdint.h>

#define u32m3_2_u8m3(dwValue, pbBuffer) { (pbBuffer)[3] = (u8m3)(dwValue), \
											(pbBuffer)[2] = (u8m3)((dwValue)>>8); \
											(pbBuffer)[1] = (u8m3)((dwValue)>>16); \
											(pbBuffer)[0] = (u8m3)((dwValue)>>24); }

#define T0 (0x79cc4519)
#define T1 (0x7a879d8a)
#define FF0(X, Y, Z) ( (X) ^ (Y) ^ (Z) )
#define FF1(X, Y, Z) ( ((X)&(Y)) | ((X)&(Z)) | ((Y)&(Z)) )
#define GG0(X, Y, Z) ( (X) ^ (Y) ^ (Z) )
#define GG1(X, Y, Z) ( ((X)&(Y)) | ((~(X))&(Z)) )
#define ROL(X, cnt)  ( ( (X)<<((cnt)&31) ) | ( (X)>>(32-((cnt)&31)) ) )
#define P0(X)		 ( (X) ^ ROL(X,  9) ^ ROL(X, 17))
#define P1(X)		 ( (X) ^ ROL(X, 15) ^ ROL(X, 23))

static int ProcessOneGroup(u8m3 *pbData, SM3_CTX* pSm3Ctx);

int SM3_HASH_INIT(SM3_CTX* pSm3Ctx)
{
    pSm3Ctx->m_dwLastLen = 0x00;
    pSm3Ctx->m_dwGroupNum = 0x00;
    pSm3Ctx->m_AA = 0x7380166f;
    pSm3Ctx->m_BB = 0x4914b2b9;
    pSm3Ctx->m_CC = 0x172442d7;
    pSm3Ctx->m_DD = 0xda8a0600;
    pSm3Ctx->m_EE = 0xa96f30bc;
    pSm3Ctx->m_FF = 0x163138aa;
    pSm3Ctx->m_GG = 0xe38dee4d;
    pSm3Ctx->m_HH = 0xb0fb0e4e;

    return 1;
}

int SM3_HASH_UPDATE(SM3_CTX*	pSm3Ctx,
                    u8m3*			pbData,
                    u32m3			dwDataLen)
{
    if ( (dwDataLen + pSm3Ctx->m_dwLastLen) < 0x40 ) {
        memcpy(pSm3Ctx->m_pbLastGroup + pSm3Ctx->m_dwLastLen, pbData, dwDataLen);
        pSm3Ctx->m_dwLastLen += dwDataLen;
    } else {
        u32m3 dwCopyLen;
        dwCopyLen = 0x40 - pSm3Ctx->m_dwLastLen;
        memcpy(pSm3Ctx->m_pbLastGroup + pSm3Ctx->m_dwLastLen, pbData, dwCopyLen);
        pbData += dwCopyLen;
        dwDataLen -= dwCopyLen;
        ProcessOneGroup(pSm3Ctx->m_pbLastGroup, pSm3Ctx);
        pSm3Ctx->m_dwGroupNum++;

        while ( dwDataLen >= 0x40 ) {
            ProcessOneGroup(pbData, pSm3Ctx);
            dwDataLen -= 0x40;
            pbData += 0x40;
            pSm3Ctx->m_dwGroupNum++;
        }
        memcpy(pSm3Ctx->m_pbLastGroup, pbData, dwDataLen);
        pSm3Ctx->m_dwLastLen = dwDataLen;
    }
    return 1;
}

/**
* 获取当前SM3运算的中间状态，得到向量IV和剩余未处理数据。
* 调用者需要保证变量iv的内存大小不小于32字节，lastData的内存大小不小于63个字节。
*@param [in] pSm3Ctx 上下文句柄
*@param [out] iv IV的当前值，固定为32个字节
*@param [out] lastData 剩余的未参与运算的数据，长度最长为63个字节
*@param [out] lastDataLen 剩余的未参与运算的数据长度，值最大为63
*/
int SM3_HASH_GETSTATE(SM3_CTX*	pSm3Ctx, u8m3* iv, u8m3* lastData, int* lastDataLen, int64_t *bitsHashProcessed)
{
    u8m3 *pbHashValue = 0;
    *lastDataLen = pSm3Ctx->m_dwLastLen;
    memcpy(lastData, pSm3Ctx->m_pbLastGroup, pSm3Ctx->m_dwLastLen);

    pbHashValue = iv;
    u32m3_2_u8m3(pSm3Ctx->m_AA, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_BB, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_CC, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_DD, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_EE, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_FF, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_GG, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_HH, pbHashValue);

    *bitsHashProcessed = pSm3Ctx->m_dwGroupNum * 64 * 8;
    return 1;
}

int SM3_HASH_FINAL(u8m3*		pbHashValue,
                   SM3_CTX*	pSm3Ctx)
{
    u8m3	pbLastGroup[0x40*2];
    u32m3	dwLastLen;
    u32m3	dwDataLen;
    u32m3	dwOffset;

    dwLastLen = pSm3Ctx->m_dwLastLen;
    if (dwLastLen>=56) {
        dwOffset = 0x40;
    } else {
        dwOffset = 0x00;
    }
    memset(pbLastGroup, 0x00, sizeof(pbLastGroup));
    memcpy(pbLastGroup, pSm3Ctx->m_pbLastGroup, dwLastLen);
    pbLastGroup[dwLastLen] = 0x80;
    dwDataLen = pSm3Ctx->m_dwGroupNum * 0x40 + dwLastLen;
    dwDataLen <<= 3;
    pbLastGroup[dwOffset+63] = (u8m3)(dwDataLen);
    pbLastGroup[dwOffset+62] = (u8m3)(dwDataLen>>8);
    pbLastGroup[dwOffset+61] = (u8m3)(dwDataLen>>16);
    pbLastGroup[dwOffset+60] = (u8m3)(dwDataLen>>24);

    ProcessOneGroup(pbLastGroup, pSm3Ctx);

    if ( 0x40 == dwOffset ) {
        ProcessOneGroup(pbLastGroup+0x40, pSm3Ctx);
    }
    // 杈撳嚭
    u32m3_2_u8m3(pSm3Ctx->m_AA, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_BB, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_CC, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_DD, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_EE, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_FF, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_GG, pbHashValue);
    pbHashValue += 4;
    u32m3_2_u8m3(pSm3Ctx->m_HH, pbHashValue);

    return 1;
}


static int ProcessOneGroup(u8m3 *pbData, SM3_CTX* pSm3Ctx)
{
    u32m3 W[68], W_[64];
    u32m3 A, B, C, D, E, F, G, H;
    u32m3 SS1, SS2, TT1, TT2;
    int j;

    // 娑堟伅鎵╁睍
    for (j=0; j<16; j++) {
        W[j] = (pbData[j*4]<<24) | (pbData[j*4+1]<<16) | (pbData[j*4+2]<<8) | pbData[j*4+3];
    }
    for ( ; j<68; j++) {
        W[j] = P1(W[j-16]^W[j-9]^ROL(W[j-3], 15)) ^ ROL(W[j-13], 7) ^ W[j-6];
    }
    for (j=0; j<64; j++) {
        W_[j] = W[j] ^ W[j+4];
    }

    // 鍘嬬缉鍑芥暟
    A = pSm3Ctx->m_AA;
    B = pSm3Ctx->m_BB;
    C = pSm3Ctx->m_CC;
    D = pSm3Ctx->m_DD;
    E = pSm3Ctx->m_EE;
    F = pSm3Ctx->m_FF;
    G = pSm3Ctx->m_GG;
    H = pSm3Ctx->m_HH;
    for (j=0; j<16; j++) {
        SS1 = ROL(ROL(A, 12) + E + ROL(T0, j), 7);
        SS2 = SS1 ^ ROL(A, 12);
        TT1 = FF0(A, B, C) + D + SS2 + W_[j];
        TT2 = GG0(E, F, G) + H + SS1 + W[j];
        D = C;
        C = ROL(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = ROL(F, 19);
        F = E;
        E = P0(TT2);
    }
    for ( ; j<64; j++) {
        SS1 = ROL(ROL(A, 12) + E + ROL(T1, j), 7);
        SS2 = SS1 ^ ROL(A, 12);
        TT1 = FF1(A, B, C) + D + SS2 + W_[j];
        TT2 = GG1(E, F, G) + H + SS1 + W[j];
        D = C;
        C = ROL(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = ROL(F, 19);
        F = E;
        E = P0(TT2);
    }
    pSm3Ctx->m_AA ^= A;
    pSm3Ctx->m_BB ^= B;
    pSm3Ctx->m_CC ^= C;
    pSm3Ctx->m_DD ^= D;
    pSm3Ctx->m_EE ^= E;
    pSm3Ctx->m_FF ^= F;
    pSm3Ctx->m_GG ^= G;
    pSm3Ctx->m_HH ^= H;

    return 1;
}


