/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_cist_SoftAlgNative */

#ifndef _Included_com_cist_SoftAlgNative
#define _Included_com_cist_SoftAlgNative
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_cist_SoftAlgNative
 * Method:    forTest
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cist_SoftAlgNative_forTest
  (JNIEnv *, jobject);

/*
 * Class:     com_cist_SoftAlgNative
 * Method:    VerifySM2Sign
 * Signature: ([B[B)I
 */
JNIEXPORT jint JNICALL Java_com_cist_SoftAlgNative_VerifySM2Sign
  (JNIEnv *env, jobject, jbyteArray byteCert, jbyteArray byteSignature);

#ifdef __cplusplus
}
#endif
#endif