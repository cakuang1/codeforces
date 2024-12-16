#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Input probabilities as integers
    int p1, q1, p2, q2;
    cin >> p1 >> q1 >> p2 >> q2;

    // Convert to floating-point probabilities
    double p = (double)p1 / q1; // Probability for SmallR
    double q = (double)p2 / q2; // Probability for Zanoes

    // Calculate the probability that SmallR wins
    double result = p / (p + q - p * q);

    // Output the result with precision
    cout << fixed << setprecision(10) << result << "\n";

    return 0;
}
