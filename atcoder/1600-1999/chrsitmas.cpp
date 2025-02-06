#include <bits/stdc++.h>
#include <atcoder/segtree>

using namespace std;
using namespace atcoder;

using ll = long long;

double dist(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt((ll) dx * dx + (ll) dy * dy);
}

using S = double;

S op(S a, S b) { return min(a, b); }

S e() { return 1e18; }

int main() {
    int n, k, sx, sy;
    cin >> n >> k >> sx >> sy;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    x.push_back(sx), y.push_back(sy);
    double ans = dist(sx, sy, x[0], y[0]);
    vector<double> d(n);
    for (int i = 0; i < n; i++) {
        double dir = dist(x[i], y[i], x[i + 1], y[i + 1]);
        double ret = dist(x[i], y[i], sx, sy) + dist(sx, sy, x[i + 1], y[i + 1]);
        ans += dir;
        d[i] = ret - dir;
    }
    segtree<S, op, e> dp(n + 1);
    dp.set(0, 0);
    for (int i = 1; i <= n; i++) {
        dp.set(i, dp.prod(max(0, i - k), i) + d[i - 1]);
    }
    ans += dp.get(n);
    cout << fixed << setprecision(15) << ans << endl;
}
    