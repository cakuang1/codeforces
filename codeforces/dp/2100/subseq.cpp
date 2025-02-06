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

int MAXN = 205
int dp[MAXN][MAXN][MAXN];
int dp2[MAXN][MAXN]; 
// how to see thtsi 

// whow woudl you wsee thsi w w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    precomputeFactorials(N - 1);

    int n , k ;
    cin >> n >> k;
    
    string s1;
    string s2;
    cin >> s1 >> s2;    
    vector<int>  A(n);
    for (int i = 0 ; i < n; i++) {
        cin >> A[i];    
    } 
    memset(dp ,-1 ,  sizeof(dp)); 
    

    dp[0][0][0] = 0 ;
    // how can you push 
    for (int index  = 0 ; index < n; i ++) {
        for (int changes  =  0 ; changes <=  k ; changes ++) {
            for (int count  = 0 , count  <= index + 1 ; count  ++) {
                // uncreachable
                if (dp[index][changes][count] == -1 ) continue;

                // define flags 
                
                int  e0 = s1[i] == s2[0];
                int  e1 = s1[i] == s2[1]; 
                int  e01 = s2[0] == s2[1]; 
                
                dp[index + 1][changes][count + e0] =  max(dp[index + 1][changes][count + e0], dp[index][changes][count] + (e1  ?  count : 0));
                if (changes < k) {
                    // change it to
                    dp[index + 1][changes + 1][count + 1] = max(dp[index + 1][changes + 1][count + 1] , dp[index][changes][count] + (e01 ? count : 0)); 
                    dp[index + 1][changes + 1][count + e01] = max(dp[index + 1][changes + 1][count + e01], dp[index][changes][count] + (count)); 
                 }


            }
        }
    }

    int res = -1;
    for (int i = 0 ; i <= k ; i ++ ) {
        for (int j = 0 ; j <= n ; j ++ ) {
            res = max(dp[n][i][j], res);
        }
    }

    cout << res << endl;

    // transitions  
    // this dosen ttwrealy eamke wsense wer
    // then wwhat we 




    return 0;
}
