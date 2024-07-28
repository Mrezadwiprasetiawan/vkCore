#include "utils.h"

std::string API(void){
  std::stringstream ss;
  VkInstance ins;
  
  VkApplicationInfo appInfo{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = "Check Version",
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
	
	if(vkCreateInstance(&insInfo, nullptr, &ins) != VK_SUCCESS){
		return "gagal membuat instance";
	}
	
	//membuat container GPU dan properti GPU
	VkPhysicalDevice GPU;
	VkPhysicalDeviceProperties GPUprop;
	uint32_t gpuCount;
	if(vkEnumeratePhysicalDevices(ins, &gpuCount, nullptr)!=VK_SUCCESS){
		return "gagal mendapatkan jumlah GPU";
	}
	std::vector<VkPhysicalDevice> tmpGPU(gpuCount);
	if(vkEnumeratePhysicalDevices(ins, &gpuCount, tmpGPU.data())!=VK_SUCCESS){
		return "gagal memilih GPU";
	}
	
	GPU=tmpGPU[0];
	vkGetPhysicalDeviceProperties(GPU, &GPUprop);
	
	//menyisipkan nilai ke StringStream
	ss<<"GPU\t:"<<std::endl;
	ss<<"Nama\t:\t"<<GPUprop.deviceName<<std::endl;
	ss<<"Device ID\t:\t"<<versionToString(GPUprop.deviceID)<<""<<std::endl;
	ss<<"Vendor ID\t:\t"<<versionToString(GPUprop.vendorID)<<std::endl;
	ss<<"Versi driver\t:\t"<<versionToString(GPUprop.driverVersion)<<std::endl;
	ss<<"Api Version\t:\t"<<versionToString(GPUprop.apiVersion)<<std::endl;
	
	//menghancurkan instance
	vkDestroyInstance(ins, nullptr);
	return ss.str();
}
std::string versionToString(uint32_t versionCode){
	std::stringstream ss;
	ss<<VK_VERSION_MAJOR(versionCode)<<"."<<VK_VERSION_MINOR(versionCode)<<"."<<VK_VERSION_PATCH(versionCode);
	return ss.str();
}