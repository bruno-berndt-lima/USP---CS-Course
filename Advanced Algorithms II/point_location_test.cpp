#include <bits/stdc++.h>
 
using namespace std;
 
double norm(double x, double y) {
    return sqrt(x * x + y * y);
}
 
double cross_product(double x1, double y1, double x2, double y2) {
    return (x1 * y2) - (y1 * x2);
}
 
int main() {
    int n_tests;
    double x1, y1, x2, y2, x3, y3;
    cin >> n_tests;
 
    while (n_tests > 0) {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        double cross_result = cross_product(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
        double norm_p2 = norm(x2 - x1, y2 - y1);
        double norm_p3 = norm(x3 - x1, y3 - y1);
 
        double sin_theta = cross_result / (norm_p2 * norm_p3);
 
        if (sin_theta > 0)
            cout << "LEFT\n";
        else if (sin_theta < 0)
            cout << "RIGHT\n";
        else
            cout << "TOUCH\n";
 
        n_tests--;
    }
 
    return 0;
}
