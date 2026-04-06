#include <bits/stdc++.h>

using namespace std;

#define MAXIMUM(a,b,c) max(max(a,b),c)
#define MAX 5000

int delta = 0;
int MEMO[MAX+1][MAX+1];

char str1[MAX];
char str2[MAX];

int letterPrices[26];

int alpha(int i, int j){
	char cx = str1[i];
	char cy = str2[j];

	if(cx == cy)
		return letterPrices[cx - 97];

    return 0;
}

int alin(int m, int n){

    for (int i = 0; i <= int(strlen(str1)); ++i)
    	MEMO[0][i] =  i*delta;

    for (int i = 0; i <= int(strlen(str2)); ++i)
    	MEMO[i][0] =  i*delta;
    	
   
    for (int i = 1; i <= m; ++i)
  		for (int j = 1; j <= n; ++j)
	       MEMO[i][j] =  MAXIMUM(alpha(i-1,j-1) + MEMO[i-1][j-1], delta + MEMO[i-1][j], delta + MEMO[i][j-1]);

	return MEMO[m][n];
}

int main() {
    int subSeq1Lenght, subSeq2Lenght;
    cin >> subSeq1Lenght >> subSeq2Lenght;

    for (int i = 0; i < 26; i++) {
        cin >> letterPrices[i];
    }

    for (int i = 0; i < subSeq1Lenght; i++) {
        cin >> str1[i];
    }

    for (int i = 0; i < subSeq2Lenght; i++) {
        cin >> str2[i];
    }

    int res = alin(subSeq1Lenght, subSeq2Lenght);
    cout << res << endl;
}