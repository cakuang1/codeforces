#include <bits/stdc++.h>
using namespace std;

using ld = long double;

// Check if a given time T is feasible
bool isFeasible(ld T, const vector<ld>& positions, const vector<ld>& speeds) {
    ld left = -1e18, right = 1e18; // Start with an infinite range
    int n = positions.size();
    for (int i = 0; i < n; i++) {
        ld posLeft = positions[i] - speeds[i] * T;
        ld posRight = positions[i] + speeds[i] * T;
        left = max(left, posLeft);    // Update left bound
        right = min(right, posRight); // Update right bound
        if (left > right) return false; // If no overlap, T is not feasible
    }
    return true; // Overlapping range exists
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<ld> positions(n), speeds(n);
    for (int i = 0; i < n; i++) cin >> positions[i];
    for (int i = 0; i < n; i++) cin >> speeds[i];

    ld low = 0.0, high = 1e9; // Initial search range for T
    while (high - low > 1e-7) { // Precision of 10^-7
        ld mid = (low + high) / 2.0;
        if (isFeasible(mid, positions, speeds)) {
            high = mid; // Try for a smaller T
        } else {
            low = mid; // Increase T
        }
    }

    cout << fixed << setprecision(7) << low << endl;
    return 0;
}
