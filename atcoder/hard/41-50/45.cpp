#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <climits> 



using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const ll mod2 = 998244353; 
const ll p = 31;        // Base for hashing


// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N), invFact(N);

ll mod_power(ll a, ll b, ll m) {
    ll result = 1;  // Initialize result
    a = a % m;      // Reduce 'a' modulo m (in case a >= m)

    while (b > 0) {
        // If b is odd, multiply 'a' with result and reduce modulo m
        if (b & 1) {
            result = (result * a) % m;
        }

        // Square the base and reduce modulo m
        a = (a * a) % m;

        // Divide b by 2
        b >>= 1;
    }

    return result;
}  

ll mod_inverse(ll n, ll m = mod)  {
    return mod_power(n, m - 2,m);
} 



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



int N =  100001;
 

vector<bool> primes(N, false); 

void sieve() {
    for (int i = 2; i <= 100000;  i ++) {
        if (!primes[i]) {
            for (int curr = i ; curr <= 100000 ; curr += i) {
                primes[curr] = true; 
            }
        }
    }
}
 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    sieve(); 
    vector<int> prefix(100001, 0 ); 
    for (int i = 2 ; i <= 100000 ; i ++) { 
        prefix[i] = prefix[i - 1] + (primes[i] && primes[(i + 1)/2]);
    }

    int q;
    for (int i = 0 ;i  < q; i ++) {
        int a , b ;
        cin >> a >> b; 
        cout << prefix[b] - prefix[a - 1] << endl ; 
    }

    

     
     
    

    return 0;
}


