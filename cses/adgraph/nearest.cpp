#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k;
    cin >> n >> m >> k;
    vector<int> shops(k);
    for(int i=0;i<k;i++) {
        cin >> shops[i];
        --shops[i];  // zero‐index
    }

    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int a,b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    const int INF = 1e9;
    vector<int> dist(n, INF), src(n, -1), best(n, INF);
    queue<int> q;

    // Initialize multi-source BFS
    for(int s : shops){
        dist[s] = 0;
        src[s]  = s;
        q.push(s);
    }

    // BFS
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : adj[u]){
            if(dist[v] == INF) {
                // first time seen: claim by same source
                dist[v] = dist[u] + 1;
                src[v]  = src[u];
                q.push(v);
            } 
            else if(src[v] != src[u]) {
                // collision: wave from src[u] meets wave from src[v]
                int su = src[u], sv = src[v];
                int d = dist[u] + dist[v] + 1;
                best[su] = min(best[su], d);
                best[sv] = min(best[sv], d);
            }
        }
    }

    // Output
    // For each city:
    // - if it's *not* a shop: dist[i] (or -1 if INF)
    // - if it *is* a shop: best[i] (or -1 if INF)
    vector<bool> isShop(n,false);
    for(int s: shops) isShop[s] = true;

    for(int i=0;i<n;i++){
        int ans;
        if(!isShop[i]) {
            ans = (dist[i]==INF ? -1 : dist[i]);
        } else {
            ans = (best[i]==INF ? -1 : best[i]);
        }
        cout << ans << (i+1<n?' ':'\n');
    }
    return 0;
}
