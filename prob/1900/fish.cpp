#include <bits/stdc++.h>
using namespace std;

const int MAXN = 18;
double dp[1 << MAXN];  // dp[mask]: Probability of fish in mask surviving
double probs[MAXN][MAXN];  // Probability matrix
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    // Read probabilities
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> probs[i][j];
        }
    }

    // Initialize the full mask
    dp[(1 << n) - 1] = 1.0;

    // Iterate over all masks in reverse order
    for (int mask = (1 << n) - 1; mask >= 0; mask--) {
        int bitcount = __builtin_popcount(mask); // Count the number of fish alive in the mask
        if (bitcount < 2) continue; // Skip masks with fewer than 2 fish

        double total_pairs = bitcount * (bitcount - 1) / 2.0; // Total interactions

        // Process all pairs of fish in the mask
        for (int a = 0; a < n; a++) {
            if (!(mask & (1 << a))) continue; // Fish `a` is not in the mask
            for (int b = 0; b < n; b++) {
                if (a == b || !(mask & (1 << b))) continue; // Fish `b` is not in the mask

                int newmaska = mask ^ (1 << b); // Remove fish `b` from the mask
                dp[newmaska] += dp[mask] * probs[a][b] / total_pairs; // Transition
            }
        }
    }

    // Compute the survival probability for each fish
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(6) << dp[1 << i] << " ";
    } 
    cout << endl;

    return 0;
}
