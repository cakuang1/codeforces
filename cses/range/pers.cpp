#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Persistent segment tree nodes
struct Node {
    ll sum;
    int l, r;
};

static int n, q;
static vector<int> roots;
static vector<Node> st;
static int nxt = 0;

// Build an all-zero tree over [L..R]
int build(int L, int R, const vector<ll> &arr) {
    int u = nxt++;
    st[u].sum = 0;
    st[u].l = st[u].r = -1;
    if (L == R) {
        st[u].sum = arr[L];
    } else {
        int M = (L + R) >> 1;
        st[u].l = build(L, M, arr);
        st[u].r = build(M+1, R, arr);
        st[u].sum = st[st[u].l].sum + st[st[u].r].sum;
    }
    return u;
}

// Point‐update: set position pos to val, based on previous version prev
int update(int prev, int L, int R, int pos, ll val) {
    int u = nxt++;
    st[u] = st[prev];  // copy
    if (L == R) {
        st[u].sum = val;
    } else {
        int M = (L + R) >> 1;
        if (pos <= M) {
            st[u].l = update(st[prev].l, L, M, pos, val);
        } else {
            st[u].r = update(st[prev].r, M+1, R, pos, val);
        }
        st[u].sum = st[st[u].l].sum + st[st[u].r].sum;
    }
    return u;
}

// Range‐sum query on version u over [ql..qr]
ll query(int u, int L, int R, int ql, int qr) {
    if (qr < L || R < ql) return 0;
    if (ql <= L && R <= qr) return st[u].sum;
    int M = (L + R) >> 1;
    return query(st[u].l, L, M, ql, qr)
         + query(st[u].r, M+1, R, ql, qr);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    vector<ll> arr(n+1);
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }

    // Reserve plenty of nodes: ~n + q*log n
    st.reserve((n + q*20) * 2);
    roots.reserve(q + 1);

    // Build initial version (array 1)
    nxt = 0;
    roots.push_back(build(1, n, arr));

    while(q--){
        int type;
        cin >> type;
        if (type == 1) {
            // set array k at position a to x
            int k, a;
            ll x;
            cin >> k >> a >> x;
            int idx = k - 1;
            // update version idx
            roots[idx] = update(roots[idx], 1, n, a, x);
        }
        else if (type == 2) {
            // sum query on array k
            int k, a, b;
            cin >> k >> a >> b;
            int idx = k - 1;
            ll ans = query(roots[idx], 1, n, a, b);
            cout << ans << "\n";
        }
        else {
            int k;
            cin >> k;
            roots.push_back(roots[k-1]);
        }
    }
    return 0;
}



