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


bool cond(int mid , vector<int> arr , int k) {
    int n  = arr.size(); 
    for (int i = 0  ; i  < n;  i ++) {
        if  (arr[i] >= mid) {
            arr[i] =  1;
        } else {
            arr[i] = -1; 
        }
    }
    // maximum sum subarray 
    vector<int> prefix(n); 
    prefix[0] = arr[0];
    for (int i =  1 ; i  < n; i ++) {
        prefix[i] = prefix[i - 1] + arr[i]; 
    }
    int currmin = 0;
    
    for (int i = k - 1; i < n; i ++) {
        if ((prefix[i] - currmin) > 0) {
            return true; 
        }
        currmin = min(currmin, prefix[i - (k - 1)]); 
    }
    return false; 
    
}

// whow woudl you wsee thsi w w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    ll n,k; 
    cin >> n >> k;
    
    vector<int> arr(n);
    for (int i = 0 ; i < n; i ++) {
        cin >> arr[i]; 
    }


    int left =  1;
    int right =  n;
    

    int res = left;
    while (left <= right) {
        
        int mid = left + (right - left)/2;
        if (cond(mid,  arr ,k)) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1; 
        }
    }
    cout << res << endl;
    // pre
    return 0;
}
