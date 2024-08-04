#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class Engine {
public:
    Engine();
    ~Engine();

    bool initialize();
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

    bool createInstance();
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
};
