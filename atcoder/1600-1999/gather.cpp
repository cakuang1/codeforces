#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const ll mod2 = 998244353; 
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing


// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N), invFact(N);



// take the modular inverse 

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

    int h,w,n;
    cin >> h >> w >> n; 
    
    vector<pair<int,int>> coins(n); 
    
    sort(coins.begin(), coins.end());
    vector<int> dp; 
    vector<int> p(n);
    vector<int> i(n);

    for (int i = 0 ; i < n ; i ++) {
        auto it lower_bound(dp.begin(),dp.end(), nums[i]);
        int pos= it -  dp.begin();
        

        if (it == dp.end()) {
            dp.push_back()
        }
    }

    // exists only 

    
     
    return 0;
}