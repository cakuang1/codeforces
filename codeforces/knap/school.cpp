#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n+1);
        sz.assign(n+1, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a,b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
    int size(int x) {
        return sz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dsu.unite(a, b);
    }

    // collect sizes
    unordered_map<int,int> compSize;
    for (int i = 1; i <= n; i++) {
        compSize[dsu.find(i)] = dsu.size(i);
    }

    // count multiplicities of sizes
    unordered_map<int,int> freq;
    for (auto &p : compSize) {
        freq[p.second]++;
    }

    // binary decomposition of multiplicities
    vector<int> eff;
    for (auto &[sz, occ] : freq) {
        int base = 1;
        while (occ > 0) {
            int take = min(base, occ);
            eff.push_back(take * sz);
            occ -= take;
            base <<= 1;
        }
    }
    bitset<100001> dp;
    dp[0] = 1;
    for (int w : eff) {
        dp |= (dp << w);
    }
    for (int i = 1; i <= n; i++) {
        if (dp[i]) cout << 1;
        else {
            cout << 0;
        }
    }
    cout << "\n";
    return 0;
}
