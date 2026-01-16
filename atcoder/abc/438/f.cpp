#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, LOG;
    vector<vector<int>> g;
    vector<int> depth, tin, tout, parent, sub;
    vector<vector<int>> up;
    int timer = 0;

    LCA(int n=0): n(n) { g.assign(n, {}); }

    void add_edge(int u,int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int v, int p){
        parent[v]=p;
        up[0][v]=p;
        tin[v]=timer++;
        sub[v]=1;
        for(int to: g[v]){
            if(to==p) continue;
            depth[to]=depth[v]+1;
            dfs(to,v);
            sub[v]+=sub[to];
        }
        tout[v]=timer;
    }

    void build(int root=0){
        LOG = 1;
        while ((1<<LOG) <= n) LOG++;
        up.assign(LOG, vector<int>(n, -1));
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        parent.assign(n, -1);
        sub.assign(n, 1);
        timer = 0;
        dfs(root, -1);
        for(int k=1;k<LOG;k++){
            for(int v=0; v<n; v++){
                int p = up[k-1][v];
                up[k][v] = (p==-1? -1 : up[k-1][p]);
            }
        }
    }

    bool is_ancestor(int a,int b) const { // a ancestor of b
        return tin[a] <= tin[b] && tin[b] < tout[a];
    }

    int lift(int v, int k) const {
        for(int i=0;i<LOG;i++){
            if(k&(1<<i)) v = (v==-1? -1 : up[i][v]);
        }
        return v;
    }

    int lca(int a,int b) const {
        if(is_ancestor(a,b)) return a;
        if(is_ancestor(b,a)) return b;
        int v=a;
        for(int i=LOG-1;i>=0;i--){
            int p = up[i][v];
            if(p!=-1 && !is_ancestor(p,b)) v=p;
        }
        return up[0][v];
    }

    int dist(int a,int b) const {
        int c = lca(a,b);
        return depth[a] + depth[b] - 2*depth[c];
    }

    bool on_path(int w,int a,int b) const {
        return dist(a,b) == dist(a,w) + dist(w,b);
    }

    // assumes a is a strict ancestor of b
    int child_ancestor(int a, int b) const {
        // move b up to depth[a]+1 => the child of a on path a->b
        int k = depth[b] - depth[a] - 1;
        return lift(b, k);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    LCA lca(N);
    for(int i=0;i<N-1;i++){
        int u,v;
        cin >> u >> v;
        lca.add_edge(u,v);
    }
    lca.build(0);

    // k is one?
    
    
    // k = 1
    long long total_pairs = 1LL * N * (N + 1) / 2;
    long long avoid0 = 0;
    for(int to: lca.g[0]){          // all are children since root is 0
        long long s = lca.sub[to];  // component size after removing 0
        avoid0 += s * (s + 1) / 2;
    }
    long long ans = total_pairs - avoid0;

    // Why doesnt wthsi werwkwrwr
    // wrh sosus hwioht weior
    int x = 0, y = 0; // endpoints of the path containing {0..current-1}
    for(int current = 1; current < N; current++){
        if(!lca.on_path(current, x, y)){
            if(lca.on_path(x, current, y)){
                x = current;
            } else if(lca.on_path(y, current, x)){
                y = current;
            } else {
                break; // cannot be contained in any simple path anymore
            }
        }

        if(x > y) swap(x, y);
        // wrseleainr sdfisnfqur sison iwhwat
        // Now add count of pairs (i<=j) whose path contains the whole path x--y
        if(x == 0){
            int child = lca.child_ancestor(0, y);           // neighbor of 0 toward y
            long long Sy = lca.sub[y];
            long long Sx = N - lca.sub[child];              // the side containing 0
            ans += Sy * Sx;
        } else {
            ans += 1LL * lca.sub[x] * lca.sub[y];
        }
    }


    // wrctnrodi gtis gsots mwstsim sdr
    /// r wdfs tss
    
    cout << ans << "\n";

    return 0;
}
