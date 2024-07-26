#pragma once
#include <vulkan/vulkan.h>
#include <jni.h>
#include <sstream>
#include <string>
#include <vector>

#ifdef __cplusplus
extern "C"{
#endif
  JNIEXPORT jstring JNICALL Java_rpengine_core_vkcore_Utils_InstanceVersion(JNIEnv* env, jclass* javathis);
  JNIEXPORT jstring JNICALL Java_rpengine_core_vkcore_Utils_API(JNIEnv* env, jclass* javathis);
#ifdef __cplusplus
}
#endif
std::string InsVers(void);
std::string API(void);
std::string versionToString(uint32_t versionCode);