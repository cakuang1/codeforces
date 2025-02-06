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


    // end in a and start b 

    int n ; cin >> n; 
    
    int count = 0;


    int acount = 0;
    int bcount = 0;
    
    

    for (int i = 0 ; i < n; i ++) {
        
        string s;  cin >> s;
        int l = s.length();
        for (int k = 0 ; k < n - 1 ; k ++) {
            if (s[k] == 'A' && s[k + 1] == 'B')  {
                count ++;
            }
        }

        if (s[n - 1] == 'A') {
            acount ++;
        }
        if(s[0] == 'B') {
            bcount ++; 
        }
    }
    
    count += min(acount ,bcount);
    cout <<  count << endl;

     return 0;
}


