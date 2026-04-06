#include <bits/stdc++.h>

using namespace std;

// inicializa o vetor de direções para o caminho que será percorrido na matriz
int dRow[] = { 0, 1, 0, -1 };
int dCol[] = { -1, 0, 1, 0 };

bool isValid(int height, int width, vector<vector<bool> > &vis, int row, int col) {
    // verifica os limites da matriz
    if (row < 0 || col < 0 || row >= height || col >= width)
        return false;
 
    // verifica se a célula ja foi visitada
    if (vis[row][col])
        return false;
 
    return true;
}


void DFS(int row, int col, vector<vector<char> > &grid, vector<vector<bool> > &vis, int height, int width, string word, int wordIndex, bool &wordFound) {
    
    if (!isValid(height, width, vis, row, col)) {
        return;
    }

    if (wordIndex == int(word.length())) {
        wordFound = true;
        return;
    }

    vis[row][col] = true;

    if (grid[row][col] == word[wordIndex]) {
        wordIndex++;
    } else {
        vis[row][col] = false;
        return;
    }

    //cout << grid[row][col] << " ";

    // chama a dfs para todas as células adjascentes
    for (int i = 0; i < 4; i++) {
        int adjx = row + dRow[i];
        int adjy = col + dCol[i];
        DFS(adjx, adjy, grid, vis, height, width, word, wordIndex, wordFound);
    }

    vis[row][col] = false;
}

int main() {
    int height, width;
    cin >> height >> width;

    vector<vector<char> > grid(height, vector<char>(width));
    vector<vector<bool> > vis(height, vector<bool>(width, false));

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            cin >> grid[i][j]; 
        }
    }

    int wordLenght;
    string word;
    cin >> wordLenght;
    cin >> word;

    bool wordFound = false;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            DFS(i, j, grid, vis, height, width, word, 0, wordFound);
        }
    }
    
    if (wordFound) {
        cout << "Yes";
    } else {
        cout << "No";
    }

    return 0;
}