#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

// Euclidean distance between two points
double dist(const Point &A, const Point &B) {
    double dx = B.x - A.x;
    double dy = B.y - A.y;
    return sqrt(dx*dx + dy*dy);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<Point> points(n);
    for(int i = 0; i < n; i++){
        cin >> points[i].x >> points[i].y;
    }

    // total length of one signature
    double length = 0;
    for(int i = 1; i < n; i++){
        length += dist(points[i-1], points[i]);
    }

    // he signs k times at 50 mm/s
    double totalTime = (length * k) / 50.0;

    // print with enough precision
    cout << fixed << setprecision(6) << totalTime << "\n";
    return 0;
}


// determine contribution w