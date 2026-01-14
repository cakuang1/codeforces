#include <bits/stdc++.h>
using namespace std;

// merge operation: change to gcd, max, etc.
inline int mergeOp(int a, int b) {
    return min(a, b);
}

struct SparseTable {
    int N, K;
    vector<vector<int>> st;
    vector<int> log2;

    // a = input array of size n
    SparseTable(const vector<int>& a) {
        N = a.size();
        K = 32 - __builtin_clz(N);  // max power s.t. 2^K <= N
        st.assign(K, vector<int>(N));
        log2.assign(N + 1, 0);

        // precompute logs
        for (int i = 2; i <= N; i++)
            log2[i] = log2[i/2] + 1;

        // initialize level 0
        for (int i = 0; i < N; i++)
            st[0][i] = a[i];

        // build higher levels
        for (int k = 1; k < K; k++) {
            int len = 1 << k;
            for (int i = 0; i + len <= N; i++) {
                st[k][i] = mergeOp(
                    st[k-1][i],
                    st[k-1][i + (1 << (k-1))]
                );
            }
        }
    }

    // query on [L..R] inclusive, 0-based
    int query(int L, int R) const {
        int len = R - L + 1;
        int k = log2[len];
        // we take two overlapping intervals of length 2^k
        return mergeOp(
            st[k][L],
            st[k][R - (1 << k) + 1]
        );
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    SparseTable st(a);

    while (q--) {
        int l, r;
        cin >> l >> r;
        // assume input is 1-based and inclusive:
        l--; r--;
        cout << st.query(l, r) << "\n";
    }
    return 0;
}
