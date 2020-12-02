#include "gmjtest.h"
#include "debug.h"
#include "interface.h"


extern u32 nettest(unsigned char *indata, unsigned int lenth, unsigned char *outdata);



static void charTopucKey(const unsigned char *data, ECCrefPublicKey *puc)
{
    puc->bits = 256;
    memcpy(&(puc->x[32]), data, 32);
    memcpy(&(puc->y[32]), data + 32, 32);
}

static void charTopriKey(const unsigned char *data, ECCrefPrivateKey *pri)
{
    pri->bits = 256;
    memcpy(&(pri->D[32]), data, 32);
}



/******************************** 国密局接口测试 **********************************/
int gmjInterfaceTestAll()
{
    int ret = 0;
    return ret;
}

int gmjInterfaceDevManageTest()
{
    int ret = 0;
    return ret;
}

/******************************** 国密算法正确性测试 **********************************/





/********************************  国密算法速度测试  **********************************/






/**********************************************************
 * \brief 测试函数,暂时不使用
 *
 * \param[in]  phDeviceHandle 句柄
 * \param[in]  encdec 0加密，!0 解密
 * \param[in]  uiAlgID 算法类型
 * \param[in]  count 循环次数
 * \param[out]
 * \return
 *
 * \author wangzhanbei
 * \history
 * \time 2020/07/23

 输入参数长度是1024
 choice 选择 0 加密，1 解密 2 MAC
 ************************************************************/
int gmjSDF_SYM_Speed(HANDLE phDeviceHandle, unsigned int choice, unsigned int uiAlgID, unsigned int count)
{
    HANDLE phSessionHandle = nullptr;
    HANDLE phKeyHandle0 = nullptr;
    HANDLE phKeyHandle1 = nullptr;
    HANDLE phKeyHandle2 = nullptr;

    unsigned char indata[4096] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                 };
    unsigned int inlenth = 0, outlenth = 0;
    unsigned char outdata[4096] = { 0 };
    unsigned char iv[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 };
    unsigned char symkey[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 };
    unsigned int ret = 0;

    ret = SDF_OpenSession(phDeviceHandle, &phSessionHandle);
    ret = SDF_ImportKey(phSessionHandle, symkey, 16, &phKeyHandle0);

    if( choice == 0) {
        for (int i = 0; i < count; i++) {
            ret = SDF_Encrypt(phSessionHandle, phKeyHandle0, uiAlgID, iv, indata, TESTLENTH, outdata, &outlenth);
        }
    } else if(choice == 1) {
        for (int i = 0; i < count; i++) {
            ret = SDF_Decrypt(phSessionHandle, phKeyHandle0, uiAlgID, iv, indata, TESTLENTH, outdata, &outlenth);
        }
    } else if (choice == 2) {
        for (int j = 0; j < count; j++) {
            ret = SDF_CalculateMAC(phSessionHandle, phKeyHandle0, uiAlgID, iv, indata, TESTLENTH, outdata, &outlenth);
        }

    } else {
        return 0xFFFFFFFF;
    }
    ret = SDF_DestroyKey(phSessionHandle, phKeyHandle0);
    ret = SDF_CloseSession(phSessionHandle);
    return ret;
}




/**********************************************************
 * \brief 测试hash函数速度,暂时没有使用
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author wangzhanbei
 * \history
 * \time 2020/08/11
 ************************************************************/
int gmjSDF_Hash_Speed(HANDLE phDeviceHandle, unsigned int choice, unsigned int uiAlgID, unsigned int count)
{
    HANDLE phSessionHandle = nullptr;
    int rv = 0;

    unsigned char		inbuf[4096] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
    unsigned char		outbuf[100];
    unsigned int		inlen, outlen;
    inlen = 32;
    ECCCipher			encrystruct;
    ECCrefPublicKey		eccpuk;
    ECCrefPrivateKey	eccprk;
    ECCSignature		signdata;
    unsigned char pin[9] = "12345678";

    rv = SDF_OpenSession(phDeviceHandle, &phSessionHandle);
    if (rv != SDR_OK) {
        SDF_CloseSession(phSessionHandle);
        mydebug << "SDF_GenerateKeyPair_ECC errorcode:" << rv << endl;
        return rv;
    }
    for (int i = 0; i < count; i++) {


        rv = SDF_HashInit(phSessionHandle, SGD_SM3, nullptr, nullptr, 0);
        if (rv != 0) {
            mydebug << "error" << endl;
        }

        rv = SDF_HashUpdate(phSessionHandle, inbuf, TESTLENTH);
        if (rv != 0) {
            mydebug << "error" << endl;
        }
        rv = SDF_HashFinal(phSessionHandle, outbuf, &outlen);
        if (rv != 0) {
            mydebug << "error" << endl;
        }

    }
    rv = SDF_CloseSession(phSessionHandle);
    return rv;

}
/**************************************************使用中测试函数**********************************************/

/**********************************************************
 * \brief 网络速度测试
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author wangzhanbei
 * \history
 * \time 2020/08/11
 ************************************************************/
#ifndef PUT_ULONG_BE
#define PUT_ULONG_BE(n,b,i)                             \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif
unsigned char indata[4096] = {0, 1, 2, 3, 4, 5, 6, 7, 0x00, 0x00, 0x40, 0, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
unsigned char outdata[4096];
int gmjSDF_NetTest_Speed(HANDLE phDeviceHandle, unsigned int choice, unsigned int uiAlgID, unsigned int count)
{
    unsigned int sendlenth = TESTLENTH;
    PUT_ULONG_BE(sendlenth, indata, 8);
    for (int i = 0; i < count; i++) {
        nettest(indata, TESTLENTH, outdata);
    }

    return 0;
}

/**********************************************************
 * \brief 随机数 SM1 SM4 SM3 算法速度测试
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author wangzhanbei
 * \history
 * \time 2020/08/11
 ************************************************************/

ECCrefPublicKey HashPublicKey;
unsigned char pucSignId[16];


int gmjSDF_SYM_Speed_test(int choice, void *phSessionHandle, void *phKeyHandle0, unsigned int uiAlgID, unsigned int count)
{

    unsigned char indata[1024 * 32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                      };
    unsigned int inlenth = 0, outlenth = 0;
    unsigned char outdata[1024 * 32] = { 0 };
    unsigned char iv[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 };
    unsigned char symkey[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 };
    unsigned int ret = 0;
    for (int i = 0; i < TESTLENTH; i++) {
        indata[i] = i % 256;
    }
    switch (choice) {
    case CRYPTO_ENC:
        for (int i = 0; i < count; i++) {
            ret = SDF_Encrypt(phSessionHandle, phKeyHandle0, uiAlgID, iv, indata, TESTLENTH, outdata, &outlenth);
            if (ret != 0) {
                std::cout << "SDF_Encrypt error:" << ret << endl;
            }
        }
        break;
    case CRYPTO_DEC:
        for (int i = 0; i < count; i++) {
            ret = SDF_Decrypt(phSessionHandle, phKeyHandle0, uiAlgID, iv, indata, TESTLENTH, outdata, &outlenth);
        }
        break;
    case CRYPTO_MAC:
        for (int i = 0; i < count; i++) {
            ret = SDF_CalculateMAC(phSessionHandle, phKeyHandle0, uiAlgID, iv, indata, TESTLENTH, outdata, &outlenth);
            if (ret != 0) {
                std::cout << "SDF_CalculateMAC error!" << endl;
                while(1);
            }
        }
        break;
    case CRYPTO_HASH:
        for (int i = 0; i < count; i++) {
            ret = SDF_HashInit(phSessionHandle, uiAlgID, nullptr, nullptr, 0);
            if (ret != 0) {
                std::cout << "SDF_HashInit error" << endl;
            }

            ret = SDF_HashUpdate(phSessionHandle, indata, TESTLENTH);
            if (ret != 0) {
                std::cout << "SDF_HashUpdate error" << endl;
            }


            ret = SDF_HashFinal(phSessionHandle, outdata, &outlenth);
            if (ret != 0) {
                std::cout << "SDF_HashFinal error" << endl;
            }
        }
        break;
    case CRYPTO_RAND:
        for (int i = 0; i < count; i++) {
            ret = SDF_GenerateRandom(phSessionHandle, TESTLENTH, outdata);
            if (ret != 0) {
                mydebug << "SDF_GenerateRandom error" << endl;
            }
        }
        break;
    default:
        break;
    }
    return ret;
}
/**********************************************************
 * \brief  测试SM2算法的加解密,签名验签,产生密钥对
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author wangzhanbei
 * \history
 * \time 2020/08/11
 ************************************************************/
int gmjSDF_ASYM_Speed_test(int choice, HANDLE phSessionHandle, HANDLE phkeyHandle, unsigned int uiAlgID, unsigned int count)
{
    unsigned char		inbuf[4096] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };
    unsigned char		outbuf[100];
    unsigned int		inlen, outlen;
    inlen = 32;
    ECCCipher			encrystruct;
    ECCrefPublicKey		eccpuk;
    ECCrefPrivateKey	eccprk;
    ECCSignature		signdata;
    unsigned char pin[9] = "12345678";
    int ret = 0;

    unsigned char pubkey[64] = {
        0x59, 0x89, 0x9D, 0xBC, 0x89, 0x8E, 0xAF, 0x3F, 0xC9, 0xC6, 0x39, 0x10, 0x58, 0x7C, 0x57, 0x93,
        0xE6, 0xFB, 0x2B, 0x54, 0x7A, 0xB9, 0xA3, 0x5F, 0xBD, 0xD1, 0xDB, 0xCD, 0x85, 0x1F, 0xCE, 0xD7,
        0x56, 0xBE, 0xEA, 0x79, 0x53, 0xF9, 0x59, 0x7E, 0x91, 0x80, 0x26, 0xC6, 0xA9, 0x1D, 0x63, 0x1D,
        0x4E, 0xE7, 0x11, 0x1F, 0xAF, 0xBF, 0xED, 0xE9, 0xB2, 0xA4, 0x40, 0xC7, 0x36, 0x96, 0x33, 0xFA
    };
    unsigned char prikey[32] = {
        0x5F, 0x70, 0x45, 0x5E, 0x48, 0x0D, 0x5A, 0x29, 0xE0, 0x55, 0x9B, 0x4B, 0x90, 0x58, 0x48, 0x3E,
        0x84, 0x97, 0x0F, 0xB0, 0x80, 0x74, 0x11, 0x8E, 0x6F, 0x79, 0x20, 0xD7, 0x6E, 0x26, 0xA4, 0x76
    };
    unsigned char plain[16] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F };
    unsigned char cipher[108] = {
        0x35, 0xEC, 0xC5, 0x0F, 0x43, 0x5F, 0x98, 0x6A, 0xCC, 0x42, 0x88, 0x8D, 0x5E, 0x60, 0xA8, 0x81,
        0x29, 0xFF, 0x9C, 0xE0, 0x90, 0x0C, 0xE4, 0x1F, 0x93, 0x90, 0xF4, 0xD1, 0x2C, 0xE7, 0xC0, 0x2F,
        0x82, 0x38, 0xF7, 0x97, 0xFA, 0x40, 0xE1, 0x15, 0x07, 0xF4, 0xD3, 0xB8, 0x99, 0x34, 0x19, 0xE1,
        0x11, 0xE6, 0x2B, 0x48, 0x8D, 0x16, 0x32, 0xA9, 0xF5, 0xD9, 0x96, 0x11, 0x06, 0x57, 0x95, 0x23,
        0x78, 0xCE, 0x4F, 0x72, 0x0C, 0x71, 0x92, 0xAE, 0x52, 0xBF, 0x77, 0x32, 0xD8, 0x04, 0x97, 0xB6,
        0xF5, 0xF4, 0x42, 0x22, 0x76, 0x4B, 0xAD, 0xDF, 0xA8, 0x4A, 0x6F, 0xB0, 0x54, 0xAA, 0xFB, 0xCB,
        0xE4, 0x17, 0x34, 0x4F, 0xA2, 0x3D, 0x6D, 0x43, 0x75, 0x75, 0x2B, 0x52,
    };

	charTopucKey(pubkey, &eccpuk);

    switch (choice) {
    case CRYPTO_ENC:
        for (int i = 0; i < count; i++) {

            ret = SDF_ExternalEncrypt_ECC(phSessionHandle, uiAlgID, &eccpuk, plain, 16, &encrystruct);
            if (ret != SDR_OK) {
                mydebug << "SDF_ExternalEncrypt_ECC error!" << endl;
                while (1);
            }
        }
        break;
    case CRYPTO_DEC:
        for (int i = 0; i < count; i++) {
            mydebug << "No interface" << endl;
        }
        break;

    case CRYPTO_SIGN:
        for (int i = 0; i < count; i++) {
            //需要获取操作权限
            ret = SDF_InternalSign_ECC(phSessionHandle, 1, inbuf, 32, &signdata);
            mydebug << "No interface" << endl;
        }
        break;
    case CRYPTO_VER:
        for (int i = 0; i < count; i++) {
            ret = SDF_InternalVerify_ECC(phSessionHandle, 1, inbuf, 32, &signdata);
        }
        break;
    case CRYPTO_GENKEY:
        for (int i = 0; i < count; i++) {
            ret = SDF_GenerateKeyPair_ECC(phSessionHandle, uiAlgID, 256, &eccpuk, &eccprk);
            if (ret != SDR_OK) {
                mydebug << "SDF_GenerateKeyPair_ECC errorcode:" << ret << endl;
                while (1);
            }
        }
        break;
    default:
        break;
    }
    return ret;
}