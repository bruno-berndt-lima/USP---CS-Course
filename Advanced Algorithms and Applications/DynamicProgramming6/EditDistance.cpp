#include <bits/stdc++.h>

using namespace std;

#define MIN(a,b,c) min(min(a,b),c)
#define MAX 2000

string strA;
string strB;

int delta = 1;
int MEMO[MAX+1][MAX+1];

int alpha(int i, int j){
	char cx = strA[i];
	char cy = strB[j];

	if(cx == cy)
		return 0;

	if ( (cx=='a' || cx=='e' || cx=='i' || cx=='o' || cx=='u') &&  
         (cy=='a' || cy=='e' || cy=='i' || cy=='o' || cy=='u') )
     return 1;
    if ( !(cx=='a' || cx=='e' || cx=='i' || cx=='o' || cx=='u') &&  
         !(cy=='a' || cy=='e' || cy=='i' || cy=='o' || cy=='u') )
     return 1;

    return 1;

}

int alin(int m, int n){

    for (int i = 0; i <= int(strB.length()); ++i)
    	MEMO[0][i] =  i*delta;

    for (int i = 0; i <= int(strA.length()); ++i)
    	MEMO[i][0] =  i*delta;
    	
   
    for (int i = 1; i <= m; ++i)
  		for (int j = 1; j <= n; ++j)
            MEMO[i][j] =  MIN(alpha(i-1,j-1) + MEMO[i-1][j-1], delta + MEMO[i-1][j], delta + MEMO[i][j-1]);

	return MEMO[m][n];
}

int main() {
    int nTests;
    cin >> nTests;
    for (int i = 0; i < nTests; i++) {
        cin >> strA >> strB;
        cout << alin(strA.length(), strB.length()) << endl;
    }

}