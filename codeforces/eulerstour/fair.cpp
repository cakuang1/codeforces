#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;       // neighbor node
    int id;       // edge ID
    int arr_idx;  // which array this occurrence belongs to
    int pos;      // position in that array
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    vector<vector<long long>> arrays(m);
    vector<int> n(m);
    long long total = 0;
    for (int i = 0; i < m; i++) {
        cin >> n[i];
        arrays[i].resize(n[i]);
        for (int j = 0; j < n[i]; j++) cin >> arrays[i][j];
        total += n[i];
    }

    // Compress all values
    vector<long long> vals;
    for (auto &a : arrays) vals.insert(vals.end(), a.begin(), a.end());
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto id = [&](long long x) {
        return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    };
    int V = vals.size(); // number of unique values

    // Count occurrences of each number
    vector<int> freq(V, 0);
    for (auto &a : arrays)
        for (auto x : a)
            freq[id(x)]++;

    for (int f : freq)
        if (f % 2) {
            cout << "NO\n";
            return 0;
        }

    int leftN = m;      // arrays
    int rightN = V;     // values
    int totalNodes = leftN + rightN;

    vector<vector<Edge>> g(totalNodes);
    int edge_id = 0;

    // Build graph: array i (0..m-1), value node = m + valueID
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n[i]; j++) {
            int valNode = m + id(arrays[i][j]);
            g[i].push_back({valNode, edge_id, i, j});
            g[valNode].push_back({i, edge_id, i, j});
            edge_id++;
        }
    }

    vector<bool> used(edge_id, false);
    vector<string> ans(m);
    for (int i = 0; i < m; i++) ans[i].assign(n[i], '?');

    function<void(int)> dfs = [&](int u) {
        while (!g[u].empty()) {
            auto e = g[u].back();
            g[u].pop_back();
            if (used[e.id]) continue;
            used[e.id] = true;
            dfs(e.to);
            // when we return, the direction is reversed:
            // we came to u from e.to
            // if u is array node → this is from value→array (assign R)
            // if u is value node → from array→value (assign L)
            if (u < m)
                ans[e.arr_idx][e.pos] = 'R';
            else
                ans[e.arr_idx][e.pos] = 'L';
        }
    };

    for (int i = 0; i < totalNodes; i++)
        dfs(i);

    cout << "YES\n";
    for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
}










// use distinc tprimes unqieu werfactoizeiotn wer
// prodicstunqieu werindedi wtwfiyt er
// wedemtienr ww con wenrwcsoitnw w am wewt er