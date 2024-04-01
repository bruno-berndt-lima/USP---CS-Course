#include <bits/stdc++.h>

using namespace std;

void kmpPreProcess(int *b, string pattern, int pattern_size) {
    int i = 0, j = -1;
    b[0] = -1;

    while(i < pattern_size) {
        while(j >= 0 && pattern[i] != pattern[j]) {
            j = b[j];
        }
        i++;
        j++;
        b[i] = j;
    }
} 

vector<int> findBorders(int *b, string pattern, int pattern_size) {
    vector<int> borders;
    int j = pattern_size;

    while (j > 0) {
        borders.push_back(j);
        j = b[j];
    }

    return borders;
}

int main() {
    string str;
    cin >> str;

    int str_size = str.length();
    int b[1000001];

    kmpPreProcess(b, str, str_size);
    vector<int> borderLengths = findBorders(b, str, str_size);

    for (int i = borderLengths.size() - 1; i > 0; i--) {
        cout << borderLengths[i] << " ";
    }
    cout << endl;

    return 0;
}
