#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n = 0) { init(n); }
    void init(int n) { p.assign(n+1, -1); }
    int find(int x){
        if(p[x] < 0) return x;
        return p[x] = find(p[x]);
    }
    void unite(int a,int b){
        a = find(a); b = find(b);
        if(a == b) return;
        if(p[a] < p[b]) swap(a,b); // p[x] negative size
        p[b] += p[a];
        p[a] = b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if(!(cin >> N >> M)) return 0;

    vector<vector<int> > G(N+1);
    DSU dsu(N);
    for(int i=0,a,b;i<M;i++){
        cin >> a >> b;
        G[a].push_back(b);
        dsu.unite(a,b); // treat as undirected for weak components
    }

    // group vertices by weak component id
    unordered_map<int,int> id;
    vector<vector<int> > comps;
    comps.reserve(N);
    for(int v=1; v<=N; ++v){
        int r = dsu.find(v);
        if(id.find(r) == id.end()){
            int newId = (int)comps.size();
            id[r] = newId;
            comps.push_back(vector<int>());
        }
        comps[id[r]].push_back(v);
    } 

    // 
    vector<int> state(N+1, 0); // 0=unvisited, -1=in stack, 1=done
    function<bool(int)> dfs = [&](int u)->bool{
        state[u] = -1;
        for(size_t i=0;i<G[u].size();++i){
            int v = G[u][i];
            if(state[v] == -1) return true;        // back edge -> cycle
            if(state[v] == 0 && dfs(v)) return true;
        }
        state[u] = 1;
        return false;
    };

    long long answer = 0;
    for(size_t ci=0; ci<comps.size(); ++ci){
        vector<int> &C = comps[ci];
        bool hasCycle = false;
        for(size_t i=0;i<C.size() && !hasCycle;++i){
            int u = C[i];
            if(state[u] == 0)
                hasCycle = dfs(u);
        }
        int sz = (int)C.size();
        answer += hasCycle ? sz : (sz - 1);
    }

    cout << answer << "\n";
    return 0;
}
