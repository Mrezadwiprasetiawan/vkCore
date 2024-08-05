#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include <android/native_window.h>
#include <algorithm>

class Engine {
public:
    Engine();
    ~Engine();

    bool initialize(std::string* appName, uint32_t appVersion, std::string* engineName, uint32_t engineVers, uint32_t physicalDeviceIndex, ANativeWindow* window);
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
    ANativeWindow* window;

    std::vector<VkImage> swapChainImages;

    bool createInstance(std::string* appName, uint32_t appVersion, std::string* engineName, uint32_t engineVers);
    bool createDevice();
    bool createSwapChain();
    bool createImageViews();
    bool createRenderPass();
    bool createGraphicsPipeline();
    bool createFramebuffers();
    bool createCommandPool();
    bool createCommandBuffer();
    bool createSemaphores();
    void pickPhysicalDevice();
    void cleanupSwapChain();
    bool createSurface();
};