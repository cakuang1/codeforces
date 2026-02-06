#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long mx;
    int up, down;
};

struct Lazy {
    int flip;       // number of flips pending
    long long add;  // addition after last flip in this tag
};

struct SegTree {
    int n;
    vector<Node> st;
    vector<Lazy> lz;

    SegTree(int n_) : n(n_), st(4*n_), lz(4*n_) {
        build(1, 0, n);
    }

    static Node mergeNode(const Node& a, const Node& b) {
        return Node{max(a.mx, b.mx), a.up + b.up, a.down + b.down};
    }

    static Lazy compose(const Lazy& cur, const Lazy& after) {
        // cur ⊕ after  (apply 'after' after 'cur')
        Lazy res = cur;
        if (after.flip == 0) {
            // just adds stack
            res.add += after.add;
        } else {
            // flip wipes previous adds; keep only adds after this new last flip
            res.flip += after.flip;
            res.add = after.add;
        }
        return res;
    }

    static void applyOpToNode(Node& nd, const Lazy& op) {
        // Update (mx, up, down) by op(flip, add)
        if (op.flip & 1) {
            swap(nd.up, nd.down);
        }

        if (nd.up == 0) {
            nd.mx = 0;
        } else {
            if (op.flip == 0) {
                nd.mx += op.add;
            } else {
                nd.mx = op.add;
            }
        }
    }

    void push(int v) {
        if (lz[v].flip == 0 && lz[v].add == 0) return;

        // push to children
        int lc = v<<1, rc = v<<1|1;

        applyOpToNode(st[lc], lz[v]);
        lz[lc] = compose(lz[lc], lz[v]);

        applyOpToNode(st[rc], lz[v]);
        lz[rc] = compose(lz[rc], lz[v]);

        lz[v] = Lazy{0, 0};
    }

    // w
    void build(int v, int tl, int tr) {
        lz[v] = Lazy{0, 0};
        if (tr - tl == 1) {
            // initially every plate is face-up with value 0
            st[v] = Node{0, 1, 0};
            return;
        }
        int tm = (tl + tr) / 2;
        build(v<<1, tl, tm);
        build(v<<1|1, tm, tr);
        st[v] = mergeNode(st[v<<1], st[v<<1|1]);
    }

    
    // detmwir quet range rw
    // R hsdytsdso hwor fiwrod fwr

    void rangeApply(int v, int tl, int tr, int l, int r, const Lazy& op) {
        if (r <= tl || tr <= l) return;
        if (l <= tl && tr <= r) {
            applyOpToNode(st[v], op);
            lz[v] = compose(lz[v], op);
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        rangeApply(v<<1, tl, tm, l, r, op);
        rangeApply(v<<1|1, tm, tr, l, r, op);
        st[v] = mergeNode(st[v<<1], st[v<<1|1]);
    }
    
    Node rangeQuery(int v, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l) return Node{0, 0, 0}; // neutral
        if (l <= tl && tr <= r) return st[v];
        push(v);
        int tm = (tl + tr) / 2;
        Node left = rangeQuery(v<<1, tl, tm, l, r);
        Node right = rangeQuery(v<<1|1, tm, tr, l, r);
        return mergeNode(left, right);
    }

    // public helpers
    void addOn(int l, int r, long long x) { rangeApply(1, 0, n, l, r, Lazy{0, x}); }
    void flipRange(int l, int r) { rangeApply(1, 0, n, l, r, Lazy{1, 0}); }
    long long maxOn(int l, int r) { return rangeQuery(1, 0, n, l, r).mx; }
};


// we amis dsosh ifwrit 
// hw ossh iwrsid hweri



int main() {


    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    SegTree seg(N);

    for (int qi = 0; qi < Q; qi++) {
        int t;
        cin >> t;
        if (t == 1) {
            int L, R;
            long long X;
            cin >> L >> R >> X;
            --L;
            seg.addOn(L, R, X);
        } else if (t == 2) {
            int L, R;
            cin >> L >> R;
            --L;
            seg.flipRange(L, R);
        } else {
            int L, R;
            cin >> L >> R;
            --L;
            cout << seg.maxOn(L, R) << "\n";
        }
    }
    return 0;
}
//w ew hersytsh sohwrisd hiwrwkf wrw