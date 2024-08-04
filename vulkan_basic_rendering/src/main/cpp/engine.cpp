#include "engine.h"
#include <stdexcept>
#include <iostream>

Engine::Engine() 
    : instance(VK_NULL_HANDLE), physicalDevice(VK_NULL_HANDLE), device(VK_NULL_HANDLE),
      graphicsQueue(VK_NULL_HANDLE), surface(VK_NULL_HANDLE), swapChain(VK_NULL_HANDLE),
      swapChainImageView(VK_NULL_HANDLE), renderPass(VK_NULL_HANDLE), graphicsPipeline(VK_NULL_HANDLE),
      framebuffer(VK_NULL_HANDLE), commandPool(VK_NULL_HANDLE), commandBuffer(VK_NULL_HANDLE),
      imageAvailableSemaphore(VK_NULL_HANDLE), renderFinishedSemaphore(VK_NULL_HANDLE) {}

Engine::~Engine() {
    cleanup();
}

bool Engine::initialize() {
    if (!createInstance()) return false;
    pickPhysicalDevice();
    if (!createDevice()) return false;
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
    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
        instance = VK_NULL_HANDLE;
    }
}
void onDrawFrame(){
	//logic here from java jni
}
void Engine::drawFrame() {
    onDrawFrame();
}

bool Engine::createInstance() {
    // Implement Vulkan instance creation here
    return true;
}

void Engine::pickPhysicalDevice() {
    // Implement physical device selection here
}

bool Engine::createDevice() {
    // Implement Vulkan device creation here
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