#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[b] = a;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, W;
    cin >> n >> m >> W;
    vector<int> w(n), b(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y; 
        --x; --y;
        dsu.unite(x, y);
    }

    // collect groups
    unordered_map<int, vector<int>> groups;
    for (int i = 0; i < n; i++) groups[dsu.find(i)].push_back(i);

    vector<int> dp(W+1, 0);

    for (auto &g : groups) {
        auto &members = g.second;
        int sumW = 0, sumB = 0;
        for (int idx : members) {
            sumW += w[idx];
            sumB += b[idx];
        }

        vector<int> next = dp; // copy to transition

        for (int j = 0; j <= W; j++) {
            if (dp[j] == 0 && j != 0) continue;

            // option 2: take all
            if (j + sumW <= W) {
                next[j + sumW] = max(next[j + sumW], dp[j] + sumB);
            }
            // option 3: take one
            for (int idx : members) {
                if (j + w[idx] <= W) {
                    next[j + w[idx]] = max(next[j + w[idx]], dp[j] + b[idx]);
                }
            }
        }
        dp.swap(next);
    }

    cout << *max_element(dp.begin(), dp.end()) << "\n";
    return 0;
}
