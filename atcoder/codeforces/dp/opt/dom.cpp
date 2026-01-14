#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// A simple iterative segment tree for range‐max, 0‐indexed.
struct SegTree {
    int n;
    vector<int> t;
    SegTree(int _n): n(_n), t(2*_n, 0) {}

    // point update: set pos -> value
    void update(int pos, int value) {
        pos += n;
        t[pos] = value;
        for (pos >>= 1; pos > 0; pos >>= 1)
            t[pos] = max(t[pos<<1], t[pos<<1|1]);
    }

    // range max on [l..r] inclusive
    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l <= r; l >>=1, r>>=1) {
            if (l&1) res = max(res, t[l++]);
            if (!(r&1)) res = max(res, t[r--]);
        }
        return res;
    }
};

struct Dom {
    ll x, h;
    int idx;
    bool operator<(Dom const& o) const {
        return x < o.x;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Dom> doms(n);
    for (int i = 0; i < n; i++) {
        cin >> doms[i].x >> doms[i].h;
        doms[i].idx = i;
    }

    sort(doms.begin(), doms.end());

    // ans[i] = how many fall when pushing original domino i
    vector<int> ans(n);

    // segtree[i] will store the furthest‐index (in [0..n-1]) that domino i knocks down
    SegTree seg(n);

    // process from rightmost to leftmost
    for (int i = n - 1; i >= 0; i--) {
        // direct reach: any domino with x <= x_i + h_i - 1
        ll reachX = doms[i].x + doms[i].h - 1;
        // binary‐search the first domino > reachX
        int lo = i + 1, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (doms[mid].x <= reachX) lo = mid + 1;
            else hi = mid;
        }
        // now [i+1 .. lo-1] are directly knocked over
        int furthest = lo - 1;
        if (furthest >= i+1) {
            // some fall—check if they cascade even further
            int cascaded = seg.query(i+1, furthest);
            furthest = max(furthest, cascaded);
        }
        // record: domino i knocks down everything up to `furthest`
        seg.update(i, furthest);

        // number of dominoes = indices [i..furthest] inclusive
        ans[ doms[i].idx ] = furthest - i + 1;
    }


    // print in original order
    for (int v : ans) 
        cout << v << " ";
    cout << "\n";
    return 0;
}
