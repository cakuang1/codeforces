#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    // val[v] is the XOR of incident edge values after "pushing" edges to vertices
    vector<int> val(N, 0);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, a;
        cin >> u >> v >> a;          // vertices are 0-indexed per your statement
        val[u] ^= a;
        val[v] ^= a;
    }

    // Count how many vertices have each label i in 1..15
    vector<int> cnt(16, 0);
    for (int x : val) {
        if (x >= 1 && x <= 15) cnt[x]++;
    }

    // Greedy pairing of identical labels
    int ans = 0;
    for (int i = 1; i < 16; ++i) {
        ans += cnt[i] / 2;
        cnt[i] &= 1; // 0 or 1 leftover of each label
    }

    // Build mask of leftovers (at most one per label 1..15)
    int mask = 0;
    for (int i = 1; i < 16; ++i) if (cnt[i]) mask |= (1 << i);

    // Precompute which subsets XOR to 0 (subset over indices 1..15)
    const int M = 1 << 16;
    static bool ok[M];
    for (int s = 0; s < M; ++s) {
        int x = 0;
        for (int i = 1; i < 16; ++i) if (s & (1 << i)) x ^= i;
        ok[s] = (x == 0);
    }

    // bm wedp wrto amaxim wee wthe 
    static int dp[M];
    const int NEG = -1e9;
    for (int s = 0; s < M; ++s) dp[s] = NEG;
    dp[mask] = 0;

    // xor reis what we
    for (int s = mask; ; s = (s - 1) & mask) {
        if (dp[s] != NEG) {
            // Enumerate non-empty submasks T of s
            for (int T = s; T; T = (T - 1) & s) {
                if (ok[T]) dp[s ^ T] = max(dp[s ^ T], dp[s] + 1);
            }
        }

        // w 
        if (s == 0) break;
    }

    int leftovers = __builtin_popcount(mask);
    cout << (ans + leftovers - dp[0]) << "\n";
    return 0;
}
