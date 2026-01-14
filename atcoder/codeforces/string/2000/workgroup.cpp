#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 200005;

vector<int> vals;          // Efficiency of each node
vector<vector<int>> adj;   // Adjacency list
ll dp[N][2];               // dp[v][0] = even parity, dp[v][1] = odd parity


//
void dfs(int u) {
    int tmp0 = dp[u][0],tmp1 = dp[u][1];
    for (int v : adj[u]) {
        tmp0 = dp[u][0];
        tmp1 = dp[u][1];
        dfs(v); // Recursively process the child
        dp[u][0] = max(dp[u][0] + dp[v][0] ,  dp[u][1] + dp[v][1]); 
        dp[u][1] = max(tmp0 + dp[v][1] , dp[u][1] + dp[v][0]); 
    } 
    dp[u][1] = max(dp[u][1] , dp[u][0] + vals[u]); 
}

    // this dosent envemake we=any sense w
    // 
// how to see thwi 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vals.resize(n + 1);
    adj.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int p, a;
        cin >> p >> a; // p = supervisor, a = efficiency of i-th employee
        vals[i] = a;

        if (p != -1) {
            adj[p].push_back(i); // Add child to adjacency list
        }
    }
    if (n == 1) {
        cout << vals[1] << endl;
        return 0;
    }
    // ewehow wet wee thsi w how owto dtemrine wethis w weehow to wdetemrien wehtsswe
    dfs(1); // Start DFS from the root (node 1)
    cout << dp[1][0] << endl; // Maximum efficiency with even parity
    return 0;
}

//  how doe this wwork wyou weasusme werthreees doeswetis wrmak ewanysnes 