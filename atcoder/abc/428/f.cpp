#include <bits/stdc++.h>
using namespace std;

static const long long INF = (long long)4e18;

const int MAXN = 200000;

long long sumv[4*MAXN];
long long max1v[4*MAXN], max2v[4*MAXN];
int      maxcv[4*MAXN];
long long min1v[4*MAXN], min2v[4*MAXN];
int      mincv[4*MAXN];
long long addv[4*MAXN];

vector<long long> a;
int N, Q;

#define LCH (t*2)
#define RCH (t*2+1)


void pull(int t) {
    int L = LCH, R = RCH;

    sumv[t] = sumv[L] + sumv[R];

    // ---- MAX MERGE ----
    if (max1v[L] == max1v[R]) {
        max1v[t] = max1v[L];
        max2v[t] = max(max2v[L], max2v[R]);
        maxcv[t] = maxcv[L] + maxcv[R];
    }
    else if (max1v[L] > max1v[R]) {
        max1v[t] = max1v[L];
        max2v[t] = max(max2v[L], max1v[R]);
        maxcv[t] = maxcv[L];
    }
    else {
        max1v[t] = max1v[R];
        max2v[t] = max(max1v[L], max2v[R]);
        maxcv[t] = maxcv[R];
    }

    // ---- MIN MERGE ----
    if (min1v[L] == min1v[R]) {
        min1v[t] = min1v[L];
        min2v[t] = min(min2v[L], min2v[R]);
        mincv[t] = mincv[L] + mincv[R];
    }
    else if (min1v[L] < min1v[R]) {
        min1v[t] = min1v[L];
        min2v[t] = min(min2v[L], min1v[R]);
        mincv[t] = mincv[L];
    }
    else {
        min1v[t] = min1v[R];
        min2v[t] = min(min1v[L], min2v[R]);
        mincv[t] = mincv[R];
    }
}


//---------------------------------------------
// Apply ADD to node
//---------------------------------------------
void apply_add(int t, long long v, int len) {
    sumv[t] += v * len;

    max1v[t] += v;
    if (max2v[t] != -INF) max2v[t] += v;

    min1v[t] += v;
    if (min2v[t] != INF) min2v[t] += v;

    addv[t] += v;
}


//---------------------------------------------
// Apply CHMIN to node: max1 -> x
//---------------------------------------------
void apply_chmin_node(int t, long long x) {
    if (max1v[t] <= x) return;
    sumv[t] -= (max1v[t] - x) * (long long)maxcv[t];
    max1v[t] = x;
    if (min1v[t] > x) min1v[t] = x;
    if (min2v[t] > x) min2v[t] = x;
}


//---------------------------------------------
// Apply CHMAX to node: min1 -> x
//---------------------------------------------
void apply_chmax_node(int t, long long x) {
    if (min1v[t] >= x) return;
    sumv[t] += (x - min1v[t]) * (long long)mincv[t];
    min1v[t] = x;
    if (max1v[t] < x) max1v[t] = x;
    if (max2v[t] < x) max2v[t] = x;
}


//---------------------------------------------
// Push lazy updates
//---------------------------------------------
void push(int t, int l, int r) {
    if (l == r) return;
    int m = (l+r)/2;

    // 1. Push ADD first
    if (addv[t] != 0) {
        long long v = addv[t];
        apply_add(LCH, v, m-l+1);
        apply_add(RCH, v, r-m);
        addv[t] = 0;
    }

    // 2. Push CHMIN bound
    long long mx = max1v[t];
    if (max1v[LCH] > mx) apply_chmin_node(LCH, mx);
    if (max1v[RCH] > mx) apply_chmin_node(RCH, mx);

    // 3. Push CHMAX bound
    long long mn = min1v[t];
    if (min1v[LCH] < mn) apply_chmax_node(LCH, mn);
    if (min1v[RCH] < mn) apply_chmax_node(RCH, mn);
}


//---------------------------------------------
// Build
//---------------------------------------------
void build(int t, int l, int r) {
    addv[t] = 0;
    if (l == r) {
        long long x = a[l];
        sumv[t] = x;

        max1v[t] = min1v[t] = x;
        max2v[t] = -INF;
        min2v[t] = INF;
        maxcv[t] = mincv[t] = 1;
        return;
    }

    int m = (l+r)/2;
    build(LCH, l, m);
    build(RCH, m+1, r);
    pull(t);
}


//---------------------------------------------
// RANGE CHMIN
//---------------------------------------------
void update_chmin(int t, int l, int r, int ql, int qr, long long x) {
    if (qr < l || r < ql || max1v[t] <= x) return;
    if (ql <= l && r <= qr && max2v[t] < x) {
        apply_chmin_node(t, x);
        return;
    }

    push(t, l, r);
    int m = (l+r)/2;
    update_chmin(LCH, l, m, ql, qr, x);
    update_chmin(RCH, m+1, r, ql, qr, x);
    pull(t);
}


//---------------------------------------------
// RANGE CHMAX
//---------------------------------------------
void update_chmax(int t, int l, int r, int ql, int qr, long long x) {
    if (qr < l || r < ql || min1v[t] >= x) return;
    if (ql <= l && r <= qr && min2v[t] > x) {
        apply_chmax_node(t, x);
        return;
    }

    push(t, l, r);
    int m = (l+r)/2;
    update_chmax(LCH, l, m, ql, qr, x);
    update_chmax(RCH, m+1, r, ql, qr, x);
    pull(t);
}


//---------------------------------------------
// RANGE ADD
//---------------------------------------------
void update_add(int t, int l, int r, int ql, int qr, long long v) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        apply_add(t, v, r-l+1);
        return;
    }
    push(t, l, r);
    int m = (l+r)/2;
    update_add(LCH, l, m, ql, qr, v);
    update_add(RCH, m+1, r, ql, qr, v);
    pull(t);
}


//---------------------------------------------
// RANGE SUM
//---------------------------------------------
long long query_sum(int t, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return sumv[t];
    push(t, l, r);
    int m = (l+r)/2;
    return query_sum(LCH, l, m, ql, qr) +
           query_sum(RCH, m+1, r, ql, qr);
}


//---------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    a.resize(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    build(1, 0, N-1);

    while (Q--) {
        int t, l, r;
        cin >> t >> l >> r;
        r--;

        if (t == 0) {
            long long b; cin >> b;
            update_chmin(1, 0, N-1, l, r, b);
        }
        else if (t == 1) {
            long long b; cin >> b;
            update_chmax(1, 0, N-1, l, r, b);
        }
        else if (t == 2) {
            long long b; cin >> b;
            update_add(1, 0, N-1, l, r, b);
        }
        else {
            cout << query_sum(1, 0, N-1, l, r) << "\n";
        }
    }
}
