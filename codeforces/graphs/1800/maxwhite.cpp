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

int n ;
vector<int> color;

vector<vector<int>> adj;


// subtree must contain wethe w w 

vector<int> dp1;
vector<int> dp2;


void dfs(int curr , int p) {
    
    // some dp aspects 
    int val = color[curr] == 1 ? 1 : -1;  
    for (int n : adj[curr] ) {
        if (n == p) continue;
        dfs(n,curr); 
        val += dp1[n]; 
    }
    //  max isfi yo uwedo take it hten wwhat d oyuo do w wmight as well not take wit w
    dp1[curr] = max(0, val); 
}


// max including this but

void dfs2(int curr , int parent )  { 
    
    for (int n : adj[curr]) {
        if (n == parent) continue;
            
    }
}
// grab the val and how do you dealwith wsuc w w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    
    // whats the maximum subtree of this size    w how do  w w
    colors.resize(n + 1 );
    for (int i = 1; i <= n; i ++) {
        cin >> colors[i];
    }


    
    for (int i = 0 ; i < n; i ++) {
        int a , b;
        cin >> a >> b; 
        adj[a].push_back(b); 
        adj[b].push_back(a); 
    }    

    // whats wthe difrene herwer 
    dp1.resize(n + 1, 0); 
    dp2.resize(n + 1, 0); 
    // must include 
    for (int i =  1 ; i <= n; i ++) {
        dp2[i] = colors[i] == 1 ? 1 : -1; 
    }
    // o(n);   
    dfs1(1,-1); 
    dfs2(1, -1);
    
    for (int i = 1 ; i <= n ; i ++ ) [
        cout << dp2[i] << endl; 
    ]





    // wdefine wd wp  
    


    
    return 0;
}
