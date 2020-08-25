#include <stdio.h>
#include "openssl/bio.h"
#include "openssl/evp.h"


int bio_test()
{
	BIO *b = NULL;
	int lenth = 0;
	char *out = NULL;

	b = BIO_new(BIO_s_mem());            //生成一个mem类型的BIO
	lenth = BIO_write(b, "openssl", 4);  //将字符串openssl写入到bio中
	lenth = BIO_printf(b, "%s", "zcb");
	lenth = BIO_ctrl_pending(b);         //得到缓冲区中待读取数据的大小
	out = (char *)OPENSSL_malloc(lenth);
	lenth = BIO_read(b, out, lenth);    //将缓冲区中的数据读取到out中
	OPENSSL_free(out);
	BIO_free(b);
	return 0;
}
/**********************************************************
 * \brief md5算法，学习使用BIO接口
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author wangdavid2012@163.com
 * \history
 * \time 2020/3/6
 ***********************************************************/
void md_bio_test()
{
	BIO *bmd = NULL, *b = NULL;
	const EVP_MD *md = EVP_md5();

	int lenth;
	char tmp[1024];

	bmd = BIO_new(BIO_f_md());
	BIO_set_md(bmd, md);

	b = BIO_new(BIO_s_null());
	b = BIO_push(bmd, b);

	lenth = BIO_write(b, "openssl", 7);
	lenth = BIO_gets(b, tmp, 1024);

	BIO_free(b);



}