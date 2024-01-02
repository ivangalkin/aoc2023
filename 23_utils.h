// see https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/


#ifndef AOC2023_23_UTILS_H
#define AOC2023_23_UTILS_H
// A C++ program to find single source longest distances
// in a DAG
#include <iostream>
#include <limits.h>
#include <list>
#include <stack>
#define NINF INT_MIN
using namespace std;

// Graph is represented using adjacency list. Every
// node of adjacency list contains vertex number of
// the vertex to which edge connects. It also
// contains weight of the edge
class AdjListNode {
    int v;
    int weight;

public:
    AdjListNode(int _v, int _w)
    {
        v = _v;
        weight = _w;
    }
    int getV() { return v; }
    int getWeight() { return weight; }
};

// Class to represent a graph using adjacency list
// representation
class Graph {
    int V; // No. of vertices'

    // Pointer to an array containing adjacency lists
    list<AdjListNode>* adj;

    // A function used by longestPath
    void topologicalSortUtil(int v, bool visited[],
                             stack<int>& Stack);

public:
    Graph(int V); // Constructor
    ~Graph(); // Destructor

    // function to add an edge to graph
    void addEdge(int u, int v, int weight);

    // Finds longest distances from given source vertex
    int longestPath(int s, int target);
};

Graph::Graph(int V) // Constructor
{
    this->V = V;
    adj = new list<AdjListNode>[V];
}

Graph::~Graph() // Destructor
{
    delete [] adj;
}


void Graph::addEdge(int u, int v, int weight)
{
    AdjListNode node(v, weight);
    adj[u].push_back(node); // Add v to u's list
}

// A recursive function used by longestPath. See below
// link for details
// https:// www.geeksforgeeks.org/topological-sorting/
void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<AdjListNode>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        AdjListNode node = *i;
        if (!visited[node.getV()])
            topologicalSortUtil(node.getV(), visited, Stack);
    }

    // Push current vertex to stack which stores topological
    // sort
    Stack.push(v);
}

// The function to find longest distances from a given vertex.
// It uses recursive topologicalSortUtil() to get topological
// sorting.
int Graph::longestPath(int s, int target)
{
    stack<int> Stack;
    int dist[V];

    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Initialize distances to all vertices as infinite and
    // distance to source as 0
    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;
    // Process vertices in topological order
    while (Stack.empty() == false) {
        // Get the next vertex from topological order
        int u = Stack.top();
        Stack.pop();

        // Update distances of all adjacent vertices
        list<AdjListNode>::iterator i;
        if (dist[u] != NINF) {
            for (i = adj[u].begin(); i != adj[u].end(); ++i){

                if (dist[i->getV()] < dist[u] + i->getWeight())
                    dist[i->getV()] = dist[u] + i->getWeight();
            }
        }
    }

    // Print the calculated longest distances
    for (int i = 0; i < V; i++)
        (dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";
    std::cout << std::endl;

    delete [] visited;

    return dist[target];
}
#endif //AOC2023_23_UTILS_H
