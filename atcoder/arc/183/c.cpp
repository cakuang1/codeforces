#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
static const int MAXN = 505;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    struct Query {
        int L, R, X;
    };

    vector<Query> qs(M);

    for (auto &[L, R, X] : qs) {
        cin >> L >> R >> X;
        --L;
        --R;
        --X;
    }

    // C[n][k]
    static int C[MAXN][MAXN];

    for (int n = 0; n <= N; ++n) {
        C[n][0] = C[n][n] = 1;

        for (int k = 1; k < n; ++k) {
            C[n][k] = C[n - 1][k - 1] + C[n - 1][k];

            if (C[n][k] >= MOD)
                C[n][k] -= MOD;
        }
    }

    // bad[l][r][m] would be too large / inconvenient.
    //
    // Instead precompute forbid[l][r] as a bitset:
    // forbid[l][r][m] = whether m cannot be the maximum of [l,r].
    //
    // N <= 500, so bitset works nicely.
    static bitset<MAXN> forbid[MAXN][MAXN];

    // For every left endpoint l, add constraints as r grows.
    for (int l = 0; l < N; ++l) {
        vector<vector<int>> add(N);

        for (auto [L, R, X] : qs) {
            if (L >= l) {
                add[R].push_back(X);
            }
        }

        bitset<MAXN> cur;

        for (int r = l; r < N; ++r) {
            for (int x : add[r]) {
                cur.set(x);
            }

            forbid[l][r] = cur;
        }
    }

    static int dp[MAXN][MAXN];

    // Process by increasing interval length.
    for (int len = 1; len <= N; ++len) {
        for (int l = 0; l + len <= N; ++l) {
            int r = l + len - 1;

            long long ans = 0;

            for (int m = l; m <= r; ++m) {
                if (forbid[l][r].test(m))
                    continue;

                long long left =
                    (m == l ? 1 : dp[l][m - 1]);

                long long right =
                    (m == r ? 1 : dp[m + 1][r]);

                long long ways = C[len - 1][m - l];

                ways = ways * left % MOD;
                ways = ways * right % MOD;

                ans += ways;

                if (ans >= MOD)
                    ans -= MOD;
            }

            dp[l][r] = ans;
        }
    }

    cout << dp[0][N - 1] << '\n';
}