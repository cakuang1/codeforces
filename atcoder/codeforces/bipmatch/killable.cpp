#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; long long cap; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> lvl, it;
    Dinic(int n): n(n), g(n), lvl(n), it(n) {}
    void add_edge(int u, int v, long long cap){
        g[u].push_back({v, (int)g[v].size(), cap});
        g[v].push_back({u, (int)g[u].size()-1, 0});
    }
    bool bfs(){
        fill(lvl.begin(), lvl.end(), -1);
        queue<int>q;
        lvl[s]=0; q.push(s);
        while(!q.empty()){
            int v=q.front(); q.pop();
            for(auto &e:g[v]) if(e.cap>0 && lvl[e.to]==-1){
                lvl[e.to]=lvl[v]+1;
                q.push(e.to);
            }
        }
        return lvl[t]!=-1;
    }
    long long dfs(int v, long long f){
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
        long long res=0;
        while(bfs()){
            fill(it.begin(), it.end(), 0);
            while(long long f=dfs(s, LLONG_MAX)) res+=f;
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<long long> D(N+1);
    for(int i=1;i<=N;i++) cin >> D[i];

    const long long INF = 1e15;
    int S = 0, T = N+1;
    Dinic din(N+2);

    long long posSum = 0;
    for(int i=1;i<=N;i++){
        if(D[i] > 0){
            posSum += D[i];
            din.add_edge(S, i, D[i]);
        } else if(D[i] < 0){
            din.add_edge(i, T, -D[i]);
        }
    }

    for(int i=0;i<M;i++){
        int u,v;
        cin >> u >> v;
        // if we take v, must take u → v→u with infinite capacity
        din.add_edge(v, u, INF);
    }

    long long flow = din.maxflow(S, T);
    cout << posSum - flow << "\n";
}
 
// wee