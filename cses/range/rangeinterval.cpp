#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n = 0) : n(_n), f(n, 0) {}
    // add v at index i (0‑indexed)
    void update(int i, int v) {
        for (; i < n; i = i | (i + 1)) {
            f[i] += v;
        }
    }
    // sum of [0..i]
    int query(int i) const {
        int s = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) {
            s += f[i];
        }
        return s;
    }
    // sum of [l..r]
    int query(int l, int r) const {
        if (r < l) return 0;
        return query(r) - (l ? query(l - 1) : 0);
    }
    void reset() {
        fill(f.begin(), f.end(), 0);
    }
};

struct Query {
    int a, b;
    int T;
    int id;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vector<Query> Qd, Qc;
    Qd.reserve(q);
    Qc.reserve(q);

    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b;
        Qd.push_back({a, b, d, i});
        Qc.push_back({a, b, c - 1, i});
    }

    auto cmpT = [](const Query &A, const Query &B){
        return A.T < B.T;
    };
    sort(Qd.begin(), Qd.end(), cmpT);
    sort(Qc.begin(), Qc.end(), cmpT);

    // pair of (value, index)
    vector<pair<int,int>> vals(n);
    for (int i = 0; i < n; i++) {
        vals[i] = {x[i], i};
    }
    sort(vals.begin(), vals.end());

    Fenwick bit(n);
    vector<int> ans_d(q), ans_c(q);

    auto sweep = [&](const vector<Query> &Q, vector<int> &ans) {
        int p = 0;
        for (auto &qu : Q) {
            while (p < n && vals[p].first <= qu.T) {
                bit.update(vals[p].second, 1);
                p++;
            }
            ans[qu.id] = bit.query(qu.a, qu.b);
        }
    };

    // answer ≤ d
    sweep(Qd, ans_d);
    // reset and answer ≤ c-1
    bit.reset();
    sweep(Qc, ans_c);

    // output final answers
    for (int i = 0; i < q; i++) {
        cout << (ans_d[i] - ans_c[i]) << "\n";
    }

    return 0;
}
