#include <openssl/sm3.h>
#include <iostream>
using namespace std;


int hmac_test()
{
	//HMAC ≤‚ ‘
	unsigned char hmac_key[16] = { 0 };
	unsigned char data[8192] = { 0 };
	unsigned char mac[SM3_HMAC_SIZE] = { 0 };
	for (int i = 0; i < 16; i++)
	{
		hmac_key[i] = 0x30 + i;
	}
	sm3_hmac(data, 8192, hmac_key, 16, mac);
	cout << "sm3_hmac 8192byte data :" << endl;
	for (int i = 0; i < 16; i++)
	{
		cout << hex << mac[i] << " " << endl;
	}
	cout << endl;
	return 0;
}