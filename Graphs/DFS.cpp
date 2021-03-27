/* Program to do Recursive DFS */
#include "Graph.h"
#include <iostream>
#include <stack>
using namespace std;

class DFS
{
private:
    vector<bool> visited;
    stack<int> vertex_stack;
    void doDfs(Graph &G, int v);

public:
    DFS(Graph &G);
    void doRecursiveDfs(Graph &G, int S);
    void doIterativeDfs(Graph &G, int S);
    ~DFS();
};

DFS::DFS(Graph &G)
{
    visited.resize(G.V());
}

void DFS::doRecursiveDfs(Graph &G, int S)
{
    doDfs(G, S);
}

void DFS::doDfs(Graph &G, int v)
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

void DFS::doIterativeDfs(Graph &G, int S)
{
    visited.resize(G.V());

    vertex_stack.push(S);

    while (!vertex_stack.empty())
    {
        auto v = vertex_stack.top();
        vertex_stack.pop();
        if (!visited[v])
        {
            visited[v] = true;
            cout << v << " ";
        }

        for (const auto &w : *G.getAdjLists(v))
        {
            if (!visited[w])
            {
                vertex_stack.push(w);
            }
        }
    }
}

DFS::~DFS()
{
}

int main()
{
    Graph g(4);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    DFS dfs(g);
    cout << " DFS for node 1: ";
    dfs.doRecursiveDfs(g, 1);
    cout << endl;

    DFS dfs2(g);
    cout << " DFS for node 1: ";
    dfs2.doIterativeDfs(g, 1);
    cout << endl;
}
