#include "main.h"

Engine* engine=nullptr;
JNI_FUNCTION(void, VulkanRenderer_Init, (JNIEnv* env, jclass clz)){
	engine=new Engine();
	if(!engine->initialize){
		delete engine;
		engine=nullptr;
	}
}

JNI_FUNCTION(jlong, VulkanRenderer_CleanUp, (JNIEnv* env, jclass clz)){
	if(!engine==nullptr){
		engine->cleanup();
		delete engine;
		engine=nullptr;
	}
}
JNI_FUNCTION(jstring, Utils_InstanceVersion, (JNIEnv* env, jclass clz)){
	return env->NewStringUTF(InsVers().c_str());
}
JNI_FUNCTION(jstring, Utils_API, (JNIEnv* env, jclass clz)){
	return env->NewStringUTF(API().c_str());
}