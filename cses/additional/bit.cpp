#include <bits/stdc++.h>
using namespace std;

struct Node {
    int len;
    int pre, suf, best;
    char lc, rc;
    Node(): len(0), pre(0), suf(0), best(0), lc('?'), rc('?') {}
    Node(char c) {
        len = 1;
        pre = suf = best = 1;
        lc = rc = c;
    }
};

Node merge(const Node &L, const Node &R) {
    if (L.len == 0) return R;
    if (R.len == 0) return L;
    Node res;
    res.len = L.len + R.len;
    res.lc = L.lc;
    res.rc = R.rc;
    // prefix: either all of L, or L plus R.pre if L.rc == R.lc
    res.pre = L.pre == L.len && L.rc == R.lc
              ? L.len + R.pre
              : L.pre;
    // suffix likewise
    res.suf = R.suf == R.len && L.rc == R.lc
              ? R.len + L.suf
              : R.suf;
    // best: max of L.best, R.best, and possibly L.suf+R.pre if they match
    res.best = max(L.best, R.best);
    if (L.rc == R.lc) {
        res.best = max(res.best, L.suf + R.pre);
    }
    return res;
}

struct SegTree {
    int n;
    vector<Node> st;
    SegTree(const string &s) {
        n = s.size();
        st.assign(4*n, Node());
        build(1, 0, n-1, s);
    }
    void build(int p, int l, int r, const string &s) {
        if (l == r) {
            st[p] = Node(s[l]);
            return;
        }
        int m = (l+r)>>1;
        build(p<<1, l, m, s);
        build(p<<1|1, m+1, r, s);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }
    // point update: flip at idx
    void update(int p, int l, int r, int idx) {
        if (l == r) {
            // flip bit
            st[p] = Node(st[p].lc == '0' ? '1' : '0');
            return;
        }
        int m = (l+r)>>1;
        if (idx <= m) update(p<<1, l, m, idx);
        else          update(p<<1|1, m+1, r, idx);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }
    void update(int idx) { update(1, 0, n-1, idx); }
    int query_max_run() const { return st[1].best; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    SegTree seg(s);

    int m;
    cin >> m;
    while (m--) {
        int x;
        cin >> x;
        --x;  // zero‑based
        seg.update(x);
        cout << seg.query_max_run() << " ";
    }
    cout << "\n";

    return 0;
}
