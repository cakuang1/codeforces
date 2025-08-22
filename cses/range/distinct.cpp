#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 200000;
static const int MAXNODE = 8000000; // ~n * 40

struct Node {
    int sum;
    int l, r;
} st[MAXNODE];
int nodes = 0;

// Build an all‐zero tree over [1..n]
int build(int L, int R) {
    int u = nodes++;
    st[u].sum = 0;
    if (L < R) {
        int M = (L+R)>>1;
        st[u].l = build(L, M);
        st[u].r = build(M+1, R);
    } else {
        st[u].l = st[u].r = -1;
    }
    return u;
}

// Return a new root after setting position pos to val (0 or 1)
int update(int prev, int L, int R, int pos, int val) {
    int u = nodes++;
    st[u] = st[prev];
    if (L == R) {
        st[u].sum = val;
    } else {
        int M = (L+R)>>1;
        if (pos <= M) {
            st[u].l = update(st[prev].l, L, M, pos, val);
        } else {
            st[u].r = update(st[prev].r, M+1, R, pos, val);
        }
        st[u].sum = st[ st[u].l ].sum + st[ st[u].r ].sum;
    }
    return u;
}

// Query sum on [ql..qr]
int query(int u, int L, int R, int ql, int qr) {
    if (qr < L || R < ql) return 0;
    if (ql <= L && R <= qr) return st[u].sum;
    int M = (L+R)>>1;
    return query(st[u].l, L, M, ql, qr)
         + query(st[u].r, M+1, R, ql, qr);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    // 1) Coordinate‑compress values
    vector<int> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for(int i = 0; i < n; i++){
        a[i] = int(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());
    }
    int M = vals.size();

    // 2) Build the empty version 0
    nodes = 0;
    vector<int> root(n+1);
    root[0] = build(1, n);

    // 3) last occurrence array
    vector<int> last(M, 0);

    // 4) Build version i for prefix [1..i]
    for(int i = 1; i <= n; i++){
        int v = a[i-1];        // compressed value
        int prev_version = root[i-1];
        int cur = prev_version;
        // If seen before, set the old position to 0
        if (last[v] != 0) {
            cur = update(cur, 1, n, last[v], 0);
        }
        // Mark current position with 1
        cur = update(cur, 1, n, i, 1);
        root[i] = cur;
        last[v] = i;
    }
        
    while(q--){
        int l, r;
        cin >> l >> r;
        // Version r has 1's at the last occurrences in [1..r].
        // Version l-1 has 1's for occurrences before l.
        // Their difference counts how many last‑occurrences fall in [l..r].
        int ans = query(root[r],   1, n, l, r)
                - query(root[l-1], 1, n, l, r);
        cout << ans << "\n";
    }
    return 0;
}
