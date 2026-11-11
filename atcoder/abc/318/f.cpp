
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    int A[3];
    cin >> N >> A[0] >> A[1] >> A[2];

    int S = A[0] * A[1] * A[2] * 8;

    auto id = [&](int r0, int r1, int r2, int mask) {
        return (((r0 * A[1] + r1) * A[2] + r2) * 8 + mask);
    };

    vector<int> dp(S, 0), ndp(S, 0);
    dp[id(0, 0, 0, 0)] = 1;

    // Valid bit triples with XOR = 0
    int bits[4][3] = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    for (int pos = 59; pos >= 0; pos--) {
        fill(ndp.begin(), ndp.end(), 0);

        int nbit = (N >> pos) & 1;

        for (int r0 = 0; r0 < A[0]; r0++) {
            for (int r1 = 0; r1 < A[1]; r1++) {
                for (int r2 = 0; r2 < A[2]; r2++) {
                    for (int mask = 0; mask < 8; mask++) {
                        int cur = dp[id(r0, r1, r2, mask)];
                        if (cur == 0) continue;

                        for (auto &b : bits) {
                            int nmask = mask;
                            bool valid = true;

                            for (int i = 0; i < 3; i++) {
                                if (!(mask & (1 << i))) {
                                    if (b[i] > nbit) {
                                        valid = false;
                                        break;
                                    }
                                    if (b[i] < nbit) {
                                        nmask |= (1 << i);
                                    }
                                }
                            }

                            if (!valid) continue;

                            int nr0 = (r0 * 2 + b[0]) % A[0];
                            int nr1 = (r1 * 2 + b[1]) % A[1];
                            int nr2 = (r2 * 2 + b[2]) % A[2];

                            int &v = ndp[id(nr0, nr1, nr2, nmask)];
                            v += cur;
                            if (v >= MOD) v -= MOD;
                        }
                    }
                }
            }
        }

        dp.swap(ndp);
    }

    

    
    ll ans = 0;

    for (int mask = 0; mask < 8; mask++) {
        ans += dp[id(0, 0, 0, mask)];
    }
    ans %= MOD;

    // Remove triples where at least one Xi = 0.
    // XOR = 0 implies if one Xi = 0, the other two are equal.
    // Therefore their common value must be divisible by lcm(Aj, Ak).

    auto lcmll = [&](ll a, ll b) {
        return a / gcd(a, b) * b;
    };

    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        int k = (i + 2) % 3;

        ll L = lcmll(A[j], A[k]);
        ans = (ans - N / L + MOD) % MOD;
    }

    // (0,0,0) was subtracted three times, but should be
    // subtracted only once.
    ans = (ans + 2) % MOD;

    cout << ans << '\n';
    return 0;
}