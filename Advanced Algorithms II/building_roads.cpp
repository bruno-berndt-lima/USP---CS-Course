#include <bits/stdc++.h>

using namespace std;

class Graph {
public:
    int n_vertices;
    list<int> *adjLists;
    bool *visited;

    Graph(int V);
    void addEdge(int src, int dest);
    void DFS(int vertex);
};

Graph::Graph(int vertices) {
    n_vertices = vertices;
    adjLists = new list<int>[vertices];
    visited = new bool[vertices];
}

void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);
}

void Graph::DFS(int vertex) {
    if(visited[vertex]) 
        return;
    visited[vertex] = true;
    list<int> adjList = adjLists[vertex];
    for (int neighbor : adjList)
        DFS(neighbor);
}

int main() {
    int n_cities, n_roads;
    cin >> n_cities >> n_roads;

    Graph cities(n_cities + 1);

    int a, b;
    for (int i = 0; i < n_roads; i++) {
        cin >> a >> b;
        cities.addEdge(a, b);
    }
    
    vector<int> not_connected;
    int components = 0;

    for (int i = 1; i <= n_cities; i++) {
        if (!cities.visited[i]) {
            not_connected.push_back(i);
            cities.DFS(i);
            components++;
        }
    }

    cout << components - 1 << endl; 

    if (components > 1) {
        for (int i = 1; i < components; i++) {
            cout << not_connected[i - 1] << " " << not_connected[i] << endl;
        }
    }

    return 0;
}
