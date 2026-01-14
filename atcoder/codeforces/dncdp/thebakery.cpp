#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> seg, lazy;

    SegTree(int n) : n(n) {
        seg.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    void push(int idx, int l, int r) {
        if (lazy[idx] != 0) {
            seg[idx] += lazy[idx];
            if (l != r) {
                lazy[idx*2] += lazy[idx];
                lazy[idx*2+1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void update(int idx, int l, int r, int ql, int qr, int val) {
        push(idx, l, r);
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        int mid = (l+r)/2;
        update(idx*2, l, mid, ql, qr, val);
        update(idx*2+1, mid+1, r, ql, qr, val);
        seg[idx] = max(seg[idx*2], seg[idx*2+1]);
    }

    int query(int idx, int l, int r, int ql, int qr) {
        push(idx, l, r);
        if (ql > r || qr < l) return -1e9;
        if (ql <= l && r <= qr) return seg[idx];
        int mid = (l+r)/2;
        return max(query(idx*2, l, mid, ql, qr),
                   query(idx*2+1, mid+1, r, ql, qr));
    }

    void update(int l, int r, int val) { update(1,0,n-1,l,r,val); }
    int query(int l, int r) { return query(1,0,n-1,l,r); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n+1);
    for (int i=1;i<=n;i++) cin >> a[i];

    // prev occurrence
    vector<int> prevPos(n+1, 0);
    unordered_map<int,int> last;

    // dp arrays
    vector<int> dp_prev(n+1, 0), dp_cur(n+1, 0);

    for (int g=1; g<=k; g++) {
        SegTree st(n+1);

        // build initial tree with dp_prev[j] at position j
        for (int j=0;j<=n;j++) {
            st.update(j,j,dp_prev[j]);
        }

        last.clear();
        for (int i=1;i<=n;i++) {
            int y = a[i];
            int l = (last.count(y) ? last[y]+1 : 0);
            st.update(l, i, 1); // new distinct element adds +1
            dp_cur[i] = st.query(0,i-1);
            last[y] = i;
        }
        dp_prev.swap(dp_cur);
    }

    cout << dp_prev[n] << "\n";
    return 0;
}


// this ris wron wr 