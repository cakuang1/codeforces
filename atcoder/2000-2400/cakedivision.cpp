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
    int N,K
    vector<int> arr(2* N);
    for (int i = 0 ; i < N ;i ++) {
        int c; cin >> c ;
        arr[i] = c; 
        arr[i + N] = c; 
    }    
    vector<int> pre(2 * N + 1 , 0);
    for (int i = 0 ;i < 2 * N ; i ++) {
        pre[i + 1] = arr[i] + pre[i]; 
    }     
    vector<int> f(2 * N + 1);
    vector<vector<int>> adj(2 * N + 1);
    auto check = [&](int s) {
        adj.assign(2 * N + 1,  {}); 

        for (int i = 0 , j = 0 ; i <  ; i ++) {
            

            while ( )
        }
     }

    

    


    

     return 0;
}


