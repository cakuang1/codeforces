#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// fast gcd
inline ll gg(ll a, ll b) {
    return b ? gg(b, a % b) : a;
}

struct GcdSparseTable {
    int N, K;
    vector<int> log2;
    vector<vector<ll>> st;

    // build on array d[0..N-1]
    GcdSparseTable(const vector<ll>& d) {
        N = d.size();
        K = 32 - __builtin_clz(max(1, N));
        log2.resize(N+1);
        for (int i = 2; i <= N; i++)
            log2[i] = log2[i/2] + 1;

        st.assign(K, vector<ll>(N));
        // level 0
        for (int i = 0; i < N; i++)
            st[0][i] = d[i];
        // build higher levels
        for (int k = 1; k < K; k++) {
            int span = 1 << k;
            for (int i = 0; i + span <= N; i++) {
                st[k][i] = gg(st[k-1][i], st[k-1][i + (span>>1)]);
            }
        }
    }
    
    /
    ll query(int L, int R) const {
        int len = R - L + 1;
        int k   = log2[len];
        return gg(st[k][L], st[k][R - (1<<k) + 1]);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;

        vector<ll> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        // build difference array
        vector<ll> d;
        d.reserve(max(0, n-1));
        for (int i = 0; i+1 < n; i++)
            d.push_back( llabs(a[i+1] - a[i]) );

        GcdSparseTable gst(d);

        while (q--) {
            int l, r;
            cin >> l >> r;
            // 1-based → 0-based
            if (l == r) {
                cout << 0 << "\n";
            } else {
                // differences cover [l..r-1] in 1-based
                int L = l-1, R = r-2;
                cout << gst.query(L, R) << "\n";
            }
        }
    }
    return 0;
}
