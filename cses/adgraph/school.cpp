#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> adj;   // adjacency from left side [1..nL] to right [1..nR]
    vector<int> dist, pairU, pairV;

    HopcroftKarp(int _nL, int _nR)
        : nL(_nL), nR(_nR),
          adj(nL+1),
          dist(nL+1),
          pairU(nL+1),
          pairV(nR+1)
    {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        // distance 0 for all free u
        for(int u = 1; u <= nL; u++){
            if(pairU[u] == 0){
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INT_MAX;
            }
        }
        dist[0] = INT_MAX;

        while(!q.empty()){
            int u = q.front(); q.pop();
            if(dist[u] < dist[0]){
                for(int v: adj[u]){
                    if(dist[pairV[v]] == INT_MAX){
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        // if we reached free node on right (pairV[v]==0) we have an augmenting path
        return dist[0] != INT_MAX;
    }

    bool dfs(int u) {
        if(u == 0) return true;
        for(int v: adj[u]){
            if(dist[pairV[v]] == dist[u] + 1){
                if(dfs(pairV[v])){
                    pairU[u] = v;
                    pairV[v] = u;
                    return true;
                }
            }
        }
        dist[u] = INT_MAX; // no augmenting path through u
        return false;
    }

    int maxMatching() {
        int matching = 0;
        // repeatedly build layered graph and find blocking flow
        while(bfs()){
            for(int u = 1; u <= nL; u++){
                if(pairU[u] == 0 && dfs(u)){
                    matching++;
                }
            }
        }
        return matching;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    HopcroftKarp hk(n, m);
    vector<pair<int,int>> edges(k);
    for(int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b;
        hk.addEdge(a, b);
        edges[i] = {a,b};
    }

    int r = hk.maxMatching();
    cout << r << "\n";
    // output any matched pairs
    for(int u = 1; u <= n; u++){
        if(hk.pairU[u] != 0){
            cout << u << " " << hk.pairU[u] << "\n";
        }
    }

    return 0;
}
