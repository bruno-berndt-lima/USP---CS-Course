#include <bits/stdc++.h>

using namespace std;

string str;
string pattern;

void kmpPreProcessamento(int *b, string pat){
	int tamp = pat.length();
	int i = 0, j = -1; b[0] = -1;

	while (i < tamp){
		//printf("%d\n", j);
		while (j>=0 && pat[i] != pat[j]) { // eh diferente... Reseta j, usando b .
			j = b[j]; 
			//cout << "pat[i] = " << pat[i] << " pat[j] = "<< pat[j] << " j eh diferente = " << j << endl;
		}
			//j = -1;    
		i++; j++;
		b[i] = j;     // observe que b[i] so deixa de ser zero quando o padrao se repetir em pattern!
	}

}

int kmp (int *b, string text, string pat, int* positions){
	int tamt = str.length();
	int tamp = pattern.length();
	int i = 0, j = 0;
    int count = 0;

	while (i < tamt){     // tem texto para  consumir.....
		while (j >= 0 &&  text[i] != pat[j]) {
			j = b[j];/* code */
			//cout << "opa... j = b[j] " << j << " i = " << i << endl;
		}
		i++; j++;
		if (j == tamp) { // opa... teve matching !!!
            positions[count] = i - j + 1;
            count++;
			//cout << "A sub string foi encontrada na posicao = " << i - j << endl;
			j = b[j];        // prepara j para um provavel matching novo....
		}
	}
    return count;
}

int main(int argc, char const *argv[]) {
    int n_cases;
    cin >> n_cases;
    int b[1000001];
    int n;
    int positions[1000001];

    for (int i = 0; i < n_cases; i++) {
        cin >> str >> pattern;
        kmpPreProcessamento(b, pattern);
        n = kmp(b, str, pattern, positions);
        n != 0 ? cout << n << endl : cout << "Not Found";
        for (int i = 0; i < n; i++) {
            cout << positions[i] << " ";
        }
        cout << endl << endl;
        
    }
    
	return 0;
}