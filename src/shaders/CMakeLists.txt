set(GLSLC_HINTS "") 

if(DEFINED ENV{VULKAN_SDK})
    set(VULKAN_SDK_PATH "$ENV{VULKAN_SDK}")
    message(STATUS "Shader Compilation: Using VULKAN_SDK hint: ${VULKAN_SDK_PATH}")
    if(WIN32)
        list(APPEND GLSLC_HINTS "${VULKAN_SDK_PATH}/Bin")
    elseif(APPLE)
        list(APPEND GLSLC_HINTS "${VULKAN_SDK_PATH}/macOS/bin")
    elseif(UNIX) 
        list(APPEND GLSLC_HINTS "${VULKAN_SDK_PATH}/bin") 
        list(APPEND GLSLC_HINTS "${VULKAN_SDK_PATH}/x86_64/bin") 
        list(APPEND GLSLC_HINTS "${VULKAN_SDK_PATH}/aarch64/bin") 
    endif()
else()
    message(STATUS "Shader Compilation: VULKAN_SDK environment variable is not set. Relying on system PATH for glslc.")
endif()


find_program(GLSLC_COMPILER glslc
    HINTS ${GLSLC_HINTS} 
    DOC "GLSL to SPIR-V compiler")

if(NOT GLSLC_COMPILER)
    message(FATAL_ERROR "glslc compiler not found. \n"
                        "Ensure the Vulkan SDK is installed, glslc (or glslc.exe on Windows) is in your system PATH, \n"
                        "or the VULKAN_SDK environment variable is set correctly and points to the SDK root directory. \n"
                        "Checked hint paths (if VULKAN_SDK was set): ${GLSLC_HINTS}")
endif()
message(STATUS "Shader Compiler: Found glslc at ${GLSLC_COMPILER}")

set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glsl)
set(SHADER_BINARY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/compiled_shaders) 

file(MAKE_DIRECTORY ${SHADER_BINARY_OUTPUT_DIR})

set(GLSL_SHADER_SOURCES
    ${SHADER_SOURCE_DIR}/shader.vert
    ${SHADER_SOURCE_DIR}/shader.frag
)

set(COMPILED_SPIRV_FILES "") 

foreach(GLSL_SOURCE_FILE ${GLSL_SHADER_SOURCES})
    get_filename_component(BASENAME ${GLSL_SOURCE_FILE} NAME_WE) 
    get_filename_component(EXT ${GLSL_SOURCE_FILE} EXT)       
    # out file name: shader.vert.spv, shader.frag.spv 
    set(SPIRV_OUTPUT_FILE "${SHADER_BINARY_OUTPUT_DIR}/${BASENAME}${EXT}.spv")

    add_custom_command(
        OUTPUT ${SPIRV_OUTPUT_FILE}
        COMMAND ${GLSLC_COMPILER} ${GLSL_SOURCE_FILE} -o ${SPIRV_OUTPUT_FILE}
        DEPENDS ${GLSL_SOURCE_FILE} 
        COMMENT "Compiling ${GLSL_SOURCE_FILE} to ${SPIRV_OUTPUT_FILE}"
        VERBATIM 
    )
    list(APPEND COMPILED_SPIRV_FILES ${SPIRV_OUTPUT_FILE})
endforeach()

add_custom_target(ShaderCompilationTarget ALL
    DEPENDS ${COMPILED_SPIRV_FILES}
    COMMENT "Compiling all GLSL shaders to SPIR-V"
)