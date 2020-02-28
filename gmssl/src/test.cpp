#include <iostream>    
#include <cassert>  
#include <string>    
#include <vector>    
#include "openssl/md5.h"    
#include "openssl/sha.h"    
#include "openssl/des.h"    
#include "openssl/rsa.h"    
#include "openssl/pem.h"    

// ---- md5ժҪ��ϣ ---- //    
void md5(const std::string &srcStr, std::string &encodedStr, std::string &encodedHexStr)
{
	// ����md5��ϣ    
	unsigned char mdStr[33] = { 0 };
	MD5((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);

	// ��ϣ����ַ���    
	encodedStr = std::string((const char *)mdStr);
	// ��ϣ���ʮ�����ƴ� 32�ֽ�    
	char buf[65] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 32; i++)
	{
		sprintf(tmp, "%02x", mdStr[i]);
		strcat(buf, tmp);
	}
	buf[32] = '\0'; // ���涼��0����32�ֽڽض�    
	encodedHexStr = std::string(buf);
}

// ---- sha256ժҪ��ϣ ---- //    
void sha256(const std::string &srcStr, std::string &encodedStr, std::string &encodedHexStr)
{
	// ����sha256��ϣ    
	unsigned char mdStr[33] = { 0 };
	SHA256((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);

	// ��ϣ����ַ���    
	encodedStr = std::string((const char *)mdStr);
	// ��ϣ���ʮ�����ƴ� 32�ֽ�    
	char buf[65] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 32; i++)
	{
		sprintf(tmp, "%02x", mdStr[i]);
		strcat(buf, tmp);
	}
	buf[32] = '\0'; // ���涼��0����32�ֽڽض�    
	encodedHexStr = std::string(buf);
}

// ---- des�ԳƼӽ��� ---- //    
// ���� ecbģʽ    
std::string des_encrypt(const std::string &clearText, const std::string &key)
{
	std::string cipherText; // ����    

	DES_cblock keyEncrypt;
	memset(keyEncrypt, 0, 8);

	// ���첹������Կ    
	if (key.length() <= 8)
		memcpy(keyEncrypt, key.c_str(), key.length());
	else
		memcpy(keyEncrypt, key.c_str(), 8);

	// ��Կ�û�    
	DES_key_schedule keySchedule;
	DES_set_key_unchecked(&keyEncrypt, &keySchedule);

	// ѭ�����ܣ�ÿ8�ֽ�һ��    
	const_DES_cblock inputText;
	DES_cblock outputText;
	std::vector<unsigned char> vecCiphertext;
	unsigned char tmp[8];

	for (int i = 0; i < clearText.length() / 8; i++)
	{
		memcpy(inputText, clearText.c_str() + i * 8, 8);
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCiphertext.push_back(tmp[j]);
	}

	if (clearText.length() % 8 != 0)
	{
		int tmp1 = clearText.length() / 8 * 8;
		int tmp2 = clearText.length() - tmp1;
		memset(inputText, 0, 8);
		memcpy(inputText, clearText.c_str() + tmp1, tmp2);
		// ���ܺ���    
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCiphertext.push_back(tmp[j]);
	}

	cipherText.clear();
	cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

	return cipherText;
}

// ���� ecbģʽ    
std::string des_decrypt(const std::string &cipherText, const std::string &key)
{
	std::string clearText; // ����    

	DES_cblock keyEncrypt;
	memset(keyEncrypt, 0, 8);

	if (key.length() <= 8)
		memcpy(keyEncrypt, key.c_str(), key.length());
	else
		memcpy(keyEncrypt, key.c_str(), 8);

	DES_key_schedule keySchedule;
	DES_set_key_unchecked(&keyEncrypt, &keySchedule);

	const_DES_cblock inputText;
	DES_cblock outputText;
	std::vector<unsigned char> vecCleartext;
	unsigned char tmp[8];

	for (int i = 0; i < cipherText.length() / 8; i++)
	{
		memcpy(inputText, cipherText.c_str() + i * 8, 8);
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCleartext.push_back(tmp[j]);
	}

	if (cipherText.length() % 8 != 0)
	{
		int tmp1 = cipherText.length() / 8 * 8;
		int tmp2 = cipherText.length() - tmp1;
		memset(inputText, 0, 8);
		memcpy(inputText, cipherText.c_str() + tmp1, tmp2);
		// ���ܺ���    
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCleartext.push_back(tmp[j]);
	}

	clearText.clear();
	clearText.assign(vecCleartext.begin(), vecCleartext.end());

	return clearText;
}


// ---- rsa�ǶԳƼӽ��� ---- //    
#define KEY_LENGTH  2048             // ��Կ����  
#define PUB_KEY_FILE "pubkey.pem"    // ��Կ·��  
#define PRI_KEY_FILE "prikey.pem"    // ˽Կ·��  

// ��������������Կ��   
void generateRSAKey(std::string strKey[2])
{
	// ��˽��Կ��    
	size_t pri_len;
	size_t pub_len;
	char *pri_key = NULL;
	char *pub_key = NULL;

	// ������Կ��    
	RSA *keypair = RSA_generate_key(KEY_LENGTH, RSA_3, NULL, NULL);

	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSAPublicKey(pub, keypair);

	// ��ȡ����    
	pri_len = BIO_pending(pri);
	pub_len = BIO_pending(pub);

	// ��Կ�Զ�ȡ���ַ���    
	pri_key = (char *)malloc(pri_len + 1);
	pub_key = (char *)malloc(pub_len + 1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';

	// �洢��Կ��    
	strKey[0] = pub_key;
	strKey[1] = pri_key;

	// �洢�����̣����ַ�ʽ�洢����begin rsa public key/ begin rsa private key��ͷ�ģ�  
	FILE *pubFile = fopen(PUB_KEY_FILE, "w");
	if (pubFile == NULL)
	{
		assert(false);
		return;
	}
	fputs(pub_key, pubFile);
	fclose(pubFile);

	FILE *priFile = fopen(PRI_KEY_FILE, "w");
	if (priFile == NULL)
	{
		assert(false);
		return;
	}
	fputs(pri_key, priFile);
	fclose(priFile);

	// �ڴ��ͷ�  
	RSA_free(keypair);
	BIO_free_all(pub);
	BIO_free_all(pri);

	free(pri_key);
	free(pub_key);
}

// �����з������ɹ�˽Կ�ԣ�begin public key/ begin private key��  
// �ҵ�openssl�����й��ߣ���������  
// openssl genrsa -out prikey.pem 1024   
// openssl rsa - in privkey.pem - pubout - out pubkey.pem  

// ��Կ����    
std::string rsa_pub_encrypt(const std::string &clearText, const std::string &pubKey)
{
	std::string strRet;
	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);
	// �˴������ַ���  
	// 1, ��ȡ�ڴ������ɵ���Կ�ԣ��ٴ��ڴ�����rsa  
	// 2, ��ȡ���������ɵ���Կ���ı��ļ����ڴ��ڴ�����rsa  
	// 3��ֱ�ӴӶ�ȡ�ļ�ָ������rsa  
	RSA* pRSAPublicKey = RSA_new();
	rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);

	int len = RSA_size(rsa);
	char *encryptedText = (char *)malloc(len + 1);
	memset(encryptedText, 0, len + 1);

	// ���ܺ���  
	int ret = RSA_public_encrypt(clearText.length(), (const unsigned char*)clearText.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(encryptedText, ret);

	// �ͷ��ڴ�  
	free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

// ˽Կ����    
std::string rsa_pri_decrypt(const std::string &cipherText, const std::string &priKey)
{
	std::string strRet;
	RSA *rsa = RSA_new();
	BIO *keybio;
	keybio = BIO_new_mem_buf((unsigned char *)priKey.c_str(), -1);

	// �˴������ַ���  
	// 1, ��ȡ�ڴ������ɵ���Կ�ԣ��ٴ��ڴ�����rsa  
	// 2, ��ȡ���������ɵ���Կ���ı��ļ����ڴ��ڴ�����rsa  
	// 3��ֱ�ӴӶ�ȡ�ļ�ָ������rsa  
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

	int len = RSA_size(rsa);
	char *decryptedText = (char *)malloc(len + 1);
	memset(decryptedText, 0, len + 1);

	// ���ܺ���  
	int ret = RSA_private_decrypt(cipherText.length(), (const unsigned char*)cipherText.c_str(), (unsigned char*)decryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(decryptedText, ret);

	// �ͷ��ڴ�  
	free(decryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

int crypto_test()
{
	// ԭʼ����    
	std::string srcText = "this is an example";

	std::string encryptText;
	std::string encryptHexText;
	std::string decryptText;

	std::cout << "=== ԭʼ���� ===" << std::endl;
	std::cout << srcText << std::endl;

	// md5    
	std::cout << "=== md5��ϣ ===" << std::endl;
	md5(srcText, encryptText, encryptHexText);
	std::cout << "ժҪ�ַ��� " << encryptText << std::endl;
	std::cout << "ժҪ���� " << encryptHexText << std::endl;

	// sha256    
	std::cout << "=== sha256��ϣ ===" << std::endl;
	sha256(srcText, encryptText, encryptHexText);
	std::cout << "ժҪ�ַ��� " << encryptText << std::endl;
	std::cout << "ժҪ���� " << encryptHexText << std::endl;

	// des    
	std::cout << "=== des�ӽ��� ===" << std::endl;
	std::string desKey = "12345";
	encryptText = des_encrypt(srcText, desKey);
	std::cout << "�����ַ��� " << std::endl;
	std::cout << encryptText << std::endl;
	decryptText = des_decrypt(encryptText, desKey);
	std::cout << "�����ַ��� " << std::endl;
	std::cout << decryptText << std::endl;

	// rsa    
	std::cout << "=== rsa�ӽ��� ===" << std::endl;
	std::string key[2];
	generateRSAKey(key);
	std::cout << "��Կ: " << std::endl;
	std::cout << key[0] << std::endl;
	std::cout << "˽Կ�� " << std::endl;
	std::cout << key[1] << std::endl;
	encryptText = rsa_pub_encrypt(srcText, key[0]);
	std::cout << "�����ַ��� " << std::endl;
	std::cout << encryptText << std::endl;
	decryptText = rsa_pri_decrypt(encryptText, key[1]);
	std::cout << "�����ַ��� " << std::endl;
	std::cout << decryptText << std::endl;

	system("pause");
	return 0;
}
