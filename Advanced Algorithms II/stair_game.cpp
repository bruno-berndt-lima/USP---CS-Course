#include <bits/stdc++.h>

using namespace std;

int main() {
    int n_tests, n_stairs;
    cin >> n_tests;

    while(n_tests > 0) {
        cin >> n_stairs;
        vector<int> balls_on_stair(n_stairs);
        int res = 0;
        for (int i = 0; i < n_stairs; i++) {
            cin >> balls_on_stair[i];
            if(i % 2 == 1) {
                res ^= balls_on_stair[i];
            }
        }
        
        res == 0 ? cout << "second\n" : cout << "first\n";
        
        n_tests--;
    }

    return 0;
}
