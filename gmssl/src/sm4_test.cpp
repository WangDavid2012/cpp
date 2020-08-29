#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/sms4.h>
#include <iostream>
using namespace std;


int sm4_test1()
{
	int err = 0;
	int i;
	sms4_key_t key;
	unsigned char buf[16];
	unsigned char tmp[16] = { 0 };

	unsigned char user_key[16] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
		0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
	};

	uint32_t rk[32] = {
		0xf12186f9, 0x41662b61, 0x5a6ab19a, 0x7ba92077,
		0x367360f4, 0x776a0c61, 0xb6bb89b3, 0x24763151,
		0xa520307c, 0xb7584dbd, 0xc30753ed, 0x7ee55b57,
		0x6988608c, 0x30d895b7, 0x44ba14af, 0x104495a1,
		0xd120b428, 0x73b55fa3, 0xcc874966, 0x92244439,
		0xe89e641f, 0x98ca015a, 0xc7159060, 0x99e1fd2e,
		0xb79bd80c, 0x1d2115b0, 0x0e228aeb, 0xf1780c81,
		0x428d3654, 0x62293496, 0x01cf72e5, 0x9124a012,
	};

	unsigned char plaintext[16] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
		0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
	};

	unsigned char ciphertext1[16] = {
		0x68, 0x1e, 0xdf, 0x34, 0xd2, 0x06, 0x96, 0x5e,
		0x86, 0xb3, 0xe9, 0x4f, 0x53, 0x6e, 0x42, 0x46,
	};

	unsigned char ciphertext2[16] = {
		0x59, 0x52, 0x98, 0xc7, 0xc6, 0xfd, 0x27, 0x1f,
		0x04, 0x02, 0xf8, 0x04, 0xc3, 0x3d, 0x3f, 0x66,
	};

	/* test key scheduling */
	sms4_set_encrypt_key(&key, user_key);

	if (memcmp(key.rk, rk, sizeof(rk)) != 0) {
		printf("sms4 key scheduling not passed!\n");
		return -1;
	}
	printf("sms4 key scheduling passed!\n");

	/* test encrypt once */
	sms4_encrypt(plaintext, buf, &key);

	if (memcmp(buf, ciphertext1, sizeof(ciphertext1)) != 0) {
		printf("sms4 encrypt not pass!\n");
		return -1;
	}
	printf("sms4 encrypt pass!\n");

	/* test encrypt 1000000 times */
	memcpy(buf, plaintext, sizeof(plaintext));
	for (i = 0; i < 1000000; i++) {
		sms4_encrypt(buf, buf, &key);
	}

	if (memcmp(buf, ciphertext2, sizeof(ciphertext2)) != 0) {
		printf("sms4 encrypt 1000000 times not pass!\n");
		return -1;
	}
	printf("sms4 encrypt 1000000 times pass!\n");
	printf("sms4 all test vectors pass!\n");

	return err;

}




int sm4_test2()
{
	//SM4 算法测试
	unsigned char in[16] = { 0 };
	unsigned char out[16] = { 0 };
	unsigned char ciphertxt[16] = { 0 };
	unsigned char key[16] = { 0 };
	for (int i = 0; i < 16; i++)
	{
		in[i] = i;
		key[i] = i;
	}
	sms4_key_t sm4_enckey;
	sms4_key_t sm4_deckey;
	memset(&sm4_enckey, 0, sizeof(sms4_key_t));
	sms4_set_encrypt_key(&sm4_enckey, key);
	sms4_ecb_encrypt(in, out, &sm4_enckey, 1);

	for (int i = 0; i < 16; i++)
	{
		cout << hex << out[i] << " ";
	}
	cout << endl;
	sms4_set_decrypt_key(&sm4_deckey, key);
	sms4_ecb_encrypt(out, ciphertxt, &sm4_deckey, 0);

	return 0;
}

int sm4_test()
{
	sms4_key_t sm4key;
	//ECB模式测试
	unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	unsigned char plain[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	unsigned char cipher[16] = { 0x68,0x1e,0xdf,0x34,0xd2,0x06,0x96,0x5e,0x86,0xb3,0xe9,0x4f,0x53,0x6e,0x42,0x46 };
	unsigned char tmp[16] = { 0 };

	//SGD_SMS4_CBC：
	unsigned char cbc_key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	unsigned char cbc_iv[16] = { 0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7 };
	unsigned char cbc_plain[32] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0x29,0xbe,0xe1,0xd6,0x52,0x49,0xf1,0xe9,0xb3,0xdb,0x87,0x3e,0x24,0x0d,0x06,0x47 };
	unsigned char cbc_cipher[32] = { 0x3f,0x1e,0x73,0xc3,0xdf,0xd5,0xa1,0x32,0x88,0x2f,0xe6,0x9d,0x99,0x6c,0xde,0x93,0x54,0x99,0x09,0x5d,0xde,0x68,0x99,0x5b,0x4d,0x70,0xf2,0x30,0x9f,0x2e,0xf1,0xb7 };
	unsigned char cbc_tmp[32] = { 0 };


	//SM4 ECB 模式测试
	sms4_set_encrypt_key(&sm4key, key);
	sms4_encrypt(plain, tmp, &sm4key);
	if (0 != memcmp(cipher, tmp, sizeof(tmp)))
	{
		printf("SM4 ECB encrypt failed...\n");
		return -1;
	}
	else
	{
		printf("SM4 ECB encrypt success...\n");
	}

	memset(tmp, 0, sizeof(tmp));
	sms4_set_decrypt_key(&sm4key, key);
	sms4_decrypt(cipher, tmp, &sm4key);
	if (0 != memcmp(plain, tmp, sizeof(tmp)))
	{
		printf("SM4 ECB decrypt failed...\n");
		return -1;
	}
	else
	{
		printf("SM4  ECB decrypt success...\n");
	}

	//SM4 CBC模式测试
	unsigned char cbc_iv1[16] = { 0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7 };
	memset(cbc_tmp, 0, sizeof(cbc_tmp));
	sms4_set_encrypt_key(&sm4key, cbc_key);
	sms4_cbc_encrypt(cbc_plain, cbc_tmp, 32, &sm4key, cbc_iv, 1);
	if (0 != memcmp(cbc_cipher, cbc_tmp, sizeof(cbc_tmp)))
	{
		printf("SM4 CBC encrypt failed...\n");
		return -1;
	}
	else
	{
		printf("SM4 CBC encrypt success...\n");
	}

	memset(cbc_tmp, 0, sizeof(cbc_tmp));
	sms4_set_decrypt_key(&sm4key, cbc_key);
	sms4_cbc_encrypt(cbc_cipher, cbc_tmp, 32, &sm4key, cbc_iv1, 0);
	if (0 != memcmp(cbc_plain, cbc_tmp, sizeof(cbc_tmp)))
	{
		printf("SM4 CBC decrypt failed...\n");
		return -1;
	}
	else
	{
		printf("SM4 CBC decrypt success...\n");
	}
	return 0;
}

