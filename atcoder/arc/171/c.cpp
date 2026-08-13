#include <bits/stdc++.h>
using namespace std;

static constexpr long long MOD = 998244353;

int N;
vector<vector<int>> graph;
vector<long long> fact;

// dp[v][k]:
// After processing the subtree of v,
// exactly k edges from v to its children are selected.
//
// Contributions of all descendants are already included,
// but the factorial contribution for v itself is not yet included.
vector<vector<long long>> dp;

void dfs(int v, int parent) {
    dp[v] = {1};

    for (int u : graph[v]) {
        if (u == parent) continue;

        dfs(u, v);

        // Contribution of u's subtree when edge (v,u) is not selected.
        long long edgeNotUsed = 0;

        // Contribution of u's subtree when edge (v,u) is selected.
        long long edgeUsed = 0;

        for (int k = 0; k < (int)dp[u].size(); ++k) {
            // If parent edge is not selected, degree of u is k.
            edgeNotUsed += dp[u][k] * fact[k] % MOD;
            edgeNotUsed %= MOD;

            // If parent edge is selected, degree of u is k + 1.
            edgeUsed += dp[u][k] * fact[k + 1] % MOD;
            edgeUsed %= MOD;
        }

        vector<long long> next(dp[v].size() + 1, 0);

        for (int k = 0; k < (int)dp[v].size(); ++k) {
            // Do not select edge (v,u).
            next[k] += dp[v][k] * edgeNotUsed % MOD;
            next[k] %= MOD;

            // Select edge (v,u).
            next[k + 1] += dp[v][k] * edgeUsed % MOD;
            next[k + 1] %= MOD;
        }

        dp[v] = move(next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    graph.assign(N, {});
    dp.resize(N);

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    fact.resize(N + 1);
    fact[0] = 1;

    for (int i = 1; i <= N; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    int root = 0;
    dfs(root, -1);

    long long answer = 0;

    // The root has no parent edge, so its degree is exactly k.
    for (int k = 0; k < (int)dp[root].size(); ++k) {
        answer += dp[root][k] * fact[k] % MOD;
        answer %= MOD;
    }

    cout << answer << '\n';
}