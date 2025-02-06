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

int dir[4][2] = {{1,0}, {-1, 0} ,{0,1} , {0,-1}}; 


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll h,w,k ;
    cin >> h >> w >>k;
    ll x,y; cin >> x >> y;
    x --;
    y --;  
    vector<vector<int>> grid(h, vector<int> (w));

    for (int i = 0 ; i < h ; i ++) { 
        for (int j = 0;  j < w ; j ++) {
            cin >> grid[i][j];
        }
    }    
    vector<vector<ll>> prev(h, vector<ll>(w, INT_MIN));

    // search for the max here 
    int maxsteps = min(k, h * w); 
    prev[x][y] = 0;    
    ll res = k * grid[x][y];
    for (int d =  1  ; d < maxsteps; d ++ ) { 
        vector<vector<ll>> curr(h, vector<ll>(w, INT_MIN));
        for (int r = 0 ; r < h ; r ++) {
            for (int c = 0 ;c < w ; c ++) {
                if (prev[r][c] == INT_MIN) continue; 
                for (int i = 0; i < 4; i++) {
                    int new_r = r + dir[i][0];
                    int new_c = c + dir[i][1];
                    if (new_r >= 0 && new_r < h && new_c >= 0 && new_c < w) {
                        curr[new_r][new_c] = max(
                            curr[new_r][new_c], 
                            prev[r][c] + grid[new_r][new_c]
                        );
                        res = max(res, curr[new_r][new_c] + ( (k - d) * (grid[new_r][new_c])) ); 
                    }
                }               
            }
        }
        prev = curr;
    }


    
    
    cout << res << endl; 

    return 0;
}


