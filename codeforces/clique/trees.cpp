#include <bits/stdc++.h>
using namespace std;

const int N = 300000 + 5;

vector<int> A[N], B[N];
int tin[N], tout[N], timerB;
int ans;

void dfsB(int v) {
    tin[v] = ++timerB;
    for (int u : B[v]) dfsB(u);
    tout[v] = timerB;
}

void dfsA(int v, set<pair<int,int>>& S) {
    // Decide how to update S when visiting v
    int l = tin[v], r = tout[v];
    pair<int,int> cur = {l, v};

    enum Op { NONE, INSERT, REPLACE };
    Op op = NONE;
    pair<int,int> replaced = {-1, -1};

    // 1) Is there a node in S that lies in v's B-subtree?
    auto it = S.lower_bound({l, INT_MIN}); // first with tin >= l
    bool hasDescendantInS = false;
    if (it != S.end()) {
        int node = it->second;
        if (tout[node] <= r) {
            // it is inside v's subtree in B
            hasDescendantInS = true;
        }
    }

    if (!hasDescendantInS) {
        // 2) Is there a B-ancestor of v in S? Only predecessor can contain [l, r]
        bool hasAncestorInS = false;
        pair<int,int> predPair;
        if (it != S.begin()) {
            auto pit = prev(it);
            int node = pit->second;
            if (tout[node] >= r) {
                hasAncestorInS = true;
                predPair = *pit;
            }
        }

        if (hasAncestorInS) {
            // Replace that ancestor by v
            S.erase(predPair);
            S.insert(cur);
            replaced = predPair;
            op = REPLACE;
        } else {
            // 3) No descendant and no ancestor in S -> insert v
            S.insert(cur);
            op = INSERT;
        }

        ans = max(ans, (int)S.size());
    }

    // Recurse on A-children
    for (int u : A[v]) dfsA(u, S);

    // Backtrack
    if (op == INSERT) {
        S.erase(cur);
    } else if (op == REPLACE) {
        S.erase(cur);
        S.insert(replaced);
    }
    // if op == NONE, we did nothing on entry; nothing to undo
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        int n; cin >> n;

        // clear per test
        for (int i = 1; i <= n; ++i) {
            A[i].clear();
            B[i].clear();
        }

        for (int i = 2; i <= n; ++i) {
            int p; cin >> p;
            A[p].push_back(i);
        }
        for (int i = 2; i <= n; ++i) {
            int p; cin >> p;
            B[p].push_back(i);
        }

        timerB = 0;
        dfsB(1);

        ans = 1; // at least one node
        set<pair<int,int>> S; // stores (tin_B[x], x), always an antichain in B
        dfsA(1, S);

        cout << ans << '\n';
    }
    return 0;
}

