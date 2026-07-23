#ifndef NRP_JNI_STUB_H
#define NRP_JNI_STUB_H

#include <cstdint>
#include <cstddef>

typedef unsigned char jboolean;
typedef signed char jbyte;
typedef unsigned short jchar;
typedef short jshort;
typedef int jint;
typedef long long jlong;
typedef float jfloat;
typedef double jdouble;
typedef jint jsize;

typedef void* jobject;
typedef jobject jclass;
typedef jobject jstring;
typedef jobject jarray;
typedef jobject jlongArray;
typedef jobject jthrowable;

#define JNI_FALSE 0
#define JNI_TRUE 1

#ifndef JNIEXPORT
#define JNIEXPORT
#endif

#ifndef JNICALL
#define JNICALL
#endif

struct JNIEnv_ {
    const char* GetStringUTFChars(jstring str, jboolean* isCopy) {
        (void)isCopy;
        return reinterpret_cast<const char*>(str);
    }
    void ReleaseStringUTFChars(jstring str, const char* chars) {
        (void)str; (void)chars;
    }
    jstring NewStringUTF(const char* utf) {
        return const_cast<jstring>(reinterpret_cast<const void*>(utf));
    }
    jlongArray NewLongArray(jsize len) {
        (void)len;
        return nullptr;
    }
    void SetLongArrayRegion(jlongArray array, jsize start, jsize len, const jlong* buf) {
        (void)array; (void)start; (void)len; (void)buf;
    }
};

typedef struct JNIEnv_ JNIEnv;

#endif // NRP_JNI_STUB_H
