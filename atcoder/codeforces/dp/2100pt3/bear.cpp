#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, k;
vector<vector<int>> adj;

// Global sums: S is the sum of distances over all pairs,
// and extra is the extra cost such that L + f(L,k) is divisible by k.
ll S = 0, extra = 0;

// DFS to compute subtree sizes and accumulate S
int dfsSize(int u, int p) {
    int size = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        int sz = dfsSize(v, u);
        S += (ll) sz * (n - sz);
        size += sz;
    }
    return size;
}

// dp[u][r] = number of vertices in u's subtree (including u)
// that are at a distance d from u with d mod k == r.
vector<vector<ll>> dp;

void dfsDP(int u, int p) {
    dp[u].assign(k, 0);
    dp[u][0] = 1; // The trivial path (u alone) has distance 0.
    
    for (int v : adj[u]) {
        if (v == p) continue;
        dfsDP(v, u);
        
        // Count contributions for pairs:
        // one vertex from the current dp[u] (with remainder i)
        // and one vertex from dp[v] (with remainder j).
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                // The distance between these two vertices is: i + j + 1.
                int d = i + j + 1;
                int r = d % k;
                int addVal = (r == 0 ? 0 : k - r);
                extra += dp[u][i] * dp[v][j] * addVal;
            }
        }
        
        // Merge dp[v] into dp[u]: shift distances by one (due to the edge from u to v).
        vector<ll> shifted(k, 0);
        for (int j = 0; j < k; j++) {
            int new_r = (j + 1) % k;
            shifted[new_r] += dp[v][j];
        }
        for (int i = 0; i < k; i++) {
            dp[u][i] += shifted[i];
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    adj.resize(n + 1);
    dp.resize(n + 1, vector<ll>(k, 0));
    
    for (int i = 1; i <= n - 1; i++){
        int u, v;
        cin >> u >> v;
        // Build an undirected tree.
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // First, compute S = sum of distances over all pairs.
    dfsSize(1, -1);
    // Next, compute the extra cost from "rounding up" each distance.
    dfsDP(1, -1);
    
    // The final answer is (S + extra) divided by k.
    ll ans = (S + extra) / k;
    cout << ans << "\n";
    
    return 0;
}
