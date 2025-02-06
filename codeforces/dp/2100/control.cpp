#include <bits/stdc++.h>
 
using namespace std;
 
void solve() {
    int n, q;
    cin >> n >> q;
    
    vector < vector <int> > g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    vector <int> depth(n);
    vector <int> d(n);
    vector < vector < pair <int,int> > > qrs(n); // <p, idx>
    vector <int> res(q);
    
    for (int i = 0; i < q; i++) {
        int v, p;
        cin >> v >> p;
        v--;
        qrs[v].push_back({p, i});
    }
    multiset <int> st[2]; // store negative number to be able to use usual foreach loop
    function <void(int, int, int)> dfs = [&](int v, int p, int pp) {
        if (depth[v] == 1) d[v] = 1; 
        if (depth[v] > 1) d[v] = d[pp] + 2 * (int)g[p].size();
        
        for (pair <int, int> qr : qrs[v]) {
            int p = qr.first, idx = qr.second;
            int ans = d[v];
            for (int i : st[1 - depth[v] % 2]) {
                if (p == 0) break;
                ans -= (-i - 1) * 2;
                p--;
            }
            res[idx] = ans;
        }
        
        if (depth[v] != 0) st[depth[v] % 2].insert(-(int)g[v].size());
        
        for (int to : g[v]) {
            if (to == p) continue;
            depth[to] = depth[v] + 1;
            dfs(to, v, p);
        }
        
        if (depth[v] != 0) st[depth[v] % 2].erase(st[depth[v] % 2].find(-(int)g[v].size()));
    };
    
    dfs(0, 0, 0);
    
    for (int i = 0; i < q; i++)
        cout << res[i] << '\n';
}
 
int main() {
    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
 
    return 0;
}

// very difficult wrpboeslms w