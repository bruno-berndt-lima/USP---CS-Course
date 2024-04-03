#include <bits/stdc++.h>

using namespace std;

int grundy(int n) {
    return n % 4;
}

int main() {
    int n_tests, n_heaps;
    cin >> n_tests;

    while(n_tests > 0) {
        cin >> n_heaps;
        vector<int> sticks_in_heap(n_heaps);
        int res = 0, buffer;
        for (int i = 0; i < n_heaps; i++) {
            cin >> sticks_in_heap[i];
            res ^= grundy(sticks_in_heap[i]);
        }
        
        res == 0 ? cout << "second\n" : cout << "first\n";
        
        n_tests--;
    }


    return 0;
}
