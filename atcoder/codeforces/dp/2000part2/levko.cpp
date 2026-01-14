#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;
using ll = long long;

const int INF = 1e9;

// Global variables
int n, k;
vector<ll> a;

// Returns true if we can achieve an array with max adjacent difference <= x using at most k changes.
bool canAchieve(ll x) {
    // We'll use 1-indexing: dp[i] = minimal modifications needed for positions 1..i, if we keep a[i] unchanged.
    // If we choose a[i] as the first kept element, we must change all earlier ones, i.e. cost = i-1.
    vector<int> dp(n+1, INF);
    for (int i = 1; i <= n; i++) {
        dp[i] = i - 1; // using a[i] as the first kept element means changing all earlier positions.
    }
    
    // Now, try to "chain" kept positions.
    for (int i = 1; i <= n; i++) {
        if(dp[i] == INF) continue;
        for (int j = i + 1; j <= n; j++) {
            // The cost to fix positions from i+1 to j-1 is (j-i-1).
            // Transition from i (kept) to j (to be kept) is valid if:
            // |a[j]-a[i]| <= (j-i)*x.
            if (abs(a[j-1] - a[i-1]) <= (j - i) * x) {
                dp[j] = min(dp[j], dp[i] + (j - i - 1));
            }
        }
    }
    
    // Finally, if we keep element i as the last kept element,
    // then we need to change all positions after i (cost = n - i).
    int best = INF;
    for (int i = 1; i <= n; i++) {
        best = min(best, dp[i] + (n - i));
    }
    
    return best <= k;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    
    // Binary search on x.
    // Lower bound: 0. Upper bound: maximum difference between any two elements.
    ll lo = 0, hi = *max_element(a.begin(), a.end()) - *min_element(a.begin(), a.end());
    ll ans = hi;
    
    while(lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (canAchieve(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
