
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;

    DSU(int n) : p(n + 1), sz(n + 1, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);

        p[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    DSU dsu(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        dsu.merge(u, v);
    }

    int K;
    cin >> K;

    set<pair<int, int>> forbidden;

    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;

        int a = dsu.find(x);
        int b = dsu.find(y);

        if (a > b) swap(a, b);
        forbidden.insert({a, b});
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int p, q;
        cin >> p >> q;

        int a = dsu.find(p);
        int b = dsu.find(q);

        if (a > b) swap(a, b);

        if (forbidden.count({a, b})) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
        }
    }

    return 0;
}
