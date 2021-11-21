#pragma once
#include <vector>
#include <list>
#include <memory>
using namespace std;

class WeightedGraph :
{
private:
    /* data */
    int m_num_vertices;
    std::vector<std::list<pair<int,int>>> adjLists;

public:
    WeightedGraph(int V);
    int V() { return m_num_vertices; };

    const list<pair<int,int>>& adj(int s) { return adjLists[s]; }
    void addEdge(int src, int dst,int weight);
    ~WeightedGraph();
};

WeightedGraph::WeightedGraph(int V)
{
    m_num_vertices = V;

    adjLists.resize(m_num_vertices);
}

void WeightedGraph::addEdge(int src, int dst, int weight)
{
    adjLists[src].push_front(make_pair(dst,weight));
    adjLists[dst].push_front(make_pair(src,weight));
}

WeightedGraph::~WeightedGraph()
{
    adjLists.clear();
}
