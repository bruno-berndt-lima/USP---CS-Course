    #include <bits/stdc++.h>
    using namespace std;

    // Function to print an array
    void print_array(vector<int> arr, int n) {
        for (int i = 0; i < n; i++) {
            cout << arr[i];
        }
        cout << endl;
    }

    // Function to print all the hamming distances of length = n and number of 1's = h
    void print_hamming_distances(vector<int> arr, int n, int h, int i, int ones_remaining) {
        if (i == n) {
            if (ones_remaining == 0) {
                print_array(arr, n);
            }
            return;
        }

        // Choose 0
        arr[i] = 0;
        print_hamming_distances(arr, n, h, i + 1, ones_remaining);

        // Choose 1 (only if ones_remaining > 0)
        if (ones_remaining > 0) {
            arr[i] = 1;
            print_hamming_distances(arr, n, h, i + 1, ones_remaining - 1);
        }
    }

    int main() {
        int n_datasets;
        cin >> n_datasets;

        int N, H;
        for (int i = 0; i < n_datasets; i++) {
            cin.ignore(); // Consume the blank line
            
            cin >> N >> H;
            vector<int> arr(N);

            print_hamming_distances(arr, N, H, 0, H); 

            if (i != n_datasets - 1) {
                cout << endl;
            }
        }

        return 0;
    }

