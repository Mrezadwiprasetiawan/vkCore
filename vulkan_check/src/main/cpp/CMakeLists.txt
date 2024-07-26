cmake_minimum_required(VERSION 3.22.1)

project(vkcore)

add_library(vkcore SHARED main.cpp)

target_link_libraries(vkcore PRIVATE vulkan)