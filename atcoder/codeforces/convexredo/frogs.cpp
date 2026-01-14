#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll m, b;
    ll eval(ll x) const { return m*x + b; }
    long double intersectX(const Line &l) const {
        return (long double)(b - l.b) / (l.m - m);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll C;
    cin >> N >> C;
    vector<ll> h(N+1);
    for (int i=1;i<=N;i++) cin >> h[i];
    
    // ntoiwecness dn wecutneeseswerover the groupw efo ktiten we
    // 
    vector<ll> dp(N+1);
    dp[1] = 0;

    deque<Line> dq;
    dq.push_back({-2*h[1], dp[1] + h[1]*h[1]}); 
    // w    
    for (int j=2; j<=N; j++) {

        // Query
        while (dq.size() >= 2 && dq[0].eval(h[j]) >= dq[1].eval(h[j]))
            dq.pop_front();
        ll best = dq.front().eval(h[j]);
        dp[j] = h[j]*h[j] + C + best;

        // Insert new line
        Line cur = {-2*h[j], dp[j] + h[j]*h[j]};
        while (dq.size() >= 2 && cur.intersectX(dq[dq.size()-2]) <= dq[dq.size()-2].intersectX(dq.back()))
            dq.pop_back();
        dq.push_back(cur);
    }

    cout << dp[N] << "\n";
}


// 