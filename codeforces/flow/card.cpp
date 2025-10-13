#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev, cap; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> level, ptr;
    Dinic(int n=0): n(n), g(n), level(n), ptr(n) {}
    void reset(int N){ n=N; g.assign(n,{}); level.assign(n,0); ptr.assign(n,0); }
    void addEdge(int u, int v, int c){
        Edge a{v,(int)g[v].size(),c};
        Edge b{u,(int)g[u].size(),0};
        g[u].push_back(a); g[v].push_back(b);
    }
    bool bfs(){
        fill(level.begin(), level.end(), -1);
        queue<int> q; q.push(s); level[s]=0;
        while(!q.empty()){
            int v=q.front(); q.pop();
            for(auto &e:g[v]) if(e.cap>0 && level[e.to]==-1){
                level[e.to]=level[v]+1; q.push(e.to);
            }
        }
        return level[t]!=-1;
    }
    int dfs(int v, int pushed){
        if(!pushed) return 0;
        if(v==t) return pushed;
        for(int &cid=ptr[v]; cid<(int)g[v].size(); cid++){
            Edge &e=g[v][cid];
            if(e.cap<=0 || level[e.to]!=level[v]+1) continue;
            int tr=dfs(e.to, min(pushed, e.cap));
            if(!tr) continue;
            e.cap-=tr; g[e.to][e.rev].cap+=tr;
            return tr;
        }
        return 0;
    }
    long long flow(int S, int T){
        s=S; t=T;
        long long f=0;
        while(bfs()){
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed=dfs(s, INT_MAX)) f+=pushed;
        }
        return f;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; long long k;
    if(!(cin>>n>>k)) return 0;
    struct Card{int p; int c; int l;};
    vector<Card> a(n);
    int maxC = 0;
    for(int i=0;i<n;i++){
        cin>>a[i].p>>a[i].c>>a[i].l;
        maxC = max(maxC, a[i].c);
    }

    // Sieve up to 2*maxC (sum of two magic numbers)
    int LIM = max(4, 2*maxC + 5);
    vector<char> isPrime(LIM, true);
    isPrime[0]=isPrime[1]=false;
    for(int p=2;p*p<LIM;p++) if(isPrime[p])
        for(long long q=1LL*p*p; q<LIM; q+=p) isPrime[(int)q]=false;

    auto can = [&](int lvl)->bool{
        // pick cards with l <= lvl
        vector<int> idx;
        idx.reserve(n);
        for(int i=0;i<n;i++) if(a[i].l<=lvl) idx.push_back(i);
        if(idx.empty()) return false;

        // handle c==1: keep only max power among them
        int best1 = -1, best1_idx = -1;
        vector<int> filtered; filtered.reserve(idx.size());
        for(int id: idx){
            if(a[id].c==1){
                if(a[id].p > best1){
                    best1 = a[id].p; best1_idx = id;
                }
            }
        }
        // push all non-c==1, and push the single best c==1 (if any)
        for(int id: idx){
            if(a[id].c!=1) filtered.push_back(id);
        }
        if(best1_idx!=-1) filtered.push_back(best1_idx);

        if(filtered.empty()) return false;

        // Build bipartite flow: odd c on left, even c on right
        // Node mapping: S=0, T=1, then assign ids to chosen cards
        int M = filtered.size();
        vector<int> nodeId(n, -1);
        int nextId = 2;
        for(int id: filtered) nodeId[id] = nextId++;

        const int S = 0, T = 1;
        Dinic din(nextId);
        long long sumPower = 0;
        const int INF = 1e9;

        // S->odd: cap=p; even->T: cap=p
        vector<int> oddIds, evenIds;
        for(int id: filtered){
            sumPower += a[id].p;
            int u = nodeId[id];
            if(a[id].c & 1){
                din.addEdge(S, u, a[id].p);
                oddIds.push_back(id);
            }else{
                din.addEdge(u, T, a[id].p);
                evenIds.push_back(id);
            }
        }

        // odd->even: INF if prime(c[i]+c[j])
        for(int oi: oddIds){
            for(int ej: evenIds){
                int sumc = a[oi].c + a[ej].c;
                if(sumc < LIM && isPrime[sumc]){
                    din.addEdge(nodeId[oi], nodeId[ej], INF);
                }
            }
        }

        long long minCut = din.flow(S,T);
        long long best = sumPower - minCut;
        return best >= k;
    };

    // quick impossible check
    if(!can(n)){
        cout << -1 << '\n';
        return 0;
    }

    int lo = 1, hi = n, ans = n;
    while(lo<=hi){
        int mid = (lo+hi)/2;
        if(can(mid)){ ans = mid; hi = mid-1; }
        else lo = mid+1;
    }
    cout << ans << '\n';
    return 0;
}

// ecadf gameswerw wer detmiern conflxi wer