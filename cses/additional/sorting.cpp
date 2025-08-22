#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Fenwick tree for counting inversions
struct Fenwick {
    int n;
    vector<ll> f;
    Fenwick(int _n): n(_n), f(n+1,0) {}
    void update(int i, ll v=1) {
        for (; i <= n; i += i & -i) f[i] += v;
    }
    ll query(int i) const {
        ll s = 0;
        for (; i > 0; i -= i & -i) s += f[i];
        return s;
    }
    // sum on [l..r]
    ll query(int l, int r) const {
        return query(r) - query(l-1);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; i++){
        cin >> p[i];
    }

    //
    // 1) Adjacent swaps = number of inversions
    //
    Fenwick fw(n);
    ll inv = 0;
    for(int i = 0; i < n; i++){
        // count how many already‐seen are > p[i]
        inv += fw.query(p[i]+1, n);
        fw.update(p[i], 1);
    }

    //
    // 2) Arbitrary swaps = n – (# of cycles in the permutation)
    //
    vector<bool> seen(n,false);
    int cycles = 0;
    for(int i = 0; i < n; i++){
        if (!seen[i]) {
            cycles++;
            int cur = i;
            while (!seen[cur]) {
                seen[cur] = true;
                cur = p[cur] - 1;  // perm is 1‑based
            }
        }
    }
    ll arb_swaps = (ll)n - cycles;

    //
    // 3) Remove+insert anywhere = n – length of LIS on p
    //
    vector<int> lis;
    lis.reserve(n);
    for(int x : p){
        auto it = lower_bound(lis.begin(), lis.end(), x);
        if (it == lis.end()) lis.push_back(x);
        else *it = x;
    }
    ll lis_len = lis.size();
    ll arb_moves = (ll)n - lis_len;

    //
    // 4) Move‐to‐front operations = n – length of longest suffix
    //    matching the tail [n,n–1,…] in order.
    //
    int expected = n;
    for(int i = n-1; i >= 0; i--){
        if (p[i] == expected) {
            expected--;
        }
    }
    // if we matched k = n – expected elements, need n – k = expected moves
    ll move_front = expected;
    cout
      << inv << " "
      << arb_swaps << " "
      << arb_moves << " "
      << move_front << "\n";

    return 0;
}
