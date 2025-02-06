// have to mat #include <iostream>
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
const int N = 2e5 + 10; // Adjust size as needed
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

    
  
    // does this really wmake any wsense w
    // take pairs until 
    return 0;
}


