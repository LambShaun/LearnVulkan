set(APP_SOURCES
    main.cpp
)

add_executable(VulkanApp ${APP_SOURCES})

add_subdirectory(shaders)

if(TARGET VulkanApp AND TARGET ShaderCompilationTarget)
    add_dependencies(VulkanApp ShaderCompilationTarget)
else()
    message(WARNING "CMake: Could not establish dependency between VulkanApp and ShaderCompilationTarget.")
endif()

target_include_directories(VulkanApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} 
)

target_link_libraries(VulkanApp PRIVATE
    Vulkan::Vulkan  
    glfw            
    glm            
)

if (APPLE)
    target_compile_definitions(VulkanApp PRIVATE ENABLE_PLATFORM_EXTENSIONS)
endif()
