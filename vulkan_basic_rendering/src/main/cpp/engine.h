#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

class Engine {
public:
    Engine();
    ~Engine();

    bool initialize(VkAllocationCallbacks* allocator,std::string* appName,uint32_t appVersion,std::string* engineName,uint32_t engineVers,uint32_t physicalDeviceIndex);
    void cleanup();
    void drawFrame();

private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    VkImageView swapChainImageView;
    VkRenderPass renderPass;
    VkPipeline graphicsPipeline;
    VkFramebuffer framebuffer;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;

    std::vector<VkImage> swapChainImages;

    bool createInstance(VkAllocationCallbacks* allocator,std::string* appName,uint32_t appVersion,std::string* engineName, uint32_t engineVers);
    bool createDevice(VkAllocationCallbacks* allocator);
    bool createSwapChain();
    bool createImageViews();
    bool createRenderPass();
    bool createGraphicsPipeline();
    bool createFramebuffers();
    bool createCommandPool();
    bool createCommandBuffer();
    bool createSemaphores();
    void pickPhysicalDevice(VkAllocationCallbacks* allocator);
    void cleanupSwapChain();
};
