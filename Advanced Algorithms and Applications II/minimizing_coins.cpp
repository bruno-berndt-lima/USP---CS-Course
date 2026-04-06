#include <bits/stdc++.h>
using namespace std;

#define MAX 1000000

int coins[MAX];

int min_coins(int coins[], int n_coins, int desired_money) {
    // Inicializa um vetor que armazena o numero minimo de 
    // moedas necessarias para cada soma de 0 ate a quantidade desejada
    vector<int> dp(desired_money + 1, INT_MAX); 
    
    dp[0] = 0;
    
    // Para cada valor de soma de 1 ate desired_money, 
    // verifica qual o numero minimo necessario de moedas
    for (int i = 1; i <= desired_money; i++) {
        for (int j = 0; j < n_coins; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    
    //retorna -1 caso nao seja possivel obter o valor, ou retorna o numero de moedas
    return (dp[desired_money] == INT_MAX) ? -1 : dp[desired_money];
}

int main () {
    int n_coins, desired_money;
    cin >> n_coins >> desired_money;

    for(int i = 0; i < n_coins; i++) {
        cin >> coins[i];
    }
    
    int res = min_coins(coins, n_coins, desired_money);

    cout << res << endl;

    return 0;
}
