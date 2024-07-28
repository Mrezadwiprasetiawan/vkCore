#include "VkRenderer.h"

VkRenderer::Init{
	VkApplicationInfo appInfo{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = "Core",
		.applicationVersion = VK_MAKE_VERSION(1,0,0),
		.pEngineName = "RP ENGINE",
		.engineVersion = VK_MAKE_VERSION(1,0,0)
	};
	vkEnumerateInstanceVersion(&appInfo.apiVersion);
	
	VkInstanceCreateInfo insInfo{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = nullptr,
		.pApplicationInfo = &appInfo,
	};
	VkResult result=vkCreateInstance(&insInfo, nullptr, &ins);
	if(VK_SUCCESS!=result){
		setResult(result);
		return;
	}
	
}
VkRenderer::setResult(VkResult result){
	this->result=result;
}
VkRenderer::CleanUp(){
	if(inst!=VK_NULL_HANDLE||surface!=VK_NULL_HANDLE||)
	vkDestroyInstance(inst);
	vkDestroySurfaceKHR(surface);
}