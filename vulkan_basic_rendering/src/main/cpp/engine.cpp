//imageView page 6 with image page 5

#include "engine.h"

Engine::Engine() 
  : instance(VK_NULL_HANDLE), physicalDevice(VK_NULL_HANDLE), device(VK_NULL_HANDLE),
    graphicsQueue(VK_NULL_HANDLE), surface(VK_NULL_HANDLE), swapChain(VK_NULL_HANDLE),
    swapChainImageView(VK_NULL_HANDLE), renderPass(VK_NULL_HANDLE), graphicsPipeline(VK_NULL_HANDLE),
    framebuffer(VK_NULL_HANDLE), commandPool(VK_NULL_HANDLE), commandBuffer(VK_NULL_HANDLE),
    imageAvailableSemaphore(VK_NULL_HANDLE), renderFinishedSemaphore(VK_NULL_HANDLE), window(nullptr) {}

Engine::~Engine() {
  cleanup();
}

bool Engine::initialize(std::string* appName, uint32_t appVersion, std::string* engineName, uint32_t engineVers, uint32_t physicalDeviceIndex, ANativeWindow* window) {
  this->window = window;
  if (!createInstance(appName, appVersion, engineName, engineVers)) return false;
  pickPhysicalDevice();
  if (!createDevice()) return false;
  if (!createSurface()) return false;
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

void Engine::cleanup() {
  cleanupSwapChain();
  if (device != VK_NULL_HANDLE) {
    vkDestroyDevice(device, nullptr);
    device = VK_NULL_HANDLE;
  }
  if (surface != VK_NULL_HANDLE) {
    vkDestroySurfaceKHR(instance, surface, nullptr);
    surface = VK_NULL_HANDLE;
  }
  if (instance != VK_NULL_HANDLE) {
    vkDestroyInstance(instance, nullptr);
    instance = VK_NULL_HANDLE;
  }
}

void Engine::drawFrame() {
  // Implement frame drawing here
}

bool Engine::createInstance(std::string* appName, uint32_t appVersion, std::string* engineName, uint32_t engineVers) {
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
    .ppEnabledLayerNames = nullptr,  // temporary
    .enabledExtensionCount = 0,  // temporary
    .ppEnabledExtensionNames = nullptr  // temporary
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

  std::vector<VkPhysicalDevice> devices(physicalDeviceCount);
  if (vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, devices.data()) != VK_SUCCESS) {
    return;
  }

  if (!devices.empty()) {
    physicalDevice = index >= devices.size() ? devices.back() : devices[index];
  }
}

bool Engine::createDevice() {
  float queuePriority = 1.0f;
  VkDeviceQueueCreateInfo queueCreateInfo {
    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .queueFamilyIndex = 0, // Update with appropriate value
    .queueCount = 1,
    .pQueuePriorities = &queuePriority
  };

  VkDeviceCreateInfo createInfo {
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext = nullptr,
    .queueCreateInfoCount = 1,
    .pQueueCreateInfos = &queueCreateInfo,
    .enabledLayerCount = 0,
    .ppEnabledLayerNames = nullptr,
    .enabledExtensionCount = 0,
    .ppEnabledExtensionNames = nullptr,
    .pEnabledFeatures = nullptr
  };

  if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
    return false;
  }

  vkGetDeviceQueue(device, 0, 0, &graphicsQueue);
  return true;
}

bool Engine::createSurface() {
  VkAndroidSurfaceCreateInfoKHR surfaceCreateInfo {
    .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
    .pNext = nullptr,
    .window = window
  };

  if (vkCreateAndroidSurfaceKHR(instance, &surfaceCreateInfo, nullptr, &surface) != VK_SUCCESS) {
    return false;
  }
  return true;
}

bool Engine::createSwapChain() {
    // Query the surface capabilities
    VkSurfaceCapabilitiesKHR capabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities) != VK_SUCCESS) {
        return false;
    }

    // Query supported surface formats
    uint32_t formatCount;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr) != VK_SUCCESS) {
        return false;
    }

    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, formats.data()) != VK_SUCCESS) {
        return false;
    }

    VkSurfaceFormatKHR surfaceFormat = formats[0];
    for (const auto& format : formats) {
        if (format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
            surfaceFormat = format;
            break;
        }
    }

    // Query supported present modes
    uint32_t presentModeCount;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr) != VK_SUCCESS) {
        return false;
    }

    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data()) != VK_SUCCESS) {
        return false;
    }

    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR; // FIFO is always supported
    for (const auto& mode : presentModes) {
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR) {
            presentMode = mode;
            break;
        }
    }

    // Set up swapchain creation info
    VkSwapchainCreateInfoKHR swapChainInfo = {};
    swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapChainInfo.surface = surface;
    swapChainInfo.minImageCount = capabilities.minImageCount + 1;
    swapChainInfo.imageFormat = surfaceFormat.format;
    swapChainInfo.imageColorSpace = surfaceFormat.colorSpace;
    swapChainInfo.imageExtent = capabilities.currentExtent;
    swapChainInfo.imageArrayLayers = 1;
    swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    uint32_t queueFamilyIndices[] = { 0 }; // Update with actual queue family indices
    if (queueFamilyIndices[0] != queueFamilyIndices[1]) {
        swapChainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapChainInfo.queueFamilyIndexCount = 2;
        swapChainInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapChainInfo.queueFamilyIndexCount = 0;
        swapChainInfo.pQueueFamilyIndices = nullptr;
    }

    swapChainInfo.preTransform = capabilities.currentTransform;
    swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapChainInfo.presentMode = presentMode;
    swapChainInfo.clipped = VK_TRUE;
    swapChainInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(device, &swapChainInfo, nullptr, &swapChain) != VK_SUCCESS) {
        return false;
    }

    // Retrieve swapchain images
    uint32_t imageCount;
    if (vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr) != VK_SUCCESS) {
        return false;
    }

    swapChainImages.resize(imageCount);
    if (vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data()) != VK_SUCCESS) {
        return false;
    }

    return true;
}
bool Engine::createImageViews() {
  
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
  VkSemaphoreCreateInfo semaphoreInfo {
    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0
  };

  if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
      vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS) {
    return false;
  }
  return true;
}

void Engine::cleanupSwapChain() {
  if (framebuffer != VK_NULL_HANDLE) {
    vkDestroyFramebuffer(device, framebuffer, nullptr);
    framebuffer = VK_NULL_HANDLE;
  }
  if (swapChainImageView != VK_NULL_HANDLE) {
    vkDestroyImageView(device, swapChainImageView, nullptr);
    swapChainImageView = VK_NULL_HANDLE;
  }
  if (swapChain != VK_NULL_HANDLE) {
    vkDestroySwapchainKHR(device, swapChain, nullptr);
    swapChain = VK_NULL_HANDLE;
  }
}