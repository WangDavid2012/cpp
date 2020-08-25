#include "openssl/asn1.h"

/**********************************************************************
 * \brief ����һ�������ʶ��(Object Identifier),Ȼ��ת����ASN.1�����DER��ʽ
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author runwang2020@163.com
 * \history
 * \time 2020/3/9
 *********************************************************************/
void asn1_test1()
{
	const char oid[] = { "2.99999.3" };
	int i;
	unsigned char *buf;

	i = a2d_ASN1_OBJECT(NULL, 0, oid, -1);
	if (i <= 0)
		return;
	buf = (unsigned char *)malloc(sizeof(unsigned char)*i);
	i = a2d_ASN1_OBJECT(buf, i, oid, -1);  //86 8d 6f 03
	free(buf);
	return;
}
/**********************************************************
 * \brief ��bp�е�ASCII��ת����ASN1_INTEGER,buf���BIO�е�ASC��
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author runwang2020@163.com
 * \history
 * \time 2020/3/9
 ***********************************************************/
void asn1_test2()
{

	BIO *bp;
	ASN1_INTEGER *i;
	int retlen = 0;

	char buf[50];
	int size, len;
	bp = BIO_new(BIO_s_mem());
	len = BIO_write(bp, "0FAB08BBDDEECC", 14);
	size = 50;
	i = ASN1_INTEGER_new();
	retlen = a2i_ASN1_INTEGER(bp, i, buf, size);

	BIO_free(bp);
	ASN1_INTEGER_free(i);
}
/**********************************************************
 * \brief ��ascii��ת����ASN1_STRING ����
 *
 * \param[in]
 * \param[out]
 * \return
 *
 * \author runwang2020@163.com
 * \history
 * \time 2020/3/9
 ***********************************************************/
void asn1_test3()
{

	BIO *bp;
	ASN1_STRING *str;
	char buf[50] = { 0 };
	int size, len;
	bp = BIO_new(BIO_s_mem());
	len = BIO_write(bp, "B2E2CAD4", 8);

	size = 50;
	str = ASN1_STRING_new();
	a2i_ASN1_STRING(bp, str, buf, size);

	BIO_free(bp);
	ASN1_STRING_free(str);
}
