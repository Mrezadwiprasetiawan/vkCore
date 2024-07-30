#pragma once
#include <jni.h>
#include "vkRenderer.h"
#include "utils.h"
#ifdef __cplusplus
extern "C"{
#endif

//main method
JNIEXPORT void JNICALL Java_rpengine_core_vkcore_VulkanRenderer_Init(JNIEnv* env, jclass* clz);
JNIEXPORT jlong JNICALL Java_rpengine_core_vkcore_VulkanRenderer_CleanUp(JNIEnv* env, jclass* clz);

//utils
JNIEXPORT jstring JNICALL Java_rpengine_core_vkcore_Utils_InstanceVersion(JNIEnv* env, jclass* clz);
JNIEXPORT jstring JNICALL Java_rpengine_core_vkcore_Utils_API(JNIEnv* env, jclass* clz);

#ifdef __cplusplus
}
#endif