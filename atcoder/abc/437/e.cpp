#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // rep[i] = trie node id representing sequence A_i
    vector<int> rep(N + 1, 0);

    // Trie adjacency: children[u] = list of (label y, child node v)
    vector<vector<pair<int,int>>> children;
    children.reserve(N + 1);
    children.push_back({}); // node 0 = root (empty sequence)

    // bucket[v] = all original indices i whose sequence maps to trie node v
    vector<vector<int>> bucket;
    bucket.reserve(N + 1);
    bucket.push_back({});

    // transition map: key = (u << 32) | y  -> child node id
    unordered_map<uint64_t, int> nxt;
    nxt.reserve((size_t)N * 2);
    nxt.max_load_factor(0.7f);

    auto get_key = [&](int u, int y) -> uint64_t {
        return (uint64_t(uint32_t(u)) << 32) | uint32_t(y);
    };

    for (int i = 1; i <= N; i++) {
        int x, y;
        cin >> x >> y;

        int u = rep[x];
        uint64_t key = get_key(u, y);

        auto it = nxt.find(key);
        int v;
        if (it == nxt.end()) {
            v = (int)children.size();
            nxt.emplace(key, v);

            children.push_back({});
            bucket.push_back({});

            children[u].push_back({y, v});
        } else {
            v = it->second;
        }

        rep[i] = v;
        bucket[v].push_back(i);
    }

    // Sort children by label y to enforce lexicographic traversal
    for (auto &vec : children) {
        sort(vec.begin(), vec.end(), [](auto &a, auto &b){
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });
    }

    // Sort buckets so ties (equal sequences) are by smaller index first
    for (auto &b : bucket) sort(b.begin(), b.end());

    vector<int> ans;
    ans.reserve(N);

    // Iterative preorder DFS:
    // visit node -> output its bucket -> visit children in increasing y
    vector<int> st;
    st.reserve(children.size());
    st.push_back(0);

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        if (u != 0) {
            for (int idx : bucket[u]) ans.push_back(idx);
        }

        // push in reverse so smallest y is processed first
        auto &ch = children[u];
        for (int k = (int)ch.size() - 1; k >= 0; --k) {
            st.push_back(ch[k].second);
        }
    }

    // Output permutation
    for (int i = 0; i < N; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
