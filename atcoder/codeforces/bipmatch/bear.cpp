#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int cap;
};
struct Dinic {
    int N;
    vector<vector<Edge>> G;
    vector<int> level, it;
    Dinic(int n): N(n), G(n), level(n), it(n) {}
    void add_edge(int u, int v, int c){
        Edge a{v, (int)G[v].size(), c};
        Edge b{u, (int)G[u].size(), 0};
        G[u].push_back(a); G[v].push_back(b);
    }
    bool bfs(int s, int t){
        fill(level.begin(), level.end(), -1);
        queue<int> q; level[s]=0; q.push(s);
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(auto &e:G[u]) if(e.cap>0 && level[e.to]==-1){
                level[e.to]=level[u]+1;
                q.push(e.to);
            }
        }
        return level[t]!=-1;
    }
    int dfs(int u, int t, int f){
        if(!f || u==t) return f;
        for(int &i=it[u]; i<(int)G[u].size(); ++i){
            Edge &e=G[u][i];
            if(e.cap>0 && level[e.to]==level[u]+1){
                int got = dfs(e.to, t, min(f, e.cap));
                if(got){
                    e.cap -= got;
                    G[e.to][e.rev].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }
    long long maxflow(int s, int t){
        long long flow=0;
        while(bfs(s,t)){
            fill(it.begin(), it.end(), 0);
            while(int pushed=dfs(s,t,INT_MAX)) flow+=pushed;
        }
        return flow;
    }
};

// count of numbers x in [1..T] with x % 5 == r (r in 0..4)
static inline int cnt_leq(int T, int r){
    if(T<=0) return 0;
    if(r==0) return T/5;
    if(T<r) return 0;
    return 1 + (T - r)/5;
}
// count in (L, R] = count≤R − count≤L
static inline int cnt_in_range(int L, int R, int r){
    return cnt_leq(R, r) - cnt_leq(L, r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, b, q;
    if(!(cin >> n >> b >> q)) return 0;

    // read hints, merge by upTo ensuring consistency
    map<int,int> mp;
    for(int i=0;i<q;i++){
        int up, qty; cin >> up >> qty;
        if(up<1 || up>b || qty<0 || qty>n){ cout<<"unfair\n"; return 0; }
        auto it = mp.find(up);
        if(it==mp.end()) mp[up]=qty;
        else if(it->second!=qty){ cout<<"unfair\n"; return 0; } // conflicting hints
    }

    // Enforce that upTo=b must have quantity = n
    auto itb = mp.find(b);
    if(itb!=mp.end() && itb->second!=n){ cout<<"unfair\n"; return 0; }
    mp[b]=n; // add/override to match problem’s global condition
    mp[0]=0; // add starting checkpoint

    // Build sorted checkpoints and validate monotonicity & per-interval feasibility
    vector<pair<int,int>> chk;
    chk.reserve(mp.size());
    for(auto &kv: mp) chk.push_back(kv);
    sort(chk.begin(), chk.end());

    for(size_t i=1;i<chk.size();++i){
        int L = chk[i-1].first;
        int R = chk[i].first;
        int need = chk[i].second - chk[i-1].second;
        if(need < 0) { cout<<"unfair\n"; return 0; }                // counts must be nondecreasing
        if(need > R - L) { cout<<"unfair\n"; return 0; }            // can’t pick more than interval length
    }

    // Build flow network
    // Nodes:
    // S = 0
    // residues r nodes: 1..5   (r=0 at node 1, r=4 at node 5)
    // interval nodes: next indices
    // T = last
    int intervals = (int)chk.size()-1;
    int S = 0;
    int residueStart = 1;
    int residueCnt = 5;
    int intervalStart = residueStart + residueCnt;  // intervalStart .. intervalStart + intervals-1
    int T = intervalStart + intervals;

    Dinic din(T+1);

    // Source -> residue (each needs n/5)
    if(n%5!=0){ cout<<"unfair\n"; return 0; }
    int perResidue = n/5;
    for(int r=0;r<5;r++){
        din.add_edge(S, residueStart + r, perResidue);
    }
    
    long long totalNeed = 0;
    for(int j=0;j<intervals;j++){
        int L = chk[j].first;
        int R = chk[j+1].first;
        int need = chk[j+1].second - chk[j].second;
        totalNeed += need;

        int intervalNode = intervalStart + j;
        din.add_edge(intervalNode, T, need);

        for(int r=0;r<5;r++){
            int cap = cnt_in_range(L, R, r);
            if(cap>0){
                din.add_edge(residueStart + r, intervalNode, cap);
            }
        }
    }
    // fwwe
    long long flow = din.maxflow(S, T);
    cout << (flow == totalNeed && flow == n ? "fair\n" : "unfair\n");
    return 0;
}

// w sodoethi rwrk wwandwrwho sdoyo werosuvlsthi