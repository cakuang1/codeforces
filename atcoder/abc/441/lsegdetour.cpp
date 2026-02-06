#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegTree {
    static constexpr int B = 21; // enough for values up to 1e6 (2^20 ~ 1,048,576)
    int n;
    vector<array<int, B>> cnt;   // cnt[v][b]
    vector<ll> sum;              // sum[v]
    vector<int> lz;              // lazy xor mask

    SegTree(const vector<int>& a) {
        n = (int)a.size();
        cnt.assign(4 * n, {});
        sum.assign(4 * n, 0);
        lz.assign(4 * n, 0);
        build(1, 0, n, a);
    }

    static ll sumFromCnt(const array<int, B>& c) {
        ll s = 0;
        for (int b = 0; b < B; b++) s += (1LL << b) * c[b];
        return s;
    }

    void build(int v, int tl, int tr, const vector<int>& a) {
        lz[v] = 0;
        if (tr - tl == 1) {
            cnt[v].fill(0);
            int x = a[tl];
            for (int b = 0; b < B; b++) {
                if ((x >> b) & 1) cnt[v][b] = 1;
            }
            sum[v] = x;
            return;
        }
        int tm = (tl + tr) >> 1;
        build(v << 1, tl, tm, a);
        build(v << 1 | 1, tm, tr, a);
        pull(v);
    }

    void pull(int v) {
        for (int b = 0; b < B; b++) {
            cnt[v][b] = cnt[v << 1][b] + cnt[v << 1 | 1][b];
        }
        sum[v] = sum[v << 1] + sum[v << 1 | 1];
    }

    void applyXor(int v, int tl, int tr, int mask) {
        int len = tr - tl;
        for (int b = 0; b < B; b++) {
            if ((mask >> b) & 1) {
                cnt[v][b] = len - cnt[v][b];
            }
        }
        sum[v] = sumFromCnt(cnt[v]);
        lz[v] ^= mask;
    }

    void push(int v, int tl, int tr) {
        if (lz[v] == 0 || tr - tl == 1) return;
        int tm = (tl + tr) >> 1;
        applyXor(v << 1, tl, tm, lz[v]);
        applyXor(v << 1 | 1, tm, tr, lz[v]);
        lz[v] = 0;
    }

    void rangeXor(int l, int r, int mask) { rangeXor(1, 0, n, l, r, mask); }

    void rangeXor(int v, int tl, int tr, int l, int r, int mask) {
        if (r <= tl || tr <= l) return;
        if (l <= tl && tr <= r) {
            applyXor(v, tl, tr, mask);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) >> 1;
        rangeXor(v << 1, tl, tm, l, r, mask);
        rangeXor(v << 1 | 1, tm, tr, l, r, mask);
        pull(v);
    }

    ll rangeSum(int l, int r) { return rangeSum(1, 0, n, l, r); }

    ll rangeSum(int v, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l) return 0;
        if (l <= tl && tr <= r) return sum[v];
        push(v, tl, tr);
        int tm = (tl + tr) >> 1;
        return rangeSum(v << 1, tl, tm, l, r) + rangeSum(v << 1 | 1, tm, tr, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    SegTree st(a);

    int m;
    cin >> m;
    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            --l; // to 0-index
            cout << st.rangeSum(l, r) << "\n";
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            st.rangeXor(l, r, x);
        }
    }
    return 0;
}
// w tshi wermakest fnesr wew