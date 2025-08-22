#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Graph edge: to 'v' with weight 'w'
struct Edge { int v; ll w; };

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // adjacency for P[0..n]
    vector<vector<Edge>> adj(n+1);

    for(int i = 0; i < m; i++){
        int l, r;
        ll s;
        cin >> l >> r >> s;
        // P[r] - P[l-1] = s
        adj[l-1].push_back({r,    s});
        adj[r].push_back({l-1, -s});
    }

    vector<ll> P(n+1);            // prefix values
    vector<char> vis(n+1, 0);     // visited marker

    // For each component, BFS/DFS to assign P
    for(int start = 0; start <= n; start++){
        if(vis[start]) continue;
        // start new component, assign P[start]=0
        vis[start] = 1;
        P[start] = 0;
        queue<int> q;
        q.push(start);

        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &e : adj[u]){
                int v = e.v;
                ll want = P[u] + e.w;
                if(!vis[v]){
                    vis[v] = 1;
                    P[v] = want;
                    q.push(v);
                } else {
                    // Check consistency
                    if(P[v] != want){
                        cout << "NO\n";
                        return 0;
                    }
                }
            }
        }
    }
    // If we get here, it's consistent. Recover x_i = P_i - P_{i-1}
    cout << "YES\n";
    for(int i = 1; i <= n; i++){
        ll xi = P[i] - P[i-1];
        cout << xi << (i<n ? ' ' : '\n');
    }
    return 0;
}

// doesht iwewreally ewowkr er