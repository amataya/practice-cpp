cmake_minimum_required(VERSION 3.12)

project(practice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    add_compile_options(-Wall -Wextra -Wunreachable-code -Wpedantic -Wno-unused-variable -Wno-sign-compare)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)
    message("Compiler options set for Clang|AppleClang|GNU")
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # To be able to view std::map in debugger
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
    add_compile_options(-Wweak-vtables -Wmissing-noreturn )
    message("Compiler options set for Clang")
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /w44265 /w44061 /w44062 )
    message("Compiler options set for MSVC")
endif()

include_directories(include)
add_subdirectory(essential)
add_subdirectory(leetcode)
add_subdirectory(codility)
add_subdirectory(problems)


