#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Point {
    ll x, y;
};

int half(const Point& p) {
    return (p.y > 0 || (p.y == 0 && p.x > 0)) ? 0 : 1;
}

ll cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

bool cmp(const Point& a, const Point& b) {
    if (half(a) != half(b))
        return half(a) < half(b);

    return cross(a, b) > 0;
}

void solve() {
    int n;
    cin >> n;

    vector<Point> p(n);

    for (auto& [x, y] : p) {
        cin >> x >> y;
    }

    sort(p.begin(), p.end(), cmp);

    // Duplicate the circular ordering.
    p.resize(2 * n);
    for (int i = 0; i < n; i++) {
        p[i + n] = p[i];
    }

    int ans = 0;
    int r = 0;

    for (int l = 0; l < n; l++) {
        r = max(r, l + 1);

        // Include points strictly within 180 degrees
        // counterclockwise from p[l].
        while (r < l + n && cross(p[l], p[r]) > 0) {
            r++;
        }

        ans = max(ans, r - l);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}



// wew