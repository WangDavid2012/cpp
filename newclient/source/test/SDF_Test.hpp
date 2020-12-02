#include "./sdf/SDF.h"
#include "./sdf/SDF_EX.h"

class SDFtest
{
public:
	SDFtest(void * phDeviceHandle, void * phSessionHandle);
	int SocketConnectTest();
	int internalEccTest();
	int randTest();
	int calculateMacTest();
	int kekTest();
	int hashWithPubTest();
	int hashTest();
	int hmacTest();
	int aggrementEccTest();
	int externEccPubKeyTest();
	int pubkeyVerify();
	int externalEccSignVerifyTest();
	int internalEccSignVerifyTest();
	int symEncDecTest();
	int sm1sm4Test();
	int Demo_GenerateRSA();
	void  TEST_ECC();
	int correct_SM2PreVerify();
	int correct_SM2PreSign();
	int SM4_test();
	int externalSignTest();
private:
	void * m_phDeviceHandle;
	void * m_phSessionHandle;
	void * m_phKeyHandle;
	ECCrefPublicKey m_eccpubkey;
	ECCrefPrivateKey m_eccprikey;

	ECCCipher m_Cipher;
	unsigned char  m_inputdata[4096];
	unsigned char  m_outputdata[4096];
};