#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenw {
    int n;
    vector<int> f;
    Fenw(int _n): n(_n), f(n+1, 0) {}
    // add v at index i (1 ≤ i ≤ n)
    void add(int i, int v) {
        for (; i <= n; i += i & -i)
            f[i] += v;
    }
    // sum of prefix [1..i]
    int sum(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    const int M = 1000000;

    // xs[r] = list of L for every segment [L,R] with right endpoint R = r
    vector<vector<int>> xs(M+1);
    for (int i = 0; i < n; i++) {
        int L, R;
        cin >> L >> R;
        xs[R].push_back(L);
    }

    // xQ[r] = list of (a, query_id) for every gap (a, r)
    vector<vector<pair<int,int>>> xQ(M+2);
    vector<ll> ans(m, 0);

    // Read queries, build gaps
    for (int qi = 0; qi < m; qi++) {
        int cnt;
        cin >> cnt;
        vector<int> p(cnt);
        for (int i = 0; i < cnt; i++) {
            cin >> p[i];
        }
        int prev = 0;               // left sentinel at 0
        for (int i = 0; i < cnt; i++) {
            int cur = p[i];
            xQ[cur].emplace_back(prev, qi);
            prev = cur;
        }
        // rightmost gap up to M+1
        xQ[M+1].emplace_back(prev, qi);
    }

    // Fenwick over left‐endpoints [1..M]
    Fenw fenw(M);
    ll S = 0;  // total segments added so far (those with R < current r)

    // Sweep r = 1..M+1
    for (int r = 1; r <= M+1; r++) {
        // 1) answer all gaps ending at r
        for (auto &pr : xQ[r]) {
            int a  = pr.first;
            int qi = pr.second;
            // segments with R<r and L>a = S - fenw.sum(a)
            ll cntZero = S - fenw.sum(a);
            ans[qi] += cntZero;
        }
        // 2) now add segments whose right endpoint is r (only if r≤M)
        if (r <= M) {
            for (int L : xs[r]) {
                fenw.add(L, 1);
                ++S;
            }
        }
    }

    // Output answers: #segments containing ≥1 point = n - #zero‐point segments
    for (int qi = 0; qi < m; qi++) {
        cout << (n - ans[qi]) << "\n";
    }
    return 0;
}
