#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const ll mod2 = 998244353; 
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing


// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N), invFact(N);

    /
ll power(ll a, ll b) {
    ll result = 1;
    while (b > 0) {
        if (b & 1) { // If b is odd, multiply the current base to the result
            result *= a;
        }
        a *= a;      // Square the base
        b >>= 1;     // Divide b by 2
    }
    return result;
}

// find distinct w
ll mod_inverse(ll n, ll m = mod)  {
    return power(n, m - 2);
} 


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n; 
    vector<int> arr(n);
    for (int i = 0; i  < n; i ++) {
        cin >> arr[i]; 
    }
    
    // status we
    return 0;
}


