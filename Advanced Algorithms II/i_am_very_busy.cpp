#include <bits/stdc++.h>

using namespace std;

// Function to sort the pair <start, end> time of an activity by the end time
bool sortbysec(const pair<int,int> &a, const pair<int,int> &b) {
    return (a.second < b.second);
}

int main() {
    int n_tests, n_activities;
    cin >> n_tests;
    for(int i = 0; i < n_tests; i++) {
        cin >> n_activities;
        int start, end;
        vector<pair<int, int>> activities_time;

        for (int j = 0; j < n_activities; j++) {
            cin >> start >> end;
            activities_time.push_back(make_pair(start, end));
        }

        // Sort by the finish time of the activity
        sort(activities_time.begin(), activities_time.end(), sortbysec);

        // add the first activity to the count 
        int k = 0, n = 1;

        for (int m = 1; m < n_activities; m++) {
            // Check if the start time of next activity is bigger or 
            // equal to the last added activity finish time
            if (activities_time[m].first >= activities_time[k].second) {
                // add the activity to the count of activities
                n++;
                // set the last activity added to the count
                k = m;
            }
        }

        n_activities > 0 ? cout << n << endl : cout << 0 << endl;  
    }

    return 0;
}
