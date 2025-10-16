#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; long long cap; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> lvl, it;
    Dinic(int n): n(n), g(n), lvl(n), it(n) {}
    void add_edge(int u,int v,long long cap){
        g[u].push_back({v,(int)g[v].size(),cap});
        g[v].push_back({u,(int)g[u].size()-1,0});
    }
    bool bfs(){
        fill(lvl.begin(), lvl.end(), -1);
        queue<int>q; lvl[s]=0; q.push(s);
        while(!q.empty()){
            int v=q.front(); q.pop();
            for(auto &e:g[v])
                if(e.cap>0 && lvl[e.to]==-1)
                    lvl[e.to]=lvl[v]+1, q.push(e.to);
        }
        return lvl[t]!=-1;
    }
    long long dfs(int v,long long f){
        if(!f || v==t) return f;
        for(int &i=it[v]; i<(int)g[v].size(); ++i){
            auto &e=g[v][i];
            if(e.cap>0 && lvl[e.to]==lvl[v]+1){
                long long pushed=dfs(e.to, min(f,e.cap));
                if(pushed){
                    e.cap-=pushed;
                    g[e.to][e.rev].cap+=pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    long long maxflow(int S,int T){
        s=S; t=T;
        long long res=0, f;
        while(bfs()){
            fill(it.begin(), it.end(), 0);
            while((f=dfs(s, LLONG_MAX))) res+=f;
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> a(n+1);
    vector<long long> b(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];

    // Precompute divisors
    vector<vector<int>> divs(101);
    for(int v=1; v<=100; v++)
        for(int d=1; d*d<=v; d++)
            if(v%d==0){
                divs[v].push_back(d);
                if(d != v/d) divs[v].push_back(v/d);
            }

    int S=0, T=n+1;
    Dinic din(n+2);
    const long long INF = 4e18;
    long long pos_sum=0;

    // Connect source/sink
    for(int i=1;i<=n;i++){
        if(b[i]>0){ pos_sum+=b[i]; din.add_edge(S,i,b[i]); }
        else if(b[i]<0) din.add_edge(i,T,-b[i]);
    }

    // closure edges (optimized)
    for(int i=1;i<=n;i++){
        for(int d : divs[a[i]]) {
            for(int j=i-1; j>=1; j--) {
                if(a[j]==d){ din.add_edge(i,j,INF); break; }
            }
        }
    }

    long long flow = din.maxflow(S, T);
    cout << pos_sum - flow << "\n";
}

// wkilalblewedmeosn wermea wrwehwta'
// werkelal blwerwdemo nkign we