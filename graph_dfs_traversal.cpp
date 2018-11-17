////////////////////////////////////////////////////////////////////////////////
// Depth-first traversal of a graph
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <list>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
struct Node
{
    int dest;
    int weight;
    Node (const int d, const int w) : dest(d), weight(w) {}
};

// Use adjacency list for an directed graph
using Graph = vector<list<Node>>;

// Add edge to an directed graph
auto add_edge = [](Graph &g, int src, int dest, int wt = 0) {
    g[src].push_back({dest, wt});
};

////////////////////////////////////////////////////////////////////////////////
void dfs_util(const Graph& g, vector<int>& path, vector<bool>& visited, int v)
{
    visited[v] = true;
    path.push_back(v);

    // Loop through all adjacent vertices of v
    for(const auto& n : g[v])
        if (!visited[n.dest])
            dfs_util(g, path, visited, n.dest);
}

vector<int> dfs_traversal(const Graph &g, int v)
{
    vector<int> path;
    vector<bool> visited(g.size());
    dfs_util(g, path, visited, v);
    return path;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Graph Traversal", "[classic]")
{
    Graph g(4);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 2, 0);
    add_edge(g, 2, 3);
    add_edge(g, 3, 3);

    REQUIRE(dfs_traversal(g, 2) == vector<int>{2, 0, 1, 3});
}