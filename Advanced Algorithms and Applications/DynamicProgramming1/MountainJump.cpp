#include <bits/stdc++.h>

using namespace std;

int calcEnergy(vector<int> heights, int n) {
    // vetor de "distâncias" que guarda em cada 
    // posição o menor custo para chegar até ela
    vector<int> distances(n);
    
    // 0 -> 0 = 0
    distances[0] = 0;
    // 0 -> 1 = |h[0] - h[1]| (módulo das diferenças de altura das montanhas)
    distances[1] = abs(heights[0] - heights[1]);
    distances[2] = INT_MAX;
    if (n > 2) 
        // 0 - > 2 = minimo (|h[0] - h[2]| + d[0] , |h[1] - h[2]| + d[1])
        distances[2] = min(abs(heights[0] - heights[2]) + distances[0], abs(heights[1] - heights[2]) + distances[1]);

    for (int i = 3; i < n; i++) {
        distances[i] = min(abs(heights[i - 2] - heights[i]) + distances[i - 2], abs(heights[i - 1] - heights[i]) + distances[i - 1]);
    }
    
    return distances[n - 1];
}

int main() {
    int n;
    // número de montanhas
    cin >> n;

    // vetor que guarda a altura de cada montanha de íncide  1 < i <= n
    vector<int> heights(n);

    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    int minEnergy = calcEnergy(heights, n);
    
    cout <<  minEnergy << endl;
}