#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 200000;

int n, q;
vector<ll> arr;

// segment tree arrays (1-indexed tree nodes)
ll segSum[4*MAXN + 5];
ll lazyAdd[4*MAXN + 5];
ll lazyAssignVal[4*MAXN + 5];
bool lazyAssignFlag[4*MAXN + 5];

void build(int node, int L, int R) {
    lazyAdd[node] = 0;
    lazyAssignFlag[node] = false;
    if (L == R) {
        segSum[node] = arr[L];
    } else {
        int M = (L + R) >> 1;
        build(node<<1,   L,   M);
        build(node<<1|1, M+1, R);
        segSum[node] = segSum[node<<1] + segSum[node<<1|1];
    }
}

void applyAssign(int node, int L, int R, ll v) {
    segSum[node] = v * (R - L + 1);
    lazyAssignFlag[node] = true;
    lazyAssignVal[node]  = v;
    lazyAdd[node] = 0;
}

void applyAdd(int node, int L, int R, ll v) {
    segSum[node] += v * (R - L + 1);
    if (lazyAssignFlag[node]) {
        // if there's a pending assign, we just increase that assigned value
        lazyAssignVal[node] += v;
    } else {
        lazyAdd[node] += v;
    }
}

void pushDown(int node, int L, int R) {
    if (L == R) return;
    int M = (L + R) >> 1;
    int lc = node<<1, rc = node<<1|1;
    if (lazyAssignFlag[node]) {
        // assignment overrides everything
        applyAssign(lc, L,   M, lazyAssignVal[node]);
        applyAssign(rc, M+1, R, lazyAssignVal[node]);
        lazyAssignFlag[node] = false;
    }
    if (lazyAdd[node] != 0) {
        applyAdd(lc, L,   M, lazyAdd[node]);
        applyAdd(rc, M+1, R, lazyAdd[node]);
        lazyAdd[node] = 0;
    }
}

void updateAdd(int node, int L, int R, int ql, int qr, ll v) {
    if (qr < L || R < ql) return;
    if (ql <= L && R <= qr) {
        applyAdd(node, L, R, v);
        return;
    }
    pushDown(node, L, R);
    int M = (L + R) >> 1;
    updateAdd(node<<1,   L,   M, ql, qr, v);
    updateAdd(node<<1|1, M+1, R, ql, qr, v);
    segSum[node] = segSum[node<<1] + segSum[node<<1|1];
}

void updateAssign(int node, int L, int R, int ql, int qr, ll v) {
    if (qr < L || R < ql) return;
    if (ql <= L && R <= qr) {
        applyAssign(node, L, R, v);
        return;
    }
    pushDown(node, L, R);
    int M = (L + R) >> 1;
    updateAssign(node<<1,   L,   M, ql, qr, v);
    updateAssign(node<<1|1, M+1, R, ql, qr, v);
    segSum[node] = segSum[node<<1] + segSum[node<<1|1];
}

ll querySum(int node, int L, int R, int ql, int qr) {
    if (qr < L || R < ql) return 0;
    if (ql <= L && R <= qr) {
        return segSum[node];
    }
    pushDown(node, L, R);
    int M = (L + R) >> 1;
    return querySum(node<<1,   L,   M, ql, qr)
         + querySum(node<<1|1, M+1, R, ql, qr);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    arr.resize(n+1);
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }

    build(1, 1, n);

    while(q--){
        int type, a, b;
        ll x;
        cin >> type >> a >> b;
        if(type == 1){
            // range add
            cin >> x;
            updateAdd(1, 1, n, a, b, x);
        } else if(type == 2){
            // range assign
            cin >> x;
            updateAssign(1, 1, n, a, b, x);
        } else {
            // range sum query
            ll ans = querySum(1, 1, n, a, b);
            cout << ans << "\n";
        }
    }


    return 0;
}
