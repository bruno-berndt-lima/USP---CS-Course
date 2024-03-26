#include <bits/stdc++.h>

using namespace std;

#define MAX 256

int solve(vector<int> numbers, int array_length) {
    for(int i = 0; i < MAX; i++) {
        vector<int> b;
        for(int j = 0; j < array_length; j++) {
            int bi = numbers[j] ^ i;
            b.push_back(bi);
        }
        int res = b[0];
        for(int j = 1; j < array_length; j++) {
            res ^= b[j]; 
        }

        if(res == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n_tests;
    cin >> n_tests;

    for(int i = 0; i < n_tests; i++) {
        int array_length;
        cin >> array_length;

        vector<int> numbers;
        int num;
        for(int j = 0; j < array_length; j++) {
            cin >> num;
            numbers.push_back(num);
        }
      
        cout << solve(numbers, array_length) << endl;
    }
    
    return 0;
}



