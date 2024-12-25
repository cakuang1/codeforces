#include <bits/stdc++.h>
#include <atcoder/segtree>

using namespace std;
using namespace atcoder;

#define mod 998244353
#define inv2 499122177

// Segment tree operations
long long op(long long a, long long b) {
    return (a + b) % mod;
}

long long e() {
    return 0;
}

// Fast modular exponentiation
long long power(long long a, long long b) {
    long long result = 1, base = a;
    while (b > 0) {
        if (b & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        b >>= 1;
    }
    return result;
}

// Modular inverse using Fermat's Little Theorem
long long modular_inverse(long long n) {
    return power(n, mod - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;
    vector<long long> p(n);
    for (auto &x : p) {
        cin >> x;
        x--; // Convert to 0-based indexing
    }

    // Step 1: Calculate total inversions (bas)
    long long bas = 0;
    {
        segtree<long long, op, e> seg(n);
        for (long long i = 0; i < n; i++) {
            bas = (bas + seg.prod(p[i], n)) % mod;
            seg.set(p[i], 1);
        }
    }

    // Step 2: Calculate inversions in each block
    long long res = 0;
    long long sub = 0;
    long long add = ((k * (k - 1)) / 2) % mod;
    add = (add * inv2) % mod;

    segtree<long long, op, e> seg(n);
    for (long long i = 0; i < k; i++) {
        sub = (sub + seg.prod(p[i], n)) % mod;
        seg.set(p[i], 1);
    }

    for (long long i = k; i <= n; i++) {
        // Calculate current contribution
        long long cur = (bas - sub + add + mod) % mod;
        res = (res + cur) % mod;

        // Slide the window
        if (i == n) break;

        seg.set(p[i - k], 0);
        sub = (sub - seg.prod(0, p[i - k]) + mod) % mod;
        sub = (sub + seg.prod(p[i], n)) % mod;
        seg.set(p[i], 1);
    }
    res = (res * modular_inverse(n - k + 1)) % mod;
    cout << res << "\n";
    return 0;
}

// when  
