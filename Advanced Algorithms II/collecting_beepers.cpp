#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    int n_scenarios;
    cin >> n_scenarios;

    while(n_scenarios > 0) {
        int x_size, y_size;
        cin >> x_size >> y_size;
        int start_x, start_y;
        cin >> start_x >> start_y;

        int n_beepers;
        cin >> n_beepers;

        vector<pii> beepers;
        for (int i = 0; i < n_beepers; i++) {
            int x, y;
            cin >> x >> y;
            beepers.push_back(make_pair(x, y));
        }

        // vetor de permutacoes dos beepers
        vector<int> perm(n_beepers);
        for (int i = 0; i < n_beepers; i++) {
            perm[i] = i;
        }

        int min_distance = INT_MAX;

        do {
            int total_distance = 0;
            int prev_x = start_x, prev_y = start_y;

            for (int i = 0; i < n_beepers; i++) {
                total_distance += manhattan_distance(prev_x, prev_y, beepers[perm[i]].first, beepers[perm[i]].second);
                prev_x = beepers[perm[i]].first;
                prev_y = beepers[perm[i]].second;
            }

            total_distance += manhattan_distance(prev_x, prev_y, start_x, start_y);

            min_distance = min(min_distance, total_distance);
        } while (next_permutation(perm.begin(), perm.end())); // permuta a ordem dos beepers

        cout  << "The shortest path has length " << min_distance << endl;

        n_scenarios--;
    }

    return 0;
}
