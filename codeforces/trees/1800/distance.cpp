#include <bits/stdc++.h>
using namespace std;

const int N = 50001; // Maximum number of nodes
const int K = 501;   // Maximum distance
vector<int> adj[N];
int dp[N][K];        // dp[v][i]: number of nodes at distance i from node v
int res = 0;
int n, k;

void dfs(int curr, int parent) {
    dp[curr][0] = 1; // Current node itself is at distance 0
    for (int neighbor : adj[curr]) {
        if (neighbor == parent) continue;
        dfs(neighbor, curr);

        // Count pairs with the current subtree
        for (int i = 1; i <= k; ++i) {
            res += dp[curr][k - i] * dp[neighbor][i - 1];
        }

        // Merge dp values from child to current node
        for (int i = 1; i <= k; ++i) {
            dp[curr][i] += dp[neighbor][i - 1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(dp, 0, sizeof(dp));
    dfs(1, -1);

    cout << res << '\n';
    return 0;
}
