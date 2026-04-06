#include <bits/stdc++.h>

using namespace std;

int binarySearch(int* v, int key, int begin, int end) {
	// caso base 1
	if (begin > end) {
        return -2;	// c
    }
	// calcula ponto central e verifica se key foi encontrada
	int c = (int)((begin + end) / 2.0);  
	
    // caso base 2
	if (key > v[c-1] && key <= v[c]) return c;  

	// passo recursivo
	if (key < v[c]) 
		return binarySearch(v, key, begin, c-1); 
	
	if (key > v[c])  
		return binarySearch(v, key, c+1, end); 

    return -1;
}

int main() {
    int nSongs, nMoments;
    cin >> nSongs >> nMoments;

    // vetor de tempo acumulado das musicas 
    int accumulatedTime[nSongs + 1];
    accumulatedTime[0] = 0;

    int nTimes,duration;
    for (int i = 1; i < nSongs + 1; i++) {
        cin >> nTimes >> duration;
        accumulatedTime[i] = accumulatedTime[i-1] + (nTimes * duration);
    }

    int moments, song;
    for (int i = 0; i < nMoments; i++) {
        cin >> moments;
        song = binarySearch(accumulatedTime, moments, 0, nSongs);
        cout << song << endl;
    }
}