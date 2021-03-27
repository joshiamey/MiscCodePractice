#pragma once
#include <vector>
#include <memory>
using namespace std;

class Graph
{
private:
    /* data */
    int m_num_vertices;
    std::vector<std::vector<int>> adjLists;

public:
    Graph(int V);
    int V() { return m_num_vertices; };

    const vector<int> *getAdjLists(int s) { return &adjLists[s]; }
    void addEdge(int src, int dst);
    ~Graph();
};

Graph::Graph(int V)
{
    m_num_vertices = V;

    adjLists.resize(m_num_vertices);
}

void Graph::addEdge(int src, int dst)
{
    adjLists[src].push_back(dst);
    adjLists[dst].push_back(src);
}

Graph::~Graph()
{
}
