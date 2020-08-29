#include <iostream>    
#include <cassert>  
#include <string>    
#include "openssl/rsa.h"
#include "openssl/sha.h"
#include "openssl/x509.h"
#include "openssl/pem.h"  
#include "openssl/bio.h"  
#include <iostream>

using namespace std;













/**********************************************************
 * \brief RSA加解密测试函数
 *
 * \param[in]
 * \return 0 加解密测试成功 ~0加解密测试失败
 *
 ***********************************************************/
int rsaencdec_test()
{
	RSA *r;
	int bits = 1024;
	int ret, len, flen, padding, i;
	unsigned long e = RSA_3;
	BIGNUM *bne;
	unsigned  char *key, *p;
	BIO *b;
	unsigned char from[500], to[500], out[500];
	bne = BN_new();
	ret = BN_set_word(bne, e);
	r = RSA_new();
	ret = RSA_generate_key_ex(r, bits, bne, NULL);
	if (ret != 1)
	{
		printf("RSA_generate_key_ex failed \r\n");
		return -1;
	}

	b = BIO_new(BIO_s_mem());
	ret = i2d_RSAPrivateKey_bio(b, r);
	key = (unsigned char *)malloc(1024);
	len = BIO_read(b, key, 1024);
	BIO_free(b);

	b = BIO_new_file("rsa.key", "w");
	ret = i2d_RSAPrivateKey_bio(b, r);
	BIO_free(b);

	flen = RSA_size(r);
	//printf("please select private enc padding:\n");
	//printf("1:RSA_PKCS1_PADDING\n");
	//printf("3:RSA_NO_PADDING\n");
	//printf("5:RSA_X931_PADDING\n");

	//scanf("%d", &padding);
	//if (padding == RSA_PKCS1_PADDING)
	//	flen -= 11;
	//else if (padding == RSA_X931_PADDING)
	//	flen -= 1;
	//else if (padding == RSA_NO_PADDING)
	//	flen = flen;
	//else
	//{
	//	printf("error\n");
	//	return -1;
	//}

	for (i = 0; i < flen; i++)
	{
		from[i] = i % 255;
	}
	len = RSA_public_encrypt(flen, from, to, r, RSA_NO_PADDING);
	if (len <= 0)
	{
		printf("error\n");
		return -1;
	}
	len = RSA_private_decrypt(flen, to, out, r, RSA_NO_PADDING);
	if (len <= 0)
	{
		printf("error\n");
		return -1;
	}
	if (0 != memcmp(from, out, flen))
	{
		printf("error\n");
		return -1;
	}

	return 0;
}


#define KEY_LENGTH  2048             // 密钥长度  
#define PUB_KEY_FILE "pubkey.pem"    // 公钥路径  
#define PRI_KEY_FILE "prikey.pem"    // 私钥路径  

/****************************************************
*  \brief 生成RSA公私钥对，并将生成的公私钥对文件保存
*
*  \param [out] strKey 密钥对
*  \return
*
*  \details
*****************************************************/
void generateRSAKey(string strKey[2])
{
	// 公私密钥对    
	size_t pri_len;
	size_t pub_len;
	char *pri_key = NULL;
	char *pub_key = NULL;

	unsigned long e = RSA_3;
	BIGNUM *bne;
	int ret;


	bne = BN_new();
	ret = BN_set_word(bne, e);
	RSA *keypair = RSA_new();
	ret = RSA_generate_key_ex(keypair, KEY_LENGTH, bne, NULL);




	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSAPublicKey(pub, keypair);

	// 获取长度    
	pri_len = BIO_pending(pri);
	pub_len = BIO_pending(pub);

	// 密钥对读取到字符串    
	pri_key = (char *)malloc(pri_len + 1);
	pub_key = (char *)malloc(pub_len + 1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';

	// 存储密钥对    
	strKey[0] = pub_key;
	strKey[1] = pri_key;

	// 存储到磁盘（这种方式存储的是begin rsa public key/ begin rsa private key开头的）  
	FILE *pubFile = fopen(PUB_KEY_FILE, "w");
	if (pubFile == NULL)
	{
		return;
	}
	fputs(pub_key, pubFile);
	fclose(pubFile);

	FILE *priFile = fopen(PRI_KEY_FILE, "w");
	if (priFile == NULL)
	{
		return;
	}
	fputs(pri_key, priFile);
	fclose(priFile);



	// 内存释放  
	RSA_free(keypair);
	BIO_free_all(pub);
	BIO_free_all(pri);

	free(pri_key);
	free(pub_key);
}

// 命令行方法生成公私钥对（begin public key/ begin private key）  
// 找到openssl命令行工具，运行以下  
// openssl genrsa -out prikey.pem 1024   
// openssl rsa - in privkey.pem - pubout - out pubkey.pem  
// 实际应用中，出于安全考虑我们一般会对私钥文件加密。我们可以用如下的方式来重新生成经3DES加密后私钥文件：
// openssl genrsa -des3 -out cipherPrv.key 1024

/****************************************************
*  \brief
*
*  \param [in]
*  \param [out]
*  \param [in]
*  \return
*
*  \details
*****************************************************/
string rsa_pub_encrypt(const string &clearText, const string &pubKey)
{
	string strRet;
	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);

	RSA* pRSAPublicKey = RSA_new();
	rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);

	int len = RSA_size(rsa);
	char *encryptedText = (char *)malloc(len + 1);
	memset(encryptedText, 0, len + 1);

	// 加密函数  
	int ret = RSA_public_encrypt(clearText.length(), (const unsigned char*)clearText.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = string(encryptedText, ret);

	// 释放内存  
	free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

/****************************************************
*  \brief	私钥解密函数
*
*  \param [in]cipherText 解密密文
*  \param [in]priKey 私钥
*  \return 解密结果
*
*  \details
*****************************************************/
string rsa_pri_decrypt(const string &cipherText, const string &priKey)
{
	string strRet;
	RSA *rsa = RSA_new();
	BIO *keybio;
	keybio = BIO_new_mem_buf((unsigned char *)priKey.c_str(), -1);
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

	int len = RSA_size(rsa);
	char *decryptedText = (char *)malloc(len + 1);
	memset(decryptedText, 0, len + 1);

	// 解密函数  
	int ret = RSA_private_decrypt(cipherText.length(), (const unsigned char*)cipherText.c_str(), (unsigned char*)decryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = string(decryptedText, ret);

	// 释放内存  
	free(decryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}


void rsa_test()
{
	string plainText = "hello world!";
	string encryptText;
	string decryptText;
	string key[2];
	generateRSAKey(key);
	cout << "publickey: " << endl;
	cout << key[0] << endl;
	cout << "privatekey： " << endl;
	cout << key[1] << endl;
	encryptText = rsa_pub_encrypt(plainText, key[0]);
	cout << "enctext： " << endl;
	cout << encryptText << endl;
	decryptText = rsa_pri_decrypt(encryptText, key[1]);
	cout << "dectest： " << endl;
	cout << decryptText << endl;
}


















