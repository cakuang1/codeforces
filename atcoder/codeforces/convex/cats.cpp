#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// A little deque-based CHT for min query,
// with monotonically decreasing slopes m, and
// x-queries in non-decreasing order.
struct ConvexHull {
    struct Line {
        ll m, b;        // y = m*x + b
        long double x;  // intersection-point with next line
    };
    deque<Line> dq;

    // compute intersection of l1 and l2
    static long double intersect(const Line &l1, const Line &l2) {
        // solve l1.m * X + l1.b = l2.m * X + l2.b
        // X = (l1.b - l2.b) / (l2.m - l1.m)
        return (long double)(l1.b - l2.b) / (l2.m - l1.m);
    }

    // add new line with slope m, intercept b
    void add_line(ll m, ll b) {
        Line ln = {m, b, 0.0L};
        // pop back while the new line makes the previous one irrelevant
        while (!dq.empty()) {
            // if same slope, keep only the better intercept
            if (dq.back().m == m) {
                if (dq.back().b <= b) {
                    // old is better, drop new
                    return;
                } else {
                    dq.pop_back();
                    continue;
                }
            }
            // compute intersection with last
            long double ix = intersect(dq.back(), ln);
            if (ix <= dq.back().x) {
                // the new intersection is no further right,
                // so the back line is never optimal
                dq.pop_back();
            } else {
                ln.x = ix;
                break;
            }
        }
        if (dq.empty()) {
            ln.x = -1e30L;  // far left
        }
        dq.push_back(ln);
    }

    // query minimum at x; x must be non-decreasing across calls
    ll query(ll x) {
        while (dq.size() >= 2 && dq[1].x <= (long double)x) {
            dq.pop_front();
        }
        auto &L = dq.front();
        return L.m * x + L.b;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p;
    cin >> n >> m >> p;
    vector<ll> d(n+1), dist(n+1,0);
    for (int i = 2; i <= n; i++) {
        cin >> d[i];
        dist[i] = dist[i-1] + d[i];
    }

    // 1) read cats, compute r_j = t_j - dist[h_j]
    vector<ll> r(m);
    for (int i = 0, h; i < m; i++) {
        ll t;
        cin >> h >> t;
        r[i] = t - dist[h];
    }
    sort(r.begin(), r.end());
    // prefix sums of r
    vector<ll> S(m+1, 0);
    for (int i = 1; i <= m; i++) {
        S[i] = S[i-1] + r[i-1];
    }

    // dp0[i] = cost with 1 feeder for first i cats:
    //        = i*r_i - S[i]
    vector<ll> dp0(m+1), dp1(m+1);
    for (int i = 1; i <= m; i++) {
        dp0[i] = (ll)i * r[i-1] - S[i];
    }

    // build up to p feeders
    for (int k = 2; k <= p; k++) {
        ConvexHull cht;
        // base line j=0: slope=0, intercept=dp0[0]+S[0]=0
        cht.add_line(0, 0);

        for (int i = 1; i <= m; i++) {
            // query best j < i
            ll best = cht.query(r[i-1]);
            // add the group-cost term
            dp1[i] = best + (ll)i * r[i-1] - S[i];
            // now insert line for this i as a future j
            // slope = -i, intercept = dp0[i] + S[i]
            cht.add_line(- (ll)i, dp0[i] + S[i]);
        }

        dp0.swap(dp1);
    }

    // answer = dp0[m]
    cout << dp0[m] << "\n";
    return 0;
}

 