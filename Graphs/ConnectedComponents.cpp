/* Program to do Recursive DFS */
#include "Graph.h"
#include <iostream>
using namespace std;

class ConnectedComponents
{
private:
    vector<bool> visited;
    vector<vector<int>> connectedComponents;
    void doDfs(Graph &G, int v, vector<int> &component);

public:
    ConnectedComponents(Graph &G);
    void printConnectedComponents();
    int getConnectedComponents();
    ~ConnectedComponents();
};

ConnectedComponents::ConnectedComponents(Graph &G)
{
    visited.resize(G.V());

    for (auto i = 0; i < G.V(); ++i)
    {
        if (!visited[i])
        {
            vector<int> comp;
            doDfs(G, i, comp);
            connectedComponents.push_back(comp);
        }
    }
}

void ConnectedComponents::doDfs(Graph &G, int v, vector<int> &component)
{
    // mark visited as true
    visited[v] = true;
    component.push_back(v);
    // Iterate over adjacency lists of v
    for (const auto &w : *G.getAdjLists(v))
    {
        if (!visited[w])
        {
            doDfs(G, w, component);
        }
    }
}

void ConnectedComponents::printConnectedComponents()
{
    for (const auto &comp : connectedComponents)
    {
        for (const auto &v : comp)
            cout << v << " ";

        cout << endl;
    }
}

int ConnectedComponents::getConnectedComponents()
{
    return connectedComponents.size();
}

ConnectedComponents::~ConnectedComponents()
{
}

int main()
{
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(3, 4);
    g.addEdge(5, 5);

    ConnectedComponents cc(g);
    cout << "Noof components: " << cc.getConnectedComponents() << endl;
    cc.printConnectedComponents();
}
