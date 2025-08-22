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
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        // union by size
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        r[a] += r[b];
    }
};

struct Edge {
    int a, b, c;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> edges(m+1);
    vector<int> ws;
    ws.reserve(m);
    for(int i = 1; i <= m; i++){
        cin >> edges[i].a >> edges[i].b >> edges[i].c;
        ws.push_back(edges[i].c);
    }
    // compress weights
    sort(ws.begin(), ws.end());
    ws.erase(unique(ws.begin(), ws.end()), ws.end());
    int W = ws.size();
    vector<int> widx(m+1);
    for(int i = 1; i <= m; i++){
        widx[i] = int(lower_bound(ws.begin(), ws.end(), edges[i].c) - ws.begin());
    }
    // sort real edges by compressed weight
    vector<pair<int,int>> edgesSorted;
    edgesSorted.reserve(m);
    for(int i = 1; i <= m; i++){
        edgesSorted.emplace_back(widx[i], i);
    }
    sort(edgesSorted.begin(), edgesSorted.end(),
         [](const pair<int,int>& A, const pair<int,int>& B){
             return A.first < B.first;
         });

    // read queries, group query-edges by weight index
    vector<vector<pair<int,int>>> queryByW(W);
    vector<bool> good(q, true);
    for(int qi = 0; qi < q; qi++){
        int k; 
        cin >> k;
        while(k--){
            int eid;
            cin >> eid;
            int wi = widx[eid];
            queryByW[wi].emplace_back(qi, eid);
        }
    }
    // sort each weight-bucket by query id
    for(int w = 0; w < W; w++){
        auto &v = queryByW[w];
        sort(v.begin(), v.end(),
             [](const pair<int,int>& A, const pair<int,int>& B){
                 return A.first < B.first;
             });
    }

    DSU dsu(n);
    int epos = 0;  // pointer into edgesSorted

    // process weights in ascending order
    for(int w = 0; w < W; w++){
        // --- 1) answer queries of weight w ---
        auto &vq = queryByW[w];
        int L = vq.size();
        int i = 0;
        while(i < L){
            int qi = vq[i].first;
            int j = i;
            // group same-query entries
            while(j < L && vq[j].first == qi) j++;
            if (good[qi]) {
                // collect global roots and pairs
                vector<int> nodes;
                vector<pair<int,int>> pairs;
                pairs.reserve(j - i);
                nodes.reserve(2*(j - i));
                for(int t = i; t < j; t++){
                    int eid = vq[t].second;
                    int u = edges[eid].a;
                    int v = edges[eid].b;
                    int ru = dsu.find(u);
                    int rv = dsu.find(v);
                    pairs.emplace_back(ru, rv);
                    nodes.push_back(ru);
                    nodes.push_back(rv);
                }
                // compress nodes
                sort(nodes.begin(), nodes.end());
                nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
                int R = nodes.size();
                vector<int> locP(R, -1);
                // local DSU find
                function<int(int)> locFind = [&](int x){
                    return locP[x] < 0 ? x : locP[x] = locFind(locP[x]);
                };
                auto locUnite = [&](int x, int y){
                    x = locFind(x);
                    y = locFind(y);
                    if (x == y) return false;
                    locP[y] = x;
                    return true;
                };
                // test each pair
                for(auto &pr : pairs){
                    int ru = pr.first;
                    int rv = pr.second;
                    int iu = int(lower_bound(nodes.begin(), nodes.end(), ru) - nodes.begin());
                    int iv = int(lower_bound(nodes.begin(), nodes.end(), rv) - nodes.begin());
                    if (!locUnite(iu, iv)){
                        good[qi] = false;
                        break;
                    }
                }
            }
            i = j;
        }

        // --- 2) merge real edges of weight w ---
        while(epos < m && edgesSorted[epos].first == w){
            int eid = edgesSorted[epos].second;
            dsu.unite(edges[eid].a, edges[eid].b);
            epos++;
        }
    }

    for(int qi = 0; qi < q; qi++){
        cout << (good[qi] ? "YES\n" : "NO\n");
    }
    return 0;
}
