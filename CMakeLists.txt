cmake_minimum_required(VERSION 4.3)
project(index CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(index_core STATIC
    File/FileRecord.cpp
        File/FileRecord.h
        File/FileFlags.h
        Index/SystemIndex.cpp
        Index/SystemIndex.h
)

target_include_directories(index_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(index main.cpp
        Scanner/FileScanner.cpp
        Scanner/FileScanner.h)
target_link_libraries(index PRIVATE index_core)

# === Tests ===
include(FetchContent)
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_executable(index_tests
    tests/test_file_flags.cpp
)

target_link_libraries(index_tests PRIVATE index_core Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(index_tests)