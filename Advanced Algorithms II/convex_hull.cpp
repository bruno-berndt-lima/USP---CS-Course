#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
 
struct Point {
    int x, y;
    Point operator -(const Point& a) const { return Point{x - a.x, y - a.y}; }
    ll operator *(const Point& a) const { return (ll) x * a.y - (ll) y * a.x; }
    bool operator <(const Point& a) const { return x == a.x ? y < a.y : x < a.x; }
 
    ll cross(const Point& a, const Point& b) {
        return (a - *this) * (b - *this);
    }
};
 
vector<Point> convex_hull(Point points[], int N) {
    int s = 0;
    vector<Point> hull;
    for(int t = 0; t < 2; t++){
        for(int i = 0; i < N; i++){
            while((int) hull.size()- s >= 2){
                if(hull[hull.size()-2].cross(hull[hull.size()-1], points[i]) <= 0) break;
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        hull.pop_back();
        s = hull.size();
        reverse(points, points+N);
    }

    return hull;
}
 
int main(){
    int N;
    cin >> N;
    Point points[N];
 
    for(int i = 0; i < N; i++) {
        cin >> points[i].x >> points[i].y;
    }

    sort(points, points+N);
 
    vector<Point> hull = convex_hull(points, N);

    cout << hull.size() << endl;
    for(Point p : hull) {
        cout << p.x << " " << p.y << endl;
    }
}
