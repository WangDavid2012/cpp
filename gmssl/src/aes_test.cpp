#include <stdio.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <iostream>
#include <string.h>


int aes_test()
{
	unsigned char  userKey[AES_BLOCK_SIZE];
	unsigned char *data = (unsigned char *)malloc(AES_BLOCK_SIZE * 3);
	unsigned char *encrypto = (unsigned char *)malloc(AES_BLOCK_SIZE * 3);
	unsigned char *plain = (unsigned char *)malloc(AES_BLOCK_SIZE * 3);
	AES_KEY key;

	memcpy(userKey, "zheshiopensslexq", 16);
	memset((void*)data, 'p', AES_BLOCK_SIZE * 3);
	memset((void*)encrypto, 0, AES_BLOCK_SIZE * 3);
	memset((void*)plain, 0, AES_BLOCK_SIZE * 3);

	//设置加密key及秘钥长度
	//理论上AES加密是根据S盒进行字节替换的，因此原文和密文个字节一一对应大小相同
	AES_set_encrypt_key((const unsigned char *)userKey, AES_BLOCK_SIZE * 8, &key);

	int len = 0;
	//循环加密， 每次加密长度是AES_BLOCK_SIZE长度的数据
	while (len < AES_BLOCK_SIZE * 3)
	{
		AES_encrypt(data + len, encrypto + len, &key);
		len += AES_BLOCK_SIZE;
	}

	//设置解密key及秘钥长度
	AES_set_decrypt_key((const unsigned char *)userKey, AES_BLOCK_SIZE * 8, &key);

	len = 0;
	//循环解密
	//每次输入16字节，输出16字节，如果不够需要填充
	while (len < AES_BLOCK_SIZE * 3)
	{
		AES_decrypt(encrypto + len, plain + len, &key);
		len += AES_BLOCK_SIZE;
	}

	//解密后与元数据是否一致
	if (memcmp(plain, data, AES_BLOCK_SIZE * 3) == 0)
	{
		printf("test success\n");
	}
	else
	{
		printf("test failed\n");
	}

	return 0;
}
