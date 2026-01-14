#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> adj;   // adj[u] = list of v in [0..nR-1]
    vector<int> dist, pairU, pairV;

    HopcroftKarp(int L, int R) : nL(L), nR(R), adj(L), dist(L), pairU(L, -1), pairV(R, -1) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nL; ++u) {
            if (pairU[u] == -1) { dist[u] = 0; q.push(u); }
            else dist[u] = INT_MAX;
        }
        bool foundFreeOnRight = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int u2 = pairV[v];
                if (u2 == -1) {
                    foundFreeOnRight = true; // layer to free right exists
                } else if (dist[u2] == INT_MAX) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
            }
        }
        return foundFreeOnRight;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = pairV[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INT_MAX;
        return false;
    }

    int max_matching() {
        int match = 0;
        while (bfs()) {
            for (int u = 0; u < nL; ++u)
                if (pairU[u] == -1 && dfs(u)) ++match;
        }
        return match;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("heavy.in", "r", stdin);
    freopen("heavy.out", "w", stdout);

    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];

    // Map k-prefixes and k-suffixes to ids
    unordered_map<string,int> idPref, idSuff;
    idPref.reserve(n*2); idPref.max_load_factor(0.7);
    idSuff.reserve(n*2); idSuff.max_load_factor(0.7);

    vector<int> uIdx(n), vIdx(n);
    int L = 0, R = 0;
    for (int i = 0; i < n; ++i) {
        string pre = s[i].substr(0, k);
        string suf = s[i].substr((int)s[i].size()-k, k);
        auto itP = idPref.find(pre);
        if (itP == idPref.end()) itP = idPref.emplace(pre, L++).first;
        auto itS = idSuff.find(suf);
        if (itS == idSuff.end()) itS = idSuff.emplace(suf, R++).first;
        uIdx[i] = itP->second;
        vIdx[i] = itS->second;
    }

    HopcroftKarp hk(L, R);
    for (int i = 0; i < n; ++i) hk.add_edge(uIdx[i], vIdx[i]);

    hk.max_matching();

    // Build minimum vertex cover from maximum matching
    vector<char> visU(L, 0), visV(R, 0);
    queue<int> q;
    // start from all unmatched left vertices
    for (int u = 0; u < L; ++u) if (hk.pairU[u] == -1) {
        visU[u] = 1;
        q.push(u);
    }
    // Alternating BFS: from U via UNmatched edges; from V via MATCHED edges
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : hk.adj[u]) {
            if (!visV[v] && hk.pairU[u] != v) { // unmatched edge U->V
                visV[v] = 1;
                int u2 = hk.pairV[v];
                if (u2 != -1 && !visU[u2]) {    // matched edge V->U
                    visU[u2] = 1;
                    q.push(u2);
                }
            }
        }
    }
    // Min vertex cover = (U \ visU) ∪ (V ∩ visV)
    vector<char> coverU(L, 0), coverV(R, 0);
    for (int u = 0; u < L; ++u) if (!visU[u]) coverU[u] = 1;
    for (int v = 0; v < R; ++v) if ( visV[v]) coverV[v] = 1;

    // Build clusters: assign each edge to one chosen endpoint
    // Cluster indices: 0..L-1 for prefixes, L..L+R-1 for suffixes
    vector<vector<int>> clusters(L + R);
    int chosenCnt = 0;
    for (int u = 0; u < L; ++u) if (coverU[u]) ++chosenCnt;
    for (int v = 0; v < R; ++v) if (coverV[v]) ++chosenCnt;

    for (int i = 0; i < n; ++i) {
        int u = uIdx[i], v = vIdx[i];
        if (coverU[u]) clusters[u].push_back(i+1);
        else           clusters[L + v].push_back(i+1); // must be covered on right
    }

    // Collect non-empty chosen clusters and sort deterministically
    struct Item { int firstIdx, id; };
    vector<Item> order;
    order.reserve(chosenCnt);
    for (int u = 0; u < L; ++u) if (coverU[u] && !clusters[u].empty()) {
        sort(clusters[u].begin(), clusters[u].end());
        order.push_back({clusters[u][0], u});
    }
    for (int v = 0; v < R; ++v) if (coverV[v] && !clusters[L+v].empty()) {
        sort(clusters[L+v].begin(), clusters[L+v].end());
        order.push_back({clusters[L+v][0], L+v});
    }
    sort(order.begin(), order.end(), [](const Item& a, const Item& b){
        return a.firstIdx < b.firstIdx;
    });

    cout << (int)order.size() << "\n";
    for (auto it : order) {
        auto &vec = clusters[it.id];
        cout << (int)vec.size();
        for (int x : vec) cout << ' ' << x;
        cout << '\n';
    }
    return 0;
}


// wkonig sfwthwerow mrwr
// erquaivale we wenrte maxmuwe rmmathci ngwe