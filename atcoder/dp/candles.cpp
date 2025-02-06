#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_K = 100005;
const int MAX_N = 105;

int dp[MAX_N][MAX_K]; // dp[i][j]: ways to distribute j candies among first i children
int prefix[MAX_K];    // prefix[j]: cumulative sum of dp[i-1][j]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    dp[0][0] = 1; // Base case: One way to distribute 0 candies among 0 children

    for (int i = 1; i <= n; i++) {
        memset(prefix, 0, sizeof(prefix));
        int val = arr[i - 1];

        // Compute prefix sum for dp[i-1]
        for (int j = 0; j <= k; j++) {
            prefix[j] = dp[i - 1][j];
            if (j > 0) {
                prefix[j] = (prefix[j] + prefix[j - 1]) % MOD;
            }
        }

        for (int j = 0; j <= k; j++) {
            if (j - val < 0) { 
                dp[i][j] = prefix[j]; // Full prefix sum
            } else {
                dp[i][j] = (prefix[j] - prefix[j - val - 1] + MOD) % MOD; // Ensure non-negative result
            }
        }
    }

    cout << dp[n][k] << endl;
    return 0;
}
