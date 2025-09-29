#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1000000007;
const ll INFLL = (1LL<<60);

static inline int popcnt(int x) { return __builtin_popcount((unsigned)x); }

bool valid(int upper, int lower, int w) {
    // If two adjacent bits are set in the lower row AND the same two adjacent bits
    // are set in the upper row, that creates a 2x2 block -> invalid.
    for (int i = 1; i < w; ++i) {
        int prev = i - 1;
        bool low_pair  = ((lower & (1 << i)) && (lower & (1 << prev)));
        if (low_pair) {
            bool up_pair = ((upper & (1 << i)) && (upper & (1 << prev)));
            if (up_pair) return false;
        }
    }
    return true;
}

void solve() {
    int h, w; 
    if (!(cin >> h >> w)) return;

    vector<int> arr(h, 0);
    for (int i = 0; i < h; ++i) {
        string s; cin >> s;
        int mask = 0;
        for (int c = 0; c < w; ++c) {
            if (s[c] == '#') mask |= (1 << c);
        }
        arr[i] = mask;
    }

    const int M = 1 << w;
    vector<int> dp(M, INT_MAX);
    for (int m = 0; m < M; ++m) {
        dp[m] = popcnt(arr[0] ^ m);
    }

    for (int r = 1; r < h; ++r) {
        vector<int> ndp(M, INT_MAX);
        for (int cur = 0; cur < M; ++cur) {
            int cost_here = popcnt(arr[r] ^ cur);
            for (int prev = 0; prev < M; ++prev) {
                if (dp[prev] == INT_MAX) continue;
                if (valid(prev, cur, w)) {
                    ndp[cur] = min(ndp[cur], dp[prev] + cost_here);
                }
            }
        }
        dp.swap(ndp);
    }

    int ans = *min_element(dp.begin(), dp.end());
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    if (!(cin >> t)) return 0;
    while (t--) solve();
    return 0;
}
