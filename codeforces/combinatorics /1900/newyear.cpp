#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD2 = 998244353; 
const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 1000001; // check the limits, dummy

// (Other functions provided for modular arithmetic and combinatorics are not used in this part.)

// We'll use DFS to compute subtree sizes (dp[]) and also compute P(j) for each edge.
// The tree is represented as an adjacency list where each entry is a pair:
//   (neighbor, edge_index)
void dfs(int a, int p, vector<int> &dp, vector<vector<pair<int,int>>> &adj, vector<double> &prob, int n) { 
    dp[a] = 1;  // count itself
    for (auto c : adj[a]) {
        int nxt = c.first, edgeIdx = c.second;
        if (nxt == p) continue;
        dfs(nxt, a, dp, adj, prob, n);
        dp[a] += dp[nxt];
        // For the edge connecting a and nxt, treat nxt as the deeper node.
        // Then the subtree size on that side is dp[nxt] and the remainder is n - dp[nxt].
        // The probability that a random unordered pair of vertices is separated by this edge is:
        //   2 * dp[nxt]*(n - dp[nxt]) / (n*(n-1))
        prob[edgeIdx] = double(2LL * dp[nxt] * (n - dp[nxt])) / (n * (n - 1.0));
    } 
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n; 
    // Build the tree (vertices numbered 1..n)
    // For each edge, we store (neighbor, edge_index). There are n-1 edges.
    vector<vector<pair<int,int>>> adj(n + 1);
    vector<int> dp(n + 1, 0);
    // prob[i] will store the probability that edge i is used in the path between a random pair of vertices.
    vector<double> prob(n + 1, 0.0); 
    // w[i] will store the weight of edge i.
    vector<int> w(n + 1, 0);     
    
    // Read the n-1 edges.
    // We'll assume edges are numbered 1..n-1 in the order given.
    for (int i = 1; i <= n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        w[i] = c;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }


    // w
    dfs(1, -1, dp, adj, prob, n); 
    
    double init = 0; 
    for (int i = 1; i <= n - 1; i++) {
        init += prob[i] * w[i];
    }
    
    int q;
    cin >> q;  // Number of queries.
    
    // Process each update query.
    while (q--) {
        int e, newWeight;
        cin >> e >> newWeight; 
        
        // Update the running total:
        // Subtract old contribution of edge e, update weight, then add new contribution.
        init -= prob[e] * w[e];
        w[e] = newWeight; 
        init += prob[e] * w[e]; 
        
        // Multiply by 3 to get the final answer.
        cout << fixed << setprecision(6) << 3.0 * init << "\n";
    }
    
    return 0;
}
