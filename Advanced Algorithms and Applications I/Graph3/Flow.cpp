#include <bits/stdc++.h>

using namespace std;

#define MAX 101

int AdjMatrix[MAX][MAX] = {};
int rgrafo[MAX][MAX];
int pai[MAX];

void clearAdjMatrix(int matrix[][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            AdjMatrix[i][j] = 0;
        }
    }
}

bool caminho(int s, int t, int V){  // implementacao direta BFS...!!!!
	queue<int> q;

	q.push(s);
	pai[s] = -1;

	int visitado[V];
	memset(visitado, 0, sizeof visitado);
	visitado[s] = 1;

	while (!q.empty()){
		int u = q.front(); q.pop();
		
		// para todo v adj a u
		for (int v = 0; v < V; ++v){
			// so entra na fila se TIVER RESIDUO e NAO visitado..
			if (rgrafo[u][v]>0 && visitado[v] == 0) {
				q.push(v);
				pai[v] = u;
				visitado[v] = 1;
			}
		}
	}
	// verifica se tem caminho de s para t
	return (visitado[t] == 1);
}

int ff(int grafo[][MAX], int V, int s, int t){  // edmonds-karp !!!!!!
	int u;


	// o grafo residual é o inicialmente o grafo original...
	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			rgrafo[i][j] = grafo[i][j];

	int maxFlow = 0;

	while (caminho(s,t, V)){     // enquanto tem augmented path !!!!!
		//printMat(rgrafo,V); printf("**********************\n");
		int gargalo = 100000;
		// calcular o gargalo....
		for (int v = t; v!=s; v = pai[v]){
			u = pai[v];
			gargalo = min(gargalo, rgrafo[u][v]);
		}

		// Atualiza o forward e backward edges...
		for (int v = t; v!=s; v = pai[v]){
			u = pai[v];
			rgrafo[u][v] -= gargalo;  // FORWARD EDGE
			//rgrafo[v][u] += gargalo;  // BACKWARD EDGE !!!
		}
		maxFlow += gargalo;
	}

	return maxFlow;

}

int main() {
    int nodes;
    int network = 0;
    cin >> nodes;

    while(nodes != 0) {
        int source, dest, edges;
        cin >> source >> dest >> edges;
        
        clearAdjMatrix(AdjMatrix);
        int a, b, weight;
        for (int i = 0; i < edges; i++) {
            cin >> a >> b >> weight;
            AdjMatrix[a - 1][b - 1] += weight;
            AdjMatrix[b - 1][a - 1] += weight;
        }
        
        int res = ff(AdjMatrix, nodes, source - 1, dest - 1);
        network++;
        
        cout << "Network " << network << endl;
        cout << "The bandwidth is " << res << "." << endl;

        cin >> nodes;
        if (nodes != 0) 
            cout << endl;
    }
}
