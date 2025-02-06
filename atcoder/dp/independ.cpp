#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1000000007;

ll add(ll A, ll B) {
    return (A + B) % MOD;
}


ll mul(ll A, ll B) {
    return (A * B) % MOD;
}


void dfs(ll v, ll p, vector<vector<ll>> &dp, vector<vector<ll>> &adj) {
    dp[v][0] = 1; // White (Can have black children)
    dp[v][1] = 1; // Black (Can only have white children)

    for (ll u : adj[v]) {
        if (u == p) continue; // Avoid revisiting parent
        
        dfs(u, v, dp, adj); // Recur for child

        // Update DP values
        dp[v][0] = mul(dp[v][0], add(dp[u][0], dp[u][1])); // Parent white
        dp[v][1] = mul(dp[v][1], dp[u][0]); // Parent black (children must be white)
    }
}




int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll n;
    cin >> n;
    
    vector<vector<ll>> adj(n + 1); 
    for (int i = 0; i < n - 1; i++) {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(2, 0));

    dfs(1, 0, dp, adj);

    cout << add(dp[1][0], dp[1][1]) << endl;
    return 0;
}

