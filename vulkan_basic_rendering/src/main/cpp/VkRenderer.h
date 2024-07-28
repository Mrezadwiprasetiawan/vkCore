#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <android/native_window.h>

class VkRenderer{
	private:
	VkInstance inst;
	VkResult result;
	VkSurfaceKHR surface;
	ANative_Window* window;
	public:
	vulkanRenderer(VkResult result, ANativeWindow* window):inst(VK_NULL_HANDLE),result(result),window(window);
	void Init();
	void setResult();
	VkResult getResult();
	void CleanUp();
}