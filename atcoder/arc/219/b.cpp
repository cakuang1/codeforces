#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> P(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> P[i];
        }

        ll ans = 0;

        // Find the longest prefix:
        // P[1] = 1, P[2] = 2, ...
        for (int i = 1; i <= N; i++) {
            if (P[i] != i) break;

            ans += max(1, N - i);
            ans %= MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}


