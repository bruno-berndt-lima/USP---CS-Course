#include<bits/stdc++.h>

using namespace std;

#define INF LLONG_MAX
bool hasNegCycle = false;

// struct para representar uma aresta com peso no grafo
struct Edge {
    int src, dest;
    long long int weight;
};
 
// struct para representar um grafo conexo, direcionado e com peso
struct Graph {
    // V: numero de vertices, E: numero de arestas
    int V, E;
 
    // grafo eh representado por um vetor de arestas
    struct Edge* edge;
};
 
// cria um grafo com V vertices e E arestas
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}
 
// funcao que encontra o caminho mais curto de um vertice inicial
// para todos os outros vertices. Tbm detecta ciclos negativos
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    long long int dist[V];
 
    // inicializa as distancias do vertice inicial para todos os 
    // outros como INFINITO
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    // relaxa todas as arestas V-1 vezes. Um caminho mais curto do
    // vertice inicial para qualquer outro pode ter no maximo V-1 arestas
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            long long int weight = graph->edge[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
 
    // checa ciclo negativos. O passo acima garante as distancias
    // minimas se o grafo nao tem ciclo negativo. Se acharmos uma caminho menor
    // entao existe um ciclo negativo
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            hasNegCycle = true;
            return; 
        }
    }
  
    return;
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    struct Graph* graph = createGraph(nodes, edges);

    int a, b, c;
    for (int i = 0; i < edges; i++) {
        cin >> a >> b >> c;
        graph->edge[i].src = a;
        graph->edge[i].dest = b;
        graph->edge[i].weight = c;
    }

    BellmanFord(graph, 0);

    hasNegCycle ? cout << "YES\n" : cout << "NO\n";        
}