#include <bits/stdc++.h>

using namespace std;

const int NMAX = 305;
double dp[NMAX][NMAX][NMAX];
bool computed[NMAX][NMAX][NMAX];
int n;

// DP function to compute expected rolls
double solve(int c1, int c2, int c3) {
    if (c1 == 0 && c2 == 0 && c3 == 0) return 0; // Base case

    if (computed[c1][c2][c3]) return dp[c1][c2][c3]; // Memoization check

    double res = 0.0;
    int total = c1 + c2 + c3;

    // Recursively compute expected moves
    if (c1) res += (solve(c1 - 1, c2, c3) * (double)c1 / total);
    if (c2) res += (solve(c1 + 1, c2 - 1, c3) * (double)c2 / total);
    if (c3) res += (solve(c1, c2 + 1, c3 - 1) * (double)c3 / total);

    // Expected wasted moves before a successful move
    res += (double)n / total;

    // Store computed value
    computed[c1][c2][c3] = true;
    return dp[c1][c2][c3] = res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;

    int c1 = 0, c2 = 0, c3 = 0;
    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        if (c == 1) c1++;
        else if (c == 2) c2++;
        else c3++;
    }

    memset(dp, -1, sizeof(dp));
    memset(computed, false, sizeof(computed));

    cout << fixed << setprecision(10) << solve(c1, c2, c3) << endl;
    return 0;
}
