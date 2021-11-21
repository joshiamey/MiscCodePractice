#pragma once
#include <vector>
#include <forward_list>
#include <memory>
using namespace std;

class Graph
{
private:
    /* data */
    int m_num_vertices;

protected:
    std::vector<std::forward_list<int>> adjLists;

public:
    Graph(int V);
    int V() { return m_num_vertices; };

    const forward_list<int>& getAdjLists(int s) { return adjLists[s]; }
    virtual void addEdge(int src, int dst)= 0;
    virtual ~Graph();
};

Graph::Graph(int V)
{
    m_num_vertices = V;

    adjLists.resize(m_num_vertices);
}

Graph::~Graph()
{
}
