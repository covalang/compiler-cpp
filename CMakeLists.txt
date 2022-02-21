set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

cmake_minimum_required(VERSION 3.21)
project(main)

set(CMAKE_CXX_STANDARD 20)

find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE magic_enum::magic_enum)
target_link_libraries(main PRIVATE nlohmann_json nlohmann_json::nlohmann_json)