#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const ll mod2 = 998244353; 
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing


// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N), invFact(N);




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

ll mod_inverse(ll n, ll m = mod)  {
    return power(n, m - 2);
} 

// maximum possible values w


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







int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n ,k; cin >> n >> k ;
    vector<int> a(n),b(n); 
    for (int i = 0 ;  i < n; i ++) {
        cin >> a[i] >> b[i]; 
    }
    vector<int> ord(n);
    for (int i = 0 ; i < n ; i ++) {
        ord[i] = i;
    }
    
    sort(ord.begin(), ord.end(), [&](int i  , int j) {return b[i]  * (a[j] - 1) > b[j] * (a[i] - 1 );});  
    vector<ll> dp(k + 1,-1e9); 
    // choose not to use 
    dp[0] = 1;
    for (auto i  : ord ) {
        vector<ll> ndp = dp;

        for (int j = 0  ; j < k ; j ++) {
            if (dp[j] == 1e9 ) {
                continue;  
            }
            // find the maximum subseuqenceo flength w
            ndp[j + 1] = max(ndp[j + 1] ,dp[j] * a[i] + b[i]);
        }
        dp = move(ndp); 
    }

    cout << dp[k] << endl;

    return 0;

    // whats the max    
}
