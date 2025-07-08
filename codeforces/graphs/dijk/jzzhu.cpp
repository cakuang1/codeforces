#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll INF = LLONG_MAX / 4;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int,ll>>> adj(n+1);

    struct Edge { int u, v; ll w; };
    vector<Edge> roads(m);
    for(int i = 0; i < m; i++){
        cin >> roads[i].u >> roads[i].v >> roads[i].w;
        auto &e = roads[i];
        adj[e.u].emplace_back(e.v, e.w);
        adj[e.v].emplace_back(e.u, e.w);
    }

    vector<int> trainCity(k);
    vector<ll>  trainCost(k);
    for(int i = 0; i < k; i++){
        cin >> trainCity[i] >> trainCost[i];
        // also add train as an undirected edge
        adj[1].emplace_back(trainCity[i], trainCost[i]);
        adj[trainCity[i]].emplace_back(1, trainCost[i]);
    }

    // 1) Dijkstra from city 1
    vector<ll> dist(n+1, INF);
    dist[1] = 0;
    priority_queue<pair<ll,int>,
                   vector<pair<ll,int>>,
                   greater<>> pq;
    pq.push({0,1});
    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto &ed : adj[u]){
            int v = ed.first; ll w = ed.second;
            ll nd = d + w;
            if(nd < dist[v]){
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    // 2) Build shortest‐path DAG in‐degree from roads only
    vector<int> indeg(n+1, 0);
    for(auto &e : roads){
        int u=e.u, v=e.v; ll w=e.w;
        if(dist[u] + w == dist[v]) indeg[v]++;
        if(dist[v] + w == dist[u]) indeg[u]++;
    }

    // 3) Process trains in input order, counting which are redundant
    int canClose = 0;
    for(int i = 0; i < k; i++){
        int v = trainCity[i];
        ll y = trainCost[i];
        if(dist[v] < y){
            // strictly worse than road‐only path
            canClose++;
        }
        else if(dist[v] == y){
            if(indeg[v] > 0){
                // there's already a genuine road edge feeding v
                canClose++;
            } else {
                // this train becomes the unique incoming edge
                indeg[v]++;
            }
        }
        // if dist[v] > y, that train strictly improves dist[v],
        // but that cannot happen because we included trains in Dijkstra.
    }

    cout << canClose << "\n";
    return 0;
}

