#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using ll = long long;
using ld = long double;
const ll mod = 1e9 + 7; // Change as per the problem requirements
const int N = 2e5 + 10; // Adjust the size as needed

// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N);
vector<ll> invFact(N);

// Function to compute x^y % mod using binary exponentiation
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

// Function to precompute factorials and their modular inverses
void precomputeFactorials(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[n] = modExp(fact[n], mod - 2); // Fermat's Little Theorem for modular inverse
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}


// w
// Function to calculate nCr % mod
ll nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
}

// Function to calculate nPr % mod
ll nPr(int n, int r) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[n - r]) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    precomputeFactorials(N - 1);
  // precomputeFactorials 
    ll t;
    cin >> t;
    while (t--) {

        string s;
        cin >> s; 
        int n = s.length();
        
        if (s[0] == '0') {
            cout << 0 << endl;
            continue;
        }
        int curr = 1; 
        for (int i = 0 ; i < n ; i++) {
            if (s[i] == '?') {
                if (i == 0) {
                    curr *= 9;
                } else {
                    curr *= 10; 
                }
            }
        }

        if (curr == 1) {
            cout << 1 << endl;
        } else{ 
            cout << curr << endl;
        }

        
    }

    return 0;
}
