#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

int n;
vector<vector<pair<int,ll>>> adj;
vector<ll> w, dp;
ll answer = 0;

void dfs(int v, int p){
    // We'll collect the top two best "down-paths" through v:
    // childContribution = dp[child] - cost(edge) + w[v]
    ll best1 = -INF, best2 = -INF;

    // Recurse on children
    for(auto &e : adj[v]){
        int u        = e.first;
        ll  costEdge = e.second;
        if(u == p) continue;
        dfs(u, v);
        ll cur = dp[u] - costEdge + w[v];
        if(cur > best1){
            best2 = best1;
            best1 = cur;
        } else if(cur > best2){
            best2 = cur;
        }
    }

    // At v, the best single-leg path is either just w[v] (leaf case)
    // or the best child contribution.
    dp[v] = max(w[v], best1);
    // Update global answer with:
    // 1) the best single endpoint dp[v]
    // 2) a "through-v" path combining two children: best1 + best2 - w[v]
    answer = max(answer, dp[v]);
    if(best2 > -INF/2){
        answer = max(answer, best1 + best2 - w[v]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    w .assign(n+1, 0);
    dp.assign(n+1, 0);
    adj.assign(n+1, {});

    for(int i = 1; i <= n; i++){
        cin >> w[i];
    }
    for(int i = 0; i < n-1; i++){
        int a,b; ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }

    // Root anywhere; 1 is fine
    dfs(1, 0);

    cout << answer << "\n";
    return 0;
}
