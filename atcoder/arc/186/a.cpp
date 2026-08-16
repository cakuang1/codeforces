#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    const int M = 900;

    // dp[r][c][x] = possible to use r row vertices,
    // c column vertices, and get x non-fixed cells.
    vector<vector<bitset<M + 1>>> dp(
        N + 1,
        vector<bitset<M + 1>>(N + 1)
    );

    dp[0][0][0] = 1;

    for (int r = 0; r <= N; r++) {
        for (int c = 0; c <= N; c++) {
            for (int a = 2; r + a <= N; a++) {
                for (int b = 2; c + b <= N; b++) {
                    dp[r + a][c + b] |= dp[r][c] << (a * b);
                }
            }
        }
    }

    bitset<M + 1> possible;

    for (int r = 0; r <= N; r++) {
        for (int c = 0; c <= N; c++) {
            possible |= dp[r][c];
        }
    }

    while (Q--) {
        int K;
        cin >> K;

        int nonFixed = N * N - K;

        cout << (possible[nonFixed] ? "Yes" : "No") << '\n';
    }

} 

// wrw wnono is wersk ax emeans wrhat

// INcreas rwths wrdi. snsu wrwtouw wr w