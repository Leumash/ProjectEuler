/*
The following undirected network consists of seven vertices and twelve edges with a total weight of 243.


The same network can be represented by the matrix below.

            A   B   C   D   E   F   G
        A   -   16  12  21  -   -   -
        B   16  -   -   17  20  -   -
        C   12  -   -   28  -   31  -
        D   21  17  28  -   18  19  23
        E   -   20  -   18  -   -   11
        F   -   -   31  19  -   -   27
        G   -   -   -   23  11  27  -

However, it is possible to optimise the network by removing some edges and still ensure that all points on the network remain connected. The network which achieves the maximum saving is shown below. It has a weight of 93, representing a saving of 243 − 93 = 150 from the original network.


Using network.txt (right click and 'Save Link/Target As...'), a 6K text file containing a network with forty vertices, and given in matrix form, find the maximum saving which can be achieved by removing redundant edges whilst ensuring that the network remains connected.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

struct Edge
{
    int vertex;
    int weight;
    Edge(int v, int w) : vertex(v), weight(w) {}
    operator < (const Edge &other) const
    {
        return weight < other.weight;
    }
};

class Graph
{
    public:
        void AddVertex(int vertex);
        void AddEdge(int u, int v, int weight);
        vector<int> GetVertices() const;
        const vector<Edge>& GetEdges(int vertex) const;
    private:
        unordered_map<int,vector<Edge>> adjacencyList;
};

struct MyCompare
{
    public:
        bool operator()(const pair<int,Edge> &a, const pair<int,Edge> &b) const
        {
            return a.second.weight > b.second.weight;
        }
};

void Graph::AddVertex(int vertex)
{
    if (adjacencyList.count(vertex) == 0)
    {
        adjacencyList[vertex] = vector<Edge>();
    }
}

void Graph::AddEdge(int u, int v, int weight)
{
    AddVertex(u);
    AddVertex(v);

    adjacencyList[u].push_back(Edge(v,weight));
}

vector<int> Graph::GetVertices() const
{
    vector<int> vertices;

    for (const auto vertexToNeighbors : adjacencyList)
    {
        vertices.push_back(vertexToNeighbors.first);
    }

    return vertices;
}

const vector<Edge>& Graph::GetEdges(int vertex) const
{
    return adjacencyList.at(vertex);
}

Graph GetGraph()
{
    Graph graph;

    string edgeWeight;
    string line;
    ifstream fin("network.txt");

    int u = 0;

    while (getline(fin, line))
    {
        stringstream ss;

        ss << line;

        int v = 0;

        while (ss >> edgeWeight)
        {
            if (edgeWeight != "-")
            {
                graph.AddEdge(u, v, stoi(edgeWeight));
            }

            ++v;
        }

        ++u;
    }

    return graph;
}

int GetTotalWeight(const Graph &graph)
{
    int total = 0;

    vector<int> vertices = graph.GetVertices();

    for (int vertex : vertices)
    {
        for (const Edge &edge : graph.GetEdges(vertex))
        {
            total += edge.weight;
        }
    }

    return total / 2;
}

Graph PrimsAlgorithm(const Graph &graph)
{
    Graph minimumSpanningTree;

    unordered_set<int> visited;
    vector<int> vertices = graph.GetVertices();
    priority_queue<pair<int,Edge>, vector<pair<int,Edge>>, MyCompare> pQueue;

    visited.insert(vertices[0]);

    for (const Edge &edge : graph.GetEdges(vertices[0]))
    {
        pQueue.push(make_pair(vertices[0],edge));
    }

    while (visited.size() < vertices.size())
    {
        while (visited.count(pQueue.top().second.vertex) > 0)
        {
            pQueue.pop();
        }

        pair<int,Edge> greedyChoice = pQueue.top();
        pQueue.pop();
        visited.insert(greedyChoice.second.vertex);
        minimumSpanningTree.AddEdge(greedyChoice.first, greedyChoice.second.vertex, greedyChoice.second.weight);
        minimumSpanningTree.AddEdge(greedyChoice.second.vertex, greedyChoice.first, greedyChoice.second.weight);

        for (const Edge &edge : graph.GetEdges(greedyChoice.second.vertex))
        {
            pQueue.push(make_pair(greedyChoice.second.vertex, edge));
        }
    }

    return minimumSpanningTree;
}

int GetMaximumSaving()
{
    Graph graph = GetGraph();

    int totalWeight = GetTotalWeight(graph);

    graph = PrimsAlgorithm(graph);

    int mstWeight = GetTotalWeight(graph);

    return totalWeight - mstWeight;
}

int main()
{
    cout << GetMaximumSaving() << endl;

    return 0;
}

