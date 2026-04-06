#include <bits/stdc++.h>

#define N 8

using namespace std;

int dy[N] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dx[N] = {1, 2, 2, 1, -1, -2, -2, -1};

bool chkSafe(int y, int x, int arr[N][N]) {
    if ((0 <= x && x < N) && (0 <= y && y < N) && arr[y][x] == -1)
        return true;

    return false;
}

int countValidMoves(int y, int x, int arr[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (chkSafe(ny, nx, arr))
            count++;
    }
    return count;
}

bool knightTour(int index, int y, int x, int arr[N][N]) {
    if (index == N * N) {
        arr[y][x] = index;
        return true;
    }

    // Create an array to store the valid move counts for each direction
    int validMoves[N];
    for (int i = 0; i < N; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        validMoves[i] = chkSafe(ny, nx, arr) ? countValidMoves(ny, nx, arr) : N + 1;
    }

    // Sort directions based on the number of valid moves
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (validMoves[i] > validMoves[j]) {
                swap(validMoves[i], validMoves[j]);
                swap(dy[i], dy[j]);
                swap(dx[i], dx[j]);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (chkSafe(ny, nx, arr)) {
            arr[y][x] = index;

            if (knightTour(index + 1, ny, nx, arr))
                return true;

            arr[y][x] = -1;
        }
    }

    return false;
}

int main() {
    int x, y;
    cin >> x >> y;

    int arr[N][N];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            arr[i][j] = -1;
    }

    knightTour(1, y - 1, x - 1, arr);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }

    return 0;
}
