#include <iostream>
#include "openssl/conf.h"
#include "openssl/evp.h"
#include "openssl/err.h"
#include "openssl/crypto.h"
#include "openssl/sms4.h"
#include "openssl/sm3.h"
#include "openssl/sm2.h"
#include "openssl/ec.h"
#include "openssl/ossl_typ.h"
#include "openssl/gmapi.h"
using namespace std;

unsigned char Encdata[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x1b,0xcd,0xe8,0x2b,0xdb,0x42,0xcb,0x05,0xaa,0x97,0xa9,0xd6,0xc0,0xb8,0x0e,0xeb,
	0xc6,0x51,0xb4,0x2c,0xc1,0xae,0x1b,0xc0,0xb9,0xd6,0x62,0x86,0x4c,0x6e,0xb9,0x81,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x19,0x63,0xf3,0xd1,0x44,0x00,0xc1,0xb5,0x8c,0xde,0x61,0x31,0xc7,0xcb,0x4d,0xec,
	0xd2,0x28,0xbd,0x68,0xd6,0xc0,0x69,0x4a,0x2c,0xf4,0x7c,0x58,0xe6,0x2d,0x6d,0x5b,
	0xfd,0x09,0x73,0x21,0x87,0x60,0x61,0x71,0x66,0x60,0xae,0x53,0x75,0x5c,0x02,0x9e,
	0x1f,0xe1,0xd6,0xe3,0xde,0x5d,0xcc,0xf5,0x39,0x08,0x31,0x7b,0xaf,0xfe,0xff,0x9d,
	0x10,0x00,0x00,0x00,0x03,0xbb,0xeb,0x71,0x94,0xb6,0x3f,0x5e,0xd0,0x85,0x34,0xd5,
	0x7d,0xa7,0x71,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
static void charTopucKey(const unsigned char *data, ECCrefPublicKey *puc)
{
	puc->bits = 256;
	memcpy(&(puc->x[32]), data, 32);
	memcpy(&(puc->y[32]), data + 32, 32);
}

/**********************************************************
 * \brief
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author runwang2020@163.com
 * \history
 * \time 2020/3/9
 ***********************************************************/
int sm2_generatekey_test(ECCrefPublicKey &pubkey, ECCrefPrivateKey &prikey)
{
	EC_KEY *sm2key = NULL;
	EC_GROUP *group1 = NULL;

	sm2key = EC_KEY_new();
	if (!sm2key) {
		cout << "Failed to Gen Key" << endl;
		exit(1);
	}
	group1 = EC_GROUP_new_by_curve_name(NID_sm2p256v1);
	if (group1 == NULL) {
		cout << "Failed to Gen Key" << endl;
		exit(1);
	}
	// 可以调用set方法，设置公私钥对
	int ret1 = EC_KEY_set_group(sm2key, group1);
	if (ret1 != 1) {
		cout << "Failed to Gen Key" << endl;
		exit(1);
	}

	/********************************************************************
	* 此处已经产生密钥对，然后可以调用 get方法，分别获取公私钥
	EC_KEY *EC_KEY_new_from_ECCrefPublicKey(const ECCrefPublicKey *ref);
	int EC_KEY_set_ECCrefPublicKey(EC_KEY *ec_key, const ECCrefPublicKey *ref);
	int EC_KEY_get_ECCrefPublicKey(EC_KEY *ec_key, ECCrefPublicKey *ref);
	EC_KEY *EC_KEY_new_from_ECCrefPrivateKey(const ECCrefPrivateKey *ref);
	int EC_KEY_set_ECCrefPrivateKey(EC_KEY *ec_key, const ECCrefPrivateKey *ref);
	int EC_KEY_get_ECCrefPrivateKey(EC_KEY *ec_key, ECCrefPrivateKey *ref);
	****************************************************************************/
	int ret2 = EC_KEY_generate_key(sm2key);
	if (ret2 != 1) {
		cout << "Failed to Gen Key" << endl;
		exit(1);
	}
	EC_KEY_get_ECCrefPublicKey(sm2key, &pubkey);

	EC_KEY_get_ECCrefPrivateKey(sm2key, &prikey);
	EC_KEY_free(sm2key);

	return ret2;


}
/**********************************************************
 * \brief sm2加解密测试函数
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author runwang2020@163.com
 * \history
 * \time 2020/3/9
 ***********************************************************/
int sm2_encdec_test()
{
	ECCrefPublicKey pubkey;
	ECCrefPrivateKey prikey;
	memset(&pubkey, 0, sizeof(ECCrefPublicKey));
	memset(&prikey, 0, sizeof(ECCrefPrivateKey));
	sm2_generatekey_test(pubkey, prikey);
	printf("the pubkey is :\r\n");
	for (int i = 0; i < 32; i++)
	{
		printf("%x ", pubkey.x[32 + i]);
	}
	printf("\r\n");
	for (int i = 0; i < 32; i++)
	{
		printf("%x ", pubkey.y[32 + i]);
	}
	printf("the prikey is :\r\n");
	for (int i = 0; i < 32; i++)
	{
		printf("%x ", prikey.K[32 + i]);
	}

	return 0;
}