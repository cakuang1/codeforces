#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // The 16 primes <= 58
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

    // mask[x] = set of prime divisors of x
    vector<int> mask(59, 0);
    for (int x = 1; x <= 58; x++) {
        int m = 0;
        for (int j = 0; j < (int)primes.size(); j++) {
            if (x % primes[j] == 0) m |= (1 << j);
        }
        mask[x] = m;
    }

    int FULL = 1 << 16;

    // dp[i][S] = minimum cost after fixing first i numbers, using prime-set S
    vector<vector<int>> dp(n + 1, vector<int>(FULL, INF));
    vector<vector<int>> parentMask(n + 1, vector<int>(FULL, -1));
    vector<vector<int>> chosen(n + 1, vector<int>(FULL, -1));

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int used = 0; used < FULL; used++) {
            if (dp[i - 1][used] == INF) continue;

            for (int x = 1; x <= 58; x++) {
                int pm = mask[x];
                if (used & pm) continue; // shares a prime with something already chosen

                int nxt = used | pm;
                int cost = dp[i - 1][used] + abs(a[i] - x);

                if (cost < dp[i][nxt]) {
                    dp[i][nxt] = cost;
                    parentMask[i][nxt] = used;
                    chosen[i][nxt] = x;
                }
            }
        }
    }

    int bestMask = 0;
    for (int S = 1; S < FULL; S++) {
        if (dp[n][S] < dp[n][bestMask]) bestMask = S;
    }

    vector<int> ans(n + 1);
    int curMask = bestMask;
    for (int i = n; i >= 1; i--) {
        ans[i] = chosen[i][curMask];
        curMask = parentMask[i][curMask];
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}
// werhar. sd ossof sch ses iwriht s
//w ew fwhdsf werih