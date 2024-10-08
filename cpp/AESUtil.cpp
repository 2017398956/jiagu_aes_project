#include "AESUtil.h"
#include <string>
//#include "android_log.h"
#include "xxtea.h"

static const char* TAG = "JiaGu_SXJY";

#ifdef __cplusplus
extern "C" {
#endif



/*
 * Class:     personal_nfl_protect_lib_util_AESUtil
 * Method:    encrypt
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_personal_nfl_protect_lib_util_AESUtil_encrypt
        (JNIEnv *env, jclass clazz, jbyteArray data){

    //jbyteArray 转换成byte*
    jboolean isCopy = false;
    jbyte* dataBuff = env->GetByteArrayElements(data, &isCopy);
    jsize dataSize = env->GetArrayLength(data);
    //LOGD(TAG,"data size----%d",dataSize);
    //printf("==========>data size----%d\n", dataSize);
    const char *key = "personal_nfl_protect_app";
    size_t len;
    
    jbyte * encrypt_data = (jbyte*)xxtea_encrypt(dataBuff,dataSize,key,&len);
    //JNI_ABORT表示不拷贝数据回jbyteArray,即data
    //env->ReleaseByteArrayElements(data,encrypt_data, isCopy);
    //printf("==========>jni==========\n");

    //LOGE(TAG,"encrypt_data size === %zu",len);

    //将char*转为jbyteArray
    jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(array,0,len,reinterpret_cast<jbyte*>(encrypt_data));
    //printf("==========>jni========== end");
    return array;
}

/*
 * Class:     personal_nfl_protect_lib_util_AESUtil
 * Method:    decrypt
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_personal_nfl_protect_lib_util_AESUtil_decrypt
        (JNIEnv *env, jclass clazz, jbyteArray data){
    // 将jbyteArray转换成byte*
    jboolean isCopy = false;
    jbyte *dataBuff = env->GetByteArrayElements(data,&isCopy);
    jsize dataSize = env->GetArrayLength(data);

   // LOGD(TAG,"data size ==== %d",dataSize);
    
    //decrypt
    const char *key = "personal_nfl_protect_app";
    size_t len;
    jbyte *decrypt_data = (jbyte*)xxtea_decrypt(dataBuff,dataSize,key,&len);
    env->ReleaseByteArrayElements(data,decrypt_data, isCopy);

    //LOGD(TAG,"decrypt_data size====%zu",len);

    //将char*转为jbyteArray
    jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(array,0,len,reinterpret_cast<jbyte*>(decrypt_data));
    return array;
}

#ifdef __cplusplus
}
#endif
