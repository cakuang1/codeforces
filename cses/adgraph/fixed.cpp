#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> adj(n+1);
    for(int i = 0; i < m; ++i){
        int a,b; 
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // dist_even[u][v]: distance from u to v with even number of steps (v parity 0)
    // We will store distances from each source s to every (node, parity):
    // dist[s][node][parity]
    // To save memory, we store dist[s][2*node + parity] flattening parity dimension.
    // n <= 2500 so n*(2n) = 12.5M ints fits in memory (~50MB).
    const int INF = -1;
    vector<vector<int>> dist(n+1, vector<int>(2*(n+1), INF));

    queue<pair<int,int>> que; // (node, parity)

    for(int s = 1; s <= n; ++s){
        // BFS from (s,0)
        auto &ds = dist[s];
        while(!que.empty()) que.pop();
        ds[2*s + 0] = 0;
        que.push({s,0});

        while(!que.empty()){
            auto [u, p] = que.front(); que.pop();
            int dcur = ds[2*u + p];
            int np = p ^ 1; // parity flips after one edge
            for(int v: adj[u]){
                if(ds[2*v + np] == INF){
                    ds[2*v + np] = dcur + 1;
                    que.push({v, np});
                }
            }
        }
    }

    while(q--){
        int a,b;
        long long w;
        cin >> a >> b >> w;
        int p = w & 1;
        int d = dist[a][2*b + p];
        if(d != INF && d <= w) cout << "YES\n";
        else cout << "NO\n";
    }
    
    // mipelemetn waprity w 
    return 0;
}
