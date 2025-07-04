set(APP_SOURCES
    main.cpp
)

add_executable(VulkanApp ${APP_SOURCES})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/models DESTINATION "${CMAKE_BINARY_DIR}")

add_subdirectory(shaders)


if(TARGET VulkanApp AND TARGET ShaderCompilationTarget)
    add_dependencies(VulkanApp ShaderCompilationTarget)
else()
    message(WARNING "CMake: Could not establish dependency between VulkanApp and ShaderCompilationTarget.")
endif()

target_include_directories(VulkanApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/stb_image 
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/tinyobjloader
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(VulkanApp PRIVATE 
        -Wno-nullability-completeness
        -Wno-nullability-extension
    )
endif()

target_link_libraries(VulkanApp PRIVATE
    Vulkan::Vulkan  
    glfw            
    glm
    GPUOpen::VulkanMemoryAllocator
)

if (APPLE)
    target_compile_definitions(VulkanApp PRIVATE ENABLE_PLATFORM_EXTENSIONS)
endif()
