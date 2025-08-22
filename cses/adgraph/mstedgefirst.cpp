#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p, r;
    DSU(int n=0): p(n+1), r(n+1,1) {
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        r[a] += r[b];
        return true;
    }
};

struct Edge {
    int u, v;
    int w;
    int idx;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for(int i = 0; i < m; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].idx = i;
    }

    // sort edges by weight
    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b){
             return a.w < b.w;
         });

    DSU dsu(n);
    vector<string> ans(m);
    int i = 0;
    while(i < m){
        int j = i;
        // find range [i, j) with same weight
        while(j < m && edges[j].w == edges[i].w) j++;

        // first: for each edge in [i,j), check if endpoints in different components
        for(int k = i; k < j; k++){
            int u = edges[k].u;
            int v = edges[k].v;
            if(dsu.find(u) != dsu.find(v)){
                ans[edges[k].idx] = "YES";
            } else {
                ans[edges[k].idx] = "NO";
            }
        }
        // then: unite all edges in [i,j)
        for(int k = i; k < j; k++){
            dsu.unite(edges[k].u, edges[k].v);
        }
        i = j;
    }

    // output in original order
    for(int t = 0; t < m; t++){
        cout << ans[t] << "\n";
    }

    return 0;
}
