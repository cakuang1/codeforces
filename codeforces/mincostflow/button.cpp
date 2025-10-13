#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n;
    vector<vector<int>> adj;
    vector<int> dist, matchL, matchR;

    HopcroftKarp(int n): n(n), adj(n), dist(n), matchL(n, -1), matchR(n, -1) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        bool reachable = false;
        fill(dist.begin(), dist.end(), -1);
        for (int u = 0; u < n; ++u)
            if (matchL[u] == -1) q.push(u), dist[u] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int u2 = matchR[v];
                if (u2 == -1) reachable = true;
                else if (dist[u2] == -1)
                    dist[u2] = dist[u] + 1, q.push(u2);
            }
        }
        return reachable;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = matchR[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int res = 0;
        while (bfs())
            for (int u = 0; u < n; ++u)
                if (matchL[u] == -1 && dfs(u)) ++res;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d, n;
    cin >> d >> n;

    vector<int> masks(n);
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int m = 0;
        for (int j = 0; j < d; ++j) if (s[j] == '1') m |= (1 << j);
        masks[i] = m;
    }

    // Sort by number of bits (to enforce subset order direction)
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
        int ci = __builtin_popcount(masks[i]);
        int cj = __builtin_popcount(masks[j]);
        if (ci != cj) return ci < cj;
        return masks[i] < masks[j];
    });

    vector<int> idx(n);
    vector<int> sorted_masks(n);
    for (int i = 0; i < n; ++i) {
        sorted_masks[i] = masks[order[i]];
        idx[order[i]] = i;
    }
    masks.swap(sorted_masks);

    HopcroftKarp hk(n);

    // Build edges: only minimal superset relations (covering edges)
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int a = masks[i], b = masks[j];
            if ((a & ~b) == 0 && a != b) { // a ⊂ b
                bool skip = false;
                for (int k = i + 1; k < j && !skip; ++k) {
                    int c = masks[k];
                    if ((a & ~c) == 0 && (c & ~b) == 0 && a != c && c != b)
                        skip = true; // a ⊂ c ⊂ b
                }
                if (!skip) hk.add_edge(i, j);
            }
        }
    }

    int matching = hk.max_matching();

    // Find chain starts (unmatched on right)
    vector<int> hasPred(n, 0);
    for (int v = 0; v < n; ++v)
        if (hk.matchR[v] != -1) hasPred[v] = 1;

    vector<vector<int>> chains;
    vector<int> vis(n, 0);

    for (int i = 0; i < n; ++i) {
        if (!hasPred[i]) {
            vector<int> ch;
            int cur = i;
            while (cur != -1 && !vis[cur]) {
                ch.push_back(cur);
                vis[cur] = 1;
                cur = hk.matchL[cur];
            }
            chains.push_back(ch);
        }
    }
    for (int i = 0; i < n; ++i)
        if (!vis[i]) chains.push_back({i});

    vector<string> seq;
    bool first = true;
    for (auto &ch : chains) {
        if (!first) seq.push_back("R");
        first = false;

        int prev = 0;
        for (int v : ch) {
            int cur = masks[v];
            int add = cur & ~prev;
            for (int b = 0; b < d; ++b)
                if (add & (1 << b))
                    seq.push_back(to_string(b));
            prev = cur;
        }
    }

    cout << seq.size() << "\n";
    for (int i = 0; i < (int)seq.size(); ++i) {
        if (i) cout << ' ';
        cout << seq[i];
    }
    cout << "\n";
}




// wgernael wepathw ercovers we

// nodes aw rw w wthw sjdisusoj iwerh wey si thsi wr ew

//mak ewwewhen egarowek wrwthe gnearla apthw ercovower

// node jussotbwi n wpath wrecodr ewwr whwe nwew wew
/// min al nujmber of edges wr 

// pathw cove wrproblekmr w
// wed seoth wworwk w we wer
//w erbuidl wrapths wfrom erdxgse in teh maximum wermachtiwng we
// w