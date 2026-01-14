#include <bits/stdc++.h>
using namespace std;

static const int MAXV = 1105;  // or some appropriate max velocity

long long dp[102][MAXV];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long v1, v2;
    cin >> v1 >> v2;
    int t;
    long long d;
    cin >> t >> d;

    // Initialize DP
    // dp[i][v] = maximum sum of velocities after i steps, if i-th step velocity is v.
    for(int i = 0; i <= t; i++) {
        for(int j = 0; j < MAXV; j++) {
            dp[i][j] = -1;
        }
    }

    // Base case: after 1 step with velocity v1, sum is v1
    dp[1][v1] = v1;

    // Fill DP
    for(int i = 1; i < t; i++) {
        for(int j = 0; j < MAXV; j++) {
            if(dp[i][j] == -1) continue;
            // Try all possible next velocities in [j-d, j+d]
            for(int newV = max(0LL, j - d); newV <= j + d; newV++) {
                if(newV < MAXV) {
                    dp[i+1][newV] = max(dp[i+1][newV], dp[i][j] + newV);
                }
            }
        }
    }

    cout << dp[t][v2] << "\n";
    return 0;
}
