#include "main.h"

//main Method
//unimplemented yet
JNIEXPORT void JNICALL Java_rpengine_core_vkcore_VulkanRenderer_Init(JNIEnv* env, jclass* clz){
	
}
JNIEXPORT jlong JNICALL Java_rpengine_core_vkcore_VulkanRenderer_CleanUp(JNIEnv* env, jclass* clz){
	
}

//utils
JNIEXPORT jstring JNICALL Java_rpengine_core_vkcore_Utils_InstanceVersion(JNIEnv* env, jclass* clz){
	return env->NewStringUTF(InsVers().c_str());
}
JNIEXPORT jstring JNICALL Java_rpengine_core_vkcore_Utils_API(JNIEnv* env, jclass* clz){
	return env->NewStringUTF(API().c_str());
}