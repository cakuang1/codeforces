#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 300000;
static const int MOD  = 1000000009;

// precomputed arrays
int fib[MAXN+5], SX[MAXN+5], SY[MAXN+5];

// segment tree arrays (1-indexed tree)
long long seg[4*MAXN+20];
int tagX[4*MAXN+20], tagY[4*MAXN+20];

// build Fibonacci and prefix‐sum coefficients once
// SX[len] = sum_{i=1..len} Bx[i], where Bx[1]=1,Bx[2]=0,Bx[k]=F[k-2] for k>=3
// SY[len] = sum_{i=1..len} By[i], where By[1]=0,By[2]=1,By[k]=F[k-1] for k>=3
void init_fib(int n) {
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n+2; i++)
        fib[i] = (fib[i-1] + fib[i-2]) % MOD;

    // SX,SY for lengths 1..n
    SX[1] = 1;       SY[1] = 0;
    SX[2] = 1;       SY[2] = 1;
    for (int i = 3; i <= n; i++) {
        // Bx[i] = fib[i-2], By[i] = fib[i-1]
        SX[i] = (SX[i-1] + fib[i-2]) % MOD;
        SY[i] = (SY[i-1] + fib[i-1]) % MOD;
    }
}

// Apply a lazy‐tag (x,y) to node v covering [tl..tr]:
// it adds A[1..len] where A[1]=x, A[2]=y, A[k]=A[k-1]+A[k-2],
// so total addition = x*SX[len] + y*SY[len].
inline void apply_tag(int v, int tl, int tr, int x, int y) {
    int len = tr - tl + 1;
    long long add = ( (long long)x * SX[len] + (long long)y * SY[len] ) % MOD;
    seg[v] = (seg[v] + add) % MOD;
    tagX[v] = (tagX[v] + x) % MOD;
    tagY[v] = (tagY[v] + y) % MOD;
}

// Push v’s tags down to its children
void push(int v, int tl, int tr) {
    int x = tagX[v], y = tagY[v];
    if ((x|y) != 0 && tl < tr) {
        int tm = (tl + tr) >> 1;
        int lenL = tm - tl + 1;
        int lenR = tr - tm;

        // left child inherits (x,y)
        apply_tag(v<<1, tl, tm, x, y);

        // right child needs shifted start:
        // A[d+1] = F[k+d]   = x*F[d-1] + y*F[d]
        // A[d+2] = F[k+d+1] = x*F[d]   + y*F[d+1]
        int x2 = ( (long long)x * fib[lenL-1] + (long long)y * fib[lenL]   ) % MOD;
        int y2 = ( (long long)x * fib[lenL]   + (long long)y * fib[lenL+1] ) % MOD;
        apply_tag(v<<1|1, tm+1, tr, x2, y2);

        tagX[v] = tagY[v] = 0;
    }
}

// Build tree in O(n)
void build(int v, int tl, int tr, vector<int> &a) {
    tagX[v] = tagY[v] = 0;
    if (tl == tr) {
        seg[v] = a[tl] % MOD;
    } else {
        int tm = (tl + tr) >> 1;
        build(v<<1,   tl,   tm, a);
        build(v<<1|1, tm+1, tr, a);
        seg[v] = (seg[v<<1] + seg[v<<1|1]) % MOD;
    }
}

// Range‐update: add Fib‐sequence F_{1..(r-l+1)} on [L..R]
void update(int v, int tl, int tr, int L, int R) {
    if (R < tl || tr < L) return;
    if (L <= tl && tr <= R) {
        // node fully covered → starting offset k = tl-L+1
        int k = tl - L + 1;
        int x = fib[k];
        int y = fib[k+1];
        apply_tag(v, tl, tr, x, y);
        return;
    }
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    update(v<<1,   tl,   tm, L, R);
    update(v<<1|1, tm+1, tr, L, R);
    seg[v] = (seg[v<<1] + seg[v<<1|1]) % MOD;
}

// Range‐query sum on [L..R]
long long query(int v, int tl, int tr, int L, int R) {
    if (R < tl || tr < L) return 0;
    if (L <= tl && tr <= R) {
        return seg[v];
    }
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    long long res = query(v<<1,   tl,   tm, L, R)
                  + query(v<<1|1, tm+1, tr, L, R);
    return res % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    init_fib(n+3);
    build(1, 1, n, a);

    while (m--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            // add Fibonacci segment F1…F_{r-l+1} on [l..r]
            update(1, 1, n, l, r);
        } else {
            // print sum on [l..r]
            cout << query(1, 1, n, l, r) << "\n";
        }
    }

    return 0;
}
