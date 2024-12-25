#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;

vector<int> vals;                   // Gold in each camp
vector<vector<int>> adj;            // Adjacency list for the tree
vector<vector<ll>> dp;              // DP table: dp[node][0/1]

int c;                              // Cost to strengthen a camp's neighbors


// kth positive 

void dfs(int curr, int parent) { 
    dp[curr][0] = 0;                // Not strengthened
    dp[curr][1] = vals[curr];       // Strengthened, starts with its own gold

    for (int child : adj[curr]) {
        if (child == parent) continue;
        dfs(child, curr);
        dp[curr][1] += max(dp[child][1] - (2 * c), dp[child][0]);
        // strengthnen or dont wstrength we
        // If current node is not strengthened, take the max of strengthened or not
        dp[curr][0] += max(dp[child][0], dp[child][1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n >> c;

        vals.assign(n + 1, 0);
        adj.assign(n + 1, vector<int>());
        dp.assign(n + 1, vector<ll>(2, 0));

        for (int i = 1; i <= n; i++) {
            cin >> vals[i];
        }

        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        dfs(1, -1);  // Run DFS from node 1 (root)

        cout << max(dp[1][0], dp[1][1]) << endl;

        // Clear for the next test case
        vals.clear();
        adj.clear();
        dp.clear();
    }

    return 0;
}
