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


static void charTopucKey(const unsigned char *data, ECCrefPublicKey *puc)
{
	puc->bits = 256;
	memcpy(&(puc->x[32]), data, 32);
	memcpy(&(puc->y[32]), data + 32, 32);
}


/******************************************
函数功能：生成一组密钥对
*******************************************/
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