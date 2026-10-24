#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

// dp[remainder][contains3][used digits][tight]
int dp[3][2][1 << 10][2];
int ndp[3][2][1 << 10][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;
    cin >> n;

    dp[0][0][0][1] = 1;

    for (int i = 0; i < (int)n.size(); ++i) {
        memset(ndp, 0, sizeof(ndp));

        int bound = n[i] - '0';

        for (int m = 0; m < 3; ++m) {
            for (int contains3 = 0; contains3 < 2; ++contains3) {
                for (int used = 0; used < (1 << 10); ++used) {
                    for (int tight = 0; tight < 2; ++tight) {
                        int ways = dp[m][contains3][used][tight];
                        if (ways == 0) continue;

                        int limit = tight ? bound : 9;

                        for (int digit = 0; digit <= limit; ++digit) {
                            int newM = (m * 10 + digit) % 3;
                            int newContains3 = contains3 || (digit == 3);
                            int newTight = tight && (digit == bound);

                            int newUsed = used;

                            // Do not count leading zeros as used digits.
                            if (used != 0 || digit != 0) {
                                newUsed |= 1 << digit;
                            }

                            int& dest =
                                ndp[newM][newContains3][newUsed][newTight];

                            dest += ways;
                            if (dest >= MOD) dest -= MOD;
                        }
                    }
                }
            }
        }

        memcpy(dp, ndp, sizeof(dp));
    }

    int res = 0;

    for (int m = 0; m < 3; ++m) {
        for (int contains3 = 0; contains3 < 2; ++contains3) {
            // Exclude mask 0: it represents the integer zero.
            for (int used = 1; used < (1 << 10); ++used) {
                int conditions = (m == 0)
                               + contains3
                               + (__builtin_popcount((unsigned)used) == 3);

                if (conditions != 1) continue;

                for (int tight = 0; tight < 2; ++tight) {
                    res += dp[m][contains3][used][tight];
                    if (res >= MOD) res -= MOD;
                }
            }
        }
    }

    cout << res << '\n';
    return 0;
} 

//werhof wsdi weri