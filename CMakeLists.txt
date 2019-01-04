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

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Essential
add_library(libbt STATIC binary_tree.cpp)

# Add Executables below
add_subdirectory(codility)
add_subdirectory(leetcode)

add_executable(algo_bfsgraph graph_bfs_traversal.cpp)
add_executable(algo_dfsgraph graph_dfs_traversal.cpp)
add_executable(algo_dijkstra graph_dijkstra_shortest_path.cpp)
add_executable(algo_binary_tree binary_tree_app.cpp)
target_link_libraries(algo_binary_tree libbt)

# Other
add_executable(exer_wtjbsched weighted_job_scheduling.cpp)
add_executable(exer_formatnum format_number_into_currency.cpp)
add_executable(exer_revsent reverse_sentence.cpp)
add_executable(exer_wayssum count_ways_of_sum.cpp)
add_executable(exer_avggroup average_of_groups.cpp)
add_executable(exer_firstoccr first_occurrence_of_number.cpp)
add_executable(exer_missingwrd find_missing_words.cpp)
add_executable(exer_valtriangle array_values_form_triangle.cpp)
add_executable(exer_firstunique first_unique_number.cpp)
add_executable(exer_lexiorder lexicographic_ordering_numbers.cpp)
add_executable(exer_lenlongsubseq length_of_longest_subsequence_with_given_sum.cpp)

