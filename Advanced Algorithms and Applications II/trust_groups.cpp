#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph, reversedGraph;
vector<int> order, component;
vector<bool> visited;
int P, T;

void dfs1(int v) {
    visited[v] = true;
    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs1(u);
        }
    }
    order.push_back(v);
}

void dfs2(int v) {
    visited[v] = true;
    component.push_back(v);
    for (int u : reversedGraph[v]) {
        if (!visited[u]) {
            dfs2(u);
        }
    }
}

int findMinimumGroups() { 
    // Primeira dfs para computar a ordem
    for (int i = 0; i < P; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    // Segunda dfs para encontrar as componentes fortemente conexas
    visited.assign(P, false);
    int minGroups = 0;

    for (int i = P - 1; i >= 0; i--) {
        int v = order[i];
        if (!visited[v]) {
            component.clear();
            dfs2(v);
            minGroups++;
        }
    }

    return minGroups;
}

int main() {
 while (cin >> P >> T && (P != 0 || T != 0)) {
        // Inicilaiza todas as estruturas usadas
        graph.clear();
        reversedGraph.clear();
        order.clear();
        visited.clear();
        visited.resize(P, false); // Muda o size do vetor de visitado para o novo numero de pessoas

        vector<string> people;
        string surname, firstName;

        for (int i = 0; i < P; i++) {
            cin >> surname >> firstName;
            surname[surname.length() - 1] = '\0';

            people.push_back(firstName + surname);
            // cout << people[i] << endl; 
        }

        // Le os relacionamentos e constroi o grafo
        graph.resize(P);
        reversedGraph.resize(P);
        for (int i = 0; i < T; i++) {
            string person1, person2;
            cin >> surname >> firstName;
            surname[surname.length() - 1] = '\0';
            person1 = firstName + surname;

            cin >> surname >> firstName;
            surname[surname.length() - 1] = '\0';
            person2 = firstName + surname;

            // Constroi o grafo usando os indices das duas pessoas no vetor de pessoas
            int index1 = find(people.begin(), people.end(), person1) - people.begin();
            int index2 = find(people.begin(), people.end(), person2) - people.begin();
            graph[index1].push_back(index2);
            reversedGraph[index2].push_back(index1);
        }

        int minGroups = findMinimumGroups();
        cout << minGroups << endl;
    }

    return 0;
}
