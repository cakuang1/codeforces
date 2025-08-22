#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int NMAX = 200000;
const int MAXNODES = 6000000;

struct Node {
    ll sum;
    int l, r;
} st[MAXNODES];
int nxtFree = 0;

int build(int L, int R) {
    int u = nxtFree++;
    st[u].sum = 0;
    if (L < R) {
        int M = (L+R) >> 1;
        st[u].l = build(L, M);
        st[u].r = build(M+1, R);
    } else {
        st[u].l = st[u].r = -1;
    }
    return u;
}

int update(int prev, int L, int R, int pos, ll val) {
    int u = nxtFree++;
    st[u] = st[prev];
    if (L == R) {
        st[u].sum += val;
    } else {
        int M = (L+R) >> 1;
        if (pos <= M)
            st[u].l = update(st[prev].l, L, M, pos, val);
        else
            st[u].r = update(st[prev].r, M+1, R, pos, val);
        st[u].sum = st[ st[u].l ].sum + st[ st[u].r ].sum;
    }
    return u;
}

ll query(int aRoot, int bRoot, int L, int R, int ql, int qr) {
    if (qr < L || R < ql) return 0;
    if (ql <= L && R <= qr) {
        return st[bRoot].sum - st[aRoot].sum;
    }
    int M = (L+R) >> 1;
    return query(st[aRoot].l, st[bRoot].l, L, M, ql, qr)
         + query(st[aRoot].r, st[bRoot].r, M+1, R, ql, qr);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    // 1) Coordinate‑compress values
    vector<ll> vals = arr;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int M = vals.size();

    vector<int> comp(n);
    for(int i = 0; i < n; i++){
        comp[i] = int(lower_bound(vals.begin(), vals.end(), arr[i]) - vals.begin()) + 1;
    }

    // 2) Build empty PST and versions
    nxtFree = 0;
    int emptyRoot = build(1, M);
    vector<int> root(n+1);
    root[0] = emptyRoot;
    for(int i = 1; i <= n; i++){
        // insert arr[i-1] at version i-1 → version i
        ll v = arr[i-1];
        int c = comp[i-1];
        root[i] = update(root[i-1], 1, M, c, v);
    }

    // 3) Answer queries
    vector<ll> ans(q);
    for(int qi = 0; qi < q; qi++){
        int a, b;
        cin >> a >> b;
        ll S = 0;
        while(true) {
            // find how many compressed values ≤ S+1
            ll target = S + 1;
            int k = int(upper_bound(vals.begin(), vals.end(), target) - vals.begin()); 
            // query sum of all values ≤ S+1 in arr[a-1..b-1]
            ll T = query(root[a-1], root[b], 1, M, 1, k);
            if (T == S) break;
            S = T;
        }
        ans[qi] = S + 1;
    }
    // detemrine ethh current wersum we
    for(ll x : ans){
        cout << x << "\n";
    }
    
    return 0;
}


// greedy we