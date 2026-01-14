#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll INF = LLONG_MAX/4;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n+1);
    for(int i = 0; i < m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    // dist[v] = best known distance from 1 to v
    vector<ll> dist(n+1, INF);
    // parent[v] = how we reached v on the shortest path
    vector<int> parent(n+1, -1);

    dist[1] = 0;
    // min-heap of (dist, vertex)
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0,1});

    while(!pq.empty()){
        auto [d,u] = pq.top(); 
        pq.pop();
        if(d > dist[u]) continue;
        for(auto [v,w] : adj[u]){
            ll nd = d + w;
            if(nd < dist[v]){
                dist[v] = nd;
                parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    
    if(dist[n] == INF){
        cout << -1 << "\n";
        return 0;
    }
    vector<int> path;
    for(int x = n; x != -1; x = parent[x]){
        path.push_back(x);
    }
    reverse(path.begin(), path.end());
    for(int v: path){
        cout << v << " ";
    }
    cout << "\n";
    return 0;
}
