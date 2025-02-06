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

    ll res = 0; 
    ll n; 
    cin >> n;
    vector<ll> weights(n);
    for (int i = 0 ; i <  n;  i ++) {
        cin >> weights[i];
    }   

    // current degree 
    // determine the next increment (next increment , index, degree)  
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<tuple<ll, ll, ll>>> que;
    for (int i = 0 ; i < n ;i ++) {
        que.push({(weights[i] * 4)  - weights[i] , i,  2 });
        res += weights[i];  
    }

    for (int i = 0 ; i < n - 2 ; i ++) {
        auto [a,b,c] =  que.top(); 
        que.pop();
        res += a;
        
        ll newadd = (weights[b] * power(c + 1,2)) - (weights[b] * power(c,2)); 
        que.push({newadd,b, c + 1}); 
        
    } 


        
    cout << res << endl;     
    return 0;
}


