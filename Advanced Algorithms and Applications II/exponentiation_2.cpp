#include <bits/stdc++.h>

using namespace std;

#define mod 1000000007

string convertToBinary(int n) {
    string binaryNum = bitset<32>(n).to_string();
    return binaryNum;
}

// algoritmo Square and Multiply 
long long int calc(int base, int exponent, int m) { 
    long long int res = 1;
    string binaryNum = convertToBinary(exponent);

    for(int i = 0; i < binaryNum.length(); i++) {
        res = (res * res) % m;  

        if(binaryNum[i] == '1') {
            res = (res * base) % m;  
        }
    }

    return res;
}

int main() {
    long long int n, base, exponent, exponent2;
    cin >> n;

    while(n > 0) {
        cin >> base >> exponent >> exponent2;
        long long int x = calc(exponent, exponent2, mod-1);
        cout << calc(base, x, mod) << endl;
        n--;
    }

    return 0;
}
