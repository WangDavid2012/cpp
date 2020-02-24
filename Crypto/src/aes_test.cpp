#include <stdio.h>
#include "openssl/aes.h"
#include <stdlib.h>
#include <string.h>

int aes_test()
{
	unsigned char key[16 + 1] = "my-key-i-choosed"; // 128bits key (应该是真正的随机数才好)
	char pt1[16 + 5 + 1] = "0123456789abcdef12345";   // 明文
	char ct[16 + 5 + 1];  // 密文
	char pt2[16 + 5 + 1]; // 解密后的明文

	AES_KEY k;
	unsigned char iv1[16 + 1] = { "1023456789abcdef" }; // 16+1，加密用
	unsigned char iv2[16 + 1] = { "1023456789abcdef" }; // 16+1，解密用

	{    // single blcok test
		AES_set_encrypt_key(key, 16 * 8, &k);
		AES_encrypt((unsigned char*)pt1, (unsigned char*)ct, &k);

		AES_set_decrypt_key(key, 16 * 8, &k);
		AES_decrypt((unsigned char*)ct, (unsigned char*)pt2, &k);

		if (memcmp(pt1, pt2, 16) == 0)
			puts("AES block ok");
		else
			puts("AES block err");
	}

	{    // cfb mode (stream mode)
		int num = 0;
		AES_set_encrypt_key(key, 16 * 8, &k);
		AES_cfb128_encrypt((unsigned char*)pt1, (unsigned char*)ct,
			16 + 5, &k, (unsigned char*)iv1, &num, AES_ENCRYPT);

		num = 0;
		AES_set_encrypt_key(key, 16 * 8, &k); // MUST as enc
		AES_cfb128_encrypt((unsigned char*)ct, (unsigned char*)pt2,
			16 + 5, &k, (unsigned char*)iv2, &num, AES_DECRYPT);

		if (memcmp(pt1, pt2, 16 + 5) == 0)
			puts("AES CFB mode ok");
		else
			puts("AES CFB mode err");
	}
	//system("pause");
	return 0;
}