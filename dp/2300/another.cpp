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






int dp[260][260];
// whow woudl you wsee thsi w w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    precomputeFactorials(N - 1);
    ll n,k;
    cin >> n >> k;
    //  not sure what this means w wer
    memset(dp, -1 , sizeof(dp));


    vector<int> kexp(251); 
    vector<int> kminusexp(251); 
    kexp[0] = 1;
    for (int i = 1 ; i < 251 ; i ++) {
        kexp[1] = (kexp[i - 1] * k) % mod;
    }
    kminusexp[0] = 1;
    for (int i = 1 ; i < 251 ; i ++) {
        kminusexp[1] = (kminusexp[i - 1] * (k - 1)) % mod;
    }
    dp[1][0] =  kexp[n] - kminusexp[n]; 
    for (int r = 2 ; r <= n ; r ++ )  {
        dp[r][0] = (dp[r - 1][0] * (kexp[n] - kminusexp[n])) % mod;  
    }

    for (int c = 1 ; c <=n ; c ++)  {
        dp[1][c] = (kexp[n - c]);
    }
    // how do oyu wewse thsi we
    for (int r = 2 ;r <= n ; r ++)  {
        for (int  c = 2 ; c <= n ; c ++) {
            // what are the trnasitiosn we
            
            int part1 = ((kexp[n - c] - kminusexp[n - c]) *( kminusexp[c]) * dp[r - 1][c]) % mod;
            int part2 = 0;
            
            for (int i =)
        }
    }
    

    // this sucks wer w
    // weshiuld you werbe wselciton w weibng w

    // there is twno point 


    // pij is what wthe minum number of tickets 
    
    // one ticket , twotickets   wwnat witi all does this make sense w? 
    
    //

    


    cout << dp[n][n] << end;
    // fr cc to be the number of filling grid wer
    return 0;
}
