#include <bits/stdc++.h>

using namespace std;

int main() {
    int n_books, total_money, price;
    while(cin >> n_books) {
        vector<int> books_prices;
        for (int i = 0; i < n_books; i++) {
            cin >> price;
            books_prices.push_back(price);
        }
        cin >> total_money;
        cin.ignore();
        int lo, hi, a, b;
        sort(books_prices.begin(), books_prices.end());

        lo = 0;
        hi = n_books - 1;

        while (lo < hi) {
            if (books_prices[lo] + books_prices[hi] > total_money) {
                hi -= 1;
            } else if (books_prices[lo] + books_prices[hi] < total_money) {
                lo += 1;
            } else {
                a = books_prices[lo];
                b = books_prices[hi];
                lo += 1;
            }
        }

        if (a < b)
            cout << "Peter should buy books whose prices are " << a << " and " << b << "." << endl;
        else
            cout << "Peter should buy books whose prices are " << b << " and " << a << "." << endl;

        cout << endl;
    }
    
    return 0;
}


