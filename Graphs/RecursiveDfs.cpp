/* Program to do Recursive DFS */
#include "Graph.h"
#include <iostream>
using namespace std;

class RecursiveDfs
{
private:
    vector<bool> visited;
    void doDfs(Graph &G, int v);

public:
    RecursiveDfs(Graph &G, int S);
    ~RecursiveDfs();
};

RecursiveDfs::RecursiveDfs(Graph &G, int S)
{
    visited.resize(G.V());
    doDfs(G, S);
}

void RecursiveDfs::doDfs(Graph &G, int v)
{
    // mark visited as true
    visited[v] = true;
    cout << v << " ";
    // Iterate over adjacency lists of v
    for (const auto &w : *G.getAdjLists(v))
    {
        if (!visited[w])
        {
            doDfs(G, w);
        }
    }
}

RecursiveDfs::~RecursiveDfs()
{
}

int main()
{
    Graph g(4);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    RecursiveDfs dfs(g, 1);
}
