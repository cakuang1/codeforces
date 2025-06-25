#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100000;
const int LOG  = 18;

int n, k;
vector<pair<int,int>> adj[MAXN+1];
int parent_[MAXN+1], depth[MAXN+1];
int up[MAXN+1][LOG];
ll net[MAXN+1], sumv[MAXN+1];
int res[MAXN+1];  // res[edge_id]

// 1) DFS to compute parent_, depth, tin/tout if needed, but here just parent/depth
void dfs1(int u,int p){
    parent_[u]=p;
    for(auto &e:adj[u]){
        int v=e.first, id=e.second;
        if(v==p) continue;
        depth[v]=depth[u]+1;
        dfs1(v,u);
    }
}

// 2) LCA via binary lifting
int lca(int a,int b){
    if(depth[a]<depth[b]) swap(a,b);
    int diff=depth[a]-depth[b];
    for(int j=0;j<LOG;j++){
        if(diff&(1<<j)) a=up[a][j];
    }
    if(a==b) return a;
    for(int j=LOG-1;j>=0;j--){
        if(up[a][j]!=up[b][j]){
            a=up[a][j];
            b=up[b][j];
        }
    }
    return parent_[a];
}

// 3) DFS to accumulate net[] into sumv[], and record edge results
void dfs2(int u,int p){
    sumv[u] = net[u];
    for(auto &e:adj[u]){
        int v=e.first, id=e.second;
        if(v==p) continue;
        dfs2(v,u);
        sumv[u] += sumv[v];
        res[id] = sumv[v]; // edge u-v (id) is used sumv[v] times
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }

    // build parent_ and depth by rooting at 1
    depth[1]=0;
    dfs1(1,0);

    // build up table: up[v][0] = parent_[v]
    for(int v=1;v<=n;v++){
        up[v][0] = parent_[v];
    }
    for(int j=1;j<LOG;j++){
        for(int v=1;v<=n;v++){
            int w = up[v][j-1];
            up[v][j] = w ? up[w][j-1] : 0;
        }
    }

    // read k queries, do net-difference
    cin>>k;
    while(k--){
        int a,b;
        cin>>a>>b;
        int c = lca(a,b);
        net[a] += 1;
        net[b] += 1;
        net[c] -= 2;
    }

    // accumulate and fill res[]
    dfs2(1,0);

    // output edge answers in input order
    for(int i=0;i<n-1;i++){
        cout<<res[i]<<"\n";
    }
    return 0;
}
