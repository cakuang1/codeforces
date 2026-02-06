#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, C;
        cin >> N >> C;
        --C; // 0-index
        vector<string> S(N);
        for (int i = 0; i < N; i++) cin >> S[i];

        // low[j] = largest row index (0..N-1) where S[row][j] == '#', or -1 if none
        vector<int> low(N, -1);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) if (S[i][j] == '#') low[j] = i;
        }

        // dp[i][j] : reachable at row i, col j (0-indexed)
        vector<vector<char>> dp(N, vector<char>(N, 0));

        // Starting column C is always "good" for all rows
        for (int i = 0; i < N; i++) dp[i][C] = 1;

        // Process from bottom-1 to top
        for (int i = N - 2; i >= 0; i--) {
            for (int j = 0; j < N; j++) {
                if (dp[i][j]) continue; // already true (maybe by "flood up" below)

                bool ok = false;
                for (int dj = -1; dj <= 1; dj++) {
                    int nj = j + dj;
                    if (0 <= nj && nj < N && dp[i + 1][nj]) {
                        ok = true;
                        break;
                    }
                }
                if (!ok) continue;

                if (S[i][j] == '.') {
                    dp[i][j] = 1;
                } else {
                    // S[i][j] == '#': can enter only if it's the lowest wall in this column
                    if (low[j] == i) {
                        // break it, then this column is "safe" all the way upward
                        for (int k = 0; k <= i; k++) dp[k][j] = 1;
                    }
                }
            }
        }

        string ans(N, '0');
        for (int j = 0; j < N; j++) ans[j] = (dp[0][j] ? '1' : '0');
        cout << ans << "\n";
    }
    return 0;
}

// we dostsinsif hwo so lthjsi 
/ we