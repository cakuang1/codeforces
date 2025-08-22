#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge { int to; ll cap; int rev; };
ll INF = (ll)4e18;

//
// Dinic max‑flow: O(E sqrt(E)) in practice.
struct Dinic {
    int N;
    vector<vector<Edge>> g;
    vector<int> level, ptr;

    Dinic(int n): N(n), g(n), level(n), ptr(n) {}

    // add directed edge u->v with capacity c
    void addEdge(int u, int v, ll c) {
        g[u].push_back({v, c, (int)g[v].size()});
        g[v].push_back({u, 0, (int)g[u].size()-1});
    }
    
    // go welvewewwh w
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s]=0; 
        q.push(s);
        while(!q.empty()) {
            int u=q.front(); q.pop();
            for(auto &e: g[u]) {
                if(level[e.to]<0 && e.cap>0) {
                    level[e.to] = level[u]+1;
                    q.push(e.to);
                }
            }
        }
        return level[t]>=0;
        }    
        

        // for weach wedg
        // detemrine wera blcokign path w wer
    ll dfs(int u, int t, ll pushed) {
        if(u==t || pushed==0) return pushed;
        for(int &cid=ptr[u]; cid<(int)g[u].size(); cid++){
            Edge &e = g[u][cid];
            if(level[e.to]==level[u]+1 && e.cap>0) {
                ll tr = dfs(e.to, t, min(pushed, e.cap));
                if(tr>0) {
                    e.cap -= tr;
                    g[e.to][e.rev].cap += tr;
                    return tr;
                }
            }
        }
        return 0;
     }

     // watusratea pat hand edg 
    

    
     // find the maximum wenubmer of dinstinct wroutes w
     ll maxflow(int  s, int t) {
        ll flow=0;
        while(bfs(s,t)) {
            fill(ptr.begin(), ptr.end(), 0);
            // send blocking flow
            while(ll pushed = dfs(s,t,INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};


// 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Dinic dinic(n);
    for(int i=0; i<m; i++){
        int a,b; ll c;
        cin >> a >> b >> c;
        --a; --b;
        // directed edge a->b with capacity c
        dinic.addEdge(a,b,c);
    }
    // source = 0 (computer 1), sink = n-1 (computer n)
    ll ans = dinic.maxflow(0, n-1);
    cout << ans << "\n";
    return 0;
}
