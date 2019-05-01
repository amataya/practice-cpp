include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/include)

# Essential
add_library(libbt STATIC binary_tree.cpp)
add_library(libtrie STATIC trie.cpp)
add_library(libgraph STATIC graph.cpp)

add_executable(algo_binary_tree algo_binary_tree.cpp)
target_link_libraries(algo_binary_tree libbt)

add_executable(algo_trie algo_trie.cpp)
target_link_libraries(algo_trie libtrie)

add_executable(algo_graph algo_graph.cpp)
target_link_libraries(algo_graph libgraph)
