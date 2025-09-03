#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int addmod(int a, int b) {
    int res = a + b;
    if (res >= MOD) res -= MOD;
    return res;
}
int submod(int a, int b) {
    int res = a - b;
    if (res < 0) res += MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q, K;
    cin >> Q >> K;

    vector<int> dp(K+1, 0);
    dp[0] = 1; // empty subset

    for (int q = 0; q < Q; q++) {
        char type;
        int x;
        cin >> type >> x;

        if (type == '+') {
            for (int s = K; s >= x; s--) {
                dp[s] = addmod(dp[s], dp[s-x]);
            }
        } else {
            for (int s = x; s <= K; s++) {
                dp[s] = submod(dp[s], dp[s-x]);
            }
        }

        cout << dp[K] << "\n";
    }
}

