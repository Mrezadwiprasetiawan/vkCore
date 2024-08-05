cmake_minimum_required(VERSION 3.22.1)

project(vkcore)

add_library(vkcore SHARED utils.cpp main.cpp engine.cpp)

target_link_libraries(vkcore PRIVATE vulkan)
add_definitions(-DVK_USE_PLATFORM_ANDROID_SURFACE_KHR)