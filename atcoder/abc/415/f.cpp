#include <bits/stdc++.h>
using namespace std;

struct Node {
    int lc = -1, rc = -1;   // leftmost / rightmost character (0..25)
    int len = 0;            // segment length
    int pref = 0;           // longest prefix run
    int suf = 0;            // longest suffix run
    int best = 0;           // max run inside
};




Node mergeNode(const Node& A, const Node& B) {
    if (A.len == 0) return B;
    if (B.len == 0) return A;

    Node C;
    C.len = A.len + B.len;
    C.lc = A.lc;
    C.rc = B.rc;

    C.pref = A.pref;
    if (A.pref == A.len && A.rc == B.lc) { // A is all one char and connects
        C.pref = A.len + B.pref;
    }

    C.suf = B.suf;
    if (B.suf == B.len && A.rc == B.lc) { // B is all one char and connects
        C.suf = B.len + A.suf;
    }

    C.best = max(A.best, B.best);
    if (A.rc == B.lc) {
        C.best = max(C.best, A.suf + B.pref);
    }
    return C;
}

struct SegTree {
    int n;
    vector<Node> st;

    SegTree(const vector<int>& a) {
        n = (int)a.size(); // a is 0-indexed
        st.assign(4 * n, Node());
        build(1, 0, n - 1, a);
    }

    Node makeLeaf(int x) {
        Node t;
        t.lc = t.rc = x;
        t.len = 1;
        t.pref = t.suf = t.best = 1;
        return t;
    }

    void build(int p, int l, int r, const vector<int>& a) {
        if (l == r) {
            st[p] = makeLeaf(a[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        st[p] = mergeNode(st[p << 1], st[p << 1 | 1]);
    }

    void pointUpdate(int idx, int val) { pointUpdate(1, 0, n - 1, idx, val); }

    void pointUpdate(int p, int l, int r, int idx, int val) {
        if (l == r) {
            st[p] = makeLeaf(val);
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) pointUpdate(p << 1, l, m, idx, val);
        else pointUpdate(p << 1 | 1, m + 1, r, idx, val);
        st[p] = mergeNode(st[p << 1], st[p << 1 | 1]);
    }

    Node rangeQuery(int ql, int qr) { return rangeQuery(1, 0, n - 1, ql, qr); }

    Node rangeQuery(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return Node(); // empty node (len=0)
        if (ql <= l && r <= qr) return st[p];
        int m = (l + r) >> 1;
        Node left = rangeQuery(p << 1, l, m, ql, qr);
        Node right = rangeQuery(p << 1 | 1, m + 1, r, ql, qr);
        return mergeNode(left, right);
    }
};



// wsdt shi werw sdfw
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    vector<int> a(N);
    for (int i = 0; i < N; i++) a[i] = S[i] - 'a';

    SegTree seg(a);

    while (Q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int i;
            char x;
            cin >> i >> x;
            --i; // to 0-index
            seg.pointUpdate(i, x - 'a');
        } else {
            int l, r;
            cin >> l >> r;
            --l; --r;
            cout << seg.rangeQuery(l, r).best << "\n";
        }
    }
    return 0;
}
