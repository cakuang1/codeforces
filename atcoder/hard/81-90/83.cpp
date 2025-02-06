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

    int h ,w ;cin >> h >> w;
    queue<pair<int,int>> q; 

    vector<vector<int >> grid(h,  vector<int> (w));
    for (int r = 0 ; r < h  ;r ++) {
        for (int c = 0 ; c < w ; c ++) {
            char curr; cin >> curr;

            if (curr =='#') {
                grid[r][c] = 0;
                q.push({r,c});
            } else {
                grid[r][c] = -1;
            }
        }
    }
    

    int dx[4] =  {1,-1,0,0};
    int dy[4] =  {0,0,1,-1};
    
    // assign distance 
    while (!q.empty()) {
        auto top = q.front();
        q.pop();


        for (int i = 0 ; i < 4; i++) {
            int newx =  top.first + dx[i];
            int newy =  top.second + dy[i];

            if (newx >= 0 && newx < h && newy >= 0 && newy < w && grid[newx][newy] == -1) {
                grid[newx][newy] = grid[top.first][top.second] + 1; 
                q.push({newx,newy});
            }
        }
        
    }


    int ans = 0;
    for (int i = 0 ; i < h ; i ++) {
        for (int j = 0 ; j < w ; j ++) {
            ans = max(ans, grid[i][j]); 
        }
    }

    cout << ans << endl; 
    
    return 0;
}


