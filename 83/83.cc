/*

   In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by moving left, right, up, and down, is indicated in bold red and is equal to 2297.

   131 673 234 103  19
   201  96 342 965 150
   630 803 746 422 111
   537 699 497 121 956
   805 732 524  37 331

   131 -> 201 -> 96 -> 342 -> 234 -> 103 -> 18 -> 150 -> 111 -> 422 -> 121 -> 37 -> 331 - 2297

   Find the minimal path sum, in matrix.txt a 31K text file containing a 80 by 80 matrix, from the top left to the bottom right by moving left, right, up, and down.
*/

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <limits>

#define ROWS 80
#define COLUMNS 80

using namespace std;

class DirectedGraph
{
    public:
        set<int> GetVertices();
        void AddEdge(int, int, int);
        vector< pair<int,int> > GetEdges(int);
    private:
        set<int> vertices;
        map<int, vector< pair<int, int> > > adjacencyList;  // Key is the starting vertex
                                                            // Each pair is destination + weight
};

vector< vector<int> > LoadMatrix()
{
    int temp;
    vector< vector<int> > toReturn;

    fstream fin("matrix.txt");

    for (int row=0; row<ROWS; ++row)
    {
        toReturn.push_back(vector<int>());

        for (int col=0; col<COLUMNS; ++col)
        {
            fin >> temp;
            toReturn[row].push_back(temp);
        }
    }

    return toReturn;
}

int GetVerticeNumber(int row, int col, int maxCol)
{
    return row * maxCol + col;
}

DirectedGraph LoadGraph()
{
    DirectedGraph toReturn;

    vector< vector<int> > matrix = LoadMatrix();

    for (int row=0; row<matrix.size(); ++row)
    {
        for (int col=0; col<matrix[0].size(); ++col)
        {
            int start = GetVerticeNumber(row, col, matrix[0].size());
            int destination;
            int weight;

            // Up
            if (row > 0)
            {
                destination = GetVerticeNumber(row - 1, col, matrix[0].size());
                weight = matrix[row-1][col];
                toReturn.AddEdge(start, destination, weight);
            }

            // Down
            if (row < matrix.size() - 1)
            {
                destination = GetVerticeNumber(row + 1, col, matrix[0].size());
                weight = matrix[row+1][col];
                toReturn.AddEdge(start, destination, weight);
            }

            // Left
            if (col > 0)
            {
                destination = GetVerticeNumber(row, col - 1, matrix[0].size());
                weight = matrix[row][col-1];
                toReturn.AddEdge(start, destination, weight);
            }

            // Right
            if (col < matrix[0].size() - 1)
            {
                destination = GetVerticeNumber(row, col + 1, matrix[0].size());
                weight = matrix[row][col+1];
                toReturn.AddEdge(start, destination, weight);
            }

        }
    }

    return toReturn;
}

map<int,int> SetEachVerticeToInfinity(set<int> vertices)
{
    map<int,int> toReturn;

    for (set<int>::iterator sit = vertices.begin(); sit != vertices.end(); ++sit)
    {
        toReturn[*sit] = numeric_limits<int>::max();
    }

    return toReturn;
}

int GetMinimumDistanceVertex(const set<int> &vertices, map<int,int> &distances)
{
    int minimum = numeric_limits<int>::max();
    int minimumDistanceVertex = -1;

    for (set<int>::const_iterator sit = vertices.begin(); sit != vertices.end(); ++sit)
    {
        if (distances[*sit] < minimum)
        {
            minimum = distances[*sit];
            minimumDistanceVertex = *sit;
        }
    }

    return minimumDistanceVertex;
}

// Runtime: O(V * (V + log(V))) + O(E) = O(V^2)
map<int,int> DijkstrasAlgorithm(DirectedGraph graph, int start)
{
    set<int> vertices = graph.GetVertices();
    map<int,int> distances = SetEachVerticeToInfinity(vertices);

    distances[start] = 0;

    while (!vertices.empty())                       // O(V)
    {
        int minimumDistanceVertex = GetMinimumDistanceVertex(vertices, distances);  // O(V)
        vertices.erase(minimumDistanceVertex);      // O(log(V))

        vector< pair<int,int> > edges = graph.GetEdges(minimumDistanceVertex);

        for (int i=0; i<edges.size(); ++i)          // Total is O(E)
        {
            pair<int,int> edge = edges[i];
            int v = edge.first;
            int uTovEdgeCost = edge.second;
            int tentativeDistance = distances[minimumDistanceVertex] + uTovEdgeCost;

            if (tentativeDistance < distances[v])
            {
                distances[v] = tentativeDistance;   // O(1)
            }
        }
    }

    return distances;
}

/*
   Pseudo Code for Dijkstra's Algorithm

   1  function Dijkstra(Graph, source):
   2
   3      create vertex set Q
   4
   5      for each vertex v in Graph:             // Initialization
   6          dist[v] ← INFINITY                  // Unknown distance from source to v
   7          prev[v] ← UNDEFINED                 // Previous node in optimal path from source
   8          add v to Q                          // All nodes initially in Q (unvisited nodes)
   9
   10     dist[source] ← 0                        // Distance from source to source
   11
   12     while Q is not empty:
   13         u ← vertex in Q with min dist[u]    // Source node will be selected first
   14         remove u from Q 
   15
   16         for each neighbor v of u:           // where v is still in Q.
   17             alt ← dist[u] + length(u, v)
   18             if alt < dist[v]:               // A shorter path to v has been found
   19                 dist[v] ← alt 
   20                 prev[v] ← u 
   21
   22     return dist[], prev[]
*/

int DijkstrasAlgorithm(const DirectedGraph &graph, int start, int destination)
{
    map<int,int> distances = DijkstrasAlgorithm(graph, start);

    for (map<int,int>::iterator mit = distances.begin(); mit != distances.end(); ++mit)
    {
        if (mit->first == destination)
        {
            return mit->second;
        }
    }

    return -1;
}

int GetMinimalPathSum()
{
    DirectedGraph graph = LoadGraph();

    // Starting in an empty node. This is to include the cost of the first edge
    graph.AddEdge(-1, 0, 4445);

    int minimalPathSum = DijkstrasAlgorithm(graph, -1, ROWS * COLUMNS - 1);

    return minimalPathSum;
}

int main()
{
    cout << GetMinimalPathSum() << endl;
    return 0;
}

set<int> DirectedGraph::GetVertices()
{
    return vertices;
}

void DirectedGraph::AddEdge(int start, int destination, int weight)
{
    vertices.insert(start);

    adjacencyList[start].push_back(make_pair(destination,weight));
}

vector< pair<int,int> > DirectedGraph::GetEdges(int start)
{
    return adjacencyList[start];
}

