#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Rect {
    ll p, q, a;
};

struct Line {
    ll m, c; // slope, intercept
    ll eval(ll x) const { return m * x + c; }
    long double intersectX(const Line &l) const {
        return (long double)(c - l.c) / (l.m - m);
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Rect> rects(n);
    for (int i = 0; i < n; i++) {
        cin >> rects[i].p >> rects[i].q >> rects[i].a;
    }

    // sort by p ascending, and if tie, q descending
    sort(rects.begin(), rects.end(), [](const Rect &u, const Rect &v) {
        if (u.p == v.p) return u.q > v.q;
        return u.p < v.p;
    });

    deque<Line> dq;
    dq.push_front({0, 0}); // base line for f(0) = 0

    ll ans = 0;

    for (int i = 0; i < n; i++) {
        // Query at x = q_i
        while (dq.size() >= 2 && dq.back().eval(rects[i].q) <= dq[dq.size()-2].eval(rects[i].q))
            dq.pop_back();
        ll best = dq.back().eval(rects[i].q);

        ll f = rects[i].p * rects[i].q - rects[i].a + best;
        ans = max(ans, f);

        // Insert new line y = -p_i * x + f
        Line cur = {-rects[i].p, f};
        while (dq.size() >= 2 && cur.intersectX(dq[0]) >= dq[0].intersectX(dq[1]))
            dq.pop_front();
        dq.push_front(cur);
    }



    cout << ans << "\n";
    return 0;
}
 
// 