#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing

// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N), invFact(N);

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



struct StringHash {
    vector<ll> hash, power;
    ll n;

    StringHash(const string &s) {
        n = s.size();
        hash.resize(n + 1, 0);
        power.resize(n + 1, 1);

        // Precompute hash values and powers of p
        for (int i = 0; i < n; i++) {
            hash[i + 1] = (hash[i] + (s[i] - 'a' + 1) * power[i]) % mod;
            if (i < n - 1)
                power[i + 1] = (power[i] * p) % mod;
        }
    }

    // Compute hash of substring s[l..r] (0-based indexing)
    ll getHash(int l, int r) {
        ll result = (hash[r + 1] - hash[l] * power[r - l + 1] % mod + mod) % mod;
        return result;
    }
};



// Function to compute modular inverse of a under modulo mod
ll modInverse(ll a, ll m = mod) {
    return modExp(a, m - 2, m); // Fermat's Little Theorem for prime mod
}

// Function to precompute factorials and their modular inverses
void precomputeFactorials(int n, ll m = mod) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % m;
    }
    invFact[n] = modExp(fact[n], m - 2, m); // Fermat's Little Theorem for modular inverse
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % m;
    }
}

// Function to calculate nCr % mod
ll nCr(int n, int r, ll m = mod) {
    if (r > n || r < 0) return 0;
    return (((fact[n] * invFact[r]) % m) * invFact[n - r]) % m;
}

// Function to calculate nPr % mod
ll nPr(int n, int r, ll m = mod) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[n - r]) % m;
}

// if we are choosing to be within the segment vs not wwei the segment
// after
int dp[200005][21][3]; 


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;
    while (t--) {
        int n, k, x,;
        cin >> n >> k >> x;
        vector<int> stun(n);
        for (int i = 0 ; i < n; i ++) {
            cin >> stun[i]; 
        }
        memset(dp ,-1, sizeof(dp));    

        for (int i = 0 ; i < n; i ++ ) {
            for (int j = 0 ; j <= k ; j ++) {
                for (int t = 0 ; t < 3 ; t ++) {
                    dp[i][j][k] =  MIN_INT;
                }
            }
        }
        
        dp[0][0][0] = 0;

        for (int i = 0 ; i < n; i ++ ) {
            for (int j = 0 ; j <= k ; j ++) {
                for (int t = 0 ; t < 3 ; t ++) {
                    // forward transitions  a
                    if (dp[i][j][k] == MIN_INT) continue; 


                    for (int nextj = j ; nextj <= min(k, j + 1 ) ; j ++) {
                        


                        for (int  tt = t; tt < 3 ; tt ++) {
                            d[i + 1][jj][]
                        }
                    }
                }
            }
        }
    
        cout << res << endl; 
        
        
        
    }

    return 0;
}
