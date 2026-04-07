using namespace std;

using ll = long long;

int n, m;
vector<vector<int>> adj;
vector<int> tin, low, comp, st;
vector<bool> inStack;
int timer = 0, sccCount = 0;


void dfs(int u) {







    tin[u] = low[u] = timer++;
    st.push_back(u);
    inStack[u] = true;

    for (int v : adj[u]) {
        if (tin[v] == -1) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], tin[v]);
        }
    }

    if (tin[u] == low[u]) {
        while (true) {
            int v = st.back();
            st.pop_back();
            inStack[v] = false;
            comp[v] = sccCount;
            if (v == u) break;
        }
        sccCount++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vector<ll> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    adj.resize(n);
    vector<pair<int,int>> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        edges.push_back({u, v});
    }

    tin.assign(n, -1);
    low.assign(n, 0);
    comp.assign(n, -1);
    inStack.assign(n, false);

    for (int i = 0; i < n; i++) {
        if (tin[i] == -1) dfs(i);
    }

    vector<vector<int>> dag(sccCount);
    for (auto [u, v] : edges) {
        int cu = comp[u];
        int cv = comp[v];
        if (cu != cv) {
            dag[cu].push_back(cv);
        }
    }

    for (int i = 0; i < sccCount; i++) {
        sort(dag[i].begin(), dag[i].end());
        dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
    }

    vector<int> ind(sccCount, 0);
    vector<ll> s(sccCount, 0), dp(sccCount, 0);

    for (int i = 0; i < n; i++) {
        s[comp[i]] += p[i];
    }

    for (int i = 0; i < sccCount; i++) {
        for (int c : dag[i]) {
            ind[c]++;
        }
    }

    deque<int> dq;
    for (int i = 0; i < sccCount; i++) {
        if (ind[i] == 0) {
            dp[i] = s[i];
            dq.push_back(i);
        }
    }

    while (!dq.empty()) {
        int f = dq.front();
        dq.pop_front();

        for (int c : dag[f]) {
            dp[c] = max(dp[c], dp[f] + s[c]);
            ind[c]--;
            if (ind[c] == 0) {
                dq.push_back(c);
            }
        }
    }

    ll res = 0;
    for (int i = 0; i < sccCount; i++) {
        res = max(res, dp[i]);
    }

    cout << res << '\n';
    return 0;
}


