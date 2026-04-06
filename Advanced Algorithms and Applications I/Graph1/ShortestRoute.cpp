#include <bits/stdc++.h>

using namespace std;

// MAX: numero max de vertices
#define MAX 1000
// INF: valor usado para vertices nao conectados
#define INF LLONG_MAX

// matriz de adjacencia inicial
long long int AdjMatrix[MAX][MAX];
// matriz de distancia minima entre os vertices
long long int dist[MAX][MAX];


// algoritmo para encotrar a distancia minima para todos os pares de vertices
void floydWarshall(long long int AdjMatrix[][MAX], int nVertices) {
    int i, j, k;
    // matriz de distancias minimas entre cada par de vertices

    for (i = 0; i < nVertices; i++) {
        for (j = 0; j < nVertices; j++) {
            if (i == j) {
                dist[i][j] = 0;
                continue;
            }
            dist[i][j] = AdjMatrix[i][j];
        }
    }

    for (k = 0; k < nVertices; k++) {
        // pega todos os vertices como partida um por um
        for (i = 0; i < nVertices; i++) {
            // pega todos os vertices como destino para a escolha acima
            for (j = 0; j < nVertices; j++) {
                // se o vertice k esta no caminho mais curto de i para j, entao atualiza dist[i][j]
                if(dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }      
            }
        }
    }
}

int main() {
    // cities == vertices, roads == arestas
    int cities, roads, queries;
    cin >> cities >> roads >> queries;

    for (int i = 0; i < cities; i++) {
        for (int j = 0; j < cities; j++) {
            AdjMatrix[i][j] = INF;
        }
    }

    // "a" e "b" duas cidades com distancia "c" entre si
    int a, b, c;
    for (int i = 0; i < roads; i++) {
        cin >> a >> b >> c;
        AdjMatrix[a-1][b-1] = c;
        AdjMatrix[b-1][a-1] = c;
    }
   
    floydWarshall(AdjMatrix, cities);

    int source, dest;
    while (queries > 0) {
        cin >> source >> dest;
        dist[source - 1][dest - 1] != INF ? cout << dist[source - 1][dest - 1] << endl : cout << -1 << endl;
        queries--;
    }
}