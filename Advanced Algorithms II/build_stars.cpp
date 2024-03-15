#include <bits/stdc++.h>
using namespace std;

#define MAX 100000

long long int heights[MAX];

int main() {
    int N;
    cin >> N;
    bool flag = true;
    for (int i = 0; i < N; i++) {
        cin >> heights[i];
    }

    bool previousDecreased = false;
    for (int i = 0; i < N; i++) {
        if (i + 1 >= N) break;

        if (heights[i] < heights[i + 1]) {
            previousDecreased = false;
        } else if (heights[i + 1] == heights[i]) {
            heights[i] -= 1;
        } else {
            if ((heights[i + 1] == heights[i] - 1) && previousDecreased == false) {
                heights[i] -= 1;
                previousDecreased = true;
            } else {
                flag = false;
                break;
            }
        }
    }

    flag == true ? cout << "Yes" << endl : cout << "No" << endl;
}
