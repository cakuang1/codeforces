#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> t(n+1);
    for(int i = 1; i <= n; i++){
        cin >> t[i];
    }

    //–– 1) DECOMPOSE INTO CYCLES + IN‑TREES ––
    vector<int> comp(n+1, 0), idx(n+1, -1);
    vector<bool> inCycle(n+1, false);
    vector<int> cycleIdx(n+1), cycleLen(n+1);
    int compCount = 0;

    vector<int> path;
    path.reserve(n);

    for(int v = 1; v <= n; v++){
        if (comp[v] != 0) continue;           // already assigned
        path.clear();
        int u = v;
        // walk until we either hit an assigned node or close a cycle
        while (comp[u] == 0 && idx[u] == -1) {
            idx[u] = path.size();
            path.push_back(u);
            u = t[u];
        }

        if (comp[u] != 0) {
            // we ran into an existing component ⇒ all of path feeds into it
            int C = comp[u];
            for(int x: path){
                comp[x] = C;
                inCycle[x] = false;
            }
        } else {
            // idx[u] != -1 ⇒ we've found a fresh cycle
            int start = idx[u];
            int L = path.size() - start;
            int C = ++compCount;
            // mark cycle nodes
            for(int i = start; i < (int)path.size(); i++){
                int x = path[i];
                comp[x] = C;
                inCycle[x] = true;
                cycleIdx[x] = i - start;
            }
            cycleLen[C] = L;
            // mark the “tail” nodes (leading into the cycle)
            for(int i = 0; i < start; i++){
                int x = path[i];
                comp[x] = C;
                inCycle[x] = false;
            }
        }
        // no need to reset idx[] for these nodes, since comp[x]!=0 guards them
    }

    //–– 2) BUILD REVERSE‑TREE & EULER TIMES FOR THE IN‑TREES ––
    vector<vector<int>> rev(n+1);
    for(int u = 1; u <= n; u++){
        rev[t[u]].push_back(u);
    }

    vector<int> tin(n+1), tout(n+1), depth(n+1), root(n+1);
    int timer = 0;
    vector<pii> stk;
    stk.reserve(n);

    // For each cycle‐node, do an explicit DFS on rev‐edges to cover its in‐tree
    for(int v = 1; v <= n; v++){
        if (!inCycle[v]) continue;
        // initialize the DFS at v
        root[v] = v; depth[v] = 0;
        stk.clear();
        stk.emplace_back(v, 0);

        while(!stk.empty()){
            auto &top = stk.back();
            int u = top.first, &ci = top.second;

            if (ci == 0) {
                // first time we see u
                tin[u] = ++timer;
            }
            if (ci < (int)rev[u].size()) {
                int w = rev[u][ci++];
                if (inCycle[w]) continue;   // never go back into the cycle
                root[w]  = root[u];
                depth[w] = depth[u] + 1;
                stk.emplace_back(w, 0);
            } else {
                tout[u] = timer;
                stk.pop_back();
            }
        }
    }

    //–– 3) ANSWER QUERIES ––
    // helper to check “b is on the path from a down into the cycle?”
    auto isAncestor = [&](int a, int b){
        // requires both a,b off‐cycle
        return root[a]==root[b]
            && tin[b] <= tin[a]
            && tout[a] <= tout[b];
    };

    while(q--){
        int a, b;
        cin >> a >> b;

        // different components ⇒ impossible
        if (comp[a] != comp[b]) {
            cout << -1 << "\n";
            continue;
        }

        // CASE 1: b is off‐cycle ⇒ we must land exactly on it before hitting the cycle
        if (!inCycle[b]) {
            // either a is also off‐cycle and b is its ancestor...
            if (!inCycle[a] && isAncestor(a,b)) {
                cout << (depth[a] - depth[b]) << "\n";
            } else {
                cout << -1 << "\n";
            }
        }
        else {
            // CASE 2: b is on the cycle ⇒ we can go from a down to the cycle, then walk around
            long long dist = 0;
            int C = comp[a];
            int L = cycleLen[C];

            int idxA;
            if (!inCycle[a]) {
                dist += depth[a];
                idxA = cycleIdx[ root[a] ];
            } else {
                idxA = cycleIdx[a];
            }

            int idxB = cycleIdx[b];
            // forward distance around a cycle of length L
            int around = (idxB - idxA + L) % L;
            dist += around;
            cout << dist << "\n";
        }
    }
    
    // wdetrerirn wint ewtes w
    return 0;
}
