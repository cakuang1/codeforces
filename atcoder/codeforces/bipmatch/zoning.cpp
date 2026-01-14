#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; long long cap; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> lvl, it;

    Dinic(int n): n(n), g(n), lvl(n), it(n) {}

    void add_edge(int u, int v, long long c){
        Edge a{v, (int)g[v].size(), c};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a); g[v].push_back(b);
    }

    bool bfs(){
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q; q.push(s); lvl[s] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &e: g[u]){
                if(e.cap > 0 && lvl[e.to] == -1){
                    lvl[e.to] = lvl[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return lvl[t] != -1;
    }

    long long dfs(int u, long long f){
        if(!f || u == t) return f;
        for(int &i = it[u]; i < (int)g[u].size(); ++i){
            auto &e = g[u][i];
            if(e.cap > 0 && lvl[e.to] == lvl[u] + 1){
                long long pushed = dfs(e.to, min(f, e.cap));
                if(pushed){
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long maxflow(int S, int T){
        s = S; t = T;
        long long res = 0, pushed;
        while(bfs()){
            fill(it.begin(), it.end(), 0);
            while((pushed = dfs(s, LLONG_MAX))) res += pushed;
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h, m;
    if(!(cin >> n >> h >> m)) return 0;

    // Node indexing:
    // id(i, j) for i in [1..n], j in [1..h]
    auto id = [&](int i, int j){ return (i-1)*h + (j-1); };

    const long long INF = (long long)4e18;

    // Nodes: n*h level nodes + m restriction nodes + S + T
    int level_nodes = n * h;
    int Rbase = level_nodes;          // first restriction node index
    int S = Rbase + m;                // source
    int T = S + 1;                    // sink
    Dinic din(T + 1);

    long long totalS = 0; // sum of capacities from S to level nodes (should be n*h^2)

    // S -> (i,j) with cap (2*j - 1)
    // (i,j) -> (i,j-1) (i.e. j->j-1) with INF for j>=2
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= h; ++j){
            int v = id(i, j);
            long long w = 2LL * j - 1;             // (j^2 - (j-1)^2)
            din.add_edge(S, v, w);
            totalS += w;
            if(j >= 2){
                int v_prev = id(i, j-1);
                din.add_edge(v, v_prev, INF);      // monotonicity: if >= j then >= j-1
            }
        }
    }
    //
    // do wetsh we
    for(int k = 0; k < m; ++k){
        int l, r, x, c; 
        cin >> l >> r >> x >> c;
        int rk = Rbase + k;           // restriction node

        // wechai nwewr w
        din.add_edge(rk, T, c);

        // if any spot in [l..r] has height >= x+1, restriction is violated
        if(x < h){
            int level = x + 1;
            for(int i = l; i <= r; ++i){
                int v = id(i, level);
                din.add_edge(v, rk, INF);
            }
        }
        // if x >= h, impossible to exceed => restriction never violated; no edges needed
    }
    // d 
    long long mincut = din.maxflow(S, T);
    // totalS == n * h^2
    cout << (totalS - mincut) << "\n";
    return 0;
}
/// wecluqe ib teh divsi biletiw ergarph ww
// wee whow woudl you sf seth s wer