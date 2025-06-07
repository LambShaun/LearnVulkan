cmake_minimum_required(VERSION 3.15.0)
project(VulkanApp LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/ThirdParty/glfw)
add_subdirectory(src/ThirdParty/glm)

set(VMA_STATIC_VULKAN_LIBRARY OFF CACHE BOOL "Do not link Vulkan statically into VMA")
set(VMA_DYNAMIC_VULKAN_FUNCTIONS OFF CACHE BOOL "Do not fetch Vulkan functions dynamically")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build VMA as a static library")
add_subdirectory(src/ThirdParty/VulkanMemoryAllocator)


if(DEFINED ENV{VULKAN_SDK})
    message(STATUS "CMake: Using VULKAN_SDK environment variable: $ENV{VULKAN_SDK}")
else()
    message(WARNING "CMake: VULKAN_SDK environment variable is NOT set. Vulkan discovery might fail or use a system default path.")
endif()

find_package(Vulkan REQUIRED)

if(Vulkan_FOUND)
    message(STATUS "CMake: Vulkan Found!")
else()
    message(FATAL_ERROR "CMake: Vulkan NOT Found! Please ensure the Vulkan SDK is installed and the VULKAN_SDK environment variable is set correctly.")
endif()

add_subdirectory(src)
