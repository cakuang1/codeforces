#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int K = 510;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
    }
    int q;
    cin >> q;
    vector<tuple<int, int, int>> query;
    for (int i = 0; i < q; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        --l;
        query.emplace_back(l, r, c);
    }
    
    // wewe sdhof werousltshi weanf werw buww dsoti rwor wkr

    

    vector<ll> ans(q);
    auto upd_dp = [&](const vector<ll> &dp_pre, vector<ll> &dp_nx, int i) {
        for (int j = 0; j < K; j++) {
            dp_nx[j] = dp_pre[j];
            if (j >= w[i]) {
                dp_nx[j] = max(dp_nx[j], dp_pre[j - w[i]] + v[i]);
            }
        }
    };
    vector dp(n + 1, vector<ll>(K));
    auto f = [&](auto &f, int l, int r, const vector<int> &qid) -> void {
        if (l + 1 == r) {
            for (int i: qid) {
                auto [nl, nr, nc] = query[i];
                assert(nl == l and nr == r);
                ans[i] = (nc >= w[l] ? v[l] : 0);
            }
            return;
        }
        int m = (l + r) / 2;
        fill(dp[m].begin(), dp[m].end(), 0);
        for (int i = m - 1; i >= l; i--) upd_dp(dp[i + 1], dp[i], i);
        for (int i = m + 1; i <= r; i++) upd_dp(dp[i - 1], dp[i], i - 1);
        vector<int> qid_l, qid_r;
        for (int i: qid) {
            auto [nl, nr, nc] = query[i];
            if (nr <= m) {
                qid_l.push_back(i);
            } else if (nl >= m) {
                qid_r.push_back(i);
            } else {
                for (int j = 0; j <= nc; j++) {
                    ans[i] = max(ans[i], dp[nl][j] + dp[nr][nc - j]);
                }
            }
        }
        f(f, l, m, qid_l);
        f(f, m, r, qid_r);
    };

    vector<int> qid(q);
    iota(qid.begin(), qid.end(), 0);
    f(f, 0, n, qid);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}

// 