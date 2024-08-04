#include "engine.h"

Engine::Engine() 
  : instance(VK_NULL_HANDLE), physicalDevice(VK_NULL_HANDLE), device(VK_NULL_HANDLE),
    graphicsQueue(VK_NULL_HANDLE), surface(VK_NULL_HANDLE), swapChain(VK_NULL_HANDLE),
    swapChainImageView(VK_NULL_HANDLE), renderPass(VK_NULL_HANDLE), graphicsPipeline(VK_NULL_HANDLE),
    framebuffer(VK_NULL_HANDLE), commandPool(VK_NULL_HANDLE), commandBuffer(VK_NULL_HANDLE),
    imageAvailableSemaphore(VK_NULL_HANDLE), renderFinishedSemaphore(VK_NULL_HANDLE) {}

Engine::~Engine() {
  cleanup();
}

bool Engine::initialize(VkAllocationCallbacks* allocator,std::string* appName,uint32_t appVersion,std::string* engineName,uint32_t engineVers,uint32_t physicalDeviceIndex) {
  if (!createInstance(allocator,appName,appVersion,engineName,engineVers)) return false;
  pickPhysicalDevice(physicalDeviceIndex);
  if (!createDevice(allocator)) return false;
  if (!createSwapChain()) return false;
  if (!createImageViews()) return false;
  if (!createRenderPass()) return false;
  if (!createGraphicsPipeline()) return false;
  if (!createFramebuffers()) return false;
  if (!createCommandPool()) return false;
  if (!createCommandBuffer()) return false;
  if (!createSemaphores()) return false;
  return true;
}

void Engine::cleanup(VkAllocationCallbacks* allocator) {
  cleanupSwapChain();
  if (device != VK_NULL_HANDLE) {
    vkDestroyDevice(device, allocator);
    device = VK_NULL_HANDLE;
  }
  if (instance != VK_NULL_HANDLE) {
    vkDestroyInstance(instance, allocator);
    instance = VK_NULL_HANDLE;
  }
  if(surface != VK_NULL_HANDLE){
		vkDestroySurfaceKHR(surface, allocator);
	}
}

void Engine::drawFrame() {
  // Implement frame drawing here
}

bool Engine::createInstance(VkAllocationCallbacks* allocator,std::string* appName, uint32_t appVersion, std::string* engineName, uint32_t engineVers) {
  uint32_t* apiVersion;
  VkApplicationInfo appInfo {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext = nullptr,
    .pApplicationName = appName->c_str(),
    .applicationVersion = appVersion,
    .pEngineName = engineName->c_str(),
    .engineVersion = engineVers,
    .apiVersion = VK_API_VERSION_1_0
  };
  VkInstanceCreateInfo createInfo {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pNext = nullptr,
    .pApplicationInfo = &appInfo,
    .enabledLayerCount = 0,  // temporary
    .ppEnabledLayerNames = "",  // temporary
    .enabledExtensionCount = 0,  // temporary
    .ppEnabledExtensionNames = ""  // temporary
  };
  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    return false;
  }
  return true;
}

void Engine::pickPhysicalDevice(uint32_t index) {
  if (instance == VK_NULL_HANDLE) {
    return;
  }
  uint32_t physicalDeviceCount;
  if (vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr) != VK_SUCCESS) {
    return;
  }
  std::vector<VkPhysicalDevice> tmp(physicalDeviceCount);
  if (vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, tmp.data()) != VK_SUCCESS) {
    return;
  }
  if (tmp.size() > 0) {
    physicalDevice = index >= tmp.size() ? tmp.back() : tmp[index];
  }
}

bool Engine::createDevice(VkAllocationCallbacks* allocator) {
  VkDeviceQueueCreateInfo queueCreateInfo{
		.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.pNext=nullptr,
		.flags=VK_DEVICE_QUEUE_PROTECTED_BIT,
		.queueFamilyIndex=0, //temporary
		.queueFamiliyCount=0, //temporary
		.pQueuePriorities=0, //temporary
	};
	
  VkDeviceCreateInfo createInfo{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = nullptr , //temporary
		.queueCreateInfoCount = 0, //temporary
		.pQueueCreateInfo = &queueCreateInfo,
		.enabledLayerCount = 0, //temporary
		.ppEnabledLayerNames = "", //temporary
    .enabledExtensionCount = 0,  // temporary
    .ppEnabledExtensionNames = "",  // temporary
	  .pEnabledFeatures=nullptr
	};
	if(VK_SUCCESS!=vkCreateDevice(physicaldevice,&createInfo,&allocator,&device)){
		return false;
	}
  return true;
}

bool Engine::createSwapChain() {
  // Implement Vulkan swap chain creation here
  return true;
}

bool Engine::createImageViews() {
  // Implement image views creation here
  return true;
}

bool Engine::createRenderPass() {
  // Implement render pass creation here
  return true;
}

bool Engine::createGraphicsPipeline() {
  // Implement graphics pipeline creation here
  return true;
}

bool Engine::createFramebuffers() {
  // Implement framebuffers creation here
  return true;
}

bool Engine::createCommandPool() {
  // Implement command pool creation here
  return true;
}

bool Engine::createCommandBuffer() {
  // Implement command buffer creation here
  return true;
}

bool Engine::createSemaphores() {
  // Implement semaphores creation here
  return true;
}

void Engine::cleanupSwapChain() {
  // Implement swap chain cleanup here
}