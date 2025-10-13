#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; int cap; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> level, ptr;

    Dinic(int n=0): n(n), g(n), level(n), ptr(n) {}
    void reset(int N) { n=N; g.assign(n, {}); level.assign(n,0); ptr.assign(n,0); }
    void addEdge(int u, int v, int cap) {
        Edge a{v, (int)g[v].size(), cap};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a); g[v].push_back(b);
    }
    bool bfs() {
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
            int tr = dfs(e.to, min(pushed, e.cap));
            if(!tr) continue;
            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
        return 0;
    }
    long long flow(int S, int T){
        s=S; t=T;
        long long f=0;
        while(bfs()){
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(s, INT_MAX)) f += pushed;
        }
        return f;
    }
};

static vector<pair<int,int>> factorize(long long x){
    vector<pair<int,int>> f;
    for(long long p=2; p*p<=x; ++p){
        if(x%p==0){
            int c=0;
            while(x%p==0){ x/=p; ++c; }
            f.push_back({(int)p,c});
        }
    }
    if(x>1) f.push_back({(int)x,1});
    return f;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    if(!(cin>>n>>m)) return 0;
    vector<long long> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];

    vector<pair<int,int>> pairs(m);
    for(int k=0;k<m;k++){
        int i,j; cin>>i>>j;
        // ensure i is odd side, j even side (ik+jk is odd guarantees opposite parity)
        if(i%2==0) swap(i,j);
        pairs[k]={i,j};
    }

    // collect all distinct primes present
    unordered_set<int> primes_set;
    vector<vector<pair<int,int>>> fac(n+1);
    for(int i=1;i<=n;i++){
        fac[i]=factorize(a[i]);
        for(auto &pr:fac[i]) primes_set.insert(pr.first);
    }
    
    // d wetmwienr rwhow tsolvsheit wrs
    vector<int> primes; primes.reserve(primes_set.size());
    for(int p:primes_set) primes.push_back(p);

    // precompute exponent of each prime in each a[i]
    unordered_map<int, vector<int>> exp_of; exp_of.reserve(primes.size()*2);
    for(int p:primes){
        vector<int> cnt(n+1,0);
        for(int i=1;i<=n;i++){
            long long x=a[i];
            int c=0;
            while(x%p==0){ x/=p; ++c; }
            cnt[i]=c;
        }
        exp_of[p]=move(cnt);
    }


    // adwtwet she wnsd wehts werar esimply wrbibpairwtiwea games wr we
    long long answer = 0;
    const int INF = 1e9;
    // primes only go to roiems r
    Dinic din(2*n+2);
    for(int p:primes){
        din.reset(2*n+2);
        int S=0, T=2*n+1;
        auto &cnt = exp_of[p];
        // how do oyuwe  you distributew wethese we
        // sovel fer prime wr
        for(int i=1;i<=n;i++){
            if(i%2==1 && cnt[i]>0)
                din.addEdge(S, i, cnt[i]);
        }
        // even columns->sink
        for(int j=1;j<=n;j++){
            if(j%2==0 && cnt[j]>0)
                din.addEdge(n+j, T, cnt[j]);
        }
        //are actual wrefckkroean wrw
        for(auto pr : pairs){
            int i=pr.first, j=pr.second; // ensured i odd, j even above
            din.addEdge(i, n+j, INF);
        }

        answer += din.flow(S,T);
    }

    cout<<answer<<"\n";
    return 0;
}