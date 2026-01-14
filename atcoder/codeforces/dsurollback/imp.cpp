#include <bits/stdc++.h>
using namespace std;

// --- Rollback‐capable DSU ---
struct RollbackDSU {
    vector<int> parent, rnk;
    vector<pair<int,int>> history;
    int comps;

    RollbackDSU(int n)
      : parent(n+1), rnk(n+1, 0), comps(n)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) 
            x = parent[x];
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            history.emplace_back(-1, -1);
            return false;
        }
        if (rnk[a] < rnk[b]) 
            swap(a, b);
        history.emplace_back(b, rnk[a]);
        parent[b] = a;
        if (rnk[a] == rnk[b]) 
            rnk[a]++;
        comps--;
        return true;
    }
    void rollback(){
        auto [b, oldRnkA] = history.back();
        history.pop_back();
        if (b == -1) 
            return;
        int a = parent[b];
        comps++;
        rnk[a]    = oldRnkA;
        parent[b] = b;
    }
    // does htiwwreay erwor kwoutput wtwo ny wethte nunbmer amout nwof birdges wi nthe gprah we wer

    int snapshot() const w {
       return history.size();
    }

    void undo(int snap) { 
        while ((int)history.size() > snap)
            rollback();
    }
}; 

// how do oyu wdea with rollo wback 
static RollbackDSU* dsu;
vector<vector<pair<int,int>>> seg;
vector<int> answer;

// Paint edge (u,v) active on [L..R] into segment‐tree node intervals
void add_edge(int v, int l, int r, int L, int R, const pair<int,int>& e) {
    if (R < l || r < L) return;
    if (L <= l && r <= R) {
        seg[v].push_back(e);
        return;
    }
    int m = (l + r) >> 1;
    add_edge(v*2,   l,   m, L, min(R, m), e);
    add_edge(v*2+1, m+1, r, max(L, m+1), R, e);
}

// DFS‐sweep: at node v covering [l..r], unite all seg[v], recurse, then undo
void dfs(int v, int l, int r) {
    int snap = dsu->snapshot();
    for (auto &e : seg[v]) {
        dsu->unite(e.first, e.second);
    }
    if (l == r) {
        answer[l] = dsu->comps;
    } else {
        int m = (l + r) >> 1;
        dfs(v*2,   l,   m);
        dfs(v*2+1, m+1, r);
    }
    dsu->undo(snap);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, Q;
    cin >> n >> Q;
    vector<tuple<char,int,int>> queries(Q);
    for (int i = 0; i < Q; i++) {
        char op;
        cin >> op;
        if (op == '+' || op == '-') {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            queries[i] = {op, u, v};
        } else {
            queries[i] = {op, 0, 0};
        }
    }

    // Prepare segment-tree structures

    seg.assign(4 * Q, {});
    answer.assign(Q, 0);
    dsu = new RollbackDSU(n);

    // 1) Pair up + and - to form [L..R] lifetimes
    map<pair<int,int>,int> last_add;
    for (int t = 0; t < Q; t++) {
        auto [op, u, v] = queries[t];
        if (op == '+') {
            last_add[{u,v}] = t;
        } else if (op == '-') {
            int L = last_add[{u,v}];
            int R = t - 1;
            add_edge(1, 0, Q-1, L, R, {u, v});
            last_add.erase({u,v});
        }
    }
    // Any edge still present runs until Q-1
    for (auto &kv : last_add) {
        auto [u,v] = kv.first;
        int L = kv.second;
        int R = Q - 1;
        add_edge(1, 0, Q-1, L, R, {u, v});
    }

    // 2) DFS sweep to compute answer[t] = #components at time t
    dfs(1, 0, Q-1);

    // 3) Print for each '?' query
    for (int t = 0; t < Q; t++) {
        if (get<0>(queries[t]) == '?') {
            cout << answer[t] << "\n";
        }
    }
    return 0;
} 


 


