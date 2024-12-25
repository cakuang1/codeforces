#include <bits/stdc++.h>
using namespace std;

int dp[3001][3001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // Initialize the dp table
    memset(dp, 0, sizeof(dp));

    int res = 0; // At least one building can always be chosen

    // Fill the dp table
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (nums[i] == nums[j]) {
                int d = i - j; // Interval
                dp[i][d] = dp[j][d] + 1; // Transition
                res = max(res, dp[i][d]);
            }
        }
    }

    cout << res + 1 << endl; // Add 1 to include the first building in the subsequence
    return 0;
}
