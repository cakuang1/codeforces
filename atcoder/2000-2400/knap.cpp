// https://www.youtube.com/watch?v=R0P_f0gXXqs
// I could feel your heartbeat
// I could feel somewhere you’re looking down
// ‘Cause it’s you who I’m loving
// And it’s you that I want in need

#ifndef ONLINE_JUDGE
#include "templates/debug.hpp"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using i128 = __int128_t;

#define int i64
constexpr i64 INF = 1e18;
void solve() {
    int n, w; cin >> n >> w;
    vector<vector<int>> vw(w + 1);
    for (int i = 0; i < n; i++) {
        int w, v; cin >> w >> v;
        vw[w].push_back(v);
    }
    vector<int> ans(w + 1);
    for (int wi = 1; wi <= w; wi++) {
        if (vw[wi].empty()) continue;
        int count = w / wi;
        vector<int> values;
        for (int v: vw[wi]) {
            for (int i = 1; i <= count; i++) {
                values.push_back(v - 2 * i + 1);
            }
        }
        sort(values.begin(), values.end(), greater<>());
        values.resize(count);
        for (int v: values) {
            for (int i = w; i >= wi; i--) {
                ans[i] = max(ans[i], ans[i - wi] + v);
            }
        }
    }
    cout << ranges::max(ans) << endl;
}


#undef int

// Make bold hypotheses and verify carefully
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    };
}