#include "graph.h"

#include <vector>
#include <set>
#include <utility>
#include <climits>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Breadth-first traversal of a graph
////////////////////////////////////////////////////////////////////////////////
vector<int> bfs_traversal(const Graph& g, int v)
{
    vector<int> visits;

    vector<bool> visited(g.size());
    list<int> queue;

    visited[v] = true;
    queue.push_back(v);

    while(!queue.empty())
    {
        // Dequeue a v and visit it
        v = queue.front(); queue.pop_front();
        visits.push_back(v);

        // Loop through all adjacent vertices of v
        for(const auto& n : g[v])
        {
            if (!visited[n.dest])
            {
                visited[n.dest] = true;
                queue.push_back(n.dest);
            }
        }
    }
    return visits;
}
////////////////////////////////////////////////////////////////////////////////
// Depth-first traversal of a graph
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
// Dijkstra Shortest Path traversal of an undirected graph
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