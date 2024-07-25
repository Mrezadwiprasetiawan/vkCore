#include <vulkan/vulkan.h>

void test(void){
  uint32_t apiVers;
  vkEnumerateInstanceVersion(&apiVers);
  return;
}