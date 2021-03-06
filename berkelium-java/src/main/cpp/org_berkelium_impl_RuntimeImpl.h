/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_berkelium_impl_RuntimeImpl */

#ifndef _Included_org_berkelium_impl_RuntimeImpl
#define _Included_org_berkelium_impl_RuntimeImpl
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_dispose
  (JNIEnv *, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    getDebugObjectStats
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_berkelium_impl_RuntimeImpl_getDebugObjectStats
  (JNIEnv *, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    update
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_update
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    addUpdateEvent
 * Signature: (Lorg/berkelium/api/Update;I)V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_addUpdateEvent
  (JNIEnv *, jobject, jobject, jint);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    removeUpdateEvent
 * Signature: (Lorg/berkelium/api/Update;)V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_removeUpdateEvent
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    setDefaultExecutable
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_setDefaultExecutable
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    forExecutable
 * Signature: (Ljava/lang/String;)Lorg/berkelium/api/HostExecutable;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_forExecutable
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    forSystemInstalled
 * Signature: ()Lorg/berkelium/api/HostExecutable;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_forSystemInstalled
  (JNIEnv *, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    forProfile
 * Signature: (Ljava/lang/String;)Lorg/berkelium/api/Profile;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_forProfile
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    getChromeProfile
 * Signature: ()Lorg/berkelium/api/Profile;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_getChromeProfile
  (JNIEnv *, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    getChromiumProfile
 * Signature: ()Lorg/berkelium/api/Profile;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_getChromiumProfile
  (JNIEnv *, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    forProfilePath
 * Signature: (Ljava/lang/String;)Lorg/berkelium/api/Profile;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_forProfilePath
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    createTemporaryProfile
 * Signature: ()Lorg/berkelium/api/Profile;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_createTemporaryProfile
  (JNIEnv *, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    forVersion
 * Signature: (Ljava/lang/String;)Lorg/berkelium/api/HostVersion;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_forVersion__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    forVersion
 * Signature: (IIII)Lorg/berkelium/api/HostVersion;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_forVersion__IIII
  (JNIEnv *, jobject, jint, jint, jint, jint);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    open
 * Signature: (Lorg/berkelium/api/HostExecutable;Lorg/berkelium/api/Profile;)Lorg/berkelium/api/Instance;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_open
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    getLogger
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/berkelium/api/Logger;
 */
JNIEXPORT jobject JNICALL Java_org_berkelium_impl_RuntimeImpl_getLogger
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    addLogDelegate
 * Signature: (Lorg/berkelium/api/LogDelegate;)V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_addLogDelegate
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    removeLogDelegate
 * Signature: (Lorg/berkelium/api/LogDelegate;)V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_removeLogDelegate
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    log
 * Signature: (Lorg/berkelium/api/LogSource;Lorg/berkelium/api/LogType;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_log
  (JNIEnv *, jobject, jobject, jobject, jstring, jstring, jstring);

/*
 * Class:     org_berkelium_impl_RuntimeImpl
 * Method:    handleThrowable
 * Signature: (Ljava/lang/Throwable;)V
 */
JNIEXPORT void JNICALL Java_org_berkelium_impl_RuntimeImpl_handleThrowable
  (JNIEnv *, jobject, jthrowable);

#ifdef __cplusplus
}
#endif
#endif
