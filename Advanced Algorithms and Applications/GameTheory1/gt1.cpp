#include <bits/stdc++.h>

using namespace std;

int main() {
    int n_tests;
    cin >> n_tests;

    int n_piles, n_stones;
    for (int i = 0; i < n_tests; i++) {
        cin >> n_piles;
        int res = 0;
        for (int j = 0; j < n_piles; j++) {
            cin >> n_stones;
            res ^= n_stones;
        }
        if (res == 0) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
    
    return 0;
}