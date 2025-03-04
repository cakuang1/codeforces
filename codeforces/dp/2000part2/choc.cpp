#include <bits/stdc++.h>
using namespace std;
 
const int INF = 1e9;
 
// dp[i][j][k] = minimum cost to break an i x j chocolate bar to get exactly k squares.
int dp[32][32][51];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Precompute for all i, j up to 31 (since i, j <= 30) and for k up to 50.
    for (int i = 1; i < 32; i++){
        for (int j = 1; j < 32; j++){
            // Initialize all k states to INF.
            for (int k = 0; k < 51; k++){
                dp[i][j][k] = INF;
            }
            // Base cases.
            dp[i][j][0] = 0; 
            if (i * j < 51) {
                dp[i][j][i * j] = 0;
            }
 
            // For each target k (only consider k that do not exceed the bar area and k <= 50)
            for (int k = 1; k <= min(i * j, 50); k++){
                // If k equals the full area, no cost.
                if (k == i * j) {
                    dp[i][j][k] = 0;
                    continue;
                }
 
                // Try all horizontal splits.
                for (int x = 1; x < i; x++){
                    // Top piece: x * j, Bottom piece: (i - x) * j.
                    for (int t = 0; t <= k; t++){
                        if (t <= x * j && (k - t) <= (i - x) * j){
                            dp[i][j][k] = min(dp[i][j][k],
                                dp[x][j][t] + dp[i-x][j][k-t] + j*j);
                        }
                    }
                }
 
                // Try all vertical splits.
                for (int y = 1; y < j; y++){
                    // Left piece: i * y, Right piece: i * (j - y).
                    for (int t = 0; t <= k; t++){
                        if (t <= i * y && (k - t) <= i * (j-y)){
                            dp[i][j][k] = min(dp[i][j][k],
                                dp[i][y][t] + dp[i][j-y][k-t] + i*i);
                        }
                    }
                }
            }
        }
    }

    // d
    int T;
    cin >> T;
    while(T--){
        int n, m, k;
        cin >> n >> m >> k;
        // n, m <= 30 and k <= min(n*m, 50) as given.
        cout << dp[n][m][k] << "\n";
    }
 
    return 0;
}
