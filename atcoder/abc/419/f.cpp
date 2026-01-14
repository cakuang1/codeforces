#include <bits/stdc++.h>
using namespace std;

static const long long NEG = -(1LL<<60);

int N, K;
vector<long long> A;
vector<vector<int>> G;

struct DP {
    // dp[b][t], b=0,1,2
    array<vector<long long>, 3> dp;
    DP(int K=0) {
        for (int b=0;b<3;b++) dp[b].assign(K+1, NEG);
    }
};

DP dfs(int u, int p) {
    DP cur(K);
    cur.dp[0][0] = 0; // nothing chosen yet

    for (int v : G[u]) if (v != p) {
        DP ch = dfs(v, u);

        DP nxt(K);
        for (int b=0;b<3;b++) fill(nxt.dp[b].begin(), nxt.dp[b].end(), NEG);

        for (int i = 0; i <= K; i++) {
            for (int j = 0; j + i <= K; j++) {
                // Use child's "closed" contribution (state 0 of child)
                if (ch.dp[0][j] > NEG/2) {
                    // keep boundary state at u
                    for (int b=0;b<3;b++) if (cur.dp[b][i] > NEG/2) {
                        nxt.dp[b][i+j] = max(nxt.dp[b][i+j], cur.dp[b][i] + ch.dp[0][j]);
                    }
                }

                // Use child's "endpoint at child-root" contribution (state 1 of child)
                if (ch.dp[1][j] > NEG/2) {
                    // 1) from b=0 at u, attach to u => b becomes 1, add A[u]
                    if (cur.dp[0][i] > NEG/2) {
                        nxt.dp[1][i+j] = max(nxt.dp[1][i+j], cur.dp[0][i] + ch.dp[1][j] + A[u]);
                    }

                    // 2) carry boundary bookkeeping when u already used
                    if (cur.dp[1][i] > NEG/2) {
                        nxt.dp[1][i+j] = max(nxt.dp[1][i+j], cur.dp[1][i] + ch.dp[1][j]);
                    }
                    if (cur.dp[2][i] > NEG/2) {
                        nxt.dp[2][i+j] = max(nxt.dp[2][i+j], cur.dp[2][i] + ch.dp[1][j]);
                    }

                    // 3) connect two endpoints through u:
                    // u had b=1, child has endpoint => u becomes internal (b=2),
                    // and two endpoints merge into ONE path => (i + j - 1) paths.
                    if (cur.dp[1][i] > NEG/2 && i + j - 1 >= 0) {
                        nxt.dp[2][i+j-1] = max(nxt.dp[2][i+j-1], cur.dp[1][i] + ch.dp[1][j]);
                    }
                }

                // Also allow child endpoint but choose not to "attach" it (already covered by carry rules above),
                // and child closed already handled.
            }
        }

        cur = move(nxt);
    }

    // Start a new path consisting of just u (u becomes an endpoint): dp[1][t] from dp[0][t-1]
    for (int t = 1; t <= K; t++) {
        if (cur.dp[0][t-1] > NEG/2) {
            cur.dp[1][t] = max(cur.dp[1][t], cur.dp[0][t-1] + A[u]);
        }
    }

    // Absorb boundary states into dp[0] (parent doesn't need to know)
    for (int t = 0; t <= K; t++) {
        cur.dp[0][t] = max({cur.dp[0][t], cur.dp[1][t], cur.dp[2][t]});
    }

    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    A.resize(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    G.assign(N, {});
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        --u; --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    DP root = dfs(0, -1);
    cout << *max_element(root.dp[0].begin(), root.dp[0].end()) << "\n";
    return 0;
}

// w