#include <bits/stdc++.h>
using namespace std; 
using ll = long long;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m, mod;
    cin >> n >> m >> mod;
 
    // Read the first m rows (each of length n)
    vector<string> grid(m);
    for (int i = 0; i < m; i++) {
        cin >> grid[i];
    }
    int zeroes = 0, ones = 0;
    for (int c = 0; c < n; c++){
        int cnt = 0;
        for (int r = 0; r < m; r++){
            if (grid[r][c] == '1') cnt++;
        }
        if (cnt == 0)
            zeroes++;
        else if (cnt == 1)
            ones++;
    }

    vector<vector<ll>> dp(n+1, vector<ll>(n+1, 0));
    dp[zeroes][ones] = 1; 
    
    int rowsToProcess = n - m;



    for (int row = 0; row < rowsToProcess; row++){
        vector<vector<ll>> newdp(n+1, vector<ll>(n+1, 0));
        for (int x = 0; x <= n; x++){
            for (int y = 0; y <= n; y++){
                if(dp[x][y] == 0) continue;
                ll ways = dp[x][y];
                if(x >= 2){
                    // Number of ways = choose(x,2) = x*(x-1)/2 (using modular arithmetic)
                    ll cnt = ((ll)x * (x - 1)) % mod;
                    cnt = (cnt /2) % mod;
                    newdp[x-2][y+2] = (newdp[x-2][y+2] + ways * cnt) % mod;
                }
 
                // Option 2: choose one column from 0 ones and one from 1 one.
                if(x >= 1 && y >= 1){
                    ll cnt = ((ll)x * y) % mod;
                    newdp[x-1][y] = (newdp[x-1][y] + ways * cnt) % mod;
                }
 
                // Option 3: choose two columns from those with 1 one.
                if(y >= 2){
                    ll cnt = ((ll)y * (y - 1)) % mod;
                    cnt = (cnt/2) % mod;
                    newdp[x][y-2] = (newdp[x][y-2] + ways * cnt) % mod;
                }
            }
        }
        dp = move(newdp);
    }
    
    // The final answer is the number of ways to have state (0,0): all columns have 2 ones.
    cout << dp[0][0] % mod << "\n";
    return 0;
}
