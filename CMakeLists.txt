cmake_minimum_required(VERSION 3.15.0)
project(VulkanApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(src/ThirdParty/glfw)

add_subdirectory(src/ThirdParty/glm)

if(DEFINED ENV{VULKAN_SDK})
    message(STATUS "CMake: Using VULKAN_SDK environment variable: $ENV{VULKAN_SDK}")
else()
    message(WARNING "CMake: VULKAN_SDK environment variable is NOT set. Vulkan discovery might fail or use a system default path.")
endif()

find_package(Vulkan REQUIRED)

if(Vulkan_FOUND)
    message(STATUS "CMake: Vulkan Found!")
    message(STATUS "CMake: Vulkan_INCLUDE_DIRS: ${Vulkan_INCLUDE_DIRS}")
    message(STATUS "CMake: Vulkan_LIBRARIES: ${Vulkan_LIBRARIES}")
else()
    message(FATAL_ERROR "CMake: Vulkan NOT Found! Please ensure the Vulkan SDK is installed and the VULKAN_SDK environment variable is set correctly.")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src) 

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

target_link_libraries(${PROJECT_NAME} PRIVATE glm)

if (APPLE)
target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_PLATFORM_EXTENSIONS)
endif()
