#include <bits/stdc++.h> 

using namespace std;

double NPV(vector<int> cashflows, double IRR, int n_cashflows) {
    double sum = 0.0; 
    for (int i = 0; i < n_cashflows + 1; i++) {  
        sum += cashflows[i] / pow((1 + IRR), i);
    }

    return sum;
}

double calc_IRR(vector<int> cashflows, int n_cashflows, double left, double right, double error) {
    double mid;
    double npv;
    while(right - left > error) {
        mid = (right + left) / 2;
        npv = NPV(cashflows, mid, n_cashflows);

        if (npv > 0) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return (left + right) / 2;
}

int main() {
    int n_cashflows;
    cin >> n_cashflows;
    while (n_cashflows != 0) {
        vector<int> cashflows(n_cashflows + 1);
        int cf;
        for (int i = 0; i < n_cashflows + 1; i++) {
            cin >> cf;
            cashflows[i] = cf;
        }
        double lower_bound = -0.99999;
        double upper_bound = 1000000.0;
        double error = 0.0001;
        double IRR = -2;
    
        IRR = calc_IRR(cashflows, n_cashflows, lower_bound, upper_bound, error);
        
        if (IRR != -2) 
            cout << fixed << setprecision(2) << IRR << endl;
        else 
            cout << "No" << endl;
            
        cin >> n_cashflows;
    }
    
    return 0;
}
