#include <bits/stdc++.h>

using namespace std;

string txt, patt;

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

int kmpSearch(int *b, string pattern, string text, int pattern_size, int text_size) {
    int i = 0, j = 0, count = 0;
    while(i < text_size) {
        while(j >= 0 && text[i] != pattern[j]) {
            j = b[j];
        }
        i++;
        j++;
        if(j == pattern_size) {
            j = b[j];
            count++;
        }

    }
    return count;
}

int main() {
    cin >> txt >> patt;
    int txt_size = txt.length();
    int patt_size = patt.length();
    int b[1000001];

    kmpPreProcess(b, patt, patt_size);
    int n = kmpSearch(b, patt, txt, patt_size, txt_size);

    cout << n << endl;

    return 0;
}
