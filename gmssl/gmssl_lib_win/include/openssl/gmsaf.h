/* ====================================================================
 * Copyright (c) 2015 - 2016 The GmSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 */

#ifndef HEADER_GMSAF_H
#define HEADER_GMSAF_H

#include <openssl/opensslconf.h>
#ifndef OPENSSL_NO_SAF

#include <stdio.h>
#include <openssl/sgd.h>
#include <openssl/saf.h>

#define SAF_MAX_EC_CIPHERTEXT_LENGTH 136


#ifdef __cplusplus
extern "C" {
#endif


const char *SAF_GetErrorString(int err);

/* GmSSL Extension  */
int SAF_EccSignFile(
	void *hAppHandle,
	unsigned char *pucContainerName,
	unsigned int uiContainerNameLen,
	unsigned int uiHashAlgoType,
	unsigned char *pucFileName,
	unsigned char *pucSignature,
	unsigned int *puiSignatureLen);

int SAF_EccVerifySignFile(
	unsigned int uiHashAlgoType,
	unsigned char *pucPublicKey,
	unsigned int uiPublicKeyLen,
	unsigned char *pucFileName,
	unsigned char *pucSignature,
	unsigned int uiSignatureLen);


/* BEGIN ERROR CODES */
/*
 * The following lines are auto generated by the script mkerr.pl. Any changes
 * made after this point may be overwritten when the script is next run.
 */

int ERR_load_SAF_strings(void);

/* Error codes for the SAF functions. */

/* Function codes. */
# define SAF_F_SAF_ADDCACERTIFICATE                       100
# define SAF_F_SAF_ADDTRUSTEDROOTCACERTIFICATE            101
# define SAF_F_SAF_BASE64_CREATEBASE64OBJ                 102
# define SAF_F_SAF_BASE64_DECODE                          103
# define SAF_F_SAF_BASE64_DECODEFINAL                     104
# define SAF_F_SAF_BASE64_DECODEUPDATE                    105
# define SAF_F_SAF_BASE64_ENCODE                          106
# define SAF_F_SAF_BASE64_ENCODEFINAL                     107
# define SAF_F_SAF_BASE64_ENCODEUPDATE                    108
# define SAF_F_SAF_CHANGEPIN                              109
# define SAF_F_SAF_CREATEHASHOBJ                          110
# define SAF_F_SAF_CREATESYMMKEYOBJ                       111
# define SAF_F_SAF_DESTROYHASHOBJ                         112
# define SAF_F_SAF_ECCPUBLICKEYENC                        113
# define SAF_F_SAF_ECCPUBLICKEYENCBYCERT                  114
# define SAF_F_SAF_ECCSIGN                                115
# define SAF_F_SAF_ECCVERIFYSIGN                          116
# define SAF_F_SAF_ECCVERIFYSIGNBYCERT                    117
# define SAF_F_SAF_GENECCKEYPAIR                          118
# define SAF_F_SAF_GENERATEKEYWITHEPK                     119
# define SAF_F_SAF_GENRANDOM                              120
# define SAF_F_SAF_GENRSAKEYPAIR                          121
# define SAF_F_SAF_GETCACERTIFICATE                       122
# define SAF_F_SAF_GETCACERTIFICATECOUNT                  123
# define SAF_F_SAF_GETECCPUBLICKEY                        124
# define SAF_F_SAF_GETROOTCACERTIFICATE                   125
# define SAF_F_SAF_GETROOTCACERTIFICATECOUNT              126
# define SAF_F_SAF_GETRSAPUBLICKEY                        127
# define SAF_F_SAF_GETVERSION                             128
# define SAF_F_SAF_HASH                                   129
# define SAF_F_SAF_HASHFINAL                              130
# define SAF_F_SAF_HASHUPDATE                             131
# define SAF_F_SAF_INITIALIZE                             132
# define SAF_F_SAF_KEY_NEW                                133
# define SAF_F_SAF_LOAD_PRIVATE_KEY                       151
# define SAF_F_SAF_LOAD_PUBLIC_KEY                        152
# define SAF_F_SAF_LOGIN                                  134
# define SAF_F_SAF_LOGOUT                                 135
# define SAF_F_SAF_MACFINAL                               136
# define SAF_F_SAF_MACUPDATE                              137
# define SAF_F_SAF_PKCS7_DECODEDIGESTEDDATA               153
# define SAF_F_SAF_PKCS7_DECODEENVELOPEDDATA              154
# define SAF_F_SAF_PKCS7_DECODESIGNEDDATA                 155
# define SAF_F_SAF_PKCS7_ENCODEDIGESTEDDATA               149
# define SAF_F_SAF_PKCS7_ENCODEENVELOPEDDATA              138
# define SAF_F_SAF_PKCS7_ENCODESIGNEDDATA                 150
# define SAF_F_SAF_REMOVECACERTIFICATE                    139
# define SAF_F_SAF_REMOVEROOTCACERTIFICATE                140
# define SAF_F_SAF_RSASIGN                                141
# define SAF_F_SAF_RSAVERIFYSIGN                          142
# define SAF_F_SAF_SYMMDECRYPTFINAL                       143
# define SAF_F_SAF_SYMMDECRYPTUPDATE                      144
# define SAF_F_SAF_SYMMENCRYPTFINAL                       145
# define SAF_F_SAF_SYMMENCRYPTUPDATE                      146
# define SAF_F_SAF_SYMMKEYOBJ_DUP                         147
# define SAF_F_SAF_VERIFYSIGNBYCERT                       148

/* Reason codes. */
# define SAF_R_BUFFER_TOO_SMALL                           100
# define SAF_R_CMAC_FAILURE                               101
# define SAF_R_DECRYPT_NOT_INITIALIZED                    102
# define SAF_R_ENCRYPT_KEY_FAILURE                        103
# define SAF_R_ENCRYPT_NOT_INITIALIED                     104
# define SAF_R_GEN_RANDOM_FAILURE                         105
# define SAF_R_INT_OVERFLOW                               106
# define SAF_R_INVALID_ALGOR                              107
# define SAF_R_INVALID_APP                                124
# define SAF_R_INVALID_CERTIFICATE                        108
# define SAF_R_INVALID_DIGEST_ALGOR                       122
# define SAF_R_INVALID_HANDLE                             109
# define SAF_R_INVALID_INDEX                              110
# define SAF_R_INVALID_INPUT_LENGTH                       111
# define SAF_R_INVALID_KEY_HANDLE                         112
# define SAF_R_INVALID_KEY_LENGTH                         113
# define SAF_R_INVALID_KEY_USAGE                          114
# define SAF_R_INVALID_LENGTH                             115
# define SAF_R_INVALID_PKCS7                              125
# define SAF_R_INVALID_PKCS7_DATA                         126
# define SAF_R_INVALID_PKCS7_TYPE                         127
# define SAF_R_INVALID_PKEY_TYPE                          128
# define SAF_R_INVALID_PUBLIC_KEY                         116
# define SAF_R_LOA                                        132
# define SAF_R_LOAD_CERTS_FAILURE                         117
# define SAF_R_LOAD_KEY_FAILURE                           123
# define SAF_R_LOAD_PRIVATE_KEY_FAILURE                   129
# define SAF_R_LOAD_PUBLIC_KEY_FAILURE                    130
# define SAF_R_MAC_FAILURE                                118
# define SAF_R_NOT_SUPPORTED                              119
# define SAF_R_OPERATION_NOT_INITIALIZED                  120
# define SAF_R_PKCS7_VERIFY_FAILURE                       133
# define SAF_R_UNSUPPORTED_ALGOR                          121
# define SAF_R_UNSUPPORTED_DIGEST_ALGOR                   131

# ifdef  __cplusplus
}
# endif
#endif
#endif
