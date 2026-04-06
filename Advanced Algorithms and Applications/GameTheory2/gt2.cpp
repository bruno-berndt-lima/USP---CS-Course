#include <bits/stdc++.h>

using namespace std;

int main() {
    int n_tests;
    cin >> n_tests;

    for (int i = 0; i < n_tests; i++) {
        string str;
        cin >> str;
        for (long unsigned int i = 0; i < str.length(); i++) {
            if (i % 2 == 0) {
                if(str[i] == 'a') {
                    str[i] = 'b';
                } else {
                    str[i] = 'a';
                }
            } else {
                if(str[i] == 'z') {
                    str[i] = 'y';
                } else {
                    str[i] = 'z';
                }
            }
        }
        cout << str << endl;        
    }
    
    return 0;
}