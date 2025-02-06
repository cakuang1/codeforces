#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
const int MOD = 1000000007;
const ll INF = 1e18;

int dp[5005][5005];       // dp[i][j] = minimum time to reach node j with exactly i edges
int parent[5005][5005];   // parent[i][j] = previous node before j on path of i edges

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);    

    int n, m, t; 
    cin >> n >> m >> t;
    
    vector<vector<pair<int, int>>> adj(n + 1);
    
    // Read edges
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[b ].push_back({a, c});  // Graph adjacency list (forward edges)
    }

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = INF;
            parent[i][j] = -1;
        }
    }
    
    dp[0][1] = 0;  // Starting at node 1 with 0 edges and time 0

    int maxPathLength = 0;  // To track the longest valid path

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (auto edge : adj[j]) {
                int u = edge.first;
                int cost = edge.second;

                if (dp[i - 1][u] != INF && dp[i - 1][u] + cost < dp[i][j]) {
                    dp[i][j] = dp[i - 1][u] + cost;
                    parent[i][j] = u;  // Store previous node
                }
            }
        }
        if (dp[i][n] <= t) {
            maxPathLength = i;  // Longest valid path length
        }
    }

    cout << maxPathLength + 1 << endl;

    vector<int> path;
    int currNode = n;
    int currLength = maxPathLength;

    while (currNode != -1) {
        path.push_back(currNode);
        currNode = parent[currLength][currNode];
        currLength--;
    }
    reverse(path.begin(), path.end());

    for (int i = 0 ; i < path.size(); i ++) {
        cout << path[i] << " ";
    }
}
