#!/bin/bash

SHADER_SOURCE_DIR="shaders" 
SHADER_OUTPUT_DIR="shaders/out"

mkdir -p "$SHADER_OUTPUT_DIR" 

echo "Compiling ${SHADER_SOURCE_DIR}/shader.vert..."
glslc "${SHADER_SOURCE_DIR}/shader.vert" -o "${SHADER_OUTPUT_DIR}/vert.spv"

echo "Compiling ${SHADER_SOURCE_DIR}/shader.frag..."
glslc "${SHADER_SOURCE_DIR}/shader.frag" -o "${SHADER_OUTPUT_DIR}/frag.spv"

echo "Shader compilation completed!"
echo "The output file is located '${SHADER_OUTPUT_DIR}/' Directory."