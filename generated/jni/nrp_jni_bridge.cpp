// Auto-generated JNI Bridge for LuaSoup NRP (Android ARM64)
// Target ABI: arm64-v8a
#include <jni.h>
#include "nrp/core/runtime.hpp"
#include "nrp/luau/luau_engine.hpp"
#include "nrp/modules/html.hpp"
#include "nrp/modules/json.hpp"
#include "nrp/modules/crypto.hpp"

static nrp::Runtime g_runtime("android_arm64");
static nrp::luau::LuauEngine g_luau;

extern "C" {

JNIEXPORT jstring JNICALL
Java_com_luasoup_nrp_NRP_nativeGetTargetArch(JNIEnv* env, jclass clazz) {
    (void)env; (void)clazz;
    return env->NewStringUTF("arm64-v8a");
}

JNIEXPORT jboolean JNICALL
Java_com_luasoup_nrp_NRP_nativeInit(JNIEnv* env, jclass clazz) {
    (void)env; (void)clazz;
    g_runtime.initialize();
    g_luau.initialize();
    return JNI_TRUE;
}

JNIEXPORT jstring JNICALL
Java_com_luasoup_nrp_NRP_nativeEvalLuau(JNIEnv* env, jclass clazz, jstring jscript) {
    (void)clazz;
    const char* script = env->GetStringUTFChars(jscript, nullptr);
    auto res = g_luau.eval(script ? script : "");
    if (script) env->ReleaseStringUTFChars(jscript, script);
    std::string out = res.is_string() ? res.as_string() : "OK";
    return env->NewStringUTF(out.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_luasoup_nrp_NRP_nativeParseHTML(JNIEnv* env, jclass clazz, jstring jhtml) {
    (void)clazz;
    const char* html = env->GetStringUTFChars(jhtml, nullptr);
    auto doc = nrp::modules::html::Document::parse(html ? html : "");
    if (html) env->ReleaseStringUTFChars(jhtml, html);
    return env->NewStringUTF(doc->outer_html().c_str());
}

} // extern "C"
