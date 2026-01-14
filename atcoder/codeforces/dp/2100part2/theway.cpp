#include "bits/stdc++.h"

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define ar array
#define vec vector

using namespace std;

using ll = long long;
using pi = pair<int, int>;

using vi = vector<int>;
using vpi = vector<pair<int, int>>;

const ll INF = 2e18;
const int maxN = 3e5 + 10;

struct PathParams {
    ll num_show;
    int money;
};

bool operator==(const PathParams &a, const PathParams &b) {
    return tie(a.num_show, a.money) == tie(b.num_show, b.money);
}

bool operator!=(const PathParams &a, const PathParams &b) {
    return !(a == b);
}

struct State {
    PathParams params;
    int v;
    int best;
};

bool operator<(const PathParams &a, const PathParams &b) {
    if (a.num_show != b.num_show) return a.num_show < b.num_show;
    return a.money > b.money;
}

bool operator<(const State &a, const State &b) {
    return tie(a.params, a.v, a.best) < tie(b.params, b.v, b.best);
}

bool operator>(const State &a, const State &b) {
    return !(a < b);
}

void solve() {
    int n, m, p, group;
    cin >> n >> m >> p;
    vector dp(n, vector<PathParams>(n, {INF, 0}));
    vector<vpi> g(n);
    vi w(n);
    rep(i, n) cin >> w[i];
    rep(i, m) {
        int a, b, s;
        cin >> a >> b >> s;
        a--;
        b--;
        g[a].emplace_back(b, s);
    }
    dp[0][0] = {0, p};
    priority_queue<State, vector<State>, greater<>> pq;
    pq.push({.params = {.num_show=0, .money=p}, .v = 0, .best=0});
    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();
        int v = current.v;
        int best = current.best;
        if (dp[v][best] != current.params) continue;
        for (auto &[u, s]: g[v]) {
            auto state2 = current;
            PathParams &path = state2.params;
            if (path.money < s) {
                ll need = (s - path.money + w[best] - 1) / w[best];
                path.num_show += need;
                path.money += need * w[best];
                assert(path.money < s + w[best]);
            }
            path.money -= s;
            state2.v = u;
            if (w[u] > w[state2.best]) state2.best = u;
            if (path < dp[u][state2.best]) {
                dp[u][state2.best] = path;
                pq.push(state2);
            }
        }
    }
    ll ans = INF;
    rep(i, n) {
        ans = min(ans, dp[n - 1][i].num_show);
    }
    cout << (ans == INF ? -1 : ans) << '\n';
}


signed main() {
    int t = 1;
    cin >> t;
    rep(_, t) {
        solve();
    }
    return 0;
}