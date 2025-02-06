#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAX_N = 205;      // Maximum number of numbers
const int MAX_K = 205;      // Maximum numbers to choose
const int MAX_FIVE = 5005; // Maximum sum of powers of 5
const int INF = -1e9;

// Function to count factors of `p` in `x`
int countFactors(ll x, ll  p) {
    int count = 0;
    while (x % p == 0 && x > 0) {
        count++;
        x /= p;
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll  n, k;
    cin >> n >> k;

    // Precompute powers of 2 and 5 for all numbers
    vector<int> pw2(n), pw5(n);
    for (int i = 0; i < n; i++) {
        ll  x;
        cin >> x;
        pw2[i] = countFactors(x, 2);
        pw5[i] = countFactors(x, 5);
    }

    // DP arrays
    vector<vector<int>> dp_prev(MAX_K, vector<int>(MAX_FIVE, INF));
    vector<vector<int>> dp_curr(MAX_K, vector<int>(MAX_FIVE, INF));

    // Base case: no items taken, no powers collected
    dp_prev[0][0] = 0;

    for (int i = 0; i < n; i++) {
        dp_curr = dp_prev; // Start with the previous layer

        for (int items_used = 0; items_used < k; items_used++) {
            for (int total_five = 0; total_five < MAX_FIVE; total_five++) {
                if (dp_prev[items_used][total_five] == INF) continue;

                // Take the current item
                int new_five = total_five + pw5[i];
                if (new_five < MAX_FIVE) {
                    dp_curr[items_used + 1][new_five] = max(
                        dp_curr[items_used + 1][new_five],
                        dp_prev[items_used][total_five] + pw2[i]
                    );
                }

                // Skip the current item (already handled by copying `dp_prev`)
            }
        }

        swap(dp_prev, dp_curr); // Move to the next layer
    }

    // Find the maximum roundness
    int res = 0;
    for (int total_five = 0; total_five < MAX_FIVE; total_five++) {
        if (dp_prev[k][total_five] != INF) {
            res = max(res, min(total_five, dp_prev[k][total_five]));
        }
    }

    cout << res << endl;
    return 0;
}
