// Compile with: g++ -std=c++11 -O2 -o transfer_speeds transfer_speeds.cpp

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> parent, sz;
    DSU(int n): parent(n+1), sz(n+1,1) {
        for(int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    // Merge the components of a and b.
    // Returns the number of NEW pairs connected = size[a]*size[b]
    ll unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return 0;
        if (sz[a] < sz[b]) swap(a,b);
        ll pairs = (ll)sz[a] * sz[b];
        parent[b] = a;
        sz[a] += sz[b];
        return pairs;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector< tuple<int,int,int> > edges;
    edges.reserve(n-1);

    for(int i = 0; i < n-1; i++){
        int a, b, x;
        cin >> a >> b >> x;
        edges.emplace_back(x, a, b);
    }

    // Sort edges by speed descending
    sort(edges.begin(), edges.end(),
         [](const tuple<int,int,int> &L, const tuple<int,int,int> &R){
             return get<0>(L) > get<0>(R);
         });

    DSU dsu(n);
    ll answer = 0;

    for(size_t i = 0; i < edges.size(); i++){
        int x = get<0>(edges[i]);
        int u = get<1>(edges[i]);
        int v = get<2>(edges[i]);
        ll pairs = dsu.unite(u, v);
        answer += pairs * x;
    }

    cout << answer << "\n";
    return 0;
}
