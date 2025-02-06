#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
long double res = 0;

void dfs(int curr, int parent, long double prob, int length) {
    // Count the number of children excluding the parent
    int children = 0;
    for (int neigh : adj[curr]) {
        if (neigh != parent) {
            children++;
        }
    }

    if (children == 0) {
        res += length * prob;
        return;
    }

    // Recur for all children
    for (int neigh : adj[curr]) {
        if (neigh != parent) {
            dfs(neigh, curr, prob / children, length + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    adj.resize(n + 1); // Adjacency list for the tree

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Start DFS from node 1
    dfs(1, -1, 1.0, 0);

    // Print result with precision
    cout << fixed << setprecision(10) << res << "\n";

    return 0;
}
