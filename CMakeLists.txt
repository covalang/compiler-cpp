set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

# Read the project name and version from vcpkg.json
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json VCPKG_JSON_STRING)
string(JSON PROJECT_NAME GET ${VCPKG_JSON_STRING} name)
string(JSON PROJECT_VERSION GET ${VCPKG_JSON_STRING} version)
# Define their macros
add_compile_definitions(EXECUTABLE_NAME="${PROJECT_NAME}")
add_compile_definitions(EXECUTABLE_VERSION="${PROJECT_VERSION}")

cmake_minimum_required(VERSION 3.21)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    magic_enum::magic_enum
    nlohmann_json::nlohmann_json
    CLI11::CLI11
)
