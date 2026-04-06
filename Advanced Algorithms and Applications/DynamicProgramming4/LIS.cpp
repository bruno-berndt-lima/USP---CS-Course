#include <bits/stdc++.h>

using namespace std;

#define MAX 3000

int vet[MAX];
int MEMO[MAX];

int lisPD(int n){
	
	MEMO[0] = 1;
	
	int maxl = 1;
	for (int i = 1; i <=n; ++i){
		int maior = 1;
		for (int j = i-1; j>=0 ; j--){
			int valor = MEMO[j]+1;
			if (vet[i] > vet[j])
				maior = max(valor, maior);
		}

		if (maxl < maior)
			maxl = maior;

		MEMO[i] = maior;
	}

	return maxl;
}

int main() {
    int arrayLenght;    
    cin >> arrayLenght;

    for (int i = 0; i < arrayLenght; i++) {
        cin >> vet[i];
    }

    int res = lisPD(arrayLenght);

    cout << res << endl;
    


}