#include <bits/stdc++.h>

using namespace std;

int main() {
    int n_tests, n_heaps;
    cin >> n_tests;

    while(n_tests > 0) {
        cin >> n_heaps;
        vector<int> coins_in_heap(n_heaps);
        int res = 0;
        for (int i = 0; i < n_heaps; i++) {
            cin >> coins_in_heap[i];
            if(coins_in_heap[i] % 2 == 1) {
                res = 1;
            }
        }
        
        res == 0 ? cout << "second\n" : cout << "first\n";
        
        n_tests--;
    }


    return 0;
}
