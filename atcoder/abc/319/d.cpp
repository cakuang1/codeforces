
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<ll>> D(N, vector<ll>(N));

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cin >> D[i][j];
            D[j][i] = D[i][j];
        }
    }

    int FULL = (1 << N) - 1;
    vector<ll> dp(1 << N, -1);

    auto dfs = [&](auto&& self, int mask) -> ll {
        if (mask == FULL) return 0;

        ll &res = dp[mask];
        if (res != -1) return res;

        int i = 0;
        while (mask & (1 << i)) i++;

        // Option 1: Leave vertex i unmatched.
        res = self(self, mask | (1 << i));

        // Option 2: Match vertex i with an unused vertex j.
        for (int j = i + 1; j < N; j++) {
            if (mask & (1 << j)) continue;

            int newMask = mask | (1 << i) | (1 << j);

            res = max(res, D[i][j] + self(self, newMask));
        }

        return res;
    };

    cout << dfs(dfs, 0) << '\n';

    return 0;
}
