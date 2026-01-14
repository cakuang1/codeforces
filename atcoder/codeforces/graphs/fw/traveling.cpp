#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> edges(n+1);
    vector<int> deg(n+1, 0);
    ll W = 0;

    // adjacency for connectivity check (ignore loops)
    vector<vector<int>> adj(n+1);

    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].emplace_back(v, w);
        if(u != v){
            edges[v].emplace_back(u, w);
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++; 
            deg[v]++;
        } else {
            // loop contributes twice to degree
            deg[u] += 2;
        }
        W += w;
    }

    // If no edges, trivial tour cost = 0
    if(m == 0){
        cout << 0 << "\n";
        return 0;
    }

    // Connectivity: all vertices with deg>0 must be reachable from 1
    vector<bool> vis(n+1,false);
    queue<int> q;
    if(deg[1] > 0){
        vis[1] = true;
        q.push(1);
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v: adj[u]){
            if(!vis[v]){
                vis[v] = true;
                q.push(v);
            }
        }
    }
    for(int v = 1; v <= n; v++){
        if(deg[v] > 0 && !vis[v]){
            cout << -1 << "\n";
            return 0;
        }
    }

    // Build distance matrix and run Floyd–Warshall
    const ll INF_DIST = INF;
    vector<vector<ll>> dist(n+1, vector<ll>(n+1, INF_DIST));
    for(int i = 1; i <= n; i++){
        dist[i][i] = 0;
        for(auto &pr: edges[i]){
            int j = pr.first, w = pr.second;
            dist[i][j] = min(dist[i][j], (ll)w);
        }
    }
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            if(dist[i][k] == INF_DIST) continue;
            for(int j = 1; j <= n; j++){
                ll nd = dist[i][k] + dist[k][j];
                if(nd < dist[i][j]){
                    dist[i][j] = nd;
                }
            }
        }
    }
    vector<int> odd;
    for(int v = 1; v <= n; v++){
        if(deg[v] % 2 == 1){
            odd.push_back(v);
        }
    }
    int t = odd.size();
    // If already Eulerian
    if(t == 0){
        cout << W << "\n";
        return 0;
    }

    int FULL = 1 << t;
    vector<ll> dp(FULL, INF);
    dp[0] = 0;
    for(int mask = 1; mask < FULL; mask++){
        // find first set bit i
        int i = __builtin_ctz(mask);
        int m2 = mask ^ (1 << i);
        // pair i with some j>i
        for(int j = i+1; j < t; j++){
            if(m2 & (1 << j)){
                int m3 = m2 ^ (1 << j);
                ll cost = dist[ odd[i] ][ odd[j] ];
                dp[mask] = min(dp[mask], dp[m3] + cost);
            }
        }
    }
    


    // determine the minmiu mw
    ll matchingCost = dp[FULL - 1];
    // Total = original edges once + duplicated paths
    cout << (W + matchingCost) << "\n";
    return 0;
}
