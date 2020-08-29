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

//—È÷§«©√˚≤‚ ‘
void testverify()
{
	unsigned char hash_value[32];
	hash_value[0] = 0xdf;
	hash_value[1] = 0xaf;
	hash_value[2] = 0x23;
	hash_value[3] = 0xc9;
	hash_value[4] = 0x49;
	hash_value[5] = 0x2c;
	hash_value[6] = 0x51;
	hash_value[7] = 0x5b;
	hash_value[8] = 0xe4;
	hash_value[9] = 0xf7;
	hash_value[10] = 0x81;
	hash_value[11] = 0x9c;
	hash_value[12] = 0x2a;
	hash_value[13] = 0x98;
	hash_value[14] = 0xa8;
	hash_value[15] = 0x58;
	hash_value[16] = 0x2d;
	hash_value[17] = 0x00;
	hash_value[18] = 0xa3;
	hash_value[19] = 0x6c;
	hash_value[20] = 0xfe;
	hash_value[21] = 0x38;
	hash_value[22] = 0x40;
	hash_value[23] = 0xba;
	hash_value[24] = 0x48;
	hash_value[25] = 0x92;
	hash_value[26] = 0x03;
	hash_value[27] = 0xd8;
	hash_value[28] = 0x1b;
	hash_value[29] = 0xe8;
	hash_value[30] = 0x61;
	hash_value[31] = 0x2f;

	unsigned char sign_value[64];

	sign_value[0] = 0x47;
	sign_value[1] = 0xc0;
	sign_value[2] = 0x6d;
	sign_value[3] = 0xe0;
	sign_value[4] = 0x1c;
	sign_value[5] = 0xf7;
	sign_value[6] = 0x1c;
	sign_value[7] = 0x59;
	sign_value[8] = 0x6b;
	sign_value[9] = 0xa0;
	sign_value[10] = 0x55;
	sign_value[11] = 0x19;
	sign_value[12] = 0x00;
	sign_value[13] = 0x65;
	sign_value[14] = 0x27;
	sign_value[15] = 0xdd;
	sign_value[16] = 0x78;
	sign_value[17] = 0xb9;
	sign_value[18] = 0x80;
	sign_value[19] = 0x6c;
	sign_value[20] = 0xeb;
	sign_value[21] = 0x1c;
	sign_value[22] = 0xfc;
	sign_value[23] = 0x3b;
	sign_value[24] = 0xe6;
	sign_value[25] = 0xee;
	sign_value[26] = 0x51;
	sign_value[27] = 0x62;
	sign_value[28] = 0x3f;
	sign_value[29] = 0x21;
	sign_value[30] = 0x0c;
	sign_value[31] = 0x9e;
	sign_value[32] = 0xcd;
	sign_value[33] = 0x5a;
	sign_value[34] = 0xf1;
	sign_value[35] = 0xbc;
	sign_value[36] = 0x9b;
	sign_value[37] = 0x03;
	sign_value[38] = 0xcf;
	sign_value[39] = 0xa0;
	sign_value[40] = 0x96;
	sign_value[41] = 0x2e;
	sign_value[42] = 0x25;
	sign_value[43] = 0x2c;
	sign_value[44] = 0xfa;
	sign_value[45] = 0x33;
	sign_value[46] = 0x2d;
	sign_value[47] = 0x8a;
	sign_value[48] = 0xc0;
	sign_value[49] = 0x60;
	sign_value[50] = 0x6e;
	sign_value[51] = 0x23;
	sign_value[52] = 0xbe;
	sign_value[53] = 0x70;
	sign_value[54] = 0x18;
	sign_value[55] = 0xe7;
	sign_value[56] = 0xef;
	sign_value[57] = 0xad;
	sign_value[58] = 0xff;
	sign_value[59] = 0xe0;
	sign_value[60] = 0xd1;
	sign_value[61] = 0xc2;
	sign_value[62] = 0x21;
	sign_value[63] = 0xe5;


	unsigned char pubKey[64];
	pubKey[0] = 0x62;
	pubKey[1] = 0xb3;
	pubKey[2] = 0xaa;
	pubKey[3] = 0xf8;
	pubKey[4] = 0xbe;
	pubKey[5] = 0x65;
	pubKey[6] = 0xc2;
	pubKey[7] = 0x6a;
	pubKey[8] = 0xc4;
	pubKey[9] = 0x15;
	pubKey[10] = 0xe0;
	pubKey[11] = 0xa3;
	pubKey[12] = 0x5f;
	pubKey[13] = 0xa7;
	pubKey[14] = 0xb2;
	pubKey[15] = 0xa9;
	pubKey[16] = 0x40;
	pubKey[17] = 0x2d;
	pubKey[18] = 0xcb;
	pubKey[19] = 0x42;
	pubKey[20] = 0xbe;
	pubKey[21] = 0x9c;
	pubKey[22] = 0x55;
	pubKey[23] = 0x0d;
	pubKey[24] = 0x93;
	pubKey[25] = 0xc8;
	pubKey[26] = 0x17;
	pubKey[27] = 0xe2;
	pubKey[28] = 0x77;
	pubKey[29] = 0x2a;
	pubKey[30] = 0x2a;
	pubKey[31] = 0x8b;
	pubKey[32] = 0x2a;
	pubKey[33] = 0xef;
	pubKey[34] = 0x29;
	pubKey[35] = 0x62;
	pubKey[36] = 0xf1;
	pubKey[37] = 0x4a;
	pubKey[38] = 0x7b;
	pubKey[39] = 0x55;
	pubKey[40] = 0x89;
	pubKey[41] = 0xc6;
	pubKey[42] = 0x91;
	pubKey[43] = 0x3a;
	pubKey[44] = 0x73;
	pubKey[45] = 0xd8;
	pubKey[46] = 0x8f;
	pubKey[47] = 0x87;
	pubKey[48] = 0x9f;
	pubKey[49] = 0xa2;
	pubKey[50] = 0x1c;
	pubKey[51] = 0xa3;
	pubKey[52] = 0x4d;
	pubKey[53] = 0x2f;
	pubKey[54] = 0xff;
	pubKey[55] = 0xb3;
	pubKey[56] = 0x11;
	pubKey[57] = 0xe4;
	pubKey[58] = 0x89;
	pubKey[59] = 0x1d;
	pubKey[60] = 0x21;
	pubKey[61] = 0xd1;
	pubKey[62] = 0x3b;
	pubKey[63] = 0x26;


	ECCrefPublicKey tmppubkey;
	ECCSignature signdata;

	memset(&tmppubkey, 0, sizeof(ECCrefPublicKey));
	printf("the value is %d\n", ECCref_MAX_LEN);


	memset(&tmppubkey, 0, sizeof(ECCrefPublicKey));
	charTopucKey(pubKey, &tmppubkey);

	EC_GROUP *sm2p256v1 = EC_GROUP_new_by_curve_name(NID_sm2p256v1);
	EC_KEY *sm2key = EC_KEY_new_by_curve_name(NID_sm2p256v1);
	int tt = EC_KEY_set_ECCrefPublicKey(sm2key, &tmppubkey);

	//EC_KEY * sm2key = EC_KEY_new_from_ECCrefPublicKey(&tmppubkey);
	int rv = SM2_verify(NID_undef, hash_value, 32, sign_value, 64, sm2key);
	EC_KEY_free(sm2key);
	cout << hex << rv << endl;
	getchar();
}
unsigned char softpubkey[] = {
	0x00,0x01,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x8e,0x7a,0xf1,0x3a,0x6f,0x1f,0x45,0x7b,0x89,0x7f,0x6d,0x50,0x27,0xb7,0x82,0xd1,
	0xd6,0x65,0x71,0x4b,0x50,0xee,0x94,0x61,0x0a,0x12,0x96,0xdd,0x71,0x13,0x80,0x49,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x6c,0x9f,0xd8,0x98,0xc9,0xaa,0x5f,0xc3,0xa4,0x98,0xf4,0xa9,0x18,0x30,0x1b,0xc5,
	0x02,0x31,0xe1,0x14,0x47,0x3e,0x23,0x77,0x33,0x16,0x89,0x1c,0x9a,0x7a,0xfa,0x25
};
unsigned char softprikey[] = {
	0x00,0x01,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x03,0x5e,0x25,0xe3,0x81,0x85,0x26,0x0e,0x8c,0xa5,0x99,0x74,0x1f,0xd0,0xb5,0x88,
	0x96,0x5c,0x52,0xca,0xf5,0x04,0xe7,0x8c,0xfb,0x1a,0xbb,0x4e,0xa0,0xab,0x7e,0x0c
};



extern int aes_test();
extern int des_test();
extern int crypto_test();
extern int sm4_test1();
extern int sm4_test2();
extern int sm3_test();
extern int hmac_test();
extern int sm4_test();
extern int bio_test();
extern int sm2_generatekey_test(ECCrefPublicKey &pubkey, ECCrefPrivateKey &prikey);
extern int sm2_encdec_test();
void rsa_test();
int rsaencdec_test();
extern void asn1_test1();
extern void asn1_test2();
extern void asn1_test3();


int sm3_test1()
{
	unsigned char data[153] = { 0 };
	for (int i = 0; i < 153; i++)
		data[i] = i;
	unsigned char digest[32] = { 0 };
	sm3_ctx_t test_sm3_ctx;
	memset(&test_sm3_ctx, 0, sizeof(test_sm3_ctx));
	sm3_init(&test_sm3_ctx);
	sm3_update(&test_sm3_ctx, data, sizeof(data));
	sm3_final(&test_sm3_ctx, digest);
	return 0;

}

void myhmac_test()
{
	unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	unsigned char data[8192] = { 0 };
	unsigned char out[32] = { 0 };
	for (int i = 0; i < 8192; i++)
	{
		data[i] = i % 256;
	}
	sm3_hmac_ctx_t hmac_ctx;

	sm3_hmac_init(&hmac_ctx, key, 16);
	sm3_hmac_update(&hmac_ctx, data, 8192);

	sm3_hmac_final(&hmac_ctx, out);



}


int main()
{
	cout << "Hello,Gmssl" << endl;
	myhmac_test();
	asn1_test1();
	asn1_test2();
	asn1_test3();
	cout << "******* BIO test *******" << endl;
	bio_test();
	cout << "******* RSA test *******" << endl;
	rsa_test();
	cout << "******* SM3 test *******" << endl;
	sm3_test();
	//sm3_test1();
	cout << "******* SM4 test *******" << endl;
	sm4_test();
	system("pause");
	aes_test();
	des_test();
	sm4_test1();
	sm2_encdec_test();
	testverify();
	system("pause");
	return 0;
}




