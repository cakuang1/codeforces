#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e18; // Large number to indicate "impossible"
const int MAX_V = 100000; // Max possible sum of values (100 items * 1000 value each)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, W;
    cin >> n >> W;

    vector<ll> dp(MAX_V + 1, INF);
    dp[0] = 0; // Base case: Minimum weight needed to achieve value 0 is 0

    for (int i = 0; i < n; i++) {
        int w, v;
        cin >> w >> v;

        // Traverse backwards to prevent using the same item multiple times
        for (int value = MAX_V; value >= v; value--) {
            dp[value] = min(dp[value], dp[value - v] + w);
        }
    }

    // Find the highest achievable value without exceeding W
    ll max_value = 0;
    for (int v = 0; v <= MAX_V; v++) {
        if (dp[v] <= W) {
            max_value = v;
        }
    }

    cout << max_value << endl;
    return 0;
}
