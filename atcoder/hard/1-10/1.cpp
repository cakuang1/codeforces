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
    string s; 
    cin >> s; 
    int n = s.length();
    vector<int> a(n,0); 
    vector<int> ind;
    int rcount = 1;
    int prevr = -1;
    int prevl = -1;
    // what about the swap wfrom l to r  w     
    for (int i = 1 ; i < n ; i ++) {
        // RL then what? How would you distribute the Rs?
        if (s[i] == 'L' && s[i - 1] == 'R') {
            prevr = i - 1;
            prevl =  i;
            a[prevr] += rcount - (rcount/2);
            a[prevl] += rcount/2;
            rcount = 0;   
        }

    
    
        if (s[i] == 'R') {
            rcount ++;
        } else {
            if ((i - prevl) % 2) {
                a[prevr] ++; 
            } else {
                a[prevl] ++;
            }
        }
    }
    for (int i = 0 ; i < n ; i ++) {
        cout << a[i] << " "; 
    }
    
    return 0;
}


