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

	//���ü���key����Կ����
	//������AES�����Ǹ���S�н����ֽ��滻�ģ����ԭ�ĺ����ĸ��ֽ�һһ��Ӧ��С��ͬ
	AES_set_encrypt_key((const unsigned char *)userKey, AES_BLOCK_SIZE * 8, &key);

	int len = 0;
	//ѭ�����ܣ� ÿ�μ��ܳ�����AES_BLOCK_SIZE���ȵ�����
	while (len < AES_BLOCK_SIZE * 3)
	{
		AES_encrypt(data + len, encrypto + len, &key);
		len += AES_BLOCK_SIZE;
	}

	//���ý���key����Կ����
	AES_set_decrypt_key((const unsigned char *)userKey, AES_BLOCK_SIZE * 8, &key);

	len = 0;
	//ѭ������
	//ÿ������16�ֽڣ����16�ֽڣ����������Ҫ���
	while (len < AES_BLOCK_SIZE * 3)
	{
		AES_decrypt(encrypto + len, plain + len, &key);
		len += AES_BLOCK_SIZE;
	}

	//���ܺ���Ԫ�����Ƿ�һ��
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
