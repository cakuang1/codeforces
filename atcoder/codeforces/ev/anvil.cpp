#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;

long long mod_pow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}
long long inv(long long x) { return mod_pow((x % MOD + MOD) % MOD, MOD - 2); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<long long> l(n), r(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];

    // Reverse problems so that counting non-decreasing on reversed
    // equals non-increasing on the original.
    reverse(l.begin(), l.end());
    reverse(r.begin(), r.end());

    // Build half-open endpoints and collect breakpoints
    vector<long long> L(n), R(n), V;
    V.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        L[i] = l[i];
        R[i] = r[i] + 1;      // [l, r] -> [l, r+1)
        V.push_back(L[i]);
        V.push_back(R[i]);
    }
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());
    int S = (int)V.size() - 1;               // number of segments [V[j], V[j+1])

    // Segment lengths
    vector<long long> seglen(S);
    for (int j = 0; j < S; ++j) seglen[j] = V[j + 1] - V[j];  // >= 1

    // cover[i][j]: whole segment j is inside [L[i], R[i])
    vector<vector<char>> cover(n, vector<char>(S, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < S; ++j) {
            if (L[i] <= V[j] && V[j + 1] <= R[i]) cover[i][j] = 1;
        }
    }

    // Precompute inv(1..n) for small k (k <= n <= 50)
    vector<long long> invInt(n + 1, 1);
    for (int i = 2; i <= n; ++i) invInt[i] = inv(i);

    // DP:
    // dp[i][j] = number of ways to assign the first i problems using only the first j segments
    // (i.e., segments [0..j-1]). We'll iterate j from 0..S-1 and transition to j+1.
    vector<vector<long long>> dp(n + 1, vector<long long>(S + 1, 0));
    dp[0][0] = 1;

    for (int j = 0; j < S; ++j) {
        // run[i]: max k s.t. problems i..i+k-1 all allow segment j
        vector<int> run(n + 1, 0); // 0-based problems, run[n]=0 sentinel
        for (int i = n - 1; i >= 0; --i) {
            run[i] = cover[i][j] ? (run[i + 1] + 1) : 0;
        }

        // ways_j[k] = C(seglen[j] + k - 1, k) via rising product
        vector<long long> ways_j(n + 1, 0);
        ways_j[0] = 1;
        long long Lm = (seglen[j] % MOD + MOD) % MOD;
        for (int k = 1; k <= n; ++k) {
            long long term = (Lm + (k - 1)) % MOD;     // len + k - 1
            ways_j[k] = ways_j[k - 1] * term % MOD * invInt[k] % MOD;
        }

        // transitions: pick k (>=0) items in this segment, then move to j+1
        for (int i0 = 0; i0 <= n; ++i0) {
            long long cur = dp[i0][j];
            if (!cur) continue;
            int limit = (i0 == n ? 0 : run[i0]); // we can take at most run[i0] here
            for (int k = 0; k <= limit; ++k) {
                int i1 = i0 + k;
                long long add = cur * ways_j[k] % MOD;
                dp[i1][j + 1] = (dp[i1][j + 1] + add) % MOD;
            }
        }
    }

    long long favorable = dp[n][S] % MOD;

    // Denominator: total number of sequences
    long long total = 1;
    for (int i = 0; i < n; ++i) {
        long long len = (r[i] - l[i] + 1) % MOD;
        total = total * len % MOD;
    }

    long long ans = favorable * inv(total) % MOD;
    cout << ans << '\n';
    return 0;
}
