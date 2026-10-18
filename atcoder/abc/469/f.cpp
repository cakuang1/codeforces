    
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool merge(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int& x : A) cin >> x;

    int U = A.back();

    // id[value] is the vertex with that value, or -1 if absent.
    vector<int> id(U + 1, -1);
    for (int i = 0; i < N; ++i) {
        id[A[i]] = i;
    }

    DSU dsu(N);
    ll answer = 0;
    int edges = 0;


    // Maximum Kruskal: process possible GCDs in descending order.
    for (int d = U; d >= 1; --d) {
        int anchor = -1;

        for (int value = d; value <= U; value += d) {
            if (id[value] == -1) continue;

            if (anchor == -1) {
                anchor = id[value];
            } else if (dsu.merge(anchor, id[value])) {
                answer += d;
                ++edges;
            }
        }

        if (edges == N - 1) break;
    }

    cout << answer << '\n';
    return 0;
}
