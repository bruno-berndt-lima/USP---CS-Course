#include <bits/stdc++.h>

using namespace std;

#define mod 1000000007

string convertToBinary(int n) {
    string binaryNum = bitset<32>(n).to_string();
    return binaryNum;
}

// algoritmo Square and Multiply 
long long int calc(int base, int exponent) { 
    long long int res = 1;
    string binaryNum = convertToBinary(exponent);

    for(int i = 0; i < binaryNum.length(); i++) {
        res = (res * res) % mod;  

        if(binaryNum[i] == '1') {
            res = (res * base) % mod;  
        }
    }

    return res;
}

int main() {
    long long int n, base, exponent;
    cin >> n;

    while(n > 0) {
        cin >> base >> exponent;
        cout << calc(base, exponent) << endl;
        n--;
    }

    return 0;
}
