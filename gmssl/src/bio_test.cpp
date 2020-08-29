#include <stdio.h>
#include "openssl/bio.h"
#include "openssl/evp.h"


int bio_test()
{
	BIO *b = NULL;
	int lenth = 0;
	char *out = NULL;

	b = BIO_new(BIO_s_mem());            //����һ��mem���͵�BIO
	lenth = BIO_write(b, "openssl", 4);  //���ַ���opensslд�뵽bio��
	lenth = BIO_printf(b, "%s", "zcb");
	lenth = BIO_ctrl_pending(b);         //�õ��������д���ȡ���ݵĴ�С
	out = (char *)OPENSSL_malloc(lenth);
	lenth = BIO_read(b, out, lenth);    //���������е����ݶ�ȡ��out��
	OPENSSL_free(out);
	BIO_free(b);
	return 0;
}
/**********************************************************
 * \brief md5�㷨��ѧϰʹ��BIO�ӿ�
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