#ifndef PRACTICE_GRAPH_H
#define PRACTICE_GRAPH_H

#include <vector>
#include <list>

////////////////////////////////////////////////////////////////////////////////
struct Node
{
    int dest;
    int weight;
    Node (const int d, const int w) : dest(d), weight(w) {}
};

// Use adjacency list for an directed graph
using Graph = std::vector<std::list<Node>>;

// Add edge to an directed graph
auto add_directed_edge = [](Graph &g, int src, int dest, int wt = 0) {
    g[src].push_back({dest, wt});
};

// Add edge to an undirected graph
auto add_undirected_edge = [](Graph &g, int src, int dest, int wt = 0) {
    g[src].push_back({dest, wt});
    g[dest].push_back({src, wt});
};

////////////////////////////////////////////////////////////////////////////////

std::vector<int> bfs_traversal(const Graph& g, int v);

std::vector<int> dfs_traversal(const Graph &g, int v);

std::vector<int> dijkstra_shortest_path(const Graph& g, const int src);

#endif //PRACTICE_GRAPH_H
