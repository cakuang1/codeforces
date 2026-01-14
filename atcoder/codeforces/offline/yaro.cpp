#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD   = 1000000007;
const int MOD2  =  998244353;
const ll  INF   = 1e18;
const int MX    = 1000001;

// (Your existing modular‐arithmetic & factorial code can stay here,
//  since it isn't used by this problem.)
// ...

// Fenwick (BIT) for point‐updates & prefix sums in O(log n)
struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}

    // add v at position i (1 ≤ i ≤ n)
    void update(int i, int v) {
        for (; i <= n; i += i & -i)
            f[i] += v;
    }
    // sum on [1..i]
    int query(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }
    // sum on [l..r]
    int query(int l, int r) const {
        return query(r) - query(l-1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> p(n+1), w(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        w[p[i]] = i;                  // w[val] = position of val in p[]
    }

    // starts[R] = list of L's for which (L,R) is a divisor‐pair
    vector<vector<int>> starts(n+1);
    // Build all pairs (q,w) such that p[q] divides p[w],
    // grouping by the right‐endpoint R = max(pos_q, pos_w).
    for (int val = 1; val <= n; val++) {
        int pos_val = w[val];
        for (int mul = val; mul <= n; mul += val) {
            int pos_mul = w[mul];
            int L = min(pos_val, pos_mul);
            int R = max(pos_val, pos_mul);
            starts[R].push_back(L);
        }
    }

    // Read queries and bucket them by right endpoint
    vector<pair<int,int>> Q(m);
    vector<vector<int>> ends(n+1);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        Q[i] = {l, r};
        ends[r].push_back(i);
    }

    vector<int> ans(m, 0);
    Fenwick fw(n);

    // Sweep R = 1…n, activate all (L,R) pairs, then answer queries ending at R
    for (int R = 1; R <= n; R++) {
        // activate each L for this R
        for (int L : starts[R]) {
            fw.update(L, 1);
        }
        // answer all queries with right endpoint R
        for (int qi : ends[R]) {
            int l = Q[qi].first;
            ans[qi] = fw.query(l, R);
        }
    }

    // Output
    for (int i = 0; i < m; i++) {
        cout << ans[i] << (i+1<m ? ' ' : '\n');
    }
    return 0;
}


//  chat