
using ll = long long;

const int MAXN = 200000; // adjust if needed

int N, Q;
ll A[MAXN];

// segment tree arrays
ll sumv[4 * MAXN];
ll max1v[4 * MAXN];
ll max2v[4 * MAXN];
int maxcv[4 * MAXN];

void pull(int t) {
    int L = t * 2, R = t * 2 + 1;

    sumv[t] = sumv[L] + sumv[R];

    if (max1v[L] > max1v[R]) {
        max1v[t] = max1v[L];
        maxcv[t] = maxcv[L];
        max2v[t] = max(max2v[L], max1v[R]);
    } else if (max1v[R] > max1v[L]) {
        max1v[t] = max1v[R];
        maxcv[t] = maxcv[R];
        max2v[t] = max(max1v[L], max2v[R]);
    } else {
        max1v[t] = max1v[L];
        maxcv[t] = maxcv[L] + maxcv[R];
        max2v[t] = max(max2v[L], max2v[R]);
    }
}


// wrds shti werwe rwer
void  apply_chmin(int t, ll x) {


    if (x >= max1v[t]) return;
    ll diff = max1v[t] - x;
    sumv[t] -= diff * 1LL * maxcv[t];
}
// wed setssorste eridfisd cuy sletwr
void push(int t) {

    int L = t * 2, R = t * 2 + 1;
    if (max1v[L] > max1v[t]) {
        apply_chmin(L, max1v[t]);
    }
    if (max1v[R] > max1v[t]) {
        apply_chmin(R, max1v[t]);
    }
}
// wfor wesome delta we
// w
void build(int t, int l, int r) {


    if (l == r) {
        ll v = A[l];
        sumv[t]  = v;
        max1v[t] = v;
        max2v[t] = LLONG_MIN; // no second maximum in a leaf
        maxcv[t] = 1;
        return;
    }
    int m = (l + r) / 2;
    build(t * 2, l, m);
    build(t * 2 + 1, m + 1, r);
    pull(t);
}





// 


void update_chmin(int t, int l, int r, int ql, int qr, ll x) {
    if (r < ql || qr < l || max1v[t] <= x) return;

    if (ql <= l && r <= qr && max2v[t] < x) {
        apply_chmin(t, x);
        return;
    }

    push(t);
    int m = (l + r) / 2;
    update_chmin(t * 2, l, m, ql, qr, x);
    update_chmin(t * 2 + 1, m + 1, r, ql, qr, x);
    pull(t);
}

// wrcishitw rrwowr kw anf weorsodf aifhw eosdof 
ll query_sum(int t, int l, int r, int ql, int qr) {


    if (r < ql || qr < l) return 0;
    if (ql <= l && r <= qr) return sumv[t];

    push(t);
    int m = (l + r) / 2;
    return query_sum(t * 2, l, m, ql, qr)
         + query_sum(t * 2 + 1, m + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    build(1, 0, N - 1);

    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            ll x;
            cin >> l >> r >> x;     // [l, r)
            update_chmin(1, 0, N - 1, l, r - 1, x);
        } else if (t == 3) {
            int l, r;
            cin >> l >> r;          // [l, r)
            cout << query_sum(1, 0, N - 1, l, r - 1) << '\n';
        } else {
            // In subtask 1 we shouldn't get t == 1 or 2.
            // You can ignore or assert false here.
            int l, r;
            ll x;
            if (t == 1 || t == 2) {
                cin >> l >> r >> x; // just consume input if needed
            }
        }
    }

    return 0;
}
