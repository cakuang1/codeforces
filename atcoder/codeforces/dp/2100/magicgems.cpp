    #include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using ll = long long;
using ld = long double;
const ll MOD = 1e9 + 7; // Change as per the problem requirements
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

// Function to compute x^y % mod using binary exponentiation
long long binaryExp(long long x, long long y, long long mod) {
    long long result = 1;
    x = x % mod; // Handle large x

    while (y > 0) {
        if (y & 1) { // If y is odd, multiply x with the result
            result = (result * x) % mod;
        }
        y = y >> 1; // Divide y by 2
        x = (x * x) % mod; // Square x
    }
    return result;
}

// Multiply two matrices
vector<vector<long long>> multiply(const vector<vector<long long>>& a, const vector<vector<long long>>& b) {
    int n = a.size();
    vector<vector<long long>> c(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

// Matrix exponentiation
vector<vector<long long>> matrixExp(vector<vector<long long>> a, long long p) {
    int n = a.size();
    vector<vector<long long>> res(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1; // Identity matrix
    while (p) {
        if (p % 2) res = multiply(res, a);
        a = multiply(a, a);
        p /= 2;
    }
    return res;
}

vector<long long> multiplyMatrixVector(const vector<vector<long long>>& mat, const vector<long long>& vec) {
    int n = mat.size();
    vector<long long> result(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] = (result[i] + mat[i][j] * vec[j]) % MOD;
        }
    }
    return result;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    precomputeFactorials(N - 1);
    

    ll n,m;
    cin >> n >> m;
    
    // dp[n] = dp[n - 1] + dp[n - m]; 

    // get the first m
    // need to shift  
    vector<ll> init(m, 0);

    for (int i = 0 ; i < m ; i ++) {
        dp[i] = 1; 
    }
    vector<vector<ll>> transfrom(m ,vector<ll>(m));
    transform[0][m - 1] = 1;
    transform[0][0] = 1;
    for (int i = 1 ; i < n ; i ++) {
        if (i + 1 < m ) {
         transform[i][i + 1] = 1

        }
    }

    vector<vector<ll>>  exp =  matrixExp(transform, n - 4);
    
    vector<ll> res = multiplyMatrixVector(exp, init); 
    
    cout << res[0] << endl; 

    
    return 0;
}
