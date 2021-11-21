/* Program to do Recursive BFS */
#include "UndirectedGraph.h"
#include <iostream>
#include <queue>
using namespace std;

class BFS
{
private:
    vector<bool> visited;
    queue<int> Q;

public:
    BFS(Graph &G);
    ~BFS();
    void bfs(Graph &G, int start);
};

BFS::BFS(Graph &G)
{
    visited.resize(G.V());
}

void BFS::bfs(Graph& G, int start)
{
    // insert node in the queue.
    Q.push(start);

    while(!Q.empty())
    {
        auto node = Q.front();
        Q.pop();
        visited[node] = true;
        for(const auto& vertex: G.getAdjLists(node))
        {
            if(!visited[vertex])
            {
                Q.push(vertex);
            }
        }
    }

}

BFS::~BFS()
{
    visited.clear();
}

int main()
{
    UndirectedGraph g(4);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    BFS bfs(g);

}
