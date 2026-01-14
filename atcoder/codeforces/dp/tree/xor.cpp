#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int MAXN = 300000;
int n;
vector<int> adj[MAXN+1];
ll vals[MAXN+1];
ll sz[MAXN+1];
ll ans[MAXN+1];

// 1) First DFS: compute subtree sizes and ans[1] exactly
void dfs1(int u, int p){
    sz[u] = 1;
    for(int v: adj[u]){
        if(v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
    }
    if(u != 1){
        ll c = vals[u] ^ vals[p];
        // exact cost for that edge:
        ans[1] += sz[u] * c;
    }
}

// 2) Second DFS: reroot from u -> v exactly
void dfs2(int u, int p){
    for(int v: adj[u]){
        if(v == p) continue;
        ll c = vals[u] ^ vals[v];
        // when rerooting, the net change on that edge is
        // (n - sz[v]) * c  minus  sz[v] * c  = (n - 2*sz[v]) * c
        ans[v] = ans[u] + ( (ll)n - 2*sz[v] ) * c;
        dfs2(v,u);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 1; i <= n; i++){
            adj[i].clear();
            ans[i] = 0;
        }
        for(int i = 1; i <= n; i++){
            cin >> vals[i];
        }
        for(int i = 0; i < n-1; i++){
            int u,v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs1(1, 0);
        dfs2(1, 0);

        for(int r = 1; r <= n; r++){
            cout << ans[r] << (r==n?'\n':' ');
        }
    }
    return 0;
}
