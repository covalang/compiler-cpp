set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

# Read the project name and version from vcpkg.json
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json VCPKG_JSON_STRING)
string(JSON PROJECT_NAME GET ${VCPKG_JSON_STRING} name)
string(JSON PROJECT_VERSION GET ${VCPKG_JSON_STRING} version)

# Define their macros
add_compile_definitions(EXECUTABLE_NAME="${PROJECT_NAME}")
add_compile_definitions(EXECUTABLE_VERSION="${PROJECT_VERSION}")

# Normal CMake stuff
cmake_minimum_required(VERSION 3.21)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/lexer/lex.cpp)

# All the CMake targets provided by vcpkg
find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(SqliteOrm CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    magic_enum::magic_enum
    nlohmann_json::nlohmann_json
    CLI11::CLI11
    unofficial::sqlite3::sqlite3
    sqlite_orm::sqlite_orm)

#add_custom_command(
#    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer/lex.cpp
#    PRE_BUILD
#    COMMAND pwsh ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer/run-re2c.ps1)