#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n; 
    cin >> n;

    vector<int> dp(n + 1, INT_MAX);  // Initialize DP table with max values
    dp[0] = 0;  // Base case: 0 steps needed to reach 0

    for (int i = 1; i <= n; i++) {
        // Base case: Increment by 1 from the previous number
        dp[i] = dp[i - 1] + 1;

        // Check powers of 6
        for (int six = 6; six <= i; six *= 6) {
            dp[i] = min(dp[i], dp[i - six] + 1);
        }

        // Check powers of 9
        for (int nine = 9; nine <= i; nine *= 9) {
            dp[i] = min(dp[i], dp[i - nine] + 1);
        }
    }

    cout << dp[n] << endl;
    return 0;
}
