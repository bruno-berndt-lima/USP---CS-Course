#include <bits/stdc++.h>

using namespace std;

void mergesort(long long* v, int begin, int end, long long &counter) {
	if (end <= begin) return;

	// calcula posicao central
	int mid = (int) (end+begin)/2.0;

	// duas chamadas recursivas, uma para cada metade do vetor
	// 2 - passo recursivo (divisao)
	mergesort(v, begin, mid, counter);
	mergesort(v, mid+1, end, counter);

    // aloca um vetor auxiliar para intercalar
	long long* aux = new long long[end-begin+1];

	int i = begin; // indice inicial da L1 (begin -> centro)
	int j = mid+1; // indice inicial da L2 (centro+1 -> end)
	int k = 0;   // indice do vetor auxiliar (0 ate end-begin)

	// compara elementos das duas listas (subvetores) ordenados
	// enquanto houver elementos das DUAS listas para serem comparados
	while (i <= mid && j <= end) {
		if (v[i] < v[j]) {
			aux[k] = v[i]; // copia elemento da L1
			i++; // movo para o proximo elemento da L1
		} else {
			aux[k] = v[j]; // copia elemento da L2
            counter += mid - i + 1;
			j++;
		}
		k++;
	}

	// tenho uma das listas com elementos restantes
	// copio todos os restantes da L1
	while (i <= mid) {
		aux[k] = v[i];
		i++; k++;
	}
	// copio todos os elementos da L2
	while (j <= end) {
		aux[k] = v[j];
		j++; k++;
	}

	// aux contem a intercalacao do vetor v[ini:mid] e v[mid+1:end]
	// copia de aux para o vetor original
	for (i = begin, k = 0; i <= end; i++, k++) {
		v[i] = aux[k];
	}

	delete[] aux;
}

int main() {
    int nTests;
    cin >> nTests;

    int arrLenght;
    for (int i = 0; i < nTests; i++) {
        cin >> arrLenght;
        long long v[arrLenght];
        long long counter = 0;
        for (int j = 0; j < arrLenght; j++) {
            cin >> v[j];
        }    
        mergesort(v, 0, arrLenght - 1, counter);  
       
        cout << counter << endl;
    }
}