#ifndef HEADER_SM4_H
#define HEADER_SM4_H

#ifdef  __cplusplus
extern "C" {
#endif

    typedef unsigned char muint8;
    typedef unsigned long muint32;

#define LITTLE_ENDIAN     //����С���ֽ���
    //#define BIG_ENDIAN     //�������ֽ���
#define SM4_ENCRYPT  0     //������ܱ�־
#define SM4_DECRYPT  1     //������ܱ�־

#define SM4_BLOCK_LEN	16
#define SM4_KEY_LEN	16
#define SM4_IV_LEN	SM4_BLOCK_LEN

// SM4����Կ��չ�㷨
// ����˵����KeyΪ������Կ��rkΪ����Կ��CryptFlagΪ�ӽ��ܱ�־
    int SM4KeyExt(const muint8 *Key, muint32 *rk, muint32 CryptFlag);

    // SM4�ļӽ��ܺ���
    // ����˵����InputΪ������Ϣ���飬OutputΪ������飬rkΪ����Կ
    int SM4Crypt(const muint8 *Input, muint8 *Output, const muint32 *rk);

    //For EVP
    void sm4_set_key(muint32 *rk, const unsigned char *data, int enc);
    void sm4_ecb_encrypt(const unsigned char *in, unsigned char *out, const muint32 *rk,
                         int enc);
    void sm4_cbc_encrypt(const unsigned char *in, unsigned char *out, long length,
                         const muint32 *rk, unsigned char *iv, int enc);
    void sm4_cfb64_encrypt(const unsigned char *in, unsigned char *out,
                           long length, const muint32 *rk, unsigned char *ivec,
                           int *num, int enc);
    void sm4_ofb64_encrypt(const unsigned char *in, unsigned char *out,
                           long length, const muint32 *rk, unsigned char *ivec,
                           int *num);

#ifdef  __cplusplus
}
#endif

#endif