#include <string.h>
#include <time.h>

#include "../sm3/sm3.h"
#include "sm2.h"
#include "sm2_util.h"

#if defined(POLARSSL_PLATFORM_C)
#include "polarssl/platform.h"
#else
#include <stdlib.h>
#define polarssl_malloc     malloc
#define polarssl_free       free
#endif

#include "polarssl/hmac_drbg.h"

static int sm2_rand(void *rng_state, unsigned char *output, size_t len)
{
	size_t use_len;
	int rnd;

	if (rng_state != NULL)
	{
		rng_state = NULL;
	}

	srand((int)time(0));

	while (len > 0)
	{
		use_len = len;
		if (use_len > sizeof(int))
		{
			use_len = sizeof(int);
		}

		rnd = rand();
		memcpy(output, &rnd, use_len);
		output += use_len;
		len -= use_len;
	}

	return 0;
}

//generate the x'=2^w+(x&(2^w-1));
mpi* SM2_getXDOT(mpi *bn, unsigned int uiW)
{
	int	iRtn = 0;

	mpi	*bnXDOT = NULL;

	unsigned char	*pbBN = NULL, *pbXDOT = NULL, *pbMask = NULL;
	unsigned int	uiBNLen = 0, uiXDOTLen = 0, uiMaskLen = 0, i = 0;

	SM2_ASSERT_NEQ_EX(bn, 0, 0);
	SM2_ASSERT_NEQ_EX(uiW, 0, 0);

	uiBNLen = (unsigned int)mpi_size(bn);
	uiXDOTLen = ((uiW+1)+7)/8;
	uiMaskLen = (uiBNLen > uiXDOTLen) ? (uiBNLen) : (uiXDOTLen);

	pbBN = (unsigned char *)polarssl_malloc(uiMaskLen);
	SM2_ASSERT_NEQ_EX(pbBN, 0, 0);
	memset(pbBN, 0, uiMaskLen);
	pbXDOT = (unsigned char *)polarssl_malloc(uiMaskLen);
	SM2_ASSERT_NEQ_EX(pbXDOT, 0, 0);
	memset(pbXDOT, 0, uiMaskLen);
	pbMask = (unsigned char *)polarssl_malloc(uiMaskLen);
	SM2_ASSERT_NEQ_EX(pbMask, 0, 0);
	memset(pbMask, 0xff, uiMaskLen);

	//get pbBN
	iRtn = mpi_write_binary(bn, pbBN + uiMaskLen - uiBNLen, uiMaskLen);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	
	//get pbMask
	for (i=0; i<(uiMaskLen-uiXDOTLen); i++)
	{
		pbMask[i] = 0;
	}
	pbMask[uiMaskLen-uiXDOTLen] = ((0x01 << (uiW % 8)) - 0x01);

	//get pbXDOT
	andData(pbXDOT, pbBN, pbMask, uiMaskLen);
	pbXDOT[uiMaskLen-uiXDOTLen] |= (0x01 << (uiW % 8));

	//get bnXDOT
	bnXDOT = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnXDOT, 0, 0);
	mpi_init(bnXDOT);
	iRtn = mpi_read_binary(bnXDOT, pbXDOT + uiMaskLen - uiXDOTLen, uiXDOTLen);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	
	iRtn = 1;
END:
	if (!iRtn)
	{
		if (bnXDOT)
		{
			mpi_free(bnXDOT);
			polarssl_free(bnXDOT);
			bnXDOT = NULL;
		}
	}
	if (pbBN)
	{
		polarssl_free(pbBN);
		pbBN = NULL;
	}
	if (pbXDOT)
	{
		polarssl_free(pbXDOT);
		pbXDOT = NULL;
	}
	if (pbMask)
	{
		polarssl_free(pbMask);
		pbMask = NULL;
	}

	return bnXDOT;
}

int SM2_genAgreementData(const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
						 const sm2_keypair *eckey_sponsor, const unsigned int uiSessKeyLen, \
						 ecp_point **pubkey_sponsor_tmp, sm2_keypair **eckey_sponsor_tmp)
{
	int iRtn = 0;

	sm2_keypair	*eckey_s_tmp = NULL;
	ecp_point	*pubkey_s_tmp = NULL;

	SM2_ASSERT_NEQ_EX(pbSponsorID, 0, 0);
	SM2_ASSERT_NEQ_EX(uiSponsorIDLen, 0, 0);
	SM2_ASSERT_NEQ_EX(eckey_sponsor, 0, 0);
	SM2_ASSERT_NEQ_EX(uiSessKeyLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pubkey_sponsor_tmp, 0, 0);
	//SM2_ASSERT_EQ_EX(*pubkey_sponsor_tmp, 0, 0);//input must be NULL
	SM2_ASSERT_NEQ_EX(eckey_sponsor_tmp, 0, 0);
	//SM2_ASSERT_EQ_EX(*eckey_sponsor_tmp, 0, 0);//input must be NULL

	iRtn = ecp_check_privkey(&eckey_sponsor->grp, &eckey_sponsor->d);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	iRtn = ecp_check_pubkey(&eckey_sponsor->grp, &eckey_sponsor->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	eckey_s_tmp = (sm2_keypair *)polarssl_malloc(sizeof(sm2_keypair));
	SM2_ASSERT_NEQ_EX(eckey_s_tmp, 0, -1);

	iRtn = SM2_initKeyPair(eckey_s_tmp);
	SM2_ASSERT_EQ_EX(iRtn, 1, -1);
	iRtn = SM2_genKeyPair(eckey_s_tmp);
	SM2_ASSERT_EQ_EX(iRtn, 1, -1);

	pubkey_s_tmp = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
	SM2_ASSERT_NEQ_EX(pubkey_s_tmp, 0, -1);
	ecp_point_init(pubkey_s_tmp);
	iRtn = ecp_copy(pubkey_s_tmp, &eckey_s_tmp->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	*eckey_sponsor_tmp = eckey_s_tmp;
	*pubkey_sponsor_tmp = pubkey_s_tmp;

	iRtn = 1;
END:
	if (!iRtn)
	{
		if (eckey_s_tmp)
		{
			SM2_freeKeyPair(eckey_s_tmp);
			polarssl_free(eckey_s_tmp);
			eckey_s_tmp = 0;
		}

		if (pubkey_s_tmp)
		{
			ecp_point_free(pubkey_s_tmp);
			polarssl_free(pubkey_s_tmp);
			pubkey_s_tmp = 0;
		}

		*eckey_sponsor_tmp = NULL;
		*pubkey_sponsor_tmp = NULL;
	}

	return iRtn;
}

int SM2_genAgreementDataAndKey(const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
							   const unsigned char *pbReceiverID, const unsigned int uiReceiverIDLen, \
							   const ecp_point *pubkey_sponsor, const ecp_point *pubkey_sponsor_tmp, \
							   const sm2_keypair *eckey_receiver, const unsigned int uiSessKeyLen, \
							   ecp_point **pubkey_receiver_tmp, sm2_keypair **eckey_receiver_tmp, \
							   unsigned char *pbSessKey, unsigned char *pbSB, unsigned char *pbS2)
{
	int iRtn = 0;

	sm2_keypair	*eckey_r_tmp = NULL, *eckey_z = NULL;
	ecp_point	*ptV = NULL;
	ecp_point	*pub_r_tmp = NULL;
	ecp_point	*ptTmp = NULL;

	unsigned int	uiKeyLen = 0, uiKeyBitLen = 0, uiW = 0;

	hmac_drbg_context	*rng_ctx = 0;
	const md_info_t	*md_info = 0;

	mpi	*bnX1DOT = NULL, *bnX2DOT = NULL;
	mpi	*pmpiTmp = NULL, *pmpiTB = NULL, *pmpiH = NULL;

	unsigned char	*pbZData = NULL;
	unsigned int	uiZLen = 0, uiZDataLen = 0;

	SM2_ASSERT_NEQ_EX(pbReceiverID, 0, 0);
	SM2_ASSERT_NEQ_EX(uiReceiverIDLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pbSponsorID, 0, 0);
	SM2_ASSERT_NEQ_EX(uiSponsorIDLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pubkey_sponsor, 0, 0);
	SM2_ASSERT_NEQ_EX(pubkey_sponsor_tmp, 0, 0);
	SM2_ASSERT_NEQ_EX(eckey_receiver, 0, 0);
	SM2_ASSERT_NEQ_EX(uiSessKeyLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pubkey_receiver_tmp, 0, 0);
	//SM2_ASSERT_EQ_EX(*pubkey_receiver_tmp, 0, 0);//input must be NULL
	SM2_ASSERT_NEQ_EX(eckey_receiver_tmp, 0, 0);
	//SM2_ASSERT_EQ_EX(*eckey_receiver_tmp, 0, 0);//input must be NULL
	SM2_ASSERT_NEQ_EX(pbSessKey, 0, 0);

	iRtn = ecp_check_privkey(&eckey_receiver->grp, &eckey_receiver->d);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	iRtn = ecp_check_pubkey(&eckey_receiver->grp, &eckey_receiver->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	iRtn = ecp_check_pubkey(&eckey_receiver->grp, pubkey_sponsor);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	iRtn = ecp_check_pubkey(&eckey_receiver->grp, pubkey_sponsor_tmp);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	pmpiTmp = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(pmpiTmp, 0, 0);
	mpi_init(pmpiTmp);

	pmpiTB = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(pmpiTB, 0, 0);
	mpi_init(pmpiTB);

	pmpiH = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(pmpiH, 0, 0);
	mpi_init(pmpiH);

	ptTmp = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
	SM2_ASSERT_NEQ_EX(ptTmp, 0, 0);
	ecp_point_init(ptTmp);

	ptV = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
	SM2_ASSERT_NEQ_EX(ptV, 0, 0);
	ecp_point_init(ptV);

	pub_r_tmp = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
	SM2_ASSERT_NEQ_EX(pub_r_tmp, 0, 0);
	ecp_point_init(pub_r_tmp);

	//set random context
	md_info = md_info_from_type(POLARSSL_MD_SHA256);
	SM2_ASSERT_NEQ_EX(md_info, 0, 0);
	rng_ctx = (hmac_drbg_context*)polarssl_malloc(sizeof(hmac_drbg_context));
	SM2_ASSERT_NEQ_EX(rng_ctx, 0, 0);
	iRtn = hmac_drbg_init(rng_ctx, md_info, sm2_rand, 0, 0, 0);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//generate key
	eckey_r_tmp = (sm2_keypair *)polarssl_malloc(sizeof(sm2_keypair));
	SM2_ASSERT_NEQ_EX(eckey_r_tmp, 0, -1);
	iRtn = SM2_initKeyPair(eckey_r_tmp);
	SM2_ASSERT_EQ_EX(iRtn, 1, -1);
	iRtn = SM2_genKeyPair(eckey_r_tmp);
	SM2_ASSERT_EQ_EX(iRtn, 1, -1);

	//calc x2'
	uiKeyLen = (unsigned int)((eckey_receiver->grp.nbits + 7) / 8);
	uiKeyBitLen = uiKeyLen * 8;
	uiW = ((uiKeyBitLen + 1) / 2 - 1);
	bnX2DOT = SM2_getXDOT(&eckey_r_tmp->Q.X, uiW);
	SM2_ASSERT_NEQ_EX(bnX2DOT, 0, 0);

	//calc tB=(dB + x2'*rB) mod n
	//Tmp = x2'*rB mod N
	iRtn = mpi_mul_mpi(pmpiTmp, bnX2DOT, &eckey_r_tmp->d);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mod_mpi(pmpiTmp, pmpiTmp, &eckey_r_tmp->grp.N);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//tB = dB+Tmp mod N
	iRtn = mpi_add_mpi(pmpiTB, &eckey_receiver->d, pmpiTmp);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mod_mpi(pmpiTB, pmpiTB, &eckey_r_tmp->grp.N);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//calc x1'
	bnX1DOT = SM2_getXDOT(&pubkey_sponsor_tmp->X, uiW);
	SM2_ASSERT_NEQ_EX(bnX1DOT, 0, 0);

	//calc V=[h*tB](PA+[x1']RA) and check V not be infinite
	//ptTmp=[x1']RA
	iRtn = ecp_mul(&eckey_receiver->grp, ptTmp, bnX1DOT, pubkey_sponsor_tmp, hmac_drbg_random, rng_ctx);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//ptTmp=ptTmp+PA
	iRtn = ecp_add(&eckey_receiver->grp, ptTmp, ptTmp, pubkey_sponsor);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//bnTmp=h*tB
	iRtn = mpi_set_bit(pmpiH, 0, 1);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mul_mpi(pmpiTmp, pmpiTB, pmpiH);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//ptV=[bnTmp]ptTmp
	iRtn = ecp_mul(&eckey_receiver->grp, ptV, pmpiTmp, ptTmp, hmac_drbg_random, rng_ctx);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	
	//get pbZData, prepare the data of KDF
	uiZDataLen = 2 * uiKeyLen + 2 * SM3_DIGEST_LENGTH;//xV || yV || ZA || ZB
	pbZData = (unsigned char *)polarssl_malloc(uiZDataLen);
	SM2_ASSERT_NEQ_EX(pbZData, 0, 0);
	iRtn = mpi_write_binary(&ptV->X, pbZData, uiKeyLen);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_write_binary(&ptV->Y, pbZData + uiKeyLen, uiKeyLen);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//calc ZA=Hash(IDLA || IDA || a || b || xG || yG || xA || yA)
	eckey_z = (sm2_keypair *)polarssl_malloc(sizeof(sm2_keypair));
	SM2_ASSERT_NEQ_EX(eckey_z, 0, -1);
	iRtn = SM2_initKeyPair(eckey_z);
	SM2_ASSERT_EQ_EX(iRtn, 1, -1);
	iRtn = ecp_group_copy(&eckey_z->grp, &eckey_receiver->grp);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	iRtn = ecp_copy(&eckey_z->Q, pubkey_sponsor);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	uiZLen = SM3_DIGEST_LENGTH;
	iRtn = SM2_getZ(pbSponsorID, uiSponsorIDLen, pbZData + 2 * uiKeyLen, &uiZLen, eckey_z);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	//calc ZB=Hash(IDLB || IDB || a || b || xG || yG || xB || yB)
	iRtn = ecp_copy(&eckey_z->Q, &eckey_receiver->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	uiZLen = SM3_DIGEST_LENGTH;
	iRtn = SM2_getZ(pbReceiverID, uiReceiverIDLen, pbZData + 2 * uiKeyLen + SM3_DIGEST_LENGTH, &uiZLen, eckey_z);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	//calc KB=KDF(xV || yV || ZA || ZB, uiSessKeyLen)
	iRtn = SM2_KDF(pbZData, uiZDataLen, pbSessKey, uiSessKeyLen, 1);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	iRtn = ecp_copy(pub_r_tmp, &eckey_r_tmp->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	*eckey_receiver_tmp = eckey_r_tmp;
	*pubkey_receiver_tmp = pub_r_tmp;

	iRtn = 1;
END:
	if (!iRtn)
	{
		if (eckey_r_tmp)
		{
			SM2_freeKeyPair(eckey_r_tmp);
			polarssl_free(eckey_r_tmp);
			eckey_r_tmp = 0;
		}

		if (pub_r_tmp)
		{
			ecp_point_free(pub_r_tmp);
			polarssl_free(pub_r_tmp);
			pub_r_tmp = 0;
		}

		*eckey_receiver_tmp = NULL;
		*pubkey_receiver_tmp = NULL;
	}

	if (eckey_z)
	{
		SM2_freeKeyPair(eckey_z);
		polarssl_free(eckey_z);
		eckey_z = 0;
	}

	if (bnX1DOT)
	{
		mpi_free(bnX1DOT);
		polarssl_free(bnX1DOT);
		bnX1DOT = NULL;
	}

	if (bnX2DOT)
	{
		mpi_free(bnX2DOT);
		polarssl_free(bnX2DOT);
		bnX2DOT = NULL;
	}

	if (pmpiTmp)
	{
		mpi_free(pmpiTmp);
		polarssl_free(pmpiTmp);
		pmpiTmp = NULL;
	}

	if (pmpiH)
	{
		mpi_free(pmpiH);
		polarssl_free(pmpiH);
		pmpiH = NULL;
	}

	if (pmpiTB)
	{
		mpi_free(pmpiTB);
		polarssl_free(pmpiTB);
		pmpiTB = NULL;
	}

	if (ptTmp)
	{
		ecp_point_free(ptTmp);
		polarssl_free(ptTmp);
		ptTmp = NULL;
	}

	if (ptV)
	{
		ecp_point_free(ptV);
		polarssl_free(ptV);
		ptV = NULL;
	}

	if (pbZData)
	{
		polarssl_free(pbZData);
		pbZData = NULL;
	}

	if (rng_ctx)
	{
		hmac_drbg_free(rng_ctx);
		free(rng_ctx);
		rng_ctx = 0;
	}

	return iRtn;
}

int SM2_genKey(const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
			   const unsigned char *pbReceiverID, const unsigned int uiReceiverIDLen, \
			   const ecp_point *pubkey_receiver, const ecp_point *pubkey_receiver_tmp, \
			   const sm2_keypair *eckey_sponsor, const sm2_keypair *eckey_tmp_sponsor, \
			   const unsigned int uiSessKeyLen, unsigned char *pbSessKey, \
			   const unsigned char *pbSB, unsigned char *pbSA)
{
	int iRtn = 0;

	hmac_drbg_context	*rng_ctx = 0;
	const md_info_t	*md_info = 0;

	sm2_keypair	*eckey_z = NULL;

	mpi	*bnX1DOT = NULL, *bnX2DOT = NULL;
	mpi	*bnTA = NULL;
	mpi	*bnN = NULL, *bnH = NULL;
	mpi	*bnTmp = NULL;

	ecp_point	*ptU = NULL, *ptTmp = NULL;

	unsigned char	*pbZData = NULL;
	unsigned int	uiKeyLen = 0, uiKeyBitLen = 0, uiW = 0, uiZDataLen = 0, uiZLen = 0;

	SM2_ASSERT_NEQ_EX(pbSponsorID, 0, 0);
	SM2_ASSERT_NEQ_EX(uiSponsorIDLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pbReceiverID, 0, 0);
	SM2_ASSERT_NEQ_EX(uiReceiverIDLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pubkey_receiver, 0, 0);
	SM2_ASSERT_NEQ_EX(pubkey_receiver_tmp, 0, 0);
	SM2_ASSERT_NEQ_EX(eckey_sponsor, 0, 0);
	SM2_ASSERT_NEQ_EX(eckey_tmp_sponsor, 0, 0);
	SM2_ASSERT_NEQ_EX(uiSessKeyLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pbSessKey, 0, 0);

	bnTA = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnTA, 0, 0);
	mpi_init(bnTA);

	bnN = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnN, 0, 0);
	mpi_init(bnN);

	bnH = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnH, 0, 0);
	mpi_init(bnH);

	bnTmp = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnTmp, 0, 0);
	mpi_init(bnTmp);

	ptU = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
	SM2_ASSERT_NEQ_EX(ptU, 0, 0);
	ecp_point_init(ptU);

	ptTmp = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
	SM2_ASSERT_NEQ_EX(ptTmp, 0, 0);
	ecp_point_init(ptTmp);

	iRtn = ecp_check_privkey(&eckey_sponsor->grp, &eckey_sponsor->d);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	iRtn = ecp_check_pubkey(&eckey_sponsor->grp, &eckey_sponsor->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	iRtn = ecp_check_pubkey(&eckey_sponsor->grp, pubkey_receiver);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	iRtn = ecp_check_pubkey(&eckey_sponsor->grp, pubkey_receiver_tmp);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//set random context
	md_info = md_info_from_type(POLARSSL_MD_SHA256);
	SM2_ASSERT_NEQ_EX(md_info, 0, 0);
	rng_ctx = (hmac_drbg_context*)polarssl_malloc(sizeof(hmac_drbg_context));
	SM2_ASSERT_NEQ_EX(rng_ctx, 0, 0);
	iRtn = hmac_drbg_init(rng_ctx, md_info, sm2_rand, 0, 0, 0);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//calc x1'
	uiKeyLen = (unsigned int)((eckey_sponsor->grp.nbits + 7) / 8);
	uiKeyBitLen = uiKeyLen * 8;
	uiW = ((uiKeyBitLen + 1) / 2 - 1);
	bnX1DOT = SM2_getXDOT(&eckey_tmp_sponsor->Q.X, uiW);
	SM2_ASSERT_NEQ_EX(bnX1DOT, 0, 0);

	//calc tA=(dA+x1'*rA) mod n
	//Tmp = x1'*rA mod N
	iRtn = mpi_mul_mpi(bnTmp, bnX1DOT, &eckey_tmp_sponsor->d);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mod_mpi(bnTmp, bnTmp, &eckey_tmp_sponsor->grp.N);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//tA = dA+Tmp mod N
	iRtn = mpi_add_mpi(bnTA, &eckey_sponsor->d, bnTmp);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mod_mpi(bnTA, bnTA, &eckey_sponsor->grp.N);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//cakc x2'
	bnX2DOT = SM2_getXDOT(&pubkey_receiver_tmp->X, uiW);
	SM2_ASSERT_NEQ_EX(bnX2DOT, 0, 0);

	//calc U=[h*tA](PB + [x2']RB) and check U not be infinite
	//ptTmp=[x2']RB
	iRtn = ecp_mul(&eckey_sponsor->grp, ptTmp, bnX2DOT, pubkey_receiver_tmp, hmac_drbg_random, rng_ctx);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//ptTmp=ptTmp+PB
	iRtn = ecp_add(&eckey_sponsor->grp, ptTmp, ptTmp, pubkey_receiver);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//bnTmp=h*tA
	iRtn = mpi_set_bit(bnH, 0, 1);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mul_mpi(bnTmp, bnTA, bnH);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//ptU=[bnTmp]ptTmp
	iRtn = ecp_mul(&eckey_sponsor->grp, ptU, bnTmp, ptTmp, hmac_drbg_random, rng_ctx);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	if (mpi_cmp_int(&ptU->Z, 0) == 0)
	{
		iRtn = 0;
		goto END;
	}

	//get pbZData, prepare the data of KDF
	uiZDataLen = 2*uiKeyLen + 2*SM3_DIGEST_LENGTH;//xU || yU || ZA || ZB
	pbZData = (unsigned char *)polarssl_malloc(uiZDataLen);
	SM2_ASSERT_NEQ_EX(pbZData, 0, 0);
	iRtn = mpi_write_binary(&ptU->X, pbZData, uiKeyLen);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_write_binary(&ptU->Y, pbZData + uiKeyLen, uiKeyLen);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//calc ZA=Hash(IDLA || IDA || a || b || xG || yG || xA || yA)
	eckey_z = (sm2_keypair *)polarssl_malloc(sizeof(sm2_keypair));
	SM2_ASSERT_NEQ_EX(eckey_z, 0, -1);
	iRtn = SM2_initKeyPair(eckey_z);
	SM2_ASSERT_EQ_EX(iRtn, 1, -1);
	iRtn = ecp_group_copy(&eckey_z->grp, &eckey_sponsor->grp);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	iRtn = ecp_copy(&eckey_z->Q, &eckey_sponsor->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	uiZLen = SM3_DIGEST_LENGTH;
	iRtn = SM2_getZ(pbSponsorID, uiSponsorIDLen, pbZData + 2 * uiKeyLen, &uiZLen, eckey_z);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	//calc ZB=Hash(IDLB || IDB || a || b || xG || yG || xB || yB)
	iRtn = ecp_copy(&eckey_z->Q, pubkey_receiver);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	uiZLen = SM3_DIGEST_LENGTH;
	iRtn = SM2_getZ(pbReceiverID, uiReceiverIDLen, pbZData + 2 * uiKeyLen + SM3_DIGEST_LENGTH, &uiZLen, eckey_z);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	//calc KB=KDF(xV || yV || ZA || ZB, uiSessKeyLen)
	iRtn = SM2_KDF(pbZData, uiZDataLen, pbSessKey, uiSessKeyLen, 1);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	iRtn = 1;
END:
	if (bnX1DOT)
	{
		mpi_free(bnX1DOT);
		polarssl_free(bnX1DOT);
		bnX1DOT = NULL;
	}
	if (bnX2DOT)
	{
		mpi_free(bnX2DOT);
		polarssl_free(bnX2DOT);
		bnX2DOT = NULL;
	}
	if (bnTA)
	{
		mpi_free(bnTA);
		polarssl_free(bnTA);
		bnTA = NULL;
	}
	if (bnN)
	{
		mpi_free(bnN);
		polarssl_free(bnN);
		bnN = NULL;
	}
	if (bnH)
	{
		mpi_free(bnH);
		polarssl_free(bnH);
		bnH = NULL;
	}
	if (bnTmp)
	{
		mpi_free(bnTmp);
		polarssl_free(bnTmp);
		bnTmp = NULL;
	}

	if (ptU)
	{
		ecp_point_free(ptU);
		polarssl_free(ptU);
		ptU = NULL;
	}
	if (ptTmp)
	{
		ecp_point_free(ptTmp);
		polarssl_free(ptTmp);
		ptTmp = NULL;
	}

	if (eckey_z)
	{
		SM2_freeKeyPair(eckey_z);
		polarssl_free(eckey_z);
		eckey_z = 0;
	}

	if (rng_ctx)
	{
		hmac_drbg_free(rng_ctx);
		polarssl_free(rng_ctx);
		rng_ctx = 0;
	}

	if (pbZData)
	{
		polarssl_free(pbZData);
		pbZData = NULL;
	}
	return iRtn;
}

int SM2_genKey_Symm(const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
	const unsigned char *pbReceiverID, const unsigned int uiReceiverIDLen, \
	const ecp_point *pubkey_receiver, const ecp_point *pubkey_receiver_tmp, \
	const sm2_keypair *eckey_sponsor, const sm2_keypair *eckey_tmp_sponsor, \
	const unsigned int uiSessKeyLen, unsigned char *pbSessKey, \
	const unsigned char *pbSB, unsigned char *pbSA)
{
	int iRtn = 0;

	hmac_drbg_context	*rng_ctx = 0;
	const md_info_t	*md_info = 0;

	sm2_keypair	*eckey_z = NULL;

	mpi	*bnX1DOT = NULL, *bnX2DOT = NULL;
	mpi	*bnTA = NULL;
	mpi	*bnN = NULL, *bnH = NULL;
	mpi	*bnTmp = NULL;

	ecp_point	*ptU = NULL, *ptTmp = NULL;

	unsigned char	*pbZData = NULL;
	unsigned int	uiKeyLen = 0, uiKeyBitLen = 0, uiW = 0, uiZDataLen = 0, uiZLen = 0;

	SM2_ASSERT_NEQ_EX(pbSponsorID, 0, 0);
	SM2_ASSERT_NEQ_EX(uiSponsorIDLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pbReceiverID, 0, 0);
	SM2_ASSERT_NEQ_EX(uiReceiverIDLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pubkey_receiver, 0, 0);
	SM2_ASSERT_NEQ_EX(pubkey_receiver_tmp, 0, 0);
	SM2_ASSERT_NEQ_EX(eckey_sponsor, 0, 0);
	SM2_ASSERT_NEQ_EX(eckey_tmp_sponsor, 0, 0);
	SM2_ASSERT_NEQ_EX(uiSessKeyLen, 0, 0);
	SM2_ASSERT_NEQ_EX(pbSessKey, 0, 0);

	bnTA = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnTA, 0, 0);
	mpi_init(bnTA);

	bnN = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnN, 0, 0);
	mpi_init(bnN);

	bnH = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnH, 0, 0);
	mpi_init(bnH);

	bnTmp = (mpi *)polarssl_malloc(sizeof(mpi));
	SM2_ASSERT_NEQ_EX(bnTmp, 0, 0);
	mpi_init(bnTmp);

	ptU = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
	SM2_ASSERT_NEQ_EX(ptU, 0, 0);
	ecp_point_init(ptU);

	ptTmp = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
	SM2_ASSERT_NEQ_EX(ptTmp, 0, 0);
	ecp_point_init(ptTmp);

	iRtn = ecp_check_privkey(&eckey_sponsor->grp, &eckey_sponsor->d);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	iRtn = ecp_check_pubkey(&eckey_sponsor->grp, &eckey_sponsor->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);

	iRtn = ecp_check_pubkey(&eckey_sponsor->grp, pubkey_receiver);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	iRtn = ecp_check_pubkey(&eckey_sponsor->grp, pubkey_receiver_tmp);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//set random context
	md_info = md_info_from_type(POLARSSL_MD_SHA256);
	SM2_ASSERT_NEQ_EX(md_info, 0, 0);
	rng_ctx = (hmac_drbg_context*)polarssl_malloc(sizeof(hmac_drbg_context));
	SM2_ASSERT_NEQ_EX(rng_ctx, 0, 0);
	iRtn = hmac_drbg_init(rng_ctx, md_info, sm2_rand, 0, 0, 0);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//calc x1'
	uiKeyLen = (unsigned int)((eckey_sponsor->grp.nbits + 7) / 8);
	uiKeyBitLen = uiKeyLen * 8;
	uiW = ((uiKeyBitLen + 1) / 2 - 1);
	bnX1DOT = SM2_getXDOT(&eckey_tmp_sponsor->Q.X, uiW);
	SM2_ASSERT_NEQ_EX(bnX1DOT, 0, 0);

	//calc tA=(dA+x1'*rA) mod n
	//Tmp = x1'*rA mod N
	iRtn = mpi_mul_mpi(bnTmp, bnX1DOT, &eckey_tmp_sponsor->d);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mod_mpi(bnTmp, bnTmp, &eckey_tmp_sponsor->grp.N);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//tA = dA+Tmp mod N
	iRtn = mpi_add_mpi(bnTA, &eckey_sponsor->d, bnTmp);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mod_mpi(bnTA, bnTA, &eckey_sponsor->grp.N);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//cakc x2'
	bnX2DOT = SM2_getXDOT(&pubkey_receiver_tmp->X, uiW);
	SM2_ASSERT_NEQ_EX(bnX2DOT, 0, 0);

	//calc U=[h*tA](PB + [x2']RB) and check U not be infinite
	//ptTmp=[x2']RB
	iRtn = ecp_mul(&eckey_sponsor->grp, ptTmp, bnX2DOT, pubkey_receiver_tmp, hmac_drbg_random, rng_ctx);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//ptTmp=ptTmp+PB
	iRtn = ecp_add(&eckey_sponsor->grp, ptTmp, ptTmp, pubkey_receiver);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//bnTmp=h*tA
	iRtn = mpi_set_bit(bnH, 0, 1);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_mul_mpi(bnTmp, bnTA, bnH);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	//ptU=[bnTmp]ptTmp
	iRtn = ecp_mul(&eckey_sponsor->grp, ptU, bnTmp, ptTmp, hmac_drbg_random, rng_ctx);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	if (mpi_cmp_int(&ptU->Z, 0) == 0)
	{
		iRtn = 0;
		goto END;
	}

	//get pbZData, prepare the data of KDF
	uiZDataLen = 2 * uiKeyLen + 2 * SM3_DIGEST_LENGTH;//xU || yU || ZA || ZB
	pbZData = (unsigned char *)polarssl_malloc(uiZDataLen);
	SM2_ASSERT_NEQ_EX(pbZData, 0, 0);
	iRtn = mpi_write_binary(&ptU->X, pbZData, uiKeyLen);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
	iRtn = mpi_write_binary(&ptU->Y, pbZData + uiKeyLen, uiKeyLen);
	SM2_ASSERT_EQ_EX(iRtn, 0, 0);

	//calc ZA=Hash(IDLA || IDA || a || b || xG || yG || xA || yA)
	eckey_z = (sm2_keypair *)polarssl_malloc(sizeof(sm2_keypair));
	SM2_ASSERT_NEQ_EX(eckey_z, 0, -1);
	iRtn = SM2_initKeyPair(eckey_z);
	SM2_ASSERT_EQ_EX(iRtn, 1, -1);
	iRtn = ecp_group_copy(&eckey_z->grp, &eckey_sponsor->grp);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	iRtn = ecp_copy(&eckey_z->Q, &eckey_sponsor->Q);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	uiZLen = SM3_DIGEST_LENGTH;
	iRtn = SM2_getZ(pbSponsorID, uiSponsorIDLen, pbZData + 2 * uiKeyLen, &uiZLen, eckey_z);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	//calc ZB=Hash(IDLB || IDB || a || b || xG || yG || xB || yB)
	iRtn = ecp_copy(&eckey_z->Q, pubkey_receiver);
	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
	uiZLen = SM3_DIGEST_LENGTH;
	iRtn = SM2_getZ(pbReceiverID, uiReceiverIDLen, pbZData + 2 * uiKeyLen + SM3_DIGEST_LENGTH, &uiZLen, eckey_z);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	//calc KB=KDF(xV || yV || ZA || ZB, uiSessKeyLen)
	iRtn = SM2_KDF(pbZData, uiZDataLen, pbSessKey, uiSessKeyLen, 1);
	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);

	iRtn = 1;
END:
	if (bnX1DOT)
	{
		mpi_free(bnX1DOT);
		polarssl_free(bnX1DOT);
		bnX1DOT = NULL;
	}
	if (bnX2DOT)
	{
		mpi_free(bnX2DOT);
		polarssl_free(bnX2DOT);
		bnX2DOT = NULL;
	}
	if (bnTA)
	{
		mpi_free(bnTA);
		polarssl_free(bnTA);
		bnTA = NULL;
	}
	if (bnN)
	{
		mpi_free(bnN);
		polarssl_free(bnN);
		bnN = NULL;
	}
	if (bnH)
	{
		mpi_free(bnH);
		polarssl_free(bnH);
		bnH = NULL;
	}
	if (bnTmp)
	{
		mpi_free(bnTmp);
		polarssl_free(bnTmp);
		bnTmp = NULL;
	}

	if (ptU)
	{
		ecp_point_free(ptU);
		polarssl_free(ptU);
		ptU = NULL;
	}
	if (ptTmp)
	{
		ecp_point_free(ptTmp);
		polarssl_free(ptTmp);
		ptTmp = NULL;
	}

	if (eckey_z)
	{
		SM2_freeKeyPair(eckey_z);
		polarssl_free(eckey_z);
		eckey_z = 0;
	}

	if (rng_ctx)
	{
		hmac_drbg_free(rng_ctx);
		polarssl_free(rng_ctx);
		rng_ctx = 0;
	}

	if (pbZData)
	{
		polarssl_free(pbZData);
		pbZData = NULL;
	}
	return iRtn;
}

// int SM2_genKey_Symm(const unsigned char *pbReceiverID, const unsigned int uiReceiverIDLen, \
// 	const unsigned char *pbSponsorID, const unsigned int uiSponsorIDLen, \
// 	const ecp_point *pubkey_sponsor, const ecp_point *pubkey_sponsor_tmp, \
// 	const sm2_keypair *eckey_receiver, const sm2_keypair *eckey_tmp_receiver, \
// 	const unsigned int uiSessKeyLen, unsigned char *pbSessKey, \
// 	const unsigned char *pbSB, unsigned char *pbSA)
// {
// 	int iRtn = 0;
// 
// 	hmac_drbg_context	*rng_ctx = 0;
// 	const md_info_t	*md_info = 0;
// 
// 	sm2_keypair	*eckey_z = NULL;
// 
// 	mpi	*bnX1DOT = NULL, *bnX2DOT = NULL;
// 	mpi	*bnTA = NULL;
// 	mpi	*bnN = NULL, *bnH = NULL;
// 	mpi	*bnTmp = NULL;
// 
// 	ecp_point	*ptU = NULL, *ptTmp = NULL;
// 
// 	unsigned char	*pbZData = NULL;
// 	unsigned int	uiKeyLen = 0, uiKeyBitLen = 0, uiW = 0, uiZDataLen = 0, uiZLen = 0;
// 
// 	SM2_ASSERT_NEQ_EX(pbSponsorID, 0, 0);
// 	SM2_ASSERT_NEQ_EX(uiSponsorIDLen, 0, 0);
// 	SM2_ASSERT_NEQ_EX(pbReceiverID, 0, 0);
// 	SM2_ASSERT_NEQ_EX(uiReceiverIDLen, 0, 0);
// 	SM2_ASSERT_NEQ_EX(pubkey_sponsor, 0, 0);
// 	SM2_ASSERT_NEQ_EX(pubkey_sponsor_tmp, 0, 0);
// 	SM2_ASSERT_NEQ_EX(eckey_receiver, 0, 0);
// 	SM2_ASSERT_NEQ_EX(eckey_tmp_receiver, 0, 0);
// 	SM2_ASSERT_NEQ_EX(uiSessKeyLen, 0, 0);
// 	SM2_ASSERT_NEQ_EX(pbSessKey, 0, 0);
// 
// 	bnTA = (mpi *)polarssl_malloc(sizeof(mpi));
// 	SM2_ASSERT_NEQ_EX(bnTA, 0, 0);
// 	mpi_init(bnTA);
// 
// 	bnN = (mpi *)polarssl_malloc(sizeof(mpi));
// 	SM2_ASSERT_NEQ_EX(bnN, 0, 0);
// 	mpi_init(bnN);
// 
// 	bnH = (mpi *)polarssl_malloc(sizeof(mpi));
// 	SM2_ASSERT_NEQ_EX(bnH, 0, 0);
// 	mpi_init(bnH);
// 
// 	bnTmp = (mpi *)polarssl_malloc(sizeof(mpi));
// 	SM2_ASSERT_NEQ_EX(bnTmp, 0, 0);
// 	mpi_init(bnTmp);
// 
// 	ptU = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
// 	SM2_ASSERT_NEQ_EX(ptU, 0, 0);
// 	ecp_point_init(ptU);
// 
// 	ptTmp = (ecp_point *)polarssl_malloc(sizeof(ecp_point));
// 	SM2_ASSERT_NEQ_EX(ptTmp, 0, 0);
// 	ecp_point_init(ptTmp);
// 
// 	iRtn = ecp_check_privkey(&eckey_receiver->grp, &eckey_receiver->d);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
// 
// 	iRtn = ecp_check_pubkey(&eckey_receiver->grp, &eckey_receiver->Q);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
// 
// 	iRtn = ecp_check_pubkey(&eckey_receiver->grp, pubkey_sponsor);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 
// 	iRtn = ecp_check_pubkey(&eckey_receiver->grp, pubkey_sponsor_tmp);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 
// 	//set random context
// 	md_info = md_info_from_type(POLARSSL_MD_SHA256);
// 	SM2_ASSERT_NEQ_EX(md_info, 0, 0);
// 	rng_ctx = (hmac_drbg_context*)polarssl_malloc(sizeof(hmac_drbg_context));
// 	SM2_ASSERT_NEQ_EX(rng_ctx, 0, 0);
// 	iRtn = hmac_drbg_init(rng_ctx, md_info, sm2_rand, 0, 0, 0);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 
// 	//calc x1'
// 	uiKeyLen = (unsigned int)((eckey_receiver->grp.nbits + 7) / 8);
// 	uiKeyBitLen = uiKeyLen * 8;
// 	uiW = ((uiKeyBitLen + 1) / 2 - 1);
// 	bnX1DOT = SM2_getXDOT(&eckey_tmp_receiver->Q.X, uiW);
// 	SM2_ASSERT_NEQ_EX(bnX1DOT, 0, 0);
// 
// 	//calc tA=(dA+x1'*rA) mod n
// 	//Tmp = x1'*rA mod N
// 	iRtn = mpi_mul_mpi(bnTmp, bnX1DOT, &eckey_tmp_receiver->d);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	iRtn = mpi_mod_mpi(bnTmp, bnTmp, &eckey_tmp_receiver->grp.N);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	//tA = dA+Tmp mod N
// 	iRtn = mpi_add_mpi(bnTA, &eckey_receiver->d, bnTmp);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	iRtn = mpi_mod_mpi(bnTA, bnTA, &eckey_receiver->grp.N);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 
// 	//cakc x2'
// 	bnX2DOT = SM2_getXDOT(&pubkey_sponsor_tmp->X, uiW);
// 	SM2_ASSERT_NEQ_EX(bnX2DOT, 0, 0);
// 
// 	//calc U=[h*tA](PB + [x2']RB) and check U not be infinite
// 	//ptTmp=[x2']RB
// 	iRtn = ecp_mul(&eckey_receiver->grp, ptTmp, bnX2DOT, pubkey_sponsor_tmp, hmac_drbg_random, rng_ctx);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	//ptTmp=ptTmp+PB
// 	iRtn = ecp_add(&eckey_receiver->grp, ptTmp, ptTmp, pubkey_sponsor);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	//bnTmp=h*tA
// 	iRtn = mpi_set_bit(bnH, 0, 1);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	iRtn = mpi_mul_mpi(bnTmp, bnTA, bnH);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	//ptU=[bnTmp]ptTmp
// 	iRtn = ecp_mul(&eckey_receiver->grp, ptU, bnTmp, ptTmp, hmac_drbg_random, rng_ctx);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	if (mpi_cmp_int(&ptU->Z, 0) == 0)
// 	{
// 		iRtn = 0;
// 		goto END;
// 	}
// 
// 	//get pbZData, prepare the data of KDF
// 	uiZDataLen = 2 * uiKeyLen + 2 * SM3_DIGEST_LENGTH;//xU || yU || ZA || ZB
// 	pbZData = (unsigned char *)polarssl_malloc(uiZDataLen);
// 	SM2_ASSERT_NEQ_EX(pbZData, 0, 0);
// 	iRtn = mpi_write_binary(&ptU->X, pbZData, uiKeyLen);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 	iRtn = mpi_write_binary(&ptU->Y, pbZData + uiKeyLen, uiKeyLen);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, 0);
// 
// 	//calc ZA=Hash(IDLA || IDA || a || b || xG || yG || xA || yA)
// 	eckey_z = (sm2_keypair *)polarssl_malloc(sizeof(sm2_keypair));
// 	SM2_ASSERT_NEQ_EX(eckey_z, 0, -1);
// 	iRtn = SM2_initKeyPair(eckey_z);
// 	SM2_ASSERT_EQ_EX(iRtn, 1, -1);
// 	iRtn = ecp_group_copy(&eckey_z->grp, &eckey_receiver->grp);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
// 	iRtn = ecp_copy(&eckey_z->Q, &eckey_receiver->Q);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
// 	uiZLen = SM3_DIGEST_LENGTH;
// 	iRtn = SM2_getZ(pbSponsorID, uiSponsorIDLen, pbZData + 2 * uiKeyLen, &uiZLen, eckey_z);
// 	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);
// 
// 	//calc ZB=Hash(IDLB || IDB || a || b || xG || yG || xB || yB)
// 	iRtn = ecp_copy(&eckey_z->Q, pubkey_sponsor);
// 	SM2_ASSERT_EQ_EX(iRtn, 0, -1);
// 	uiZLen = SM3_DIGEST_LENGTH;
// 	iRtn = SM2_getZ(pbReceiverID, uiReceiverIDLen, pbZData + 2 * uiKeyLen + SM3_DIGEST_LENGTH, &uiZLen, eckey_z);
// 	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);
// 
// 	//calc KB=KDF(xV || yV || ZA || ZB, uiSessKeyLen)
// 	iRtn = SM2_KDF(pbZData, uiZDataLen, pbSessKey, uiSessKeyLen, 1);
// 	SM2_ASSERT_NEQ_EX(iRtn, 0, 0);
// 
// 	iRtn = 1;
// END:
// 	if (bnX1DOT)
// 	{
// 		mpi_free(bnX1DOT);
// 		polarssl_free(bnX1DOT);
// 		bnX1DOT = NULL;
// 	}
// 	if (bnX2DOT)
// 	{
// 		mpi_free(bnX2DOT);
// 		polarssl_free(bnX2DOT);
// 		bnX2DOT = NULL;
// 	}
// 	if (bnTA)
// 	{
// 		mpi_free(bnTA);
// 		polarssl_free(bnTA);
// 		bnTA = NULL;
// 	}
// 	if (bnN)
// 	{
// 		mpi_free(bnN);
// 		polarssl_free(bnN);
// 		bnN = NULL;
// 	}
// 	if (bnH)
// 	{
// 		mpi_free(bnH);
// 		polarssl_free(bnH);
// 		bnH = NULL;
// 	}
// 	if (bnTmp)
// 	{
// 		mpi_free(bnTmp);
// 		polarssl_free(bnTmp);
// 		bnTmp = NULL;
// 	}
// 
// 	if (ptU)
// 	{
// 		ecp_point_free(ptU);
// 		polarssl_free(ptU);
// 		ptU = NULL;
// 	}
// 	if (ptTmp)
// 	{
// 		ecp_point_free(ptTmp);
// 		polarssl_free(ptTmp);
// 		ptTmp = NULL;
// 	}
// 
// 	if (eckey_z)
// 	{
// 		SM2_freeKeyPair(eckey_z);
// 		polarssl_free(eckey_z);
// 		eckey_z = 0;
// 	}
// 
// 	if (rng_ctx)
// 	{
// 		hmac_drbg_free(rng_ctx);
// 		polarssl_free(rng_ctx);
// 		rng_ctx = 0;
// 	}
// 
// 	if (pbZData)
// 	{
// 		polarssl_free(pbZData);
// 		pbZData = NULL;
// 	}
// 	return iRtn;
// }