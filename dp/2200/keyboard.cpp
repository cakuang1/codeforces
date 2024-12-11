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


// whow woudl you wsee thsi w w

string s; 

int neigh[20][20]; 
void preprocess() {
    for (int i = 0 ; i < s.length() ; i ++) {
        if  (i > 0) {
            int val1 = s[i] - 'a'; 
            int val2 = s[i + 1]  - 'a';  
            neigh[val1][val2] ++; 
            neigh[val2][val1] ++; 
        }

        if (i <  s.lenth() - 1) {
            int val3 = s[i] - 'a'; 
            int val4 = s[i + 1]  - 'a';  
            neigh[val1][val2] ++; 
            neigh[val2][val1] ++;    
        }
    }
}

// will you be able to se e thsi w w we
// pre process 
// determine the next character  


// how to seee thsi wr w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    //wdoes this ake wense wr 
    int n ,k;
    cin >> n >> k;
    cin >> s;
    vector<int> password (n); 
    for (int i = 0 ;i < n ;i ++) {
        cin >> password[i];
    } 

    // does this make sense 
    for (int i = 0 ; i <  k;  i++) {
        for (int j = 0 ; j <  k ; j ++) {             
        


        }
    }


    // bitmask dp 


    return 0;
}
