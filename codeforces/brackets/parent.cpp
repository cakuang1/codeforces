#include <bits/stdc++.h>
using namespace std;

struct Node {
    int mn;   // minimum prefix relative to the segment start
    int sum;  // total sum over the segment
};


// minimum prefix within the segmentw 

struct SegTree {
    int n, size;
    const int INF = 1e9;
    vector<Node> t;
    static Node merge(const Node& L, const Node& R) {
        // Append R after L
        Node res;
        res.mn  = min(L.mn, L.sum + R.mn);
        res.sum = L.sum + R.sum;
        return res;
    }
    static Node id() { return { (int)1e9, 0 }; } // identity node
    SegTree(int n_ = 0): n(n_) {
        size = 1;
        while (size < n) size <<= 1;
        t.assign(2 * size, id());
    }

    void build_from_string(const string& s) {
        // s is 0-indexed
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') t[size + i] = {0, +1};
            else             t[size + i] = {-1, -1};
        }
        for (int i = size - 1; i >= 1; --i) {
            t[i] = merge(t[i<<1], t[i<<1|1]);
        }
    }

    void set_point(int idx, char c) {
        int p = size + idx;
        t[p] = (c == '(') ? Node{0, +1} : Node{-1, -1};
        for (p >>= 1; p >= 1; p >>= 1) {
            t[p] = merge(t[p<<1], t[p<<1|1]);
        }
    }

    // query inclusive [l, r], 0-indexed
    Node query(int l, int r) const {
        Node leftAcc = id(), rightAcc = id();
        l += size; r += size;
        while (l <= r) {
            if (l & 1) leftAcc = merge(leftAcc, t[l++]);
            if (!(r & 1)) rightAcc = merge(t[r--], rightAcc);
            l >>= 1; r >>= 1;
        }
        return merge(leftAcc, rightAcc);
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    string s; 
    cin >> s;
    SegTree seg(n);
    seg.build_from_string(s);

    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        --l; --r; // convert to 0-based

        if (t == 1) {
            if (l != r && s[l] != s[r]) {
                swap(s[l], s[r]);
                seg.set_point(l, s[l]);
                seg.set_point(r, s[r]);
            } else if (l != r && s[l] == s[r]) {
                // no change to segment tree needed,
                // but harmless to set again if you prefer
                // seg.set_point(l, s[l]); seg.set_point(r, s[r]);
            }
        } else { // t == 2 : check if s[l..r] is a correct parenthesis sequence
            Node res = seg.query(l, r);
            if (res.mn == 0 && res.sum == 0) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }


    return 0;
}

