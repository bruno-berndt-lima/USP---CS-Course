#include <bits/stdc++.h>

using namespace std;

struct Trie {
	map<char, Trie> mp;
	int cnt = 0; // qts string passaram aqui
	int end = 0; // qts strings terminaram aqui

	void add(string& s, int i = 0) {
		cnt++;
		if (i < (int) s.size()) {
			mp[s[i]].add(s, i + 1);
		} else end++;
	}
	
	void remove(string& s, int i = 0) {
    cnt--;
		if (i < (int) s.size()) {
			mp[s[i]].remove(s, i + 1);
		} else end--;
  }

    int search(string& s, int i = 0) {
    if (i == (int) s.size()) return cnt;
    if (mp.count(s[i])) return mp[s[i]].search(s, i + 1);
    return false;
  }
};


int main() {
    int n;
    cin >> n;
    Trie root;
    string str;
    int operatioon;
    for (int i = 0; i < n; i++) {
        cin >> operatioon >> str;
        switch (operatioon) {
        case 1:
            root.add(str);
            break;
        case 2:
            root.remove(str);
            break;
        case 3:
            cout << root.search(str) << endl;

        default:
            break;
        }
    }
    return 0;
}