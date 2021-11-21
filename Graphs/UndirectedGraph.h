#include "Graph.h"

class UndirectedGraph : public Graph
{
private:
    /* data */
public:
    UndirectedGraph(int V);
    ~UndirectedGraph();
    void addEdge(int u , int v) override;
};

UndirectedGraph::UndirectedGraph(int V):
    Graph(V)
{
}

UndirectedGraph::~UndirectedGraph()
{
}

void UndirectedGraph::addEdge(int u,int v) 
{
    adjLists[u].push_front(v);
    adjLists[v].push_front(u);
}