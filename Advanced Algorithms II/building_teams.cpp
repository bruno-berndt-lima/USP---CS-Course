#include <bits/stdc++.h>

using namespace std;

class Graph {
public:
    int n_vertices;
    list<int> *adjLists;
    bool *visited;
    vector<int> team;

    Graph(int V);
    void addEdge(int src, int dest);
    void DFS(int vertex, int current_team);
};

Graph::Graph(int vertices) {
    n_vertices = vertices;
    adjLists = new list<int>[vertices];
    visited = new bool[vertices];
    team = vector<int>(vertices, -1); // Inicializa todos alunos para nenhum time
}

void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);
}

void Graph::DFS(int vertex, int current_team) {
    if (visited[vertex])
        return;

    visited[vertex] = true;
    team[vertex] = current_team; // Insere o aluno no time atual

    list<int> adjList = adjLists[vertex];
    int next_team = (current_team == 1) ? 2 : 1; // Alterna os times (colorindo grafo)
    for (int neighbor : adjList) {
        if (team[neighbor] == current_team) {
            // Se um amigo esta no mesmo time, nao eh possivel dividi-los
            cout << "IMPOSSIBLE" << endl;
            exit(0);
        }

        if (team[neighbor] == -1) {
            DFS(neighbor, next_team);
        }
    }
}

int main() {
    int n_pupils, n_friendships;
    cin >> n_pupils >> n_friendships;

    Graph teams(n_pupils);

    int a, b;
    for (int i = 0; i < n_friendships; i++) {
        cin >> a >> b;
        teams.addEdge(a - 1, b - 1); // Comecar do 0
    }

    for (int i = 0; i < n_pupils; i++) {
        if (!teams.visited[i]) {
            // Realiza a dfs para alunos nao visitados
            teams.DFS(i, 1);
        }
    }

    for (int i = 0; i < n_pupils; i++) {
        cout << teams.team[i] << " ";
    }
    cout << endl;

    return 0;
}
