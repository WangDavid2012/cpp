#include <openssl/sm3.h>


int sm3_test()
{
	//hash≤‚ ‘
	unsigned char data[8192] = { 0 };
	size_t datalen = 8192;
	unsigned char digest[SM3_DIGEST_LENGTH] = { 0 };
	for (int i = 0; i < datalen; i++)
	{
		data[i] = i % 255;
	}
	sm3(data, datalen, digest);
	return 0;
}