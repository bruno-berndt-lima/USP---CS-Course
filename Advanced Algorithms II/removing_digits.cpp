#include <bits/stdc++.h>

using namespace std;

int min_steps(int n) {    
    // Inicializa um vetor que armazena o numero minimo de 
    // passos para zerar n
    vector<int> dp(n + 1, INT_MAX);
    
    dp[0] = 0; 
    
    // Para cada numero de 0 ate n
    for (int i = 0; i <= n; i++) {
        // itera por cada digito do numero atual
        for (char digit : to_string(i)) {
            int d = digit - '0';  // Converte de char para int 
            // Verifica se com o digito atual o numero de passos reduz e atualiza dp
            dp[i] = min(dp[i], dp[i - d] + 1);
        }
    }
    
    // Retorna a qtd de passos necessarios para zerar o valor n
    return dp[n];
}

int main () {
    int number;
    cin >> number;

    int res = min_steps(number);

    cout << res;

    return 0;
}
