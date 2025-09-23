#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Line {
    ll m, c;
    ll eval(ll x) const { return m * x + c; }
};




struct MonotoneCHT {
    deque<Line> dq;
    static bool bad(const Line& l1, const Line& l2, const Line& l3) {
        long double x12 = (long double)(l2.c - l1.c) / (long double)(l1.m - l2.m);
        long double x13 = (long double)(l3.c - l1.c) / (long double)(l1.m - l3.m);
        return x12 >= x13;
    }
    void add_line(ll m, ll c) {
        Line L{m, c};
        while (dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), L)) dq.pop_back();
        dq.push_back(L);
    }
    ll query(ll x) {
        while (dq.size() >= 2 && dq[0].eval(x) >= dq[1].eval(x)) dq.pop_front();
        return dq.front().eval(x);
    }
};



// wedetmeirn wet= werhow to do ttsi wefor some j w

//  fairnut rand triansg 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    if (!(cin >> n)) return 0;
    vector<long long> a(n+1), b(n+1), dp(n+1, 0);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    // Precondition from problem: a is strictly increasing, b is strictly decreasing.
    // DP: dp[i] = min_{j<i} (dp[j] + a[i]*b[j])
    MonotoneCHT cht;

    dp[1] = 0;
    cht.add_line(b[1], dp[1]);   // slope = b1, intercept = dp1

    for (int i = 2; i <= n; ++i) {
        dp[i] = cht.query(a[i]); // x = ai, queries increasing
        cht.add_line(b[i], dp[i]); // slopes decreasing
    }

    cout << dp[n] << '\n';
    return 0;
}
