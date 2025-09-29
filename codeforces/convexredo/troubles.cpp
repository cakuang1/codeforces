#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Kitten {
    ll A, B;
};

struct Line {
    ll m, c;                  // slope, intercept
    ll eval(ll x) const {     // y = m*x + c
        return m * x + c;
    }
};

long double intersectX(const Line &l1, const Line &l2) {
    // x where l1 and l2 intersect
    return (long double)(l2.c - l1.c) / (l1.m - l2.m);
}

// Min-hull with monotone slopes (decreasing) and monotone queries (increasing)
struct Hull {
    deque<Line> dq;

    // Add a line with slope m and intercept c.
    // Assumes lines are added in MONOTONE slope order (here: decreasing).
    void add(ll m, ll c) {
        Line l{m, c};
        // Maintain convexity: pop from back while middle line is useless
        while (dq.size() >= 2 &&
               intersectX(dq[dq.size()-2], dq.back()) >= intersectX(dq.back(), l)) {
            dq.pop_back();
        }
        dq.push_back(l);
    }

    // Query minimum at x. Assumes x queries are MONOTONE increasing.
    ll query(ll x) {
        while (dq.size() >= 2 && dq[0].eval(x) >= dq[1].eval(x)) {
            dq.pop_front();
        }
        return dq[0].eval(x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Kitten> kats(N);
    for (int i = 0; i < N; ++i) cin >> kats[i].A >> kats[i].B;

    // 1) Sort by A asc, and for equal A keep larger B first
    sort(kats.begin(), kats.end(), [](const Kitten& u, const Kitten& v){
        if (u.A == v.A) return u.B > v.B;
        return u.A < v.A;
    });

    // 2) Build Pareto frontier (A strictly increasing, B strictly decreasing)
    vector<Kitten> front;
    front.reserve(N);
    for (auto &k : kats) {
        // Remove dominated (same or smaller B at larger/equal A)
        while (!front.empty() && front.back().B <= k.B) front.pop_back();
        // If A equal but B smaller, it was popped; if A equal but B equal, keep one
        if (front.empty() || front.back().A < k.A) front.push_back(k);
        // If front.back().A == k.A we already ensured B is strictly decreasing by pop
    }

    int M = (int)front.size();
    // Edge case: if M == 0, nothing to group
    if (M == 0) {
        cout << 0 << "\n";
        return 0;
    }
    
    // this maakes sense thwe weror we we
    // 
    // if you match this  
    
    // 3) DP with CHT
    // dp[j] = min_{1<=i<=j} ( dp[i-1] + A_j * B_i )
    // Lines: slope = B_i, intercept = dp[i-1]
    // dp[0] is the min if we group by this? 
    // what can we ensure w w
    // preato werefrontier wrlgoi we
    vector<ll> dp(M + 1, 0);   // dp[0] = 0
    Hull hull;
    // Insert line for i = 1: slope = B_1, intercept = dp[0] = 0
    hull.add(front[0].B, dp[0]);

    for (int j = 1; j <= M; ++j) {
        // Query at x = A_j
        ll Aj = front[j-1].A;
        dp[j] = hull.query(Aj);

        if (j < M) {
            ll nextSlope = front[j].B;      // B_{j+1} (strictly decreasing)
            ll nextIntercept = dp[j];       // dp[j]
            hull.add(nextSlope, nextIntercept);
        }
    }

    cout << dp[M] << "\n";
    return 0;
}
