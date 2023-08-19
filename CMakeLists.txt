cmake_minimum_required(VERSION 3.21)

#option(WITH_STATIC_CRT "Disable static CRT linking in ANTLR package" Off)
#include(IfWindowsThenUseStaticMdTriplet.cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

# Read the project name and version from vcpkg.json
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json VCPKG_JSON_STRING)
string(JSON PROJECT_NAME GET ${VCPKG_JSON_STRING} name)
string(JSON PROJECT_VERSION GET ${VCPKG_JSON_STRING} version)

# Define their macros
add_compile_definitions(EXECUTABLE_NAME="${PROJECT_NAME}")
add_compile_definitions(EXECUTABLE_VERSION="${PROJECT_VERSION}")

# MSVC
#if(POLICY CMP0091)
#    cmake_policy(SET CMP0091 NEW) # Enables use of MSVC_RUNTIME_LIBRARY
#endif()

# Normal CMake stuff
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

file(GLOB ANTLR_GENERATED_SOURCE_FILES src/grammar/generated/*.cpp)
add_executable(${PROJECT_NAME} src/main.cpp ${ANTLR_GENERATED_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC src/grammar/generated)

# MSVC
#set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# All the CMake targets provided by vcpkg
find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(SqliteOrm CONFIG REQUIRED)
find_package(antlr4-runtime)

target_include_directories(${PROJECT_NAME} PUBLIC ${ANTLR4_INCLUDE_DIR})

# MSVC
#if(VCPKG_TARGET_TRIPLET MATCHES "windows$")
#    set(ANTLR_TARGET_LINK_LIBRARY antlr4_shared)
#else()
#    set(ANTLR_TARGET_LINK_LIBRARY antlr4_static)
#endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
        magic_enum::magic_enum
        nlohmann_json::nlohmann_json
        CLI11::CLI11
        unofficial::sqlite3::sqlite3
        sqlite_orm::sqlite_orm
        ${ANTLR_TARGET_LINK_LIBRARY})