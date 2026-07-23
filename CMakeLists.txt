cmake_minimum_required(VERSION 3.20)
project(luasoup VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Export symbols policy
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wshadow -O3)
endif()

# JNI Detection & Fallback
find_package(JNI QUIET)
if(JNI_FOUND)
    include_directories(${JNI_INCLUDE_DIRS})
else()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/nrp/jni_stub)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compiler/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/luau/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lexbor/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lonejson_upstream/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lexbor_upstream/source
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/luau_upstream/VM/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/luau_upstream/Compiler/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/luau_upstream/Ast/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/re2_upstream
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mbedtls_upstream/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs_upstream
)

# Third-Party Vendor Libraries
add_library(third_party_luau STATIC third_party/luau/src/luau.cpp)
add_library(third_party_lexbor STATIC third_party/lexbor/src/lexbor.c)

# Core Library Sources
set(NRP_CORE_SOURCES
    src/core/memory.cpp
    src/core/runtime.cpp
    src/core/service.cpp
    src/core/error.cpp
    src/reflection/registry.cpp
    src/bridge/conversion.cpp
    src/luau/luau_engine.cpp
    src/dsl/dsl.cpp
    src/modules/html.cpp
    src/modules/json.cpp
    src/modules/buffer.cpp
    src/modules/url.cpp
    src/modules/crypto.cpp
    src/modules/regex.cpp
    src/modules/encoding.cpp
    src/modules/utility.cpp
    src/modules/js.cpp
    generated/jni/nrp_jni_bridge.cpp
)

# Create Core Native Libraries (Static & Shared .so)
add_library(nrp_core STATIC ${NRP_CORE_SOURCES})
target_include_directories(nrp_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/third_party/luau/include ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lexbor/include)
target_link_libraries(nrp_core PRIVATE third_party_luau third_party_lexbor)

add_library(nrp_core_shared SHARED ${NRP_CORE_SOURCES})
set_target_properties(nrp_core_shared PROPERTIES OUTPUT_NAME "nrp_core")
target_include_directories(nrp_core_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/third_party/luau/include ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lexbor/include)
target_link_libraries(nrp_core_shared PRIVATE third_party_luau third_party_lexbor)

# Create NRP Compiler Library & Executable
set(NRPC_SOURCES
    compiler/src/parser.cpp
    compiler/src/analyzer.cpp
    compiler/src/ir.cpp
    compiler/src/generator.cpp
)

add_library(nrpc_lib STATIC ${NRPC_SOURCES})
target_include_directories(nrpc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/compiler/include ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(nrpc_lib PRIVATE nrp_core)

add_executable(nrpc compiler/src/main.cpp)
target_link_libraries(nrpc PRIVATE nrpc_lib nrp_core)

# Auto-run nrpc on specs/ after building nrpc (only when host building, not cross-compiling)
if(NOT CMAKE_CROSSCOMPILING)
    add_custom_command(
        TARGET nrpc POST_BUILD
        COMMAND $<TARGET_FILE:nrpc> ${CMAKE_CURRENT_SOURCE_DIR}/specs
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running NRP Compiler (nrpc) to auto-generate JNI, Reflection, and Kotlin SDK bindings..."
    )
endif()

# Enable Testing
enable_testing()
add_subdirectory(tests)
