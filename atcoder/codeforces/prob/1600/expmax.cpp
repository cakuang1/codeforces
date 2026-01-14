#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Input: number of faces (m) and number of rolls (n)
    int m, n;
    cin >> m >> n;

    // Calculate the expected maximum
    double expectedMaximum = 0.0;
    for (int i = 1; i <= m; i++) {
        double prob_i = pow((double)i / m, n) - pow((double)(i - 1) / m, n);
        expectedMaximum += i * prob_i;
    }

    // Output the result with precision
    cout << fixed << setprecision(6) << expectedMaximum << "\n";

    return 0;
}
