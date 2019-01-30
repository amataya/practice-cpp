////////////////////////////////////////////////////////////////////////////////
// Executable to test graph algorithms
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "graph.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Graph Traversal - BFS", "[classic]")
{
    Graph g(4);
    add_directed_edge(g, 0, 1);
    add_directed_edge(g, 0, 2);
    add_directed_edge(g, 1, 2);
    add_directed_edge(g, 2, 0);
    add_directed_edge(g, 2, 3);
    add_directed_edge(g, 3, 3);

    REQUIRE(bfs_traversal(g, 2) == vector<int>{2, 0, 3, 1});
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Graph Traversal - DFS", "[classic]")
{
    Graph g(4);
    add_directed_edge(g, 0, 1);
    add_directed_edge(g, 0, 2);
    add_directed_edge(g, 1, 2);
    add_directed_edge(g, 2, 0);
    add_directed_edge(g, 2, 3);
    add_directed_edge(g, 3, 3);

    REQUIRE(dfs_traversal(g, 2) == vector<int>{2, 0, 1, 3});
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Graph Traversal", "[classic]")
{
    Graph g(9);
    add_undirected_edge(g, 0, 1, 4);
    add_undirected_edge(g, 0, 7, 8);
    add_undirected_edge(g, 1, 2, 8);
    add_undirected_edge(g, 1, 7, 11);
    add_undirected_edge(g, 2, 3, 7);
    add_undirected_edge(g, 2, 8, 2);
    add_undirected_edge(g, 2, 5, 4);
    add_undirected_edge(g, 3, 4, 9);
    add_undirected_edge(g, 3, 5, 14);
    add_undirected_edge(g, 4, 5, 10);
    add_undirected_edge(g, 5, 6, 2);
    add_undirected_edge(g, 6, 7, 1);
    add_undirected_edge(g, 6, 8, 6);
    add_undirected_edge(g, 7, 8, 7);

    REQUIRE(dijkstra_shortest_path(g, 0) ==
            vector<int>{0, 4, 12, 19, 21, 11, 9, 8, 14});
}