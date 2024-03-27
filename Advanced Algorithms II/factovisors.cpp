#include <bits/stdc++.h>

using namespace std;

#define ll long long

bool solve(ll n, ll m) {
    vector <pair< ll, ll>> factors;

    ll t = m;
    for (ll i = 2; i * i <= m; i++) {
        ll count = 0;
        while (t % i == 0) {
            t /= i;
            count++;
        }

        if (count) {
            factors.push_back(make_pair(i,count));
        }

    }
    if (t != 1) {
        factors.push_back(make_pair(t,1));
    }

    ll ii;
    for (auto p: factors) {
        ii = p.first;
        while (p.second > 0) {
            if (ii > n) return 0;
            p.second -= n / ii;
            ii *= p.first;
        }

    }

    return 1;
}

int main() {
    ll n, m;
    ll temp;
    
    while (cin >> n >> m) {
        temp = m;

        if (m != 0 && solve(max((ll) 1, n), m)) {
            cout << temp << " divides " << n << "!" << endl;
        } else {
            cout << temp << " does not divide " << n << "!" << endl;
        }

  }
}
