#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;
double dp[MAX + 1][MAX + 1][MAX + 1]; // DP array to store probabilities

int main() {
    int r, s, p;
    cin >> r >> s >> p;

    // Initialize the starting state
    dp[r][s][p] = 1.0;

    // Iterate over all states
    for (int i = r; i >= 0; i--) {
        for (int j = s; j >= 0; j--) {
            for (int k = p; k >= 0; k--) {
                // Skip states with no interactions
                if (i == 0 && j == 0 || j == 0 && k == 0 || k == 0 && i == 0) continue;

                double total = i * j + j * k + k * i; // Total interactions

                if (total > 0) {
                    // Rock kills scissors
                    if (j > 0)
                        dp[i][j - 1][k] += dp[i][j][k] * (i * j) / total;

                    // Scissors kill paper
                    if (k > 0)
                        dp[i][j][k - 1] += dp[i][j][k] * (j * k) / total;

                    // Paper kills rock
                    if (i > 0)
                        dp[i - 1][j][k] += dp[i][j][k] * (k * i) / total;
                }
            }
        }
    }

    // Calculate final probabilities
    double rock_prob = 0.0, scissors_prob = 0.0, paper_prob = 0.0;

    // Rocks survive
    for (int i = 1; i <= r; i++) {
        rock_prob += dp[i][0][0];
    }

    // Scissors survive
    for (int i = 1; i <= s; i++) {
        scissors_prob += dp[0][i][0];
    }

    // Papers survive
    for (int i = 1; i <= p; i++) {
        paper_prob += dp[0][0][i];
    }

    // Output results
    cout << fixed << setprecision(10);
    cout << rock_prob << " " << scissors_prob << " " << paper_prob << endl;

    return 0;
}
