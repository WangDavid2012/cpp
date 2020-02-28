#include<openssl/des.h>
#include<openssl/pem.h>
#include<openssl/err.h>
#include <openssl/bio.h>
#include <iostream>



static int base64_decode(char *str, int str_len, unsigned char *decode)
{
	int len = 0;
	BIO *b64 = NULL, *bmem = NULL;

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new_mem_buf(str, str_len);
	bmem = BIO_push(b64, bmem);
	len = BIO_read(bmem, decode, str_len);
	decode[len] = 0;
	BIO_free_all(bmem);
	return len;
}

int des_test()
{
	//密钥
	DES_cblock key = { 's', 't', 'a', 'r', '-', 'n', 'e', 't' };

	//初始化向量,必须与加密使用的向量一致
	DES_cblock ivec = { 1, 2, 3, 4, 5, 6, 7, 8 };
	DES_key_schedule key_schedule;

	//base64每行结束符必须是\n
	char *data = "qbXat7531Oy/3ZFKNU/b4X0r/nwcnDNgT3iliJGDJr0=\n";
	unsigned char base64_de[1024];
	int base64_de_len = 0;
	unsigned char des_de[1024];

	//先base64解码
	memset(base64_de, 0, sizeof(base64_de));
	base64_de_len = base64_decode(data, strlen(data), base64_de);

	//设置密钥
	DES_set_key_unchecked(&key, &key_schedule);

	//解密
	memset(des_de, 0, sizeof(des_de));
	DES_ncbc_encrypt(base64_de, des_de, base64_de_len, &key_schedule, &ivec, DES_DECRYPT);
	printf("des_de:%s\n", des_de);

	return 0;
}