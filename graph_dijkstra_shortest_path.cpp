////////////////////////////////////////////////////////////////////////////////
// Dijkstra Shortest Path traversal of an undirected graph
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <list>
#include <set>
#include <utility>
#include <climits>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
struct Node
{
    int dest;
    int weight;
    Node (const int d, const int w) : dest(d), weight(w) {}
};

// Use adjacency list for an undirected graph
using Graph = vector<list<Node>>;

// Add edge to an undirected graph
auto add_edge = [](Graph &g, int src, int dest, int wt = 0) {
    g[src].push_back({dest, wt});
    g[dest].push_back({src, wt});
};

////////////////////////////////////////////////////////////////////////////////
vector<int> dijkstra_shortest_path(const Graph& g, const int src)
{
    // an array of dist from source to each vertex
    vector<int> dist(g.size(), INT_MAX);

    // set to store the distance from each vertex
    set<pair<int, int>> setds;

    // Insert source itself in set and initialize its distance as 0. 
    setds.insert(make_pair(0, src)); // Uses C++17 class template deduction
    dist[src] = 0;

    // Loop until all shortest distance are finalized
    while (!setds.empty())
    {
        auto [d, u] = *(setds.begin()); // Uses C++17 structured bindings
        setds.erase(setds.begin());     // Amortized constant complexity

        // Loop through all adjacent vertices of u
        for(const auto& n : g[u])
        {
            const int v = n.dest;
            const int weight = n.weight;

            // Is there a shorter path to v through u?
            if (dist[v] > dist[u] + weight)
            {
                // If distance of v is not INT_MAX then it must be in our set, 
                // so remove it and insert it again with updated less distance
                // so that it is reordered by the set
                if (dist[v] != INT_MAX)
                {
                    // Complexity is logarithmic in container size = log(N)
                    setds.erase( setds.find( {dist[v], v} ) );
                }

                // Update distance of v 
                dist[v] = dist[u] + weight;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Graph Traversal", "[classic]")
{
    Graph g(9);
    add_edge(g, 0, 1, 4);
    add_edge(g, 0, 7, 8);
    add_edge(g, 1, 2, 8);
    add_edge(g, 1, 7, 11);
    add_edge(g, 2, 3, 7);
    add_edge(g, 2, 8, 2);
    add_edge(g, 2, 5, 4);
    add_edge(g, 3, 4, 9);
    add_edge(g, 3, 5, 14);
    add_edge(g, 4, 5, 10);
    add_edge(g, 5, 6, 2);
    add_edge(g, 6, 7, 1);
    add_edge(g, 6, 8, 6);
    add_edge(g, 7, 8, 7);

    REQUIRE(dijkstra_shortest_path(g, 0) ==
                  vector<int>{0, 4, 12, 19, 21, 11, 9, 8, 14});
}