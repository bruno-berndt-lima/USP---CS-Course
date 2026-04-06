#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

// função para encontrar o número de caminhos em um tabuleiro, saindo de grid[0][0] e 
// chegando em grid[rows-1][cols - 1], considerando células ocupadas
int findNumOfPaths(vector<vector<char>> grid, vector<vector<int>> dp, int rows, int columns) {
    for (int i = rows - 2; i >= 0; i--) {
        for (int j = columns - 2; j >= 0; j--) {
            if(grid[i][j] == '#') {
                dp[i][j] = 0;
            } else {
                dp[i][j] = (dp[i + 1][j] + dp[i][j + 1]) % MOD;
            }
        }
    }

    return dp[0][0];
}

int main() {
    int rows, columns;
    cin >> rows >> columns;

    // tabuleiro que contém a posição inicial, final e posição(ões) ocupada(s) 
    vector<vector<char>> grid(rows, vector<char> (columns));

    // matriz inicializada com 0, que guarda o número de caminhos possíveis 
    // para o fim (grid[rows-1][columns-1]),  a partir da posição de cada célula
    vector<vector<int>> dp(rows, vector<int> (columns, 0));

    // lendo o tabuleiro 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> grid[i][j];
        }   
    }

    // preenchendo com 1, todas as células da última linha e coluna de dp,
    // haja visto que só pode ir para direita ou descer, então só vai haver
    // um caminho possível a partir de cada célula, e caso tenha algum célula
    // ocupada, então ela e todas as anteriores na coluna ou linha devem ser 
    // marcadas com 0, pois não há outro caminho 
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < columns - 1; j++) {
            if(i == rows - 1 || j == columns - 1) {
                if(grid[i][j] == '#') {
                    if (i == rows - 1) {
                        for (int l = j; l >= 0; l--) {
                            dp[i][l] = 0;   
                        }
                    } else if (j == columns - 1) {
                        for (int l = i; l >= 0; l--) {
                            dp[l][j] = 0;   
                        }
                    }          
                } else {
                    dp[i][j] = 1;
                }
            }
        }
    }
            
    int res = findNumOfPaths(grid, dp, rows, columns);

    cout << res << endl;

}