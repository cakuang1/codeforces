#include <bits/stdc++.h>
using namespace std;

// Dinic with integer capacities
struct Dinic {
    struct Edge { int to, rev, cap; };
    int N;
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n): N(n), g(n), level(n), it(n) {}

    void addEdge(int u, int v, int c) {
        g[u].push_back({v, (int)g[v].size(), c});
        g[v].push_back({u, (int)g[u].size()-1, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s]=0; q.push(s);
        while(!q.empty()) {
            int u=q.front(); q.pop();
            for(auto &e:g[u]){
                if(level[e.to]<0 && e.cap>0){
                    level[e.to]=level[u]+1;
                    q.push(e.to);
                }
            }
        }
        return level[t]>=0;
    }

    int dfs(int u, int t, int f) {
        if(u==t) return f;
        for(int &i=it[u]; i<(int)g[u].size(); i++){
            auto &e = g[u][i];
            if(e.cap>0 && level[e.to]==level[u]+1){
                int got = dfs(e.to, t, min(f,e.cap));
                if(got>0){
                    e.cap -= got;
                    g[e.to][e.rev].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) {
        int flow=0, f;
        while(bfs(s,t)) {
            fill(it.begin(), it.end(), 0);
            while((f=dfs(s,t,INT_MAX))>0)
                flow += f;
        }
        return flow;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<int>a(n), b(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int j=0;j<n;j++) cin>>b[j];

    int S=0, T=1, offsetR=2, offsetC=2+n;
    Dinic dinic(2+ n + n);

    int suma=0, sumb=0;
    for(int i=0;i<n;i++){
        dinic.addEdge(S, offsetR+i, a[i]);
        suma += a[i];
    }
    for(int j=0;j<n;j++){
        dinic.addEdge(offsetC+j, T, b[j]);
        sumb += b[j];
    }
    if(suma != sumb){
        cout<<"-1\n";
        return 0;
    }

    // edges row->col
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            dinic.addEdge(offsetR+i, offsetC+j, 1);
        }
    }

    int flow = dinic.maxFlow(S, T);
    if(flow != suma){
        cout<<"-1\n";
        return 0;
    }

    // Recover the matrix
    vector<string> grid(n, string(n,'.'));
    for(int i=0;i<n;i++){
        for(auto &e: dinic.g[offsetR+i]){
            // edges to columns at offsetC+j, original capacity 1
            if(e.to >= offsetC && e.to < offsetC+n && e.cap==0){
                int j = e.to - offsetC;
                grid[i][j] = 'X';
            }
        }
    }

    for(int i=0;i<n;i++){
        cout<<grid[i]<<"\n";
    }
    return 0;
}
