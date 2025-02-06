#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const ll mod2 = 998244353; 
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing


// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N), invFact(N);



// take the modular inverse 

ll power(ll a, ll b, ll m = mod2) {
    ll result = 1;
    a %= m; // Ensure 'a' is within modulo range
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return result;
}
ll mod_inverse(ll n, ll m = mod)  {
    return power(n, m - 2);
} 

// maximum possible values w


ll modExp(ll x, ll y, ll m = mod) {
    ll res = 1;
    x = x % m;
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % m;
        }
        y = y >> 1;
        x = (x * x) % m;
    }
    return res;
}





struct SegmentTree {
    struct Node {
        long long sum = 0; // Sum of the segment
        long long a = 1;   // Scaling factor (for linear transformation)
        long long b = 0;   // Addition factor (for linear transformation)
    };

    int n;
    vector<Node> tree;

    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }

    void apply(int node, int start, int end, long long a, long long b) {
        tree[node].sum = (a * tree[node].sum % mod2 + b * (end - start + 1) % mod2) % mod2;
        tree[node].a = (a * tree[node].a) % mod2;
        tree[node].b = (a * tree[node].b % mod2 + b) % mod2;
    }

    void propagate(int node, int start, int end) {
        if (tree[node].a != 1 || tree[node].b != 0) { // Check if there's a pending update
            int mid = (start + end) / 2;
            apply(2 * node, start, mid, tree[node].a, tree[node].b);     // Left child
            apply(2 * node + 1, mid + 1, end, tree[node].a, tree[node].b); // Right child
            tree[node].a = 1; // Reset lazy values
            tree[node].b = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, long long a, long long b) {
        if (r < start || l > end) return; // Out of range
        if (l <= start && end <= r) {    // Fully in range
            apply(node, start, end, a, b);
            return;
        }
        propagate(node, start, end); // Propagate updates
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, a, b);
        update(2 * node + 1, mid + 1, end, l, r, a, b);
        tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum; // Merge results
    }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0; // Out of range
        if (l <= start && end <= r) return tree[node].sum; // Fully in range
        propagate(node, start, end); // Propagate updates
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }

    void update_range(int l, int r, long long a, long long b) {
        update(1, 0, n - 1, l, r, a, b);
    }

    long long query_range(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n ,m;
    cin >> n >> m;
    SegmentTree seg(n);

     for (int i = 0 ; i < n; i ++ ) {
        ll curr; 
        cin >> curr; 
        seg.update_range(i, i, 1, curr);

    }
    
    for (int i = 0 ;i < m ; i ++) {
        ll l,r,x;
        cin >> l >> r >> x; 
        l--;
        r--;
        ll lambda =  r - l + 1;
        ll lambdainverse = mod_inverse(lambda , mod2);         
        ll term1 = ((lambda - 1) * lambdainverse )% mod2; 
        ll term2 = (x * lambdainverse) % mod2; 
        seg.update_range(l,r, term1, term2 ); 
    }
    
    for (int i = 0 ; i < n; i ++) {
        cout << seg.query_range(i,i) << " ";
    }

    return 0;
}


