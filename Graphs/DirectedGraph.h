#include "Graph.h"

class DirectedGraph : public Graph
{
private:
    /* data */
public:
    DirectedGraph(int vertices);
    ~DirectedGraph();
    void addEdge(int u , int v) override;
};

DirectedGraph::DirectedGraph(int vertices):
    Graph(vertices)
{
}

DirectedGraph::~DirectedGraph()
{
}

void DirectedGraph::addEdge(int u,int v) 
{
    adjLists[u].push_front(v);
}
