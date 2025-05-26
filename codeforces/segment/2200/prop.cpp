#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}
    // add v to f[i]
    void update(int i, long long v) {
        for (++i; i <= n; i += i & -i)
            f[i] += v;
    }
    // range add: add v to [l..r]
    void range_add(int l, int r, long long v) {
        update(l, v);
        update(r+1, -v);
    }
    // point query: prefix sum up to i
    long long point_query(int i) {
        long long s = 0;
        for (++i; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }
};

int n, m;
vector<vector<int>> adj;
vector<int> tin, sz, depth, flat;
int dfs_timer;

void dfs(int u, int p, int d) {
    depth[u] = d;
    tin[u] = dfs_timer;
    flat[dfs_timer++] = u;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, d^1);
        sz[u] += sz[v];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vector<long long> initial(n);
    for (int i = 0; i < n; i++) {
        cin >> initial[i];
    }

    adj.assign(n, {});
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    tin .assign(n, 0);
    sz  .assign(n, 0);
    depth.assign(n, 0);
    flat.assign(n, 0);
    dfs_timer = 0;
    dfs(0, -1, 0);

    Fenwick fenw_even(n), fenw_odd(n);

    while (m--) {
        int type, x;
        cin >> type >> x;
        --x;
        int L = tin[x], R = tin[x] + sz[x] - 1;

        if (type == 1) {
            long long val;
            cin >> val;
            if (depth[x] % 2 == 0) {
                fenw_even.range_add(L, R, +val);
                fenw_odd .range_add(L, R, -val);
            } else {
                fenw_even.range_add(L, R, -val);
                fenw_odd .range_add(L, R, +val);
            }
        } else {
            long long delta = (depth[x]%2==0
                              ? fenw_even.point_query(tin[x])
                              : fenw_odd .point_query(tin[x]));
            cout << (initial[x] + delta) << "\n";
        }
    }

    return 0;
}
