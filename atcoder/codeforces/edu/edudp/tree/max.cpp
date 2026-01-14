#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 200005;

vector<int> adj[N];
ll sum[N], dp1[N], vals[N]; 
int n;

// Compute subtree sums and initial cost when rooted at node 1
void dfs1(int node, int parent) {
    sum[node] = vals[node];

    for (int c : adj[node]) {
        if (c == parent) continue;
        dfs1(c, node);
        sum[node] += sum[c]; 
        dp1[1] += sum[c]; // Contribution to initial cost
    }                 
}

// Re-rooting DFS to find the maximum cost for any node
void dfs2(int node, int parent) {    
    for (int c : adj[node]) {
        if (c == parent) continue;

        // Recompute dp1[c] using dp1[node]
        dp1[c] = dp1[node] + (sum[1] - 2 * sum[c]); 

        dfs2(c, node); 
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);        

    cin >> n; 
    for (int i = 1; i <= n; i++) {
        cin >> vals[i]; 
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }    
    
    dfs1(1, -1);
    dfs2(1, -1);

    cout << *max_element(dp1 + 1, dp1 + n + 1) << '\n';
    return 0;
}
