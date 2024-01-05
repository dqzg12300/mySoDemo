#include <jni.h>
#include <string>

#include <android/log.h>
#include "dobby.h"

#define TAG_NAME "mySoDemo"
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG_NAME,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_mysodemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


int (*openat_old)(int dirfd, const char* pathname, int flags, int modes)=nullptr;

int openat_new(int dirfd, const char* pathname, int flags, int modes){
    ALOGD("enter openat_new pathname:%s",pathname);
    return openat_old(dirfd,pathname,flags,modes);
}

jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;

    ALOGD("enter my JNI_OnLoad");
    void* openatPtr= DobbySymbolResolver("libc.so","__openat");
    if(openatPtr==nullptr){
        ALOGD("openatPtr is null");
        return 0;
    }
    int ret= DobbyHook(openatPtr,(dobby_dummy_func_t)openat_new,(dobby_dummy_func_t*)&openat_old);
    ALOGD("hook ret:%d",ret);
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) == JNI_OK) {
        return JNI_VERSION_1_6;
    }

    return 0;
}