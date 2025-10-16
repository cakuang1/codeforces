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
        queue<int> q; q.push(s); lvl[s]=0;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(auto &e: g[u]){
                if(e.cap>0 && lvl[e.to]==-1){
                    lvl[e.to]=lvl[u]+1;
                    q.push(e.to);
                }
            }
        }
        return lvl[t]!=-1;
    }
    long long dfs(int u, long long f){
        if(!f || u==t) return f;
        for(int &i=it[u]; i<(int)g[u].size(); ++i){
            auto &e=g[u][i];
            if(e.cap>0 && lvl[e.to]==lvl[u]+1){
                long long pushed=dfs(e.to, min(f, e.cap));
                if(pushed){
                    e.cap-=pushed;
                    g[e.to][e.rev].cap+=pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    long long maxflow(int S, int T){
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

    int N; 
    if(!(cin >> N)) return 0;
    vector<string> S(N);
    vector<long long> A(N);
    for(int i=0;i<N;i++) cin >> S[i];
    for(int i=0;i<N;i++) cin >> A[i];

    // 1) Deduplicate equal strings: keep max weight per string
    unordered_map<string, long long> best;
    best.reserve(N*2); best.max_load_factor(0.7);
    for(int i=0;i<N;i++){
        auto it = best.find(S[i]);
        if(it==best.end()) best.emplace(S[i], A[i]);
        else it->second = max(it->second, A[i]);
    }

    // Rebuild compressed arrays
    vector<string> Tstr;
    vector<long long> W;
    Tstr.reserve(best.size());
    W.reserve(best.size());
    for(auto &kv: best){
        Tstr.push_back(kv.first);
        W.push_back(kv.second);
    }

    // For stability, sort by length increases performance a bit
    // (and makes substring checks slightly faster on average)
    vector<int> idx(Tstr.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j){
        if(Tstr[i].size() != Tstr[j].size()) return Tstr[i].size() < Tstr[j].size();
        return Tstr[i] < Tstr[j];
    });

    int M = (int)idx.size();
    vector<string> U(M);
    vector<long long> B(M);
    for(int k=0;k<M;k++){ U[k]=Tstr[idx[k]]; B[k]=W[idx[k]]; }

    // 2) Build flow network
    // Nodes: S, L_0..L_{M-1}, R_0..R_{M-1}, T
    auto L = [&](int i){ return 1 + i; };
    auto R = [&](int i){ return 1 + M + i; };
    int SRC = 0, SNK = 1 + 2*M;
    Dinic din(SNK + 1);
    const long long INF = (long long)4e18;

    long long sumW = 0;
    for(int i=0;i<M;i++){
        sumW += B[i];
        din.add_edge(SRC, L(i), B[i]); // Source -> Left i with Ai
        din.add_edge(R(i), SNK, B[i]); // Right i -> Sink with Ai
    }

    // 3) Add edges L_i -> R_j (INF) if U[i] is a substring of U[j] and i != j
    for(int i=0;i<M;i++){
        for(int j=i+1;j<M;j++){
            // check both directions (since after sorting by length, only U[i] can be substring of U[j]
            // but if equal length and different content, no substring; if equal string we deduped already.
            if(U[j].find(U[i]) != string::npos){
                din.add_edge(L(i), R(j), INF);
            }
            // (U[i] cannot be substring of U[j] if |U[i]| > |U[j]| due to sorting)
        }
    }

    // 4) mincut = minimum weighted vertex cover; answer = sumW - mincut
    long long mincut = din.maxflow(SRC, SNK);
    cout << (sumW - mincut) << "\n";
    return 0;
}

/