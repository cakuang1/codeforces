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
    ll n;
     cin >> n;    
    
    ll h1,h2 ,f1,f2 ;
    
    if (n == 1) {
        cout << "0" << " "<<"0" << endl;
        return 0; 
    }

    
    h1 = 1;
    h2 = 0;
    f1 = 0;
    f2 = 0;

    for (int i = 1 ; i < n; i ++) {

        // solving for h 
        ll p = (i * mod_inverse(n, mod2));
        ll firstfirst = mod_inverse(1 + p , mod2); 
        ll firstsecond =  (mod2 + 1 - firstfirst) % mod; 


        ll newh1 = (((h1 * firstfirst) % mod) + ((h2 * firstsecond) % mod)) % mod; 
        ll newh2 = (((h1 * firstsecond) % mod) + ((h2 * firstfirst) % mod)) % mod; 


        h1 = newh1;
        h2 = newh2;

        ll first =  (p *  mod_inverse(1 - (p * p))) % mod;
        // p2 + p4 + p6 .... 
        ll second = ((p * p) * mod_inverse(1 - (p * p))) % mod;

        

    }   



    cout << f1 << " " << f2  << endl; 

     
    return 0;
}


