// my_functions.h
#pragma once
#include <jni.h>
#include "engine.h"

#ifdef __cplusplus
extern "C" {
#endif


#define JNI_FUNCTION(return_type, class_name, method_name) \
    JNIEXPORT return_type JNICALL Java_rpengine_core_vkcore_##class_name##_##method_name

JNI_FUNCTION(void, Vulkan_Init, (JNIEnv* env, jclass clz));
JNI_FUNCTION(void, Vulkan_DrawFrame,(JNIEnv* env, jobject* obj))
JNI_FUNCTION(jlong, Vulkan_CleanUp, (JNIEnv* env, jclass clz));
JNI_FUNCTION(jstring, Vulkan_InstanceVersion, (JNIEnv* env, jclass clz));
JNI_FUNCTION(jstring, Vulkan_API, (JNIEnv* env, jclass clz));

#ifdef __cplusplus
}
#endif