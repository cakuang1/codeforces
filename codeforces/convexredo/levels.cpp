#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
static const long double INF = 1e30L;
 
struct Line {
    // we'll maintain y = slope * x + intercept
    ll slope;
    long double intercept;
};
 
// return true if L2 is never part of the max‐envelope of L1, L2, L3
// i.e. intersection(L1,L2).x >= intersection(L2,L3).x
bool isBad(const Line &L1, const Line &L2, const Line &L3) {
    // (c2-c1)/(m1-m2) >= (c3-c2)/(m2-m3)
    long double lhs = (L2.intercept - L1.intercept)
                    / (long double)(L1.slope - L2.slope);
    long double rhs = (L3.intercept - L2.intercept)
                    / (long double)(L2.slope - L3.slope);
    return lhs >= rhs;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, k;
    cin >> n >> k;
    vector<ll> t(n+1);
    for(int i = 1; i <= n; i++){
        cin >> t[i];
    }
    // Prefix sums P[i] = t[1]+...+t[i]
    vector<ll> P(n+1, 0);
    for(int i = 1; i <= n; i++) {
        P[i] = P[i-1] + t[i];
    }
    // SA[i] = sum_{j=1..i} P[j]/t[j]
    // SB[i] = sum_{j=1..i} 1/t[j]
    vector<long double> SA(n+1, 0), SB(n+1, 0);
    for(int i = 1; i <= n; i++){
        SA[i] = SA[i-1] + (long double)P[i]/t[i];
        SB[i] = SB[i-1] + 1.0L/t[i];
    }
 
    // dp_prev[r] = dp[c-1][r], dp_cur[r] = dp[c][r]
    vector<long double> dp_prev(n+1, INF), dp_cur(n+1, INF);
    dp_prev[0] = 0.0L;
 
    for(int c = 1; c <= k; c++){
        // We'll maintain a deque of Lines for max(slope * x + intercept)
        deque<Line> hull;
        // Seed with l=1  ⇒  uses dp_prev[0]
        // slope = P[0] = 0
        // f = dp_prev[0] - SA[0] + P[0]*SB[0] = 0
        // we store intercept = -f = 0
        hull.push_back({ 0, 0.0L });
 
        // Build dp_cur[1..n]
        for(int r = 1; r <= n; r++){
            long double x = SB[r];
 
            // Query: pop from front while next line is better at x
            while(hull.size() >= 2) {
                long double y0 = hull[0].slope * x + hull[0].intercept;
                long double y1 = hull[1].slope * x + hull[1].intercept;
                if(y1 >= y0) hull.pop_front();
                else break;
            }
            // best value = hull.front().slope * x + intercept
            long double bestLine = hull.front().slope * x + hull.front().intercept;
 
            // dp[c][r] = SA[r] - bestLine
            dp_cur[r] = SA[r] - bestLine;
 
            // Now insert the line corresponding to ℓ = r+1 for future r's:
            // We need slope = m_r = P[r]
            // and f_r = dp_prev[r] - SA[r] + P[r]*SB[r]
            // so intercept = -f_r
            if (dp_prev[r] < INF/2) {
                ll m_new = P[r];
                long double f_new = dp_prev[r] - SA[r] + (long double)P[r]*SB[r];
                long double c_new = -f_new;
                Line nl{ m_new, c_new };
 
                // Pop from back while the last line is made obsolete
                while(hull.size() >= 2 &&
                      isBad(hull[hull.size()-2],
                            hull[hull.size()-1],
                            nl))
                {
                    hull.pop_back();
                }
                hull.push_back(nl);
            }
        }
 
        // swap dp_cur into dp_prev, reset dp_cur
        dp_prev.swap(dp_cur);
        fill(dp_cur.begin(), dp_cur.end(), INF);
    }
 
    // answer is dp_prev[n] = dp[k][n]
    cout << fixed << setprecision(10) << (double)dp_prev[n] << "\n";
    return 0;
}

//2dwerpalc nwsi what ew