#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Fenwick (BIT) for exact 64-bit sums
struct Fenwick {
    int n;
    vector<ll> f;
    Fenwick(int _n): n(_n), f(n+1,0) {}

    // point update: A[i] += v
    void update(int i, ll v) {
        for (; i <= n; i += i & -i)
            f[i] += v;
    }
    // prefix sum: sum_{j=1}^i A[j]
    ll query(int i) const {
        ll s = 0;
        for (; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }
    // range sum [l..r]
    ll query(int l, int r) const {
        if (l > r) return 0;
        return query(r) - query(l-1);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    // Values ai are in [1..n] and all distinct,
    // so we can use n as our Fenwick size.
    int maxv = n;

    // fw[len] will store counts of increasing subseqs of length = len
    // ending at each value.
    vector<Fenwick> fw(k+2, Fenwick(maxv));

    for(int i = 0; i < n; i++){
        int v = a[i];
        // build up counts for subsequences of length 2..k+1
        for(int len = k+1; len >= 2; --len){
            // count all subseqs of length len-1 that end with < v
            ll cnt = fw[len-1].query(1, v-1);
            fw[len].update(v, cnt);
        }
        // every single element is a subsequence of length 1
        fw[1].update(v, 1);
    }

    // the answer is the total number of subsequences of length k+1
    ll answer = fw[k+1].query(1, maxv);
    cout << answer << "\n";
    return 0;
} 
