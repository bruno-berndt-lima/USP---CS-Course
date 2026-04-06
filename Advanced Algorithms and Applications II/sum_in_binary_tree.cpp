#include <bits/stdc++.h>

using namespace std;

long long int sum_vertices(long long int vertex) {
    long long int sum = 0;
    while(vertex != 0) {
        sum += vertex;
        vertex /= 2;
    }

    return sum;
}

int main() {
    int n_tests;
    long long int vertex;
    cin >> n_tests;
    for(int i = 0; i < n_tests; i++) {
        cin >> vertex;
        cout << sum_vertices(vertex) << endl;
    }

    return 0;
}
